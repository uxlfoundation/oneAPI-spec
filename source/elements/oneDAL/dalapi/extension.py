import os
import re
import time
from typing import (Dict, Tuple, Text)
from collections import OrderedDict, namedtuple
from . import directives
from . import doxypy
from . import utils

@doxypy.model.model_object
class Property(object):
    doc: doxypy.model.Doc = None
    name: Text = None
    type: Text = None
    getter: doxypy.model.Function = None
    setter: doxypy.model.Function = None
    default: Text = None
    declaration: Text = None
    fully_qualified_name: Text = None
    parent_fully_qualified_name: Text = None

class PropertyTransformer(doxypy.TransformerPass):
    _accessor_re = re.compile(r'(get|set)_(\w+)')
    _default_re = re.compile(r'default *= *(.+)')

    def enter(self, node):
        return (isinstance(node, doxypy.model.Namespace) or
                isinstance(node, doxypy.model.Class))

    def transform(self, node):
        if isinstance(node, doxypy.model.Class):
            properties = []
            for name, info in self._get_properties_info(node):
                prop = self._build_property(name, info)
                prop.getter.doc = None
                node.functions.remove(prop.getter)
                if prop.setter:
                    node.functions.remove(prop.setter)
                properties.append(prop)
            node.properties = properties

    @classmethod
    def _build_property(cls, name, info):
        parent_fqn = f'{info.getter.parent_fully_qualified_name}::{name}'
        default = cls._find_default(info)
        decl = f'{info.getter.return_type} {name}'
        if default:
            decl += f' = {default}'
        return Property(
            doc = info.getter.doc,
            name = name,
            type = info.getter.return_type,
            getter = info.getter,
            setter = info.setter,
            default = default,
            declaration = decl,
            fully_qualified_name = parent_fqn,
            parent_fully_qualified_name = info.getter.parent_fully_qualified_name,
        )

    @classmethod
    def _find_default(cls, info):
        if info.getter.doc:
            for remark in info.getter.doc.remarks:
                match = cls._default_re.match(remark)
                if match:
                    return match.group(1)

    @classmethod
    def _get_properties_info(cls, node):
        getters = OrderedDict(cls._get_access_methods(node, 'get'))
        setters = OrderedDict(cls._get_access_methods(node, 'set'))
        PropertyInfo = namedtuple('PropertyInfo', ['getter', 'setter'])
        for name in getters.keys():
            yield name, PropertyInfo(getters[name], setters.get(name, None))

    @classmethod
    def _get_access_methods(cls, node, direction):
        for func in node.functions:
            match = cls._accessor_re.match(func.name)
            if match and match.group(1) == direction:
                yield match.group(2), func


class PathResolver(object):
    def __init__(self, app,
                 relative_project_dir,
                 relative_doxygen_dir,
                 relative_include_dir):
        self.base_dir = app.confdir
        self.project_dir = self.absjoin(self.base_dir, relative_project_dir)
        self.doxygen_dir = self.absjoin(self.project_dir, relative_doxygen_dir)
        self.include_dir = self.absjoin(self.project_dir, relative_include_dir)

    def __call__(self, relative_name):
        return self.absjoin(self.base_dir, relative_name)

    def absjoin(self, *args):
        return os.path.abspath(os.path.join(*args))


