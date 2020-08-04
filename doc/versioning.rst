========================
Specification versioning
========================

This document describes the versioning of the specification for oneAPI
elements (e.g. oneMKL, oneVPL) and for oneAPI, which includes all the
elements. Specification versioning is independent of oneAPI product
versioning.

Element versioning
==================

Versioning is MAJOR.MINOR rev REVISION

Increment the:

1. MAJOR version when adding major new functionality and making
   incompatible API changes.
     
2. MINOR version when adding minor functionality and API changes
   that are backwards compatible.
     
3. REVISION when making backwards compatible bug fixes or any
   editing change in the document, including minor changes such as
   typos. Initial REVISION is 1.

The distinction between major and minor functionality is determined by
the core group. When a component identifies the version it implements
for purposes of compatibility, it lists MAJOR.MINOR. Latest REVISION
is implicit because REVISIONs do not change the meaning.

oneAPI specification versioning
===============================

Versioning is MAJOR.MINOR rev REVISION following `element versioning`_.

If MAJOR.MINOR changes for any element, the new element specification
must be incorporated into a future version of the oneAPI specification
that also changes either MAJOR or MINOR. The core group determines the
distinction between major and minor functionality. Major is reserved
for signficant changes in multiple components, especially when a
oneAPI feature requires coordinated changes to multiple
components. Breaking changes in an element are coordinated with the
oneAPI specification.


Examples
========

Example sequence of releases.

Initial
  | oneAPI 1.0 rev 1
  | oneMKL 1.0 rev 1
  | oneDAL 1.0 rev 1
  | oneVPL 1.0 rev 1


Some components make editing changes. Only the rev changes.
  | oneAPI 1.0 rev 2
  | oneMKL 1.0 rev 2
  | oneDAL 1.0 rev 1
  | oneVPL 1.0 rev 1

  
DAL goes to 1.1. oneAPI goes to 1.1.
  | oneAPI 1.1 rev 1
  | oneMKL 1.0 rev 2
  | oneDAL 1.1 rev 1
  | oneVPL 1.0 rev 1


VPL goes to 2.0, oneAPI goes to 1.2.
  | oneAPI 1.2 rev 1
  | oneMKL 1.0 rev 2
  | oneDAL 1.1 rev 1
  | oneVPL 2.0 rev 1


Major change impacts multiple elements. oneAPI goes to 2.0
  | oneAPI 2.0 rev 1
  | oneMKL 1.0 rev 2
  | oneDAL 2.0 rev 1
  | oneVPL 3.0 rev 1

Specification version approval
==============================

Element specifications must be approved by its core team and the
oneAPI spec core team. The oneAPI specification must be approved by
its core team. Updates which only change the revision may be approved
by the lead.

Provisional versions
====================

A specification may be published before approval, but must be labeled
provisional.  Provisional specifications are published as a series of
revisions until approval. After approval, the provisional label is
removed and the rev is set to 1.

Example
  | oneMKL provisional 1.1 rev 1
  | oneMKL provisional 1.1 rev 2
  | oneMKL provisional 1.1 rev 3
  | oneMKL 1.1 rev 1

