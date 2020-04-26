from typing import (List, Text)

class RstBuilder(object):
    def __init__(self):
        self._rst_list = []

    def add_class(self, declaration: str, namespace: str=None, level=0):
        if namespace:
            self(f'.. cpp:namespace:: {namespace}', level)
            self()
        self(f'.. cpp:class:: {declaration}', level)
        self()

    def add_function(self, declaration: str, namespace: str = None, level=0):
        if namespace:
            self(f'.. cpp:namespace:: {namespace}', level)
            self()
        self(f'.. cpp:function:: {declaration}', level)
        self()

    def add_property(self, definition: str, level=0):
        self(f'.. cpp:member:: {definition}', level)
        self()

    def add_doc(self, description: str, level=0):
        if description:
            self(self._format_description(description), level)
            self()

    def add_param(self, name: str, description: str, level=0):
        self._add_param('param', name, description, level)

    def add_tparam(self, name: str, description: str, level=0):
        self._add_param('tparam', name, description, level)

    def add_code_block(self, listing: List[Text], level=0):
        self(f'.. code-block:: cpp', level)
        self()
        for line in listing:
            self(line, level + 1)
        self()

    def __call__(self, string: str = '', level:int = 0):
        self._rst_list.append(' ' * level * 3 + string)

    def build(self):
        return self._rst_list

    def _add_param(self, tag: str, name: str, description: str, level=0):
        if description:
            formatted = self._format_description(description)
            self(f':{tag} {name}: {formatted}', level)

    def _format_description(self, description):
        if not description.endswith('.'):
            return description + '.'
        return description
