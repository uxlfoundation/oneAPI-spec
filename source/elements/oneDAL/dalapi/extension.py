import os
import time
from typing import (Dict, Tuple, Text)
from . import directives
from . import doxymodel
from . import utils

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

    def get_outdated_docnames(self):
        self._update_linked_docnames()
        xml_mtime = self._xml_timer()
        hpp_mtime = self._hpp_timer()
        if xml_mtime < hpp_mtime:
            self.ctx.log('Run Doxygen')
            self._doxygen.run()
            xml_mtime = self._xml_timer()

        outdated_docnames = []
        for docname, info in self._linked_docnames.items():
            filename, mtime = info
            if mtime < xml_mtime:
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
    def __init__(self, app,
                 relative_project_dir,
                 relative_doxygen_dir,
                 relative_include_dir):
        self.app = app
        self._index = None
        self._watcher = None
        self._doxygen = None
        self._path_resolver = PathResolver(
            app,
            relative_project_dir,
            relative_doxygen_dir,
            relative_include_dir
        )

    @property
    def current_docname(self):
        return self.app.env.docname

    @property
    def index(self) -> doxymodel.Index:
        if self._index is None:
            from .doxyparser import parse
            self._index = parse(self._path_resolver.doxygen_dir)
        return self._index

    @property
    def watcher(self) -> ProjectWatcher:
        if self._watcher is None:
            self._watcher = ProjectWatcher(
                self, self._path_resolver)
        return self._watcher

    @property
    def debug(self):
        is_debug = os.environ.get('DALAPI_DEBUG', '0')
        return is_debug.lower() in ['1', 'yes', 'y']

    def log(self, *args):
        if self.debug:
            print('[dalapi]:', *args)


class EventHandler(object):
    def __init__(self, ctx: Context):
        self.ctx = ctx

    def env_get_outdated(self, app, env, added, changed, removed):
        x = self.ctx.watcher.get_outdated_docnames()
        return list(set(x).difference(removed))


def setup(app):
    ctx = Context(app,
        relative_project_dir='elements/oneDAL',
        relative_doxygen_dir='doxygen/xml',
        relative_include_dir='include/onedal',
    )
    app.add_directive('onedal_class', directives.ClassDirective(ctx))

    handler = EventHandler(ctx)
    app.connect('env-get-outdated', handler.env_get_outdated)
