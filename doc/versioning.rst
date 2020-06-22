========================
Specification Versioning
========================

This document describes the versioning of the specification for oneAPI
and its components. It is independent of oneAPI product
versioning.

oneAPI specification has an expected release cadence of 4 times a
year. Each release has a unique version number. Element specifications
may have their own release cadence. A release of the overall
specification contains a specific set of version numbers of elements.


Purpose
=======

oneAPI specification is primarily a description of APIs. We use
`Semantic Versioning`_ to communicate functionality additions and
compatibility to users and implementors.  It covers cases such as
adding interfaces, removing interfaces, and making non-compatible
changes to existing interfaces. The versioning does not in general
provide information on changes in the document that are not related to
interfaces, such as document editing changes.


Semantic Versioning
===================

A summary is included below and based on `Semantic Versioning`_. Rule
1 is augmented to include major functionality additions. Rule 3 is
augmented with the definition from `Semantic Versioning for
Documents`_.

  Given a version number MAJOR.MINOR.PATCH, increment the:

  1. MAJOR version when you make incompatible API changes or add major
     new functionality,
     
  2. MINOR version when you add functionality in a backwards
     compatible manner, and
     
  3. PATCH version when you make backwards compatible bug fixes or any
     editing change in the document, including minor changes such as
     typos.

  Additional labels for pre-release and build metadata are available
  as extensions to the MAJOR.MINOR.PATCH format.

Determining Overall Specification Versioning
============================================

A release of the overall specification contains a specific set of
version numbers of elements. If any element increases it minor
version, then the overall specification must increase its minor
version. If any element increases its major version, then the overall
specification must increase its major version. An increase in major
version is effectively an increase in minor version.

Increases in major version of an element are coordinated with the
overall specification and are expected to be rare.

Example
-------

Initial release:

| oneAPI 1.0
| oneMKL 1.0
| oneDAL 1.0

oneMKL adds some API's, oneDAL does not change:

| oneAPI 1.1
| oneMKL 1.1
| oneDAL 1.0

oneDAL adds API's, oneMKL does not change:

| oneAPI 1.2
| oneMKL 1.1
| oneDAL 1.1

oneMKL removes API's:

| oneAPI 2.0
| oneMKL 2.0
| oneDAL 1.1


Relationship of Implementation and Specification Versions
=========================================================

An implementation may indicate that it provides version *X* of oneAPI
specification element. The implementation may have its own independent
version number. Implementations need to have different version numbers
because they may be supersets of a element specification: they may
include extensions or other functionality not related to the
specification.

.. _`Semantic Versioning`: https://semver.org/
.. _`Semantic Versioning for Documents`: https://semverdoc.org/
  
