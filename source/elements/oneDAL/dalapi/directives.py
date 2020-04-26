from docutils import nodes
from docutils.parsers.rst import Directive
from docutils.statemachine import ViewList
from .generator import RstBuilder

def directive(cls):
    class DirectiveFactory(cls):
        def __init__(self, ctx):
            self._ctx = ctx
        def __call__(self, *args, **kwargs):
            return cls(self._ctx, *args, **kwargs)
    return DirectiveFactory


class BaseDirective(Directive):
    def __init__(self, ctx, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.ctx = ctx


class MacroDirective(BaseDirective):
    def init(self): ...
    def rst(self, x: RstBuilder): ...

    def run(self):
        self.init()
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


class DoxyDirective(MacroDirective):
    def init(self):
        self.ctx.watcher.link_docname(self.ctx.current_docname)

    def format_description(self, desc_def):
        rst = ''
        for run in desc_def.runs:
            if run.kind == 'text':
                rst += run.content
            elif run.kind == 'math':
                rst += f':math:`{run.content}`'
            elif run.kind == 'code':
                rst += f':cpp:expr:`{run.content}`'
        return rst.strip()


@directive
class ClassDirective(DoxyDirective):
    required_arguments = 1
    optional_arguments = 0
    has_content = False

    def rst(self, x: RstBuilder):
        class_def = self.ctx.index.find_class(self.arguments[0])
        self._rst_listing(class_def, x)
        sphinx_class_decl = (f'{class_def.template_declaration} {class_def.name}'
                             if class_def.template_declaration else class_def.name)
        x.add_class(sphinx_class_decl, class_def.namespace)
        self._rst_methods(class_def, x)
        self._rst_properties(class_def, x)

    def _rst_methods(self, class_def, x: RstBuilder):
        for method_def in class_def.methods:
            x.add_function(method_def.declaration, level=1)

    def _rst_properties(self, class_def, x: RstBuilder):
        if len(class_def.properties) > 0:
            x('**Properties**', level=1)
            x()
        for property_def in class_def.properties:
            self._rst_property(property_def, x)

    def _rst_property(self, property_def, x: RstBuilder):
        x.add_property(property_def.declaration, level=1)
        if property_def.doc and property_def.doc.description:
            desc = self.format_description(property_def.doc.description)
            x.add_doc(desc, level=2)
        if property_def.getter or property_def.setter:
            x('Getter & Setter', level=2)
            if property_def.getter:
                x(f'| ``{property_def.getter.declaration}``', level=3)
            if property_def.setter:
                x(f'| ``{property_def.setter.declaration}``', level=3)
            x()
        if property_def.doc:
            invariants = property_def.doc.invariants
            if invariants and len(invariants) > 0:
                x('Invariants', level=2)
                for invariant in invariants:
                    x(f'| :cpp:expr:`{invariant}`', level=3)
                x()

    def _rst_listing(self, class_def, x: RstBuilder):
        listing = self.ctx.listing.get_class_listing(class_def)
        x.add_code_block(listing)


@directive
class FunctionDirective(DoxyDirective):
    required_arguments = 1
    optional_arguments = 0
    has_content = False

    def rst(self, x: RstBuilder):
        func_def = self.ctx.index.find_function(self.arguments[0])
        x.add_function(func_def.declaration, func_def.namespace)
        if func_def.doc and func_def.doc.description:
            desc = self.format_description(func_def.doc.description)
            x.add_doc(desc, level=1)
        for tparam_def in func_def.template_parameters:
            if tparam_def.description:
                desc = self.format_description(tparam_def.description)
                x.add_tparam(tparam_def.name, desc, level=1)
        for param_def in func_def.parameters:
            if param_def.description:
                desc = self.format_description(param_def.description)
                x.add_param(param_def.name, desc, level=1)
        x()


@directive
class ListingDirective(DoxyDirective):
    required_arguments = 1
    optional_arguments = 0
    has_content = False

    def rst(self, x: RstBuilder):
        pass
