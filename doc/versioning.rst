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

oneAPI specification is primarily a description of APIs which are
closely related to features/functionality of the components. The
primary goal of versioning will be an indication of major new
functionality added, especially if the functionality impacts multiple
components. An example would be adding support for USM, or some other
new DPC++ feature that impacted multiple components.

A secondary goal is to communicate compatibility, similar to semantic
versioning. We expect incompatible changes to be less frequent and
less impactful than major functionality changes and will likely
coordinate these type of changes with major feature/functionality
changes.

Version Structure
=================

A summary is included below and based on `Semantic Versioning`_. Rule
1 is augmented to include major functionality additions. Rule 3 is
augmented with the definition from `Semantic Versioning for
Documents`_.

  Given a version number MAJOR.MINOR.PATCH, increment the:

  1. MAJOR version when adding major new functionality and making
     incompatible API changes.
     
  2. MINOR version when you add minor functionality. API changes are
     backwards compatible.
     
  3. PATCH version when you make backwards compatible bug fixes or any
     editing change in the document, including minor changes such as
     typos.

  Additional labels for pre-release and build metadata are available
  as extensions to the MAJOR.MINOR.PATCH format.

Determining Overall Specification Versioning
============================================

A release of the overall specification contains a specific set of
version numbers of elements. If any element increases its minor
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
| oneVPL 1.0

oneMKL adds some API's, oneDAL does not change:

| oneAPI 1.1
| oneMKL 1.1
| oneDAL 1.0
| oneVPL 1.0

oneDAL adds API's, oneMKL does not change:

| oneAPI 1.2
| oneMKL 1.1
| oneDAL 1.1
| oneVPL 1.0

Major platform feature added, MKL & DAL need to add support, VPL does
not:

| oneAPI 2.0
| oneMKL 2.0
| oneDAL 2.0
| oneVPL 1.0


Relationship of Implementation and Specification Versions
=========================================================

An implementation may indicate that it provides version *X* of oneAPI
specification element. An implementation may also indicate that it
provides version *Y* of overall oneAPI, but it is expected that in
most cases it will not unnecessary to use both.

An implementation may have its own independent version number that is
different from the specification. Implementations need to have
different version numbers because they may be supersets of a element
specification: they may include extensions or other functionality not
related to the specification.

Elements will in general refer the ele

.. _`Semantic Versioning`: https://semver.org/
.. _`Semantic Versioning for Documents`: https://semverdoc.org/
  