class ProjectWatcher(object):
    def __init__(self, ctx, path_resolver):
        self.ctx = ctx
        self._path_resolver = path_resolver
        self._xml_timer = utils.FileModificationTimer(
            path_resolver.doxygen_dir, '*.xml')
        self._hpp_timer = utils.FileModificationTimer(
            path_resolver.include_dir, '*.hpp')
        self._doxygen = utils.ProcessHandle(
            'doxygen', path_resolver.project_dir)

    def link_docname(self, docname):
        full_path = self._path_resolver(f'{docname}.rst')
        self._linked_docnames[docname] = (full_path, time.time())

    def get_outdated_docnames(self, modified_docnames):
        # We do not need to check the modified documents,
        # they should be updated by Sphinx in any way
        for docname in modified_docnames:
            if docname in self._linked_docnames:
                del self._linked_docnames[docname]

        xml_mtime = self._xml_timer()
        hpp_mtime = self._hpp_timer()
        if xml_mtime < hpp_mtime:
            self.ctx.log('Run Doxygen')
            self._doxygen.run()

        outdated_docnames = []
        for docname, info in self._linked_docnames.items():
            _, link_time = info
            if (self.ctx.always_rebuild or
                link_time < xml_mtime or link_time < hpp_mtime):
                outdated_docnames.append(docname)

        if self.ctx.debug:
            for docname in outdated_docnames:
                self.ctx.log('OUTDATED', docname)

        return outdated_docnames


    def _update_linked_docnames(self):
        relevant_linked_docnames = {}
        for docname, info in self._linked_docnames.items():
            docfilename = info[0]
            if os.path.exists(docfilename):
                relevant_linked_docnames[docname] = info
        self._linked_docnames = relevant_linked_docnames

    @property
    def _linked_docnames(self) -> Dict[Text, Tuple[Text, float]]:
        if not hasattr(self.ctx.app.env, 'dalapi_linked_docnames'):
            self.ctx.app.env.dalapi_linked_docnames = {}
        return self.ctx.app.env.dalapi_linked_docnames

    @_linked_docnames.setter
    def _linked_docnames(self, value):
        self.ctx.app.env.dalapi_linked_docnames = value


class Context(object):
    def __init__(self, app):
        self.app = app
        self._index = None
        self._watcher = None
        self._doxygen = None
        self._listing = None
        self._path_resolver = None
        self._read_env()

    def configure(self, project_dir):
        self._path_resolver = PathResolver(
            self.app,
            project_dir,
            'doxygen/xml',
            'include/onedal'
        )

    @property
    def current_docname(self):
        return self.app.env.docname

    @property
    def index(self) -> doxypy.Index:
        if self._index is None:
            self._index = doxypy.index(self._paths.doxygen_dir, [
                PropertyTransformer(),
            ])
        return self._index

    @property
    def watcher(self) -> ProjectWatcher:
        if self._watcher is None:
            self._watcher = ProjectWatcher(self, self._paths)
        return self._watcher

    @property
    def listing(self) -> doxypy.ListingReader:
        if self._listing is None:
            self._listing = doxypy.ListingReader()
        return self._listing

    def log(self, *args):
        if self.debug:
            print('[dalapi]:', *args)

    @property
    def _paths(self):
        if not self._path_resolver:
            raise Exception('Context is not configured')
        return self._path_resolver

    def _read_env(self):
        def get_env_flag(env_var):
            value = os.environ.get(env_var, '0')
            return value.lower() in ['1', 'yes', 'y']
        self.debug = get_env_flag('DALAPI_DEBUG')
        self.always_rebuild = get_env_flag('DALAPI_ALWAYS_REBUILD')


class EventHandler(object):
    def __init__(self, ctx: Context):
        self.ctx = ctx

    def env_get_outdated(self, app, env, added, changed, removed):
        return self.ctx.watcher.get_outdated_docnames(added | changed | removed)

    def get_config_values(self, app):
        self.ctx.configure(app.config.onedal_project_dir)


def setup(app):
    ctx = Context(app)

    app.add_directive('onedal_class', directives.ClassDirective(ctx))
    app.add_directive('onedal_func', directives.FunctionDirective(ctx))
    app.add_directive('onedal_code', directives.ListingDirective(ctx))

    app.add_config_value('onedal_project_dir', '.', 'env')

    handler = EventHandler(ctx)
    app.connect("builder-inited", handler.get_config_values)
    app.connect('env-get-outdated', handler.env_get_outdated)
