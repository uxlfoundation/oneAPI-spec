from typing import (List, Text)
from docutils.statemachine import ViewList

class RstBuilder(object):
    def __init__(self, placeholder: ViewList, filename: Text, lineno: int):
        self._rst_list = placeholder
        self._filename = filename
        self._lineno = lineno

    def add_class(self, declaration: str, namespace: str = None, level=0):
        assert declaration
        if namespace:
            self(f'.. cpp:namespace:: {namespace}', level)
            self.add_blank_like()
        self(f'.. cpp:class:: {declaration}', level)
        self.add_blank_like()

    def add_function(self, declaration: str, namespace: str = None, level=0):
        assert declaration
        if namespace:
            self(f'.. cpp:namespace:: {namespace}', level)
            self.add_blank_like()
        self(f'.. cpp:function:: {declaration}', level)
        self.add_blank_like()

    def add_param(self, tag: str, name: str, doc_text: str, level=0):
        assert tag in ['param', 'tparam']
        assert name
        assert doc_text
        formatted = self._format_text(doc_text)
        self(f':{tag} {name}: {formatted}', level)

    def add_member(self, declaration: str, level=0):
        assert declaration
        self(f'.. cpp:member:: {declaration}', level)
        self.add_blank_like()

    def add_doc(self, doc_text: str, level=0):
        assert doc_text
        self(self._format_text(doc_text), level)
        self.add_blank_like()

    def add_code_block(self, listing: List[Text], level=0):
        assert listing is not None
        self(f'.. code-block:: cpp', level)
        self.add_blank_like()
        for line in listing:
            self(line, level + 1)
        self.add_blank_like()

    def add_blank_like(self):
        self.add()

    def add(self, string: str = '', level: int = 0):
        self._rst_list.append(' ' * level * 3 + string, self._filename, self._lineno)

    # TODO: Remove
    def __call__(self, string: str = '', level:int = 0):
        self._rst_list.append(' ' * level * 3 + string, self._filename, self._lineno)

    def _format_text(self, text):
        text = text.strip()
        if not (text.endswith('.') or text.endswith('|')):
            text += '.'
        return text
