rst_prolog = """
.. |ccl_full_name| replace:: Collective Communications Library
.. |dal_full_name| replace:: Data Analytics Library
.. |dnn_full_name| replace:: Deep Neural Network Library
.. |dpl_full_name| replace:: DPC++ Library
.. |dpcpp_full_name| replace:: DPC++
.. |l0_full_name| replace:: Level Zero
.. |mkl_full_name| replace:: Math Kernel Library
.. |tbb_full_name| replace:: Threading Building Blocks
.. |vpl_full_name| replace:: Video Processing Library
"""

oneapi_spec_version = '0.6.0'

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
