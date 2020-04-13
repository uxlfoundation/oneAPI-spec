
class RstBuilder(object):
    def __init__(self):
        self._rst_list = []

    def add_class(self, namespace: str, class_declaration: str, level=0):
        self(f'.. cpp:namespace:: {namespace}', level)
        self()
        self(f'.. cpp:class:: {class_declaration}', level)
        self()

    def add_function(self, definition: str, level=0):
        self(f'.. cpp:function:: {definition}', level)
        self()

    def add_property(self, definition: str, level=0):
        self(f'.. cpp:member:: {definition}', level)
        self()

    def add_doc_description(self, description: str, level=0):
        if len(description) > 0:
            self(self._format_description(description), level)
            self()

    def __call__(self, string: str = '', level:int = 0):
        self._rst_list.append(' ' * level * 3 + string)

    def build(self):
        return self._rst_list

    def _format_description(self, description):
        if not description.endswith('.'):
            return description + '.'
        return description
