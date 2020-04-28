from typing import (List, Text)

class RstBuilder(object):
    def __init__(self):
        self._rst_list = []

    def add_class(self, declaration: str, namespace: str = None, level=0):
        assert declaration
        if namespace:
            self(f'.. cpp:namespace:: {namespace}', level)
            self()
        self(f'.. cpp:class:: {declaration}', level)
        self()

    def add_function(self, declaration: str, namespace: str = None, level=0):
        assert declaration
        if namespace:
            self(f'.. cpp:namespace:: {namespace}', level)
            self()
        self(f'.. cpp:function:: {declaration}', level)
        self()

    def add_member(self, declaration: str, level=0):
        assert declaration
        self(f'.. cpp:member:: {declaration}', level)
        self()

    def add_doc(self, doc_text: str, level=0):
        assert doc_text
        self(self._format_text(doc_text), level)
        self()

    def add_param(self, name: str, doc_text: str, level=0):
        self._add_param('param', name, doc_text, level)

    def add_tparam(self, name: str, doc_text: str, level=0):
        self._add_param('tparam', name, doc_text, level)

    def add_code_block(self, listing: List[Text], level=0):
        assert listing is not None
        self(f'.. code-block:: cpp', level)
        self()
        for line in listing:
            self(line, level + 1)
        self()

    def __call__(self, string: str = '', level:int = 0):
        self._rst_list.append(' ' * level * 3 + string)

    def build(self):
        return self._rst_list

    def _add_param(self, tag: str, name: str, doc_text: str, level=0):
        assert name
        assert doc_text
        formatted = self._format_text(doc_text)
        self(f':{tag} {name}: {formatted}', level)

    def _format_text(self, text):
        text = text.strip()
        if not text.endswith('.'):
            text += '.'
        return text
