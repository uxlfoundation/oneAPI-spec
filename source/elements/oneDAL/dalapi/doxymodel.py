from dataclasses import dataclass, field
from typing import (
    Any, Union, List, Dict
)

@dataclass
class Doc(object):
    description: str = ''
    invariants: List[str] = field(default_factory=list)
    remarks: List[str] = field(default_factory=list)

    def add_remark(self, text):
        self.remarks.append(text)

    def add_invariant(self, text):
        self.invariants.append(text)

@dataclass
class Location(object):
    filename: str = ''
    bodystart: int = -1
    bodyend: int = -1

@dataclass
class Parameter(object):
    name: str = ''
    typename: str = ''
    default: str = ''

@dataclass
class Method(object):
    name: str = ''
    definition: str = ''
    return_type: str = ''
    parameters: List[Parameter] = field(default_factory=list)
    doc: Doc = None

    def add_parameter(self):
        parameter_def = Parameter()
        self.parameters.append(parameter_def)
        return parameter_def

    def add_doc(self):
        self.doc = Doc()
        return self.doc


@dataclass
class Property(object):
    name: str = ''
    typename: str = ''
    definition: str = ''
    default: str = ''
    getter: Method = None
    setter: Method = None
    doc: Doc = None

    def add_setter(self):
        self.setter = Method()
        return self.setter

    def add_getter(self):
        self.getter = Method()
        return self.getter


@dataclass
class Function(object):
    name: str = ''
    namespace: str = ''
    definition: str = ''
    return_type: str = ''
    parameters: List[Parameter] = field(default_factory=list)

@dataclass
class Class(object):
    name: str = ''
    kind: str = ''
    namespace: str = ''
    fully_qualified_name: str = ''
    methods: List[Method] = field(default_factory=list)
    properties: List[Property] = field(default_factory=list)
    template_parameters: List[Parameter] = field(default_factory=list)
    location: Location = None

    def __post_init__(self):
        self._properties_map = {}

    def add_method(self):
        method_def = Method()
        self.methods.append(method_def)
        return method_def

    def add_property(self, name):
        if name in self._properties_map:
            return self._properties_map[name]
        property_def = Property()
        property_def.name = name
        self.properties.append(property_def)
        self._properties_map[name] = property_def
        return property_def

    def add_location(self):
        self.location = Location()
        return self.location



class Index(object):
    def __init__(self):
        self._classes = {}
        self._functions = {}

    def find_class(self, query) -> Class:
        return self._classes['onedal::' + query]

    def add_class(self, fully_qualified_name):
        class_def = Class()
        class_def.fully_qualified_name = fully_qualified_name
        self._classes[fully_qualified_name] = class_def
        return class_def

    def __repr__(self):
        return f'{{ {self._classes} }}'
