from dataclasses import dataclass, field
from multimethod import multimethod
from typing import (
    Any, Union, List, Dict
)

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

    def add_parameter(self):
        parameter_def = Parameter()
        self.parameters.append(parameter_def)
        return parameter_def

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
    methods: List[Method] = field(default_factory=list)
    template_parameters: List[Parameter] = field(default_factory=list)

    def add_method(self):
        method_def = Method()
        self.methods.append(method_def)
        return method_def


class Index(object):
    def __init__(self):
        self._classes = {}
        self._functions = {}

    def find_class(self, query) -> Class:
        return self._classes[query]

    def add_class(self, fully_qualified_name):
        class_def = Class()
        self._classes[fully_qualified_name] = class_def
        return class_def
