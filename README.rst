=====================
oneAPI Specifications
=====================

This repo contains the sources for the `oneAPI Specification`_

The document is built with `Sphinx`_ using a theme provided by `Read
the Docs`_

-----------------------------------
Layout of the Documents in the Repo
-----------------------------------

The specification is in the source directory. Some of the
specifications have companion documents which are saved as tarballs in
the tarballs directory.

----------------
Viewing the docs
----------------

-------
Editing
-------

Using Github Web Interface
--------------------------

The simplest and quickest way to edit is directly in the github web
interface. It has an editor, previewer, and lets you commit
changes. You won't need to install any local tools. The previewer
knows how to render RST, but not the sphinx directives so it will not
display exactly as the real manual.

Working with a Local Copy
-------------------------

For bigger edits, you will need a local version of the tools.

Setup
~~~~~

First, install python and doxygen. Then install the python packages::

  pip install -r requirements.txt

The Makefile will create a python virtual environment with the required packages::

  make spec-venv

Use the virtual environment::

  source spec-venv/bin/activate
  
To install on **Ubuntu**::

   sudo scripts/install.sh
        
You can build a **Docker container** image with::

   scripts/build-image.sh

The tag will be oneapi-spec.  The script copies your proxy settings in
the invoking shell so it will work inside the firewall.

Building the docs
~~~~~~~~~~~~~~~~~

To build the html document on Linux, do::

  make html

The document is organized as a book with chapters. Each element of
oneAPI is its own chapter and can be built separately. For example, to
build the oneVPL chapter, do::

  cd source/elements/oneVPL
  python ../build.py html
  
The build.py script works on windows, linux, & mac.

To see the docs, visit build/html/index.html in your browser using a
file:// URL. Build the pdf version with::

  make latexpdf

And then view build/latexpdf/oneAPI-spec.pdf

Checking for Errors
~~~~~~~~~~~~~~~~~~~

There are rst linting tools to check for errors::

  find . -name '*.rst' | xargs rstcheck

rstcheck finds errors in some of the template code and in the cpp
examples. We may not want to try to correct them.

Editing Tools
-------------

For simple edits to individual files, you can use the github web
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

CI configuration
----------------

CI runs inside Intel until all parts of the spec are published here.

More Reading
------------

* `oneAPI Specification Style Guide <https:style-guide.rst>`_
* `Sphinx Documentation <http://www.sphinx-doc.org/en/master/>`_
* `rst docs`_: User and reference manuals.
* `online editor/viewer`_: Web page that lets you type in some rst fragments
  and view. Good for debugging.

.. _`rst tutorial`: http://www.sphinx-doc.org/en/master/usage/restructuredtext/basics.html
.. _`rst docs`: http://docutils.sourceforge.net/rst.html
.. _`online editor/viewer`: http://rst.aaroniles.net/
.. _`oneAPI Specification`: https://spec.oneapi.org
.. _`Sphinx`: http://www.sphinx-doc.org/en/master/
.. _`Read the Docs`: https://readthedocs.org/
