.. SPDX-FileCopyrightText: 2019-2020 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

=====================
oneAPI Specifications
=====================

.. important::

   **This repository is retired. The oneAPI specification has moved to a dynamic specification.**

   Start with the `oneAPI specification on the UXL Foundation website <https://uxlfoundation.org/specifications/oneapi/technical-overview/>`__.
   The website maintains shared concepts and project relationships. Each project's
   published documentation is the canonical source for its current APIs,
   requirements, compatibility and supported configurations.

   See the `oneAPI libraries and specification elements <https://uxlfoundation.org/specifications/oneapi/specification-elements/>`__
   for links to the projects and their documentation. Propose changes and report
   issues in the relevant project repository.

   This repository is archived for historical reference. Its bundled specifications,
   releases and open discussions are historical records, not the current specification.
   No further releases or contributions are planned here.

The instructions below describe how to build and maintain historical snapshots.

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

For current contributions, follow the project links on the UXL website above.
The `former contribution guide <CONTRIBUTING.rst>`__ is retained as a historical record.

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

  reuse addheader --copyright "Constributors to the oneapi-spec project" --license MIT source/examples/host-task.cpp

Doc sources::

  reuse addheader --copyright "Constributors to the oneapi-spec project" --license CC-BY-4.0 source/index.rst


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
.. _HTML: https://uxlfoundation.github.io/oneAPI-spec/spec/
.. _PDF: https://uxlfoundation.github.io/oneAPI-spec/spec/oneAPI-spec.pdf
.. _`oneapi.io`: https://oneapi.io
.. _roadmap: roadmap.rst
