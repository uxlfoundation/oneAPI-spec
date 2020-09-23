.. SPDX-FileCopyrightText: 2019-2020 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

=====================
oneAPI Specifications
=====================

.. image:: https://github.com/oneapi-src/oneapi-spec/workflows/CI/badge.svg
   :target: https://github.com/oneapi-src/oneapi-spec/actions?query=workflow%3ACI

This repo contains the sources for the `oneAPI Specification`_.

For the latest build from main branch, see `HTML
<https://oneapi-src.gihtub.io/oneAPI-spec>`__ and `PDF
<https://rscohn2.github.io/oneAPI-spec/oneAPI-spec.pdf>`__.

For more information about oneAPI, see `oneapi.com
<https://oneapi.com>`__. For information about future releases of the
oneAPI specification, see the `roadmap <roadmap.rst>`__. To be
notified about new releases, become a release-only watcher of this
repo. See `contribute <CONTRIBUTING.rst>`__ for information about
contributing.

The document is built with `Sphinx`_ using a theme provided by `Read
the Docs`_.

---------------------------------
Editing with GitHub Web Interface
---------------------------------

The simplest and quickest way to edit is directly in the GitHub web
interface. It has an editor, previewer, and lets you commit
changes. You won't need to install any local tools. The previewer
knows how to render RST, but not the sphinx directives so it will not
display exactly as the real document.

-------------------------
Working with a Local Copy
-------------------------

For bigger edits, you will need a local version of the tools. Clone
this repo to your local system. scripts/oneapi.py is a helper script
for the maintenance tasks. You can also look at the source if you want
to do the same task manually.

Setup
-----

Install Python 3, doxygen (>= 1.8.17), latex, etc.  To install on **Ubuntu**::

   sudo scripts/install.sh

Create and activate a Python virtual environment with all required tools::

  python scripts/oneapi.py spec-venv
  source spec-venv/bin/activate
  
To install directly with pip::

  pip install -r requirements.txt

On Windows::

  python scripts\oneapi.py spec-venv
  spec-venv\Scripts\activate
  

Building the docs
-----------------

To build the html document::

  python scripts/oneapi.py html

The document is organized as a book with chapters. Each element of
oneAPI is its own chapter and can be built separately. For example, to
build the oneVPL chapter, do::

  python scripts/oneapi.py html source/elements/oneVPL
  
To see the docs, visit build/html/index.html in your browser using a
file:// URL. Build the pdf version with::

  python scripts/oneapi.py latexpdf

And then view build/latexpdf/oneAPI-spec.pdf

Editing Tools
-------------

For simple edits to individual files, you can use the GitHub web
interface.

**Emacs** has a built-in ReST mode. It does some syntax highlighting and
helps with some of the tedious aspects of ReST. M-q will rejustify
long lines to fit the recommended 80 character line. It understands
ReST formatting and won't mess up lists. C-= is a Swiss army knife. It
will cycle between different characters for a section break adornment
(e.g. --, ===,...)  It will make the section break adornment match the
size of the text. Probably a lot more.

**Visual Studio Code** has extensions for previewers and automatic
linting. I could not find any support for rejustifying paragraphs to
80 characters, which makes it difficult to use.

------------------
Submitting changes
------------------

Changes are submitted as PR's to this repo. PR's and push trigger the
CI to build the doc and save it as an artifact. If you are working in
a fork on github, commits to the main branch will build and publish
the doc in the github pages associated with the repo.

------
Docker
------

You can build a **Docker container** image with::

   python scripts/oneapi.py dockerbuild

The tag will be rscohn2/oneapi-spec.  The script copies your proxy settings in
the invoking shell so it will work inside the firewall.

You can run a docker container with::

    python scripts/oneapi.py dockerrun

--
CI
--

We use GitHub actions. See `<.github/workflows/ci.yml>`_


-----------------------------
Creating a new version number
-----------------------------

Change version in `<oneapi-doc.json>`__ and update the table in
`<source/versions.rst>`__.

------------
More Reading
------------

* `oneAPI Specification Roadmap <roadmap.rst>`__
* `oneAPI Specification Style Guide <style-guide.rst>`_
* `Sphinx Documentation <http://www.sphinx-doc.org/en/master/>`_
* `rst docs`_: User and reference manuals.
* `online editor/viewer`_: Web page that lets you type in some rst fragments
  and view. Good for debugging.

.. _`rst tutorial`: http://www.sphinx-doc.org/en/master/usage/restructuredtext/basics.html
.. _`rst docs`: http://docutils.sourceforge.net/rst.html
.. _`online editor/viewer`: http://rst.aaroniles.net/
.. _`oneAPI Specification`: https://spec.oneapi.com
.. _`Sphinx`: http://www.sphinx-doc.org/en/master/
.. _`Read the Docs`: https://readthedocs.org/
