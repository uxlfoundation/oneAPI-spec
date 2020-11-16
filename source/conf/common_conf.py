# SPDX-FileCopyrightText: 2019-2020 Intel Corporation
#
# SPDX-License-Identifier: MIT

import json
import os
import sys
import string

import docutils


def path_relative_to_repo_root(relative_path):
    this_dir = os.path.dirname(os.path.realpath(__file__))
    root_dir = os.path.abspath(os.path.join(this_dir, '../..'))
    return os.path.abspath(os.path.join(root_dir, relative_path))


# oneDAL uses custom API generator based on `breathe`.
# Extend path to let Sphinx find `dalapi` module:
sys.path.insert(0, path_relative_to_repo_root('source/elements/oneDAL'))

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
    'sphinx-prompt',
    'sphinx_substitution_extensions',
    'breathe',
    'dalapi',  # oneDAL API generator
]

with open('../oneapi-doc.json') as fin:
    cfg = json.load(fin)

env = {
    'oneapi_version': cfg['version'],
    'vpl_spec_version': cfg['vpl_version'],
}

prolog_template = string.Template(
    """
.. |dpcpp_full_name| replace:: oneAPI Data Parallel C++
.. |dpcpp_version| replace:: $oneapi_version
.. |dpl_full_name| replace:: oneAPI DPC++ Library
.. |dpl_version| replace:: $oneapi_version
.. |ccl_full_name| replace:: oneAPI Collective Communications Library
.. |ccl_version| replace:: $oneapi_version
.. |dal_full_name| replace:: oneAPI Data Analytics Library
.. |dal_short_name| replace:: oneDAL
.. |dal_version| replace:: $oneapi_version
.. |dal_namespace| replace:: daal
.. |dnn_full_name| replace:: oneAPI Deep Neural Network Library
.. |dnn_version| replace:: $oneapi_version
.. |l0_full_name| replace:: oneAPI Level Zero
.. |tbb_full_name| replace:: oneAPI Threading Building Blocks
.. |tbb_version| replace:: $oneapi_version
.. |vpl_full_name| replace:: oneAPI Video Processing Library
.. |vpl_version| replace:: $vpl_spec_version
.. |mkl_full_name| replace:: oneAPI Math Kernel Library
.. |mkl_version| replace:: $oneapi_version
.. _`Level Zero Specification`: https://spec.oneapi.com/level-zero/latest/index.html
.. include:: <isonum.txt>
.. |regsup| replace:: :supsub:`reg`
.. |intel_r| replace:: Intel\ :supsub:`reg`
.. |msdk_full_name| replace:: Intel\ :supsub:`reg` Media Software Development Kit
"""
)

rst_prolog = prolog_template.substitute(env)


# for substitutions in code blocks and sphinx-prompts:
substitutions = [('|dal_short_name|', 'oneDAL'), ('|daal_in_code|', 'daal')]


primary_domain = 'cpp'

