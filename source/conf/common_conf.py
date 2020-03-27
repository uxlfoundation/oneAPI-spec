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
.. |dpcpp_full_name| replace:: oneAPI Data Parallel C++
.. |dpcpp_version| replace:: 0.7
.. |dpl_full_name| replace:: oneAPI DPC++ Library
.. |dpl_version| replace:: 0.7
.. |ccl_full_name| replace:: oneAPI Collective Communications Library
.. |ccl_version| replace:: 0.7
.. |dal_full_name| replace:: oneAPI Data Analytics Library
.. |dal_short_name| replace:: oneDAL
.. |dal_version| replace:: 0.7
.. |dal_namespace| replace:: daal
.. |dnn_full_name| replace:: oneAPI Deep Neural Network Library
.. |dnn_version| replace:: 0.7
.. |l0_full_name| replace:: oneAPI Level Zero
.. |l0_version| replace:: 0.91
.. |tbb_full_name| replace:: oneAPI Threading Building Blocks
.. |tbb_version| replace:: 0.7
.. |vpl_full_name| replace:: oneAPI Video Processing Library
.. |vpl_version| replace:: 0.7
.. |mkl_full_name| replace:: oneAPI Math Kernel Library
.. |mkl_version| replace:: 0.7
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
