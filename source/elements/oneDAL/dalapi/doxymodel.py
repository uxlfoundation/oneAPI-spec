from typing import (
    Any, Union, List, Dict
)

class Doxy(object):
    pass

class Run(Doxy):
    def __init__(self, content, kind):
        self.content = content
        self.kind = kind


class Description(Doxy):
    def __init__(self):
        self.runs = []

    def add_text(self, text):
        self.runs.append(Run(text, 'text'))
        return self.runs[-1]

    def add_math(self, math):
        self.runs.append(Run(math, 'math'))
        return self.runs[-1]

    def add_code(self, code):
        self.runs.append(Run(code, 'code'))
        return self.runs[-1]


class Doc(Doxy):
    def __init__(self):
        self.description = None
        self.invariants = []
        self.postconditions = []
        self.preconditions = []
        self.remarks = []

    def add_description(self):
        self.description = Description()
        return self.description

    def add_remark(self, text):
        self.remarks.append(text)
        return self.remarks[-1]

    def add_invariant(self, text):
        self.invariants.append(text)
        return self.invariants[-1]

    def add_precondition(self, text):
        self.preconditions.append(text)
        return self.preconditions[-1]

    def add_postcondition(self, text):
        self.postconditions.append(text)
        return self.postconditions[-1]


class Location(Doxy):
    def __init__(self):
        self.bodyend = -1
        self.bodystart = -1
        self.filename = None


class Parameter(Doxy):
    def __init__(self):
        self.default = None
        self.name = None
        self.typename = None


class Method(Doxy):
    def __init__(self):
        self.definition = None
        self.doc = None
        self.name = None
        self.parameters = []
        self.return_type = None

    def add_parameter(self):
        self.parameters.append(Parameter())
        return self.parameters[-1]

    def add_doc(self):
        self.doc = Doc()
        return self.doc


class Property(Doxy):
    def __init__(self):
        self.default = None
        self.definition = None
        self.doc = None
        self.getter = None
        self.name = None
        self.setter = None
        self.typename = None

    def add_setter(self):
        self.setter = Method()
        return self.setter

    def add_getter(self):
        self.getter = Method()
        return self.getter


class Function(Doxy):
    def __init__(self):
        self.definition = None
        self.doc = None
        self.fully_qualified_name = None
        self.name = None
        self.namespace = None
        self.parameters = []
        self.return_type = None

    def add_parameter(self):
        self.parameters.append(Parameter)
        return self.parameters[-1]

    def add_doc(self):
        self.doc = Doc()
        return self.doc


class Class(Doxy):
    def __init__(self):
        self.fully_qualified_name = None
        self.kind = None
        self.location = None
        self.methods = []
        self.name = None
        self.namespace = None
        self.properties = []
        self.template_parameters = []
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

    def add_function(self, fully_qualified_name):
        func_def = Function()
        func_def.fully_qualified_name = fully_qualified_name
        self._functions[fully_qualified_name] = func_def
        return func_def

    def to_dict(self):
        return {
            'classes': self._to_dict(self._classes),
            'functions': self._to_dict(self._functions),
        }

    def to_json(self):
        import json
        return json.dumps(self.to_dict(), indent=2, sort_keys=True)

    def to_yaml(self):
        import yaml
        return yaml.dump(self.to_dict(), sort_keys=True)

    def _to_dict(self, obj):
        if isinstance(obj, list):
            return [self._to_dict(x) for x in obj]
        elif isinstance(obj, dict):
            return {k: self._to_dict(x) for k, x in obj.items()}
        elif isinstance(obj, Doxy):
            obj_dict = {}
            for attr in self._get_public_fields(obj):
                attr_value = getattr(obj, attr)
                obj_dict[attr] = self._to_dict(attr_value)
            return obj_dict
        return obj

    def _get_public_fields(self, obj):
        for attr in dir(obj):
            is_public = not attr.startswith('_')
            is_callable = callable(getattr(obj, attr))
            if is_public and not is_callable:
                yield attr
