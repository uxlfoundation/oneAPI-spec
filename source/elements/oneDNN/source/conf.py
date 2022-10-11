# SPDX-FileCopyrightText: 2019-2020 Intel Corporation
#
# SPDX-License-Identifier: MIT

# -*- coding: utf-8 -*-
#
# Configuration file for the Sphinx documentation builder.
#
# This file does only contain a selection of the most common options. For a
# full list see the documentation:
# http://www.sphinx-doc.org/en/master/config

# -- Path setup --------------------------------------------------------------

# If extensions (or modules to document with autodoc) are in another directory,
# add these directories to sys.path here. If the directory is relative to the
# documentation root, use os.path.abspath to make it absolute, like shown here.
#
import os
import sys
from os.path import join

project = 'oneDNN'

repo_root = join('..', '..', '..', '..')
exec(open(join(repo_root, 'source', 'conf', 'common_conf.py')).read())
exec(open(join(repo_root, 'source', 'conf', 'element_conf.py')).read())


imgmath_latex_preamble = '''\\newcommand{\\src}{\\operatorname{src}}
\\newcommand{\\srclayer}{\\operatorname{src\\_layer}}
\\newcommand{\\srciter}{\\operatorname{src\\_iter}}
\\newcommand{\\srciterc}{\\operatorname{src\\_iter\\_c}}
\\newcommand{\\weights}{\\operatorname{weights}}
\\newcommand{\\weightslayer}{\\operatorname{weights\\_layer}}
\\newcommand{\\weightsiter}{\\operatorname{weights\\_iter}}
\\newcommand{\\weightspeephole}{\\operatorname{weights\\_peephole}}
\\newcommand{\\weightsprojection}{\\operatorname{weights\\_projection}}
\\newcommand{\\bias}{\\operatorname{bias}}
\\newcommand{\\dst}{\\operatorname{dst}}
\\newcommand{\\dstlayer}{\\operatorname{dst\\_layer}}
\\newcommand{\\dstiter}{\\operatorname{dst\\_iter}}
\\newcommand{\\dstiterc}{\\operatorname{dst\\_iter\\_c}}
\\newcommand{\\diffsrc}{\\operatorname{diff\\_src}}
\\newcommand{\\diffsrclayer}{\\operatorname{diff\\_src\\_layer}}
\\newcommand{\\diffsrciter}{\\operatorname{diff\\_src\\_iter}}
\\newcommand{\\diffsrciterc}{\\operatorname{diff\\_src\\_iter\\_c}}
\\newcommand{\\diffweights}{\\operatorname{diff\\_weights}}
\\newcommand{\\diffweightslayer}{\\operatorname{diff\\_weights\\_layer}}
\\newcommand{\\diffweightsiter}{\\operatorname{diff\\_weights\\_iter}}
\\newcommand{\\diffweightspeephole}{\\operatorname{diff\\_weights\\_peephole}}
\\newcommand{\\diffweightsprojection}{\\operatorname{diff\\_weights\\_projection}}
\\newcommand{\\diffbias}{\\operatorname{diff\\_bias}}
\\newcommand{\\diffdst}{\\operatorname{diff\\_dst}}
\\newcommand{\\diffdstlayer}{\\operatorname{diff\\_dst\\_layer}}
\\newcommand{\\diffdstiter}{\\operatorname{diff\\_dst\\_iter}}
\\newcommand{\\diffdstiterc}{\\operatorname{diff\\_dst\\_iter\\_c}}
\\newcommand{\\diffgamma}{\\operatorname{diff\\_\\gamma}}
\\newcommand{\\diffbeta}{\\operatorname{diff\\_\\beta}}
\\newcommand{\\workspace}{\\operatorname{workspace}}'''

mathjax3_config = {
'tex': {
    'macros': {
        'src': '\\operatorname{src}',
        'srclayer': '\\operatorname{src\\_layer}',
        'srciter': '\\operatorname{src\\_iter}',
        'srciterc': '\\operatorname{src\\_iter\\_c}',
        'weights': '\\operatorname{weights}',
        'weightslayer': '\\operatorname{weights\\_layer}',
        'weightsiter': '\\operatorname{weights\\_iter}',
        'weightspeephole': '\\operatorname{weights\\_peephole}',
        'weightsprojection': '\\operatorname{weights\\_projection}',
        'bias': '\\operatorname{bias}',
        'dst': '\\operatorname{dst}',
        'dstlayer': '\\operatorname{dst\\_layer}',
        'dstiter': '\\operatorname{dst\\_iter}',
        'dstiterc': '\\operatorname{dst\\_iter\\_c}',
        'diffsrc': '\\operatorname{diff\\_src}',
        'diffsrclayer': '\\operatorname{diff\\_src\\_layer}',
        'diffsrciter': '\\operatorname{diff\\_src\\_iter}',
        'diffsrciterc': '\\operatorname{diff\\_src\\_iter\\_c}',
        'diffweights': '\\operatorname{diff\\_weights}',
        'diffweightslayer': '\\operatorname{diff\\_weights\\_layer}',
        'diffweightsiter': '\\operatorname{diff\\_weights\\_iter}',
        'diffweightspeephole': '\\operatorname{diff\\_weights\\_peephole}',
        'diffweightsprojection': '\\operatorname{diff\\_weights\\_projection}',
        'diffbias': '\\operatorname{diff\\_bias}',
        'diffdst': '\\operatorname{diff\\_dst}',
        'diffdstlayer': '\\operatorname{diff\\_dst\\_layer}',
        'diffdstiter': '\\operatorname{diff\\_dst\\_iter}',
        'diffdstiterc': '\\operatorname{diff\\_dst\\_iter\\_c}',
        'diffgamma': '\\operatorname{diff\\_\\gamma}',
        'diffbeta': '\\operatorname{diff\\_\\beta}',
        'workspace': '\\operatorname{workspace}'
        }
    }
}
