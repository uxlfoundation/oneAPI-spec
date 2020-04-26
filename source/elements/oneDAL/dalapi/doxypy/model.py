from typing import (
    Any,
    Dict,
    List,
    Text,
    Union,
)

from collections import namedtuple

def _get_public_attrs(obj):
    for attr in dir(obj):
        is_public = not attr.startswith('_')
        is_callable = callable(getattr(obj, attr))
        if is_public and not is_callable:
            yield attr

def _iter_model_object(obj, is_root=True):
    if isinstance(obj, list):
        for v in obj:
            yield from _iter_model_object(v, is_root=False)
    elif isinstance(obj, dict):
        for k, v in obj.items():
            yield from _iter_model_object(v, is_root=False)
    elif hasattr(obj, '__fields__'):
        if is_root:
            for field in obj.__fields__:
                yield from _iter_model_object(getattr(obj, field),
                                              is_root=False)
        else:
            yield obj


class _ModelProperty(object):
    def __init__(self, var_name):
        self._var_name = var_name

    def __get__(self, instance, owner):
        if instance:
            return getattr(instance, self._var_name)
        return self

    def __set__(self, instance, value):
        if instance:
            return setattr(instance, self._var_name, value)
        return self


def _model_object(cls):
    fields = tuple(_get_public_attrs(cls))
    defaults = tuple(getattr(cls, f) for f in fields)

    for field, default in zip(fields, defaults):
        setattr(cls, field, _ModelProperty(f'_{field}'))

    # __init__
    s =  f'def __init__(self, {", ".join(fields)}): \n'
    for field in fields:
        s += f'    self._{field} = {field}\n'

    # __repr__
    repr_str = ', '.join(f'{f}={{self._{f}}}' for f in fields)
    s += f'def __repr__(self):\n'
    s += f'    return f"{{type(self).__name__}}({repr_str})"'

    namespace = {'__name__': f'__model_{cls.__name__}'}
    exec(s, namespace)

    cls.__fields__ = fields
    cls.__init__ = namespace['__init__']
    cls.__init__.__defaults__ = defaults
    cls.__repr__ = namespace['__repr__']
    cls.iter = _iter_model_object
    return cls


@_model_object
class Run(object):
    content: Text = None
    kind: Text = 'unknown'

@_model_object
class Description(object):
    runs: List[Run] = []

@_model_object
class Doc(object):
    invariants: List[Text] = []
    postconditions: List[Text] = []
    preconditions: List[Text] = []
    remarks: List[Text] = []
    params: List[Text] = []
    template_params: List[Text] = []
    description: Description = None

@_model_object
class Location(object):
    bodyend: int = -1
    bodystart: int = -1
    filename: Text = None

@_model_object
class Parameter(object):
    name: Text = None
    type: Text = None
    description: Description = None
    default: Text = None

@_model_object
class Function(object):
    doc: Doc = None
    name: Text = None
    argstring: Text = None
    parameters: List[Parameter] = []
    declaration: Text = None
    return_type: Text = None
    template_parameters: List[Parameter] = []
    template_declaration: Text = None
    fully_qualified_name: Text = None
    parent_fully_qualified_name: Text = None

@_model_object
class Class(object):
    doc: Doc = None
    kind: Text = None
    name: Text = None
    declaration: Text = None
    location: Location = None
    functions: List[Function] = []
    template_parameters: List[Parameter] = []
    template_declaration: Text = None
    fully_qualified_name: Text = None
    parent_fully_qualified_name: Text = None

@_model_object
class Namespace(object):
    doc: Doc = None
    name: Text = None
    classes: List[Text] = []
    functions: List[Function] = []
    fully_qualified_name: Text = None
    parent_fully_qualified_name: Text = None


class Visitor(object):
    def enter(self, node): ...
    def leave(self, node): ...

def visit(node, visitor: Visitor):
    if visitor.enter(node):
        for child in node.iter():
            visit(child, visitor)
        visitor.leave(node)
