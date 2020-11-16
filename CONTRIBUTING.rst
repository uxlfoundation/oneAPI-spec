.. SPDX-FileCopyrightText: 2019-2020 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

=================
How to Contribute
=================

This specification is a continuation of Intel’s decades-long history
of working with standards groups and industry/academia initiatives
such as The Khronos Group, to create and define specifications in an
open and fair process to achieve interoperability and
interchangeability. oneAPI is intended to be an open specification and
we encourage you to help us make it better. Your feedback is optional,
but to enable Intel to incorporate any feedback you may provide to
this specification, and to further upstream your feedback to other
standards bodies, including The Khronos Group SYCL specification,
please submit your feedback under the terms and conditions below. Any
contribution of your feedback to the oneAPI Specification does not
prohibit you from also contributing your feedback directly to other
standard bodies, including The Khronos Group under their respective
submission policies.

.. contents::
   :local:
   :depth: 1

----------
Governance
----------

See `governance <doc/governance.rst>`__ for more information.

---------------
Submit a Change
---------------

* For questions, feature requests, or to report a bug, submit an
  `issue <https://github.com/oneapi-src/oneAPI-spec/issues>`__.
* For changes to the document build infrastructure or minor editing of
  the text, please submit a `pull request
  <https://github.com/oneapi-src/oneAPI-spec/pulls>`__.
* For significant changes to the specification, submit an `issue
  <https://github.com/oneapi-src/oneAPI-spec/issues>`__. Make sure to

  * include "RFC" in the title,
  * explain your proposed change and the motivation for the change.

  You may also create a pull request as a way to explain the change.

If none of these methods are appropriate, you may also email
`oneapi@intel.com <mailto:oneapi@intel.com>`__.

--------------
Sign Your Work
--------------

Please include a signed-off-by tag in every contribution of
your feedback. By including a signed-off-by tag, you agree
that:

1. You have a right to license your feedback to Intel.
2. Intel will be free to use, disclose, reproduce, modify, license,
   or otherwise distribute your feedback at its sole discretion
   without any obligations or restrictions of any kind, including
   without limitation, intellectual property rights or licensing
   obligations.
3. Your feedback will be public and that a record of your feedback
   may be maintained indefinitely.

If you agree to the above, every contribution of your feedback
must include the following line using your real name and email
address: Signed-off-by: Joe Smith joe.smith@email.com

-----------
Style Guide
-----------

See the `oneAPI Specification Style Guide <style-guide.rst>`_ for information.

----------------------------------
Edit with the GitHub Web Interface
----------------------------------

The simplest and quickest way to submit an edit is via the GitHub web
interface. It provides an editor, change preview, and lets you submit
the change as a pull request. You won't need to install any local
tools. The preview will render ReST, but not the Sphinx directives, so
it will not display exactly as the final document.

----------------------
Work with a Local Copy
----------------------

For bigger edits you will need a local version of the tools. See
:ref:`Build the Specification <build_spec>` for instructions.

-------------
Editing Tools
-------------

For simple edits to individual files, you can use the GitHub web
interface.

**Emacs** has a built-in ReST mode. It does some syntax highlighting and
helps with some of the tedious aspects of ReST. M-q will rejustify
long lines to fit the recommended 80 character line. It understands
ReST formatting and won't mess up lists. C-= is a Swiss army knife. It
will cycle between different characters for a section break adornment
(e.g. --, ===, ...) It will make the section break adornment match the
size of the text. Probably a lot more.

**Visual Studio Code** has extensions for previewers and automatic
linting. I could not find any support for rejustifying paragraphs to
80 characters, which makes it difficult to use.

-----------------------------
Create a New Version Number
-----------------------------

Change version in `<oneapi-doc.json>`__ and update the table in
`<source/versions.rst>`__.

------------
More Reading
------------

* `Sphinx Documentation <http://www.sphinx-doc.org/en/master/>`_
* `reStructuredText docs`_: User and reference manuals.
* `Online editor/viewer`_: Web page that lets you type in some rst fragments
  and view. Good for debugging.

.. _`reStructuredText docs`: http://docutils.sourceforge.net/rst.html
.. _`online editor/viewer`: http://rst.aaroniles.net/
