from os import path
from typing import (
    Any, Union, List
)
from docutils import nodes
from docutils.parsers import rst
from multimethod import multimethod

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
        return path.abspath(path.join(*args))


class ProjectWatcher(object):
    def __init__(self, app, path_resolver):
        self._app = app
        self._path_resolver = path_resolver
        self._xml_timer = utils.FileModificationTimer(
            path_resolver.doxygen_dir, '*.xml')
        self._hpp_timer = utils.FileModificationTimer(
            path_resolver.include_dir, '*.hpp')

    @property
    def linked_docnames(self):
        if not hasattr(self._app.env, 'dalapi_linked_docnames'):
            self._app.env.dalapi_linked_docnames = set()
        return self._app.env.dalapi_linked_docnames

    @linked_docnames.setter
    def linked_docnames(self, value):
        self._app.env.dalapi_linked_docnames = value

    def link_docname(self, docname):
        self.linked_docnames.add(docname)

    def is_doxygen_outdated(self):
        return self._xml_timer < self._hpp_timer

    def get_outdated_docnames(self):
        linked_doc_mtime = self._get_linked_docs_mtime()
        # print(self.linked_docnames)
        # print(f'linked_doc_mtime = {linked_doc_mtime}')
        # print(f'self._xml_timer() = {self._xml_timer()}')
        # print(f'self._hpp_timer() = {self._hpp_timer()}')
        if (linked_doc_mtime < self._xml_timer() or
            linked_doc_mtime < self._hpp_timer()):
            return self.linked_docnames
        return []

    def _get_linked_docs_mtime(self):
        max_mod_time = 0.0
        relevant_docnames = []
        for docname in self.linked_docnames:
            try:
                filename = self._path_resolver(f'{docname}.rst')
                max_mod_time = max(max_mod_time, path.getmtime(filename))
                relevant_docnames.append(docname)
            except OSError:
                pass
        self.linked_docnames = set(relevant_docnames)
        return max_mod_time


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
                self.app,
                self._path_resolver
            )
        return self._watcher

    @property
    def doxygen(self) -> utils.ProcessHandle:
        if self._doxygen is None:
            self._doxygen = utils.ProcessHandle(
                'doxygen',
                self._path_resolver.project_dir
            )
        return self._doxygen


class BaseDirective(rst.Directive):
    def __init__(self, ctx: Context, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.ctx = ctx
        self.index = ctx.index


def directive(cls):
    class DirectiveFactory(cls):
        def __init__(self, ctx):
            self._ctx = ctx
        def __call__(self, *args, **kwargs):
            return cls(self._ctx, *args, **kwargs)
    return DirectiveFactory


class RstBuilder(object):
    def __init__(self):
        self._rst_list = []

    def add_class(self, namespace: str, class_declaration: str):
        self(f'.. cpp:namespace:: {namespace}')
        self()
        self(f'.. cpp:class:: {class_declaration}')

    def __call__(self, string: str = ''):
        self._rst_list.append(string)

    def build(self):
        return self._rst_list


class Macro(BaseDirective):
    def rst(self, x: RstBuilder) -> Union[str, List[str]]:
        raise NotImplementedError()

    def run(self):
        from docutils.statemachine import ViewList
        content = ViewList()
        for i, line in enumerate(self._get_rst()):
            content.append(line, '', i + 1)
        node = nodes.section()
        node.document = self.state.document
        self.state.nested_parse(content, 0, node)
        return node.children

    def _get_rst(self):
        x = RstBuilder()
        self.rst(x)
        return x.build()


@directive
class ClassDirective(Macro):
    required_arguments = 1
    optional_arguments = 0
    has_content = False

    def rst(self, x):
        self.ctx.watcher.link_docname(self.ctx.current_docname)
        class_def = self.index.find_class(self.arguments[0])
        x.add_class(class_def.namespace, class_def.name)


class EventHandler(object):
    def __init__(self, ctx: Context):
        self.ctx = ctx

    def env_get_outdated(self, app, env, added, changed, removed):
        x = self.ctx.watcher.get_outdated_docnames()
        return list(set(x).difference(removed))

    def env_before_read_docs(self, app, env, docnames):
        if (len(docnames) > 0 and self.ctx.watcher.is_doxygen_outdated()):
            self.ctx.doxygen.run()


def setup(app):
    ctx = Context(app,
        relative_project_dir='elements/oneDAL',
        relative_doxygen_dir='doxygen/xml',
        relative_include_dir='include/onedal',
    )
    app.add_directive('onedal_class', ClassDirective(ctx))

    handler = EventHandler(ctx)
    app.connect('env-get-outdated', handler.env_get_outdated)
    app.connect('env-before-read-docs', handler.env_before_read_docs)