latex_elements = {
    # 'printindex': '\\footnotesize\\raggedright\\let\\oldtwocolumn\\twocolumn\\renewcommand{\\twocolumn}[1][]{#1}\\printindex\\renewcommand{\\twocolumn}[1][]{\\oldtwocolumn}',
    # The paper size ('letterpaper' or 'a4paper').
    #
    # 'papersize': 'letterpaper',
    # The font size ('10pt', '11pt' or '12pt').
    #
    # 'pointsize': '10pt',
    # Additional stuff for the LaTeX preamble.
    #
    'preamble': r'''
\usepackage{makeidx}
\usepackage[columns=1]{idxlayout}
\makeindex
\DeclareUnicodeCharacter{2208}{$\in$}
\DeclareUnicodeCharacter{222A}{$\cup$}
\DeclareUnicodeCharacter{2236}{$\colon$}
\DeclareUnicodeCharacter{2260}{$\neq$}
\DeclareUnicodeCharacter{2264}{$\leq$}
\DeclareUnicodeCharacter{2265}{$\geq$}
\DeclareUnicodeCharacter{393}{$\gamma$}
\DeclareUnicodeCharacter{39B}{$\Lambda$}
\DeclareUnicodeCharacter{3A3}{$\Sigma$}
\DeclareUnicodeCharacter{3A6}{$\phi$}
\DeclareUnicodeCharacter{3B1}{$\alpha$}
\DeclareUnicodeCharacter{3B2}{$\beta$}
\DeclareUnicodeCharacter{3B4}{$\delta$}
\DeclareUnicodeCharacter{3BB}{$\lambda$}
\DeclareUnicodeCharacter{3BC}{$\mu$}
\DeclareUnicodeCharacter{3BD}{$\nu$}
\DeclareUnicodeCharacter{3C0}{$\pi$}
\DeclareUnicodeCharacter{3C3}{$\sigma$}
\DeclareUnicodeCharacter{FB01}{$fi$}
\DeclareUnicodeCharacter{FB02}{$fl$}
\newcommand{\src}{\operatorname{src}}
\newcommand{\srclayer}{\operatorname{src\_layer}}
\newcommand{\srciter}{\operatorname{src\_iter}}
\newcommand{\srciterc}{\operatorname{src\_iter\_c}}
\newcommand{\weights}{\operatorname{weights}}
\newcommand{\weightslayer}{\operatorname{weights\_layer}}
\newcommand{\weightsiter}{\operatorname{weights\_iter}}
\newcommand{\weightspeephole}{\operatorname{weights\_peephole}}
\newcommand{\weightsprojection}{\operatorname{weights\_projection}}
\newcommand{\bias}{\operatorname{bias}}
\newcommand{\dst}{\operatorname{dst}}
\newcommand{\dstlayer}{\operatorname{dst\_layer}}
\newcommand{\dstiter}{\operatorname{dst\_iter}}
\newcommand{\dstiterc}{\operatorname{dst\_iter\_c}}
\newcommand{\diffsrc}{\operatorname{diff\_src}}
\newcommand{\diffsrclayer}{\operatorname{diff\_src\_layer}}
\newcommand{\diffsrciter}{\operatorname{diff\_src\_iter}}
\newcommand{\diffsrciterc}{\operatorname{diff\_src\_iter\_c}}
\newcommand{\diffweights}{\operatorname{diff\_weights}}
\newcommand{\diffweightslayer}{\operatorname{diff\_weights\_layer}}
\newcommand{\diffweightsiter}{\operatorname{diff\_weights\_iter}}
\newcommand{\diffweightspeephole}{\operatorname{diff\_weights\_peephole}}
\newcommand{\diffweightsprojection}{\operatorname{diff\_weights\_projection}}
\newcommand{\diffbias}{\operatorname{diff\_bias}}
\newcommand{\diffdst}{\operatorname{diff\_dst}}
\newcommand{\diffdstlayer}{\operatorname{diff\_dst\_layer}}
\newcommand{\diffdstiter}{\operatorname{diff\_dst\_iter}}
\newcommand{\diffdstiterc}{\operatorname{diff\_dst\_iter\_c}}
\newcommand{\diffgamma}{\operatorname{diff\_\gamma}}
\newcommand{\diffbeta}{\operatorname{diff\_\beta}}
\newcommand{\workspace}{\operatorname{workspace}}
''',
    # Latex figure (float) alignment
    #
    # 'figure_align': 'htbp',
    'extraclassoptions': 'openany,oneside',
}


def supsub_role(name, rawtext, text, lineno, inliner, options={}, content=[]):
    node = docutils.nodes.superscript()
    node2 = docutils.nodes.substitution_reference(refname=text)
    node += [node2]
    return [node], []


def setup(app):
    app.add_role('supsub', supsub_role)
    add_custom_css = getattr(
        app, 'add_css_file', getattr(app, 'add_stylesheet')
    )
    add_custom_css('custom.css')
