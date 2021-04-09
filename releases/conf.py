# SPDX-FileCopyrightText: 2021 Intel Corporation
#
# SPDX-License-Identifier: MIT

# Configuration file for the Sphinx documentation builder.
#
# This file only contains a selection of the most common options. For a full
# list see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Path setup --------------------------------------------------------------

# If extensions (or modules to document with autodoc) are in another directory,
# add these directories to sys.path here. If the directory is relative to the
# documentation root, use os.path.abspath to make it absolute, like shown here.
#
# import os
# import sys
# sys.path.insert(0, os.path.abspath('.'))


# -- Project information -----------------------------------------------------

project = 'oneAPI Specification Versions'
copyright = '2021, Intel Corporation'
author = 'Intel Corporation'


# -- General configuration ---------------------------------------------------

# Add any Sphinx extension module names here, as strings. They can be
# extensions coming with Sphinx (named 'sphinx.ext.*') or your custom
# ones.
extensions = []

# List of patterns, relative to source directory, that match files and
# directories to ignore when looking for source files.
# This pattern also affects html_static_path and html_extra_path.
exclude_patterns = ['_build', 'Thumbs.db', '.DS_Store']


# -- Options for HTML output -------------------------------------------------

# The theme to use for HTML and HTML Help pages.  See the documentation for
# a list of builtin themes.
#
html_theme = 'sphinx_book_theme'

html_favicon = 'favicons.png'

html_theme_options = {
    'repository_url': 'https://github.com/oneapi-src/oneapi-spec',
    'path_to_docs': 'releases',
    'use_issues_button': True,
    'use_edit_page_button': True,
    'repository_branch': 'main',
    'single_page': True,
}
