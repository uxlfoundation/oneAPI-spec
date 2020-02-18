=====================
oneAPI Specifications
=====================

This repo contains the sources for the `oneAPI Specification`_

The document is built with `Sphinx`_ using a theme provided by `Read
the Docs`_

-----------------------------------
Layout of the Documents in the Repo
-----------------------------------

The specification is in the source directory. MKL, TBB, and Level Zero
are in separate repos. See clones function in scripts/oneapi.py on how
to clone them.

---------------------------------
Editing with Github Web Interface
---------------------------------

The simplest and quickest way to edit is directly in the github web
interface. It has an editor, previewer, and lets you commit
changes. You won't need to install any local tools. The previewer
knows how to render RST, but not the sphinx directives so it will not
display exactly as the real manual.

-------------------------
Working with a Local Copy
-------------------------

For bigger edits, you will need a local version of the tools. Clone
this repo to your local system. scripts/oneapi.py is a helper script
for the maintenance tasks. You can also look at the source if you want
to do the same task manually.

Setup
-----

Install python 3 and doxygen (>= 1.8.17).  To install on **Ubuntu**::

   sudo scripts/install.sh

Create and activate a python virtual environment with all required tools::

  python scripts/oneapi.py spec-venv
  source spec-venv/bin/activate
  
To install directly with pip::

  pip install -r requirements.txt

On windows::

  python scripts\oneapi.py spec-venv
  spec-venv\Scripts\activate
  
MKL, DAL, and Level Zero are in other repos. To clone them::

  python scripts/oneapi.py clones

Building the docs
-----------------

To build the html document::

  python scripts/oneapi.py html

This will not work on windows because we are using symbolic links for
the elements that are in separate repos. However, windows can build
individual specs for individual elements.

The document is organized as a book with chapters. Each element of
oneAPI is its own chapter and can be built separately. For example, to
build the oneVPL chapter, do::

  python scripts/oneapi.py html source/elements/oneVPL
  
To see the docs, visit build/html/index.html in your browser using a
file:// URL. Build the pdf version with::

  python scripts/oneapi.py latexpdf

And then view build/latexpdf/oneAPI-spec.pdf

Checking for Errors
-------------------

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

We are currently using gitlab CI inside the intel firewall. We expect
all the sources to be in this repo by the 3/26/2020 release, and will
move the CI system to a public service.

See .gitlab-ci.yml for the CI configuration. The CI monitors and
builds 2 repo's inside Intel. oneapi-spec-mirror is a mirror of the
repo on github. Turnaround for testing depends on the interval between
mirroring updates, which appears to be ~30 minutes. For quick
turnaround, you can push your branch to the oneapi-spec-test repo,
which will be built immmediately.

On every commit, the CI system builds and publishes the document to
the staging server. To see the URL, look at the end of the log in the
CI system.

For commits to the publish branch, the document is staged inside a
full copy of the spec.oneapi.com site, which includes redirects and
older versions of the doc. To see the URL, look at the end of the log
in the CI system.

To push to S3, the CI system configuration sets AWS_ACCESS_KEY_ID and
AWS_SECRET_ACCESS_KEY environment variables.

----------
Publishing
----------

Merge from master to publish::
  
  git checkout publish
  git merge master
  git commit -m 'merge from master'
  
After CI completes, view the results on staging server. Push to
production with::

  python scripts/oneapi.py prod-publish

------------
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
.. _`oneAPI Specification`: https://spec.oneapi.com
.. _`Sphinx`: http://www.sphinx-doc.org/en/master/
.. _`Read the Docs`: https://readthedocs.org/
