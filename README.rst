=====================
oneAPI Specifications
=====================

This repo is used to build the oneAPI specifications.  oneMKL & oneDAL
are tarballs generated outside of the repo.

The document is built with `Sphinx
<http://www.sphinx-doc.org/en/master/>` using a theme provided by
`Read the Docs <https://readthedocs.org/>`


-----------------------------------
Layout of the Documents in the Repo
-----------------------------------

The specification is in the Source directory. Some of the
specifications have companion documents which are saved as tarballs in
the Specifications directory.

----------------
Viewing the docs
----------------

The specification is re-built on every commit to the master branch and
published as `html`_ and `pdf`_.

-------
Editing
-------


Using Github Web Interface
--------------------------

The simplest and quickest way to edit is directly in the github web
interface. It has an editor, previewer, and lets you commit
changes. You won't need to install any local tools. The previewer
knows how to render RST, but not the sphinx directives so it will not
display exactly as the real manual. Here is a simple exercise. Add
your name to the `contributors page`_. Copy a line that is already
there, changing it to your name. Admire your work by clicking on the
preview tab. When you are done, click on the *commit changes*
button. You can immediately see the rendered version of the page you
just edited.

Working with a Local Copy
-------------------------

For bigger edits, you will need a local version of the tools.

Setup
~~~~~

For local editing and view, install the tools on **Ubuntu**::

   sudo Scripts/install.sh
        
You can build a **Docker container** image with::

   Scripts/build-image.sh

The tag will be oneapi-spec.  The script copies your proxy settings in
the invoking shell so it will work inside the firewall. We use this
container in the CI system. See `CI configuration`_ for its use.

Windows and Mac
```````````````

Install doxygen and python, then use pip to install the rest with::
  
        pip install -r requirements-latest.txt

You can also use `Windows ubuntu terminal`_ and then follow the ubuntu
directions in Setup_.

Building the docs
~~~~~~~~~~~~~~~~~

To build the html document on Linux, do::

  make html

The document is organized as a book with chapters. Each element of
oneAPI is its own chapter and can be built separately. For example, to
build the oneVPL chapter, do::

  cd Source/Elements/oneVPL
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

We have configuration files for gitlab and Azure Pipelines. The gitlab
file is used inside intel and azure for external. We use Azure App
service to host the web pages. Deploying to gitlab pages was very slow
and I expect that gitlab pages will have the same issue. It became
slower as the spec grew and I suspect the problem is the large number
of files. If we can significantly reduce the number of files, then it
would be worthwhile to try github pages because it is simpler to
manage permissions.

If you are setting up Azure App Service for the first time. The steps are:

* Create a HTML app following these directions:
  https://docs.microsoft.com/en-us/azure/app-service/app-service-web-get-started-html. Use
  the same app name in the appName line in the azure-pipelines.yml
* Create a service connection following these directions:
  https://docs.microsoft.com/en-us/azure/devops/pipelines/library/service-endpoints?view=azure-devops&tabs=yaml. Put
  the service connection name in the azureScription line in the
  azure-pipelines.yml

More Reading
------------

* `oneAPI Specification Style Guide <https:style-guide.rst>`_
* `Sphinx Documentation <http://www.sphinx-doc.org/en/master/>`_
* `rst docs`_: User and reference manuals.
* `online editor/viewer`_: Web page that lets you type in some rst fragments
  and view. Good for debugging.

.. _`CI server`: http://ansatnuc02.an.intel.com/oneapi
.. _`html`: http://onespec.azurewebsites.net/
.. _`pdf`: http://onespec.azurewebsites.net/oneAPI-spec.pdf
.. _`rst tutorial`: http://www.sphinx-doc.org/en/master/usage/restructuredtext/basics.html
.. _`rst docs`: http://docutils.sourceforge.net/rst.html
.. _`online editor/viewer`: http://rst.aaroniles.net/
.. _`Windows ubuntu terminal`: https://tutorials.ubuntu.com/tutorial/tutorial-ubuntu-on-windows#0
.. _`CI configuration`: https://github.com/rscohn2/onespec/blob/master/azure-pipelines.yml
.. _`contributors page`: https://gitub.com/rscohn2/onespec/edit/master/Source/contributors.rst
