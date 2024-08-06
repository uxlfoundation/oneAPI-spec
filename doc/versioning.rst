.. SPDX-FileCopyrightText: 2019-2020 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

========================
Specification versioning
========================

This document describes the versioning of the specification for oneAPI
elements (e.g. oneMKL, oneVPL) and for oneAPI, which includes all the
elements. Specification versioning is independent of oneAPI product
versioning.

Product specification vs standard specification
===============================================

A *product specification* documents a single implementation. It is
typically completed before implementation to get feedback, and as a
reference for implementation, testing, and the creation of end-user
documentation. A *standard specification* documents the standard,
which may have multiple implementations. It is used to get feedback
and agreement between potential implementations.  oneAPI specification
is primarily a standard specification. An implementation may contain
features that are not part of the standard. It may be a feature being
considered for standardization, or features that are not suitable for
inclusion in oneAPI standard.


oneAPI specification versioning
===============================

Versioning is MAJOR.MINOR rev REVISION

Increment the:

1. MAJOR version when adding major new functionality and making
   incompatible API changes, including removing APIs.

2. MINOR version when adding minor functionality and API changes
   that are backwards compatible. Supported values: 0-99 [1]

3. REVISION when making backwards compatible bug fixes or any editing
   change in the document, including minor changes such as correcting
   typos. Initial REVISION is 1. Supported values: 1-99 [1]

The distinction between major and minor functionality is determined by
the core group. Latest REVISION is implicit because REVISIONs do not
change the meaning.

Element versioning
==================

By default, elements do not have independent versioning. An element
may incorporate another specification by reference, and may include
extensions or other features that are not part of the included
specification. DPC++ is an example, as it includes SYCL, which is used
independent of oneAPI and DPC++ and has its own standards body. Other
elements can be split out and have independent versioning if the need
arises with agreement of the oneAPI core team. An example would be
when an element has multiple implementations, and the implementation
does not include the rest of the elements.

Specification version approval
==============================

Element specifications must be approved by its
core team.  Updates which only change
the revision may be approved by the leads.


Provisional versions
====================

A specification may be published before approval, but must be labeled
provisional.  Provisional specifications are published as a series of
revisions until approval. After approval, the provisional label is
removed and the rev is set to 1.

Example
  | oneAPI provisional 1.1 rev 1
  | oneAPI provisional 1.1 rev 2
  | oneAPI provisional 1.1 rev 3
  | oneAPI 1.1 rev 1

Programmatic versioning
=======================

The specification version as mentioned above can be used programatically by appending all digits of the specification version in the format of <MAJOR><MINOR><REVISION>. MINOR and REVISION version use two digits. This versioning can be used to check the compatibility of the implementation with the specification version.

Example
  | oneAPI 1.1 rev 1 will be represented as a numerical value of 10101
  | oneAPI 1.2 rev 1 will be represented as a numerical value of 10201
  | oneAPI 1.2 rev 2 will be represented as a numerical value of 10202

The implementation is required to define a macro with the numerical value of the specification version. The macro name should be `ONEAPI_SPEC_VERSION` and the value should be the numerical value of the specification version. The components within the specification, can implement their own macro with the numerical value of the specification version. The macro name should be `<COMPONENT>_SPEC_VERSION` and the value should be the numerical value of the specification version.

Example
.. code-block:: c
    #define ONEAPI_SPEC_VERSION 10101
    #define ONETBB_SPEC_VERSION ONEAPI_SPEC_VERSION
    #define ONEMKL_SPEC_VERSION ONEAPI_SPEC_VERSION


[1] MINOR and REVISION values are limited to double digits to allow programmatic comparison of versions.
