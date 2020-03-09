rst_prolog = """
.. |ccl_full_name| replace:: Collective Communications Library
.. |dal_full_name| replace:: Data Analytics Library
.. |dal_short_name| replace:: oneDAL
.. |dal_namespace| replace:: daal
.. |dnn_full_name| replace:: Deep Neural Network Library
.. |dpl_full_name| replace:: DPC++ Library
.. |dpcpp_full_name| replace:: DPC++
.. |l0_full_name| replace:: Level Zero
.. |mkl_full_name| replace:: Math Kernel Library
.. |tbb_full_name| replace:: Threading Building Blocks
.. |vpl_full_name| replace:: Video Processing Library
"""

# for substitutions in code blocks and sphinx-prompts:
substitutions = [
    ('|dal_short_name|', 'oneDAL'),
    ('|daal_in_code|', 'daal')
    ]

oneapi_spec_version = '0.6.0'
