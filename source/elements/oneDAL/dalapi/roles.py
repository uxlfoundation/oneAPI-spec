import re
from docutils import nodes
from sphinx import roles

_term_ref_re = re.compile(r'(.+)<(.+)>', flags=re.DOTALL)
def capterm_role(name, rawtext, text, lineno, inliner, options={}, content=[]):
    global _term_ref_re
    xref_role = roles.XRefRole(innernodeclass=nodes.inline,
                               warn_dangling=True)
    term_match = _term_ref_re.match(text)
    if term_match:
        txt, ref = term_match.group(1), term_match.group(2)
    else:
        txt, ref = text, text
    fixed_term = f'{txt.strip()} <{ref.strip().capitalize()}>'
    return xref_role('std:term', rawtext, fixed_term, lineno, inliner, options, content)
