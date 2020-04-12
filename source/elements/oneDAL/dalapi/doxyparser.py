from os.path import join
from lxml import etree
from .doxymodel import Index
from .utils import FileModificationTimer

def parse(doxygen_xml_directory: str) -> Index:
    all = _combine_to_xml_all(doxygen_xml_directory)
    return _parse_xml(all)

def _combine_to_xml_all(doxygen_xml_directory: str):
    xml_index_filename = join(doxygen_xml_directory, 'index.xml')
    xml_combine_filename = join(doxygen_xml_directory, 'combine.xslt')
    index = etree.parse(xml_index_filename)
    combine = etree.parse(xml_combine_filename)
    transform = etree.XSLT(combine)
    return transform(index)

def _parse_xml(all) -> Index:
    index = Index()
    _parse_all_classes(all, index)
    return index

def _parse_all_classes(root, index):
    for compounddef in root.iterfind('.//compounddef[@kind="class"]'):
        _parse_class(compounddef, index)

def _parse_class(compounddef, index):
    compoundname = compounddef.findtext('compoundname')
    namespace, name = _split_compound_name(compoundname)
    class_def = index.add_class(compoundname)
    class_def.name = name
    class_def.kind = compounddef.get('kind')
    class_def.namespace = namespace
    _parse_class_methods(compounddef, class_def)

def _parse_class_methods(compounddef, class_def):
    for memberdef in compounddef.iterfind('memberdef[@kind="function"]'):
        method_def = class_def.add_method()
        method_def.name = memberdef.findtext('name')
        _parse_method_parameters(memberdef, method_def)

def _parse_method_parameters(memberdef, method_def):
    pass


def _split_compound_name(compoundname):
    try:
        namespace, name = compoundname.rsplit('::', 1)
    except ValueError:
        namespace, name = '', compoundname
    return namespace, name
