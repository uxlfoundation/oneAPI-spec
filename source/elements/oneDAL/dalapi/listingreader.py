import os
import re
from .doxymodel import Class

class FileListingReader(object):
    def __init__(self, filename):
        self._content = open(filename, 'r').readlines()
        self._class_listings = {}

    def get_listing(self, class_def: Class):
        name = class_def.name
        if name not in self._class_listings:
            self._class_listings[name] = self._get_class_listing(class_def)
        listing = self._class_listings[name]
        return self._group_accessors(listing)

    def _get_class_listing(self, class_def: Class):
        start = self._get_class_definition_start(class_def.location.bodystart)
        end = class_def.location.bodyend + 1
        for i in range(start, end):
            line = self._content[i]
            if '///' not in line:
                yield line.rstrip()

    def _get_class_definition_start(self, bodystart):
        for i in range(bodystart - 1, 0, -1):
            line = self._content[i].strip()
            if not line or '///' in line:
                return i + 1
        return 0

    _getter_re = re.compile(r' get_\w+ *\(')
    _setter_re = re.compile(r' set_\w+ *\(')
    def _group_accessors(self, listing):
        getter_re = FileListingReader._getter_re
        setter_re = FileListingReader._setter_re
        getter_match = False
        setter_match = False
        line_stack = []
        for line in listing:
            if line:
                local_getter_match = getter_re.search(line)
                local_setter_match = setter_re.search(line)
                if (getter_match and local_getter_match or
                    setter_match and local_setter_match):
                    if line_stack[-1] == '':
                        line_stack.pop()
                getter_match = local_getter_match
                setter_match = local_setter_match
            line_stack.append(line)
        return line_stack


class ListingReader(object):
    def __init__(self, base_dir):
        self._base_dir = base_dir
        self._file_readers = {}

    def get_class_listing(self, class_def: Class):
        filename = self._get_filename(class_def.location.filename)
        if filename not in self._file_readers:
            self._file_readers[filename] = FileListingReader(filename)
        return self._file_readers[filename].get_listing(class_def)

    def _get_filename(self, relative_filename):
        return os.path.abspath(os.path.join(self._base_dir, relative_filename))
