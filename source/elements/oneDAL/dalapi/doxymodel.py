from typing import (
    Any, Union, List, Dict
)

class Doc(object):
    def __init__(self):
        self.description = ''
        self.invariants = []
        self.remarks = []

    def add_remark(self, text):
        self.remarks.append(text)

    def add_invariant(self, text):
        self.invariants.append(text)


class Location(object):
    def __init__(self):
        self.filename = ''
        self.bodystart = -1
        self.bodyend = -1


class Parameter(object):
    def __init__(self):
        self.name = ''
        self.typename = ''
        self.default = ''


class Method(object):
    def __init__(self):
        self.name = ''
        self.definition = ''
        self.return_type = ''
        self.parameters = []
        self.doc = None

    def add_parameter(self):
        parameter_def = Parameter()
        self.parameters.append(parameter_def)
        return parameter_def

    def add_doc(self):
        self.doc = Doc()
        return self.doc


class Property(object):
    def __init__(self):
        self.name = ''
        self.typename = ''
        self.definition = ''
        self.default = ''
        self.getter = None
        self.setter = None
        self.doc = None

    def add_setter(self):
        self.setter = Method()
        return self.setter

    def add_getter(self):
        self.getter = Method()
        return self.getter


class Function(object):
    def __init__(self):
        self.name = ''
        self.namespace = ''
        self.definition = ''
        self.return_type = ''
        self.parameters = []


class Class(object):
    def __init__(self):
        self.name = ''
        self.kind = ''
        self.namespace = ''
        self.fully_qualified_name = ''
        self.methods = []
        self.properties = []
        self.template_parameters = []
        self.location = None
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
