.. SPDX-FileCopyrightText: 2019-2020 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

=====================
oneAPI Specifications
=====================

.. image:: https://github.com/oneapi-src/oneapi-spec/workflows/CI/badge.svg
   :target: https://github.com/oneapi-src/oneapi-spec/actions?query=workflow%3ACI

This repository contains the sources for the `oneAPI
Specification`_. For the latest build from main branch, see `HTML
<https://oneapi-src.github.io/oneAPI-spec>`__ and `PDF
<https://rscohn2.github.io/oneAPI-spec/oneAPI-spec.pdf>`__.

For more information about oneAPI, see `oneapi.com
<https://oneapi.com>`__. For information about future releases of the
oneAPI specification, see the `oneAPI Specification Roadmap
<roadmap.rst>`__.  To be notified about new releases, become a
release-only watcher of this repo.

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

Docker
------

You can build a **Docker container** image with the following command::

   python scripts/oneapi.py dockerbuild

The tag will be rscohn2/oneapi-spec.  The script copies your proxy settings in
the invoking shell so it will work inside the firewall.

You can run a docker container with the following command::

    python scripts/oneapi.py dockerrun

--
CI
--

We use GitHub actions. See `<.github/workflows/ci.yml>`_.

PR's trigger the CI to build the document and save it as an
artifact. If you are working in a fork on GitHub, commits to the main
branch will build and publish the document in the GitHub pages
associated with the repository.


.. _`reStructuredText`: http://www.sphinx-doc.org/en/master/usage/restructuredtext/basics.html
.. _`Sphinx`: http://www.sphinx-doc.org/en/master/
.. _`Read the Docs`: https://readthedocs.org/
.. _`oneAPI Specification`: https://spec.oneapi.com
