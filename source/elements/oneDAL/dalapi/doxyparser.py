import re
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
    _parse_class_members(compounddef, class_def)

_property_re = re.compile(r'(get|set)_(\w+)')
def _parse_class_members(compounddef, class_def):
    for memberdef in compounddef.iterfind('.//memberdef[@kind="function"]'):
        name = memberdef.findtext('name')
        property_match = _property_re.match(name)
        if property_match:
            property_name = property_match.group(2)
            property_direction = property_match.group(1)
            property_def = class_def.add_property(property_name)
            _parse_property(memberdef, property_def, property_direction)
        else:
            method_def = class_def.add_method()
            _parse_method(memberdef, method_def)

def _parse_property(memberdef, property_def, direction):
    if direction == 'get':
        method_def = property_def.add_getter()
        _parse_method(memberdef, method_def)
        property_def.typename = method_def.return_type
    else:
        method_def = property_def.add_setter()
        _parse_method(memberdef, method_def)
    if method_def.doc and not property_def.doc:
        property_def.doc = method_def.doc
        property_def.default = _extract_property_default(method_def.doc)
        method_def.doc = None
    if property_def.typename:
        property_def.definition = f'{property_def.typename} {property_def.name}'
        if property_def.default:
            property_def.definition += f' = {property_def.default}'


def _parse_method(memberdef, method_def):
    method_def.name = memberdef.findtext('name')
    definition = memberdef.findtext('definition')
    argsstring = memberdef.findtext('argsstring')
    method_def.definition = (definition + argsstring).strip()
    method_def.return_type = definition.replace(method_def.name, '').strip()
    _parse_method_doc(memberdef, method_def)
    _parse_method_parameters(memberdef, method_def)

def _parse_method_parameters(memberdef, method_def):
    pass

def _parse_method_doc(memberdef, method_def):
    para = memberdef.find('detaileddescription/para')
    if para is None:
        para = memberdef.find('briefdescription/para')
    if para is not None:
        doc_def = method_def.add_doc()
        doc_def.description = _preprocess_text(para.text)
        for remark in para.iterfind('simplesect[@kind="remark"]'):
            doc_def.add_remark(_parse_inner_text(remark))
        for invariant in para.iterfind('simplesect[@kind="invariant"]'):
            doc_def.add_invariant(_parse_inner_text(invariant))

def _parse_inner_text(xml):
    text = xml.text if xml.text else ''
    for tag in xml.iter():
        if tag.text:
            text += tag.text
    return _preprocess_text(text)

_latex_re = re.compile(r'\$([^\$])\$')
def _preprocess_text(text):
    return _latex_re.sub(r':math:`\1`', text.strip())

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
    import sys
    index = parse(sys.argv[1])
    print(index)
