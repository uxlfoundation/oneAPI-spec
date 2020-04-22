import re
from os.path import join
from lxml import etree
from collections import OrderedDict
from .doxymodel import Index
from .utils import FileModificationTimer

def parse(doxygen_xml_directory: str, **kwargs) -> Index:
    all = _combine_to_xml_all(doxygen_xml_directory)
    return _parse_xml(all, **kwargs)

def _combine_to_xml_all(doxygen_xml_directory: str):
    xml_index_filename = join(doxygen_xml_directory, 'index.xml')
    xml_combine_filename = join(doxygen_xml_directory, 'combine.xslt')
    index = etree.parse(xml_index_filename)
    combine = etree.parse(xml_combine_filename)
    transform = etree.XSLT(combine)
    return transform(index)

def _parse_xml(all, only_classes = False,
                    only_functions = False,
                    filter = None) -> Index:
    index = Index()
    if not only_functions:
        _parse_all_classes(all, index, filter)
    if not only_classes:
        _parse_all_functions(all, index, filter)
    return index

def _parse_all_classes(root, index, filter):
    for classdef in root.iterfind('.//compounddef[@kind="class"]'):
        _parse_class(classdef, index, filter)

def _parse_all_functions(root, index, filter):
    for namespacedef in root.iterfind('.//compounddef[@kind="namespace"]'):
        namespace = namespacedef.findtext('compoundname').strip()
        for memberdef in namespacedef.iterfind('.//memberdef[@kind="function"]'):
            _parse_free_function(memberdef, namespace, index, filter)

def _parse_class(compounddef, index, filter):
    compoundname = compounddef.findtext('compoundname')
    if filter and compoundname != filter:
        return
    namespace, name = _split_compound_name(compoundname)
    class_def = index.add_class(compoundname)
    class_def.name = name
    class_def.kind = compounddef.get('kind')
    class_def.namespace = namespace
    location = compounddef.find('location')
    location_def = class_def.add_location()
    location_def.filename = location.get('file')
    location_def.bodystart = int(location.get('bodystart'))
    location_def.bodyend = int(location.get('bodyend'))
    _parse_class_members(compounddef, class_def)

def _parse_free_function(memberdef, namespace, index, filter):
    function_full_name = ''
    if namespace:
        function_full_name += namespace + '::'
    function_full_name += memberdef.findtext('name').strip()
    if filter and function_full_name != filter:
        return
    func_def = index.add_function(function_full_name)
    func_def.namespace = namespace
    _parse_function(memberdef, func_def)

_property_re = re.compile(r'(get|set)_(\w+)')
def _parse_class_members(compounddef, class_def):
    for memberdef in compounddef.iterfind('.//memberdef[@kind="function"]'):
        name = memberdef.findtext('name')
        property_match = _property_re.match(name)
        if property_match:
            property_name = property_match.group(2)
            property_direction = property_match.group(1)
            property_def = (class_def.get_property(property_name) or
                            class_def.add_property(property_name))
            _parse_property(memberdef, property_def, property_direction)
        else:
            method_def = class_def.add_method()
            _parse_function(memberdef, method_def)

def _parse_property(memberdef, property_def, direction):
    if direction == 'get':
        method_def = property_def.add_getter()
        _parse_function(memberdef, method_def)
        doc = method_def.doc
        typename = method_def.return_type
        definition = f'{typename} {property_def.name}'
        default_value = _extract_property_default(doc) if doc else ''
        if default_value:
            definition += f' = {default_value}'
        method_def.doc = None
        property_def.doc = doc
        property_def.default = default_value
        property_def.typename = typename
        property_def.definition = definition
    else:
        method_def = property_def.add_setter()
        _parse_function(memberdef, method_def)

def _parse_function(memberdef, function_def):
    ret = _parse_inner_text(memberdef.find('type'))
    name = _parse_inner_text(memberdef.find('name'))
    args = _parse_inner_text(memberdef.find('argsstring'))
    function_def.name = name
    function_def.return_type = ret
    function_def.definition = f'{ret} {name}{args}'.lstrip()
    _parse_function_doc(memberdef, function_def)
    _parse_function_parameters(memberdef, function_def)

def _parse_function_parameters(memberdef, function_def):
    for param in memberdef.iterchildren('param'):
        declname = param.findtext('declname')
        if declname:
            function_def.add_parameter(declname.strip())
    param_doc_xpath = './/detaileddescription/para/parameterlist[@kind="param"]/parameteritem'
    for parameteritem in memberdef.iterfind(param_doc_xpath):
        parametername = parameteritem.findtext('.//parametername').strip()
        parameterdescription = parameteritem.find('parameterdescription')
        param_def = (function_def.get_parameter(parametername) or
                     function_def.add_parameter(parametername))
        desc_def = param_def.add_description()
        _parse_doc_description(parameterdescription, desc_def)

def _parse_function_doc(memberdef, method_def):
    desc = memberdef.find('detaileddescription')
    if desc is None:
        desc = memberdef.find('briefdescription')
    if desc is not None:
        doc_def = method_def.add_doc()
        desc_def = doc_def.add_description()
        _parse_doc_description(desc, desc_def)
        _parse_doc_attributes(desc, doc_def)

def _parse_doc_description(xml, desc_def):
    def add_text_or_math(text):
        if not text:
            return
        raw_runs = text.split('$')
        for i, text in enumerate(raw_runs):
            if i % 2 == 0:
                desc_def.add_text(text)
            else:
                desc_def.add_math(text)
    for para in xml.iterchildren():
        add_text_or_math(para.text)
        for node in para.iterchildren():
            if node.tag == 'computeroutput':
                desc_def.add_code(node.text)
                add_text_or_math(node.tail)

def _parse_doc_attributes(xml, doc_def):
    kind_map = {
        'remark': doc_def.add_remark,
        'invariant': doc_def.add_invariant,
        'pre': doc_def.add_precondition,
        'post': doc_def.add_postcondition,
    }
    for node in xml.iterfind('.//simplesect'):
        kind = node.get('kind')
        if kind not in kind_map:
            continue
        for inner_para in node.iterchildren('para'):
            text = _parse_inner_text(inner_para)
            kind_map[kind](text)

def _parse_inner_text(xml):
    return ''.join(xml.itertext()).strip()

_default_remark_re = re.compile(r'default *= *(.+)')
def _extract_property_default(doc):
    default_value = None
    default_remark = None
    for remark in doc.remarks:
        m = _default_remark_re.match(remark)
        if m is not None:
            default_remark = remark
            default_value = m.group(1)
            break
    if default_remark is not None:
        doc.remarks.remove(default_remark)
    return default_value

def _split_compound_name(compoundname):
    try:
        namespace, name = compoundname.rsplit('::', 1)
    except ValueError:
        namespace, name = '', compoundname
    return namespace, name


if __name__ == "__main__":
    import argparse
    args = argparse.ArgumentParser('doxyparser')
    args.add_argument('dir', type=str,
                      help='Path to the directory with Doxygen XML output')
    args.add_argument('--only-functions', action='store_true', default=False,
                      help='If provided, displays only functions')
    args.add_argument('--filter', type=str, default=None,
                      help='Enables parsing only for the matched names')
    config = args.parse_args()
    index = parse(config.dir, only_functions=config.only_functions,
                              filter=config.filter)
    print(index.to_yaml())
