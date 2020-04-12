
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
