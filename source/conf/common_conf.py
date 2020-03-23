extensions = [
    'notfound.extension',
    'sphinx.ext.autodoc',
    'sphinx.ext.doctest',
    'sphinx.ext.todo',
    'sphinx.ext.coverage',
    'sphinx.ext.mathjax',
    'sphinx.ext.ifconfig',
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
