.. SPDX-FileCopyrightText: 2019-2020 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

=====================
oneAPI Specifications
=====================

.. image:: https://github.com/oneapi-src/oneAPI-spec/actions/workflows/ci.yml/badge.svg
   :target: https://github.com/oneapi-src/oneapi-spec/actions?query=workflow%3ACI

.. image:: https://api.reuse.software/badge/github.com/oneapi-src/oneapi-spec
   :target: https://api.reuse.software/info/github.com/oneapi-src/oneapi-spec
   :alt: REUSE status

This repository contains the sources for the `oneAPI
Specification`_. For the latest build from main branch, see HTML_ and
PDF_.

For more information about oneAPI, see `oneapi.io`_.  For information
about future releases of the oneAPI specification, see the roadmap_.
To be notified about new releases, become a release-only watcher of
this repo.

The document is written using `reStructuredText`_ and built with
`Sphinx`_ using a theme provided by `Read the Docs`_.

.. contents::
   :local:
   :depth: 1

-------
License
-------

The oneAPI specification is licensed under the Creative Commons Attribution 4.0
International License.

See `LICENSE <LICENSE.rst>`__ for more information.

----------
Contribute
----------

See `CONTRIBUTING <CONTRIBUTING.rst>`__ for more information.

.. _build_spec:

-----------------------
Build the Specification
-----------------------

To build the specification document locally, clone this repository to
your local system and follow the setup and build instructions. The
setup and build steps make use of scripts/oneapi.py, a helper script
for maintenance tasks. You can also look at the source if you want to
see how to do the same task manually.

Setup
-----

Install Python 3, Doxygen (>= 1.8.17), LaTeX, etc.  To install on **Ubuntu**::

   sudo scripts/install.sh

Create and activate a Python virtual environment with all required tools::

  python scripts/oneapi.py spec-venv
  source spec-venv/bin/activate

To install directly with pip::

  pip install -r requirements.txt

To install on Windows::

  python scripts\oneapi.py spec-venv
  spec-venv\Scripts\activate

Build the Docs
--------------

To build the HTML document, use the following command::

  python scripts/oneapi.py html

The document is organized as a book with chapters. Each element of
oneAPI is its own chapter and can be built separately. For example, to
build the oneVPL chapter, use the following command::

  python scripts/oneapi.py html source/elements/oneVPL

To view the HTML docs, visit build/html/index.html in your browser using a
file:// URL.

Build the pdf version wit the following command::

  python scripts/oneapi.py latexpdf

The generated PDF will be located at build/latexpdf/oneAPI-spec.pdf.

Spell check::

  python oneapi.doc. --verbose spelling

--
CI
--

We use GitHub actions. See `<.github/workflows/ci.yml>`_.

PR's trigger the CI to build the document and save it as an
artifact. If you are working in a fork on GitHub, commits to the main
branch will build and publish the document in the GitHub pages
associated with the repository.

------------------------
Adding licenses to files
------------------------


Use the reuse_ tool

Code examples::

  reuse addheader --copyright "Intel Corporation" --year 2020 --license MIT source/examples/host-task.cpp

Doc sources::

  reuse addheader --copyright "Intel Corporation" --year 2020 --license CC-BY-4.0 source/index.rst


----------------
Making a Release
----------------

1. Update:

   * oneapi-doc.json
   * releases/index.rst

2. Tag it.
3. Publish with oneAPI doc repo

.. _`reStructuredText`: http://www.sphinx-doc.org/en/master/usage/restructuredtext/basics.html
.. _`Sphinx`: http://www.sphinx-doc.org/en/master/
.. _`Read the Docs`: https://readthedocs.org/
.. _`oneAPI Specification`: https://oneapi.io/spec
.. _reuse: https://pypi.org/project/reuse/
.. _HTML: https://oneapi-src.github.io/oneAPI-spec/spec/
.. _PDF: https://oneapi-src.github.io/oneAPI-spec/spec/oneAPI-spec.pdf
.. _`oneapi.io`: https://oneapi.io
.. _roadmap: roadmap.rst
