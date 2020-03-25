extensions = [
    'notfound.extension',
    'sphinx.ext.autodoc',
    'sphinx.ext.doctest',
    'sphinx.ext.todo',
    'sphinx.ext.coverage',
    'sphinx.ext.mathjax',
    'sphinx.ext.ifconfig',
    'sphinx.ext.imgconverter',
    'sphinx.ext.viewcode',
    'sphinx.ext.githubpages',
    'sphinx.ext.graphviz',
    'sphinxcontrib.spelling',
    'sphinx_substitution_extensions',
    'breathe',
]

rst_prolog = """
.. |ccl_full_name| replace:: oneAPI Collective Communications Library
.. |dal_full_name| replace:: oneAPI Data Analytics Library
.. |dal_short_name| replace:: oneDAL
.. |dal_namespace| replace:: daal
.. |dnn_full_name| replace:: oneAPI Deep Neural Network Library
.. |dpl_full_name| replace:: oneAPI DPC++ Library
.. |dpcpp_full_name| replace:: DPC++
.. |l0_full_name| replace:: oneAPI Level Zero
.. |mkl_full_name| replace:: oneAPI Math Kernel Library
.. |tbb_full_name| replace:: oneAPI Threading Building Blocks
.. |vpl_full_name| replace:: oneAPI Video Processing Library
"""

# for substitutions in code blocks and sphinx-prompts:
substitutions = [
    ('|dal_short_name|', 'oneDAL'),
    ('|daal_in_code|', 'daal')
    ]

oneapi_spec_version = '0.6.0'

primary_domain = 'cpp'

latex_elements = {
    # The paper size ('letterpaper' or 'a4paper').
    #
    # 'papersize': 'letterpaper',

    # The font size ('10pt', '11pt' or '12pt').
    #
    # 'pointsize': '10pt',

    # Additional stuff for the LaTeX preamble.
    #
    'preamble': '\\DeclareUnicodeCharacter{2208}{$\\in$}',

    # Latex figure (float) alignment
    #
    # 'figure_align': 'htbp',
    'extraclassoptions': 'openany,oneside'
}

def setup(app):
    add_custom_css = getattr(app,'add_css_file',getattr(app,'add_stylesheet'))
    add_custom_css('custom.css')
