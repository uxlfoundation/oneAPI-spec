========================
Specification versioning
========================

This document describes the versioning of the specification for oneAPI
and its components. It is independent of oneAPI product versioning.

Component versioning
====================

Versioning will be MAJOR.MINOR rev REVISION

Increment the:

  1. MAJOR version when adding major new functionality and making
     incompatible API changes.
     
  2. MINOR version when you add minor functionality. API changes are
     backwards compatible.
     
  3. REVISION when you make backwards compatible bug fixes or any
     editing change in the document, including minor changes such as
     typos.

Overall spec versioning
=======================

Versioning will be MAJOR.MINOR rev REVISION

Increment the:

  1. MAJOR version when adding major new functionality
     
  2. MINOR version for all other functionality changes
     
  3. REVISION when you make backwards compatible bug fixes or any
     editing change in the document, including minor changes such as
     typos.

If MAJOR.MINOR changes for any element, then MAJOR.MINOR for overall
spec changes. MAJOR is used for large changes across multiple
components. MAJOR change to an element may only be a MINOR change in
the overall spec.

Examples
========

Sequence of releases.

Initial

| oneAPI 1.0 rev 1
| oneMKL 1.0 rev 1
| oneDAL 1.0 rev 1
| oneVPL 1.0 rev 1

Some components make editing changes

| oneAPI 1.0 rev 2
| oneMKL 1.0 rev 2
| oneDAL 1.0 rev 1
| oneVPL 1.0 rev 1

DAL goes to 1.1

| oneAPI 1.1 rev 1
| oneMKL 1.0 rev 2
| oneDAL 1.1 rev 1
| oneVPL 1.0 rev 1

VPL goes to 2.0, oneAPI to 1.2

| oneAPI 1.2 rev 1
| oneMKL 1.0 rev 2
| oneDAL 1.1 rev 1
| oneVPL 2.0 rev 1

Major change impacts multiple elements. oneAPI goes to 2.0

| oneAPI 2.0 rev 1
| oneMKL 1.0 rev 2
| oneDAL 2.0 rev 1
| oneVPL 3.0 rev 1

Provisional versions
====================

A specification version becomes final when it is approved. Before
approval a specification version must be labeled provisional when
published.  A provision spec will have a series of revisions until
approval.  Implementations may provide features in provisional
specifications before approval.

| oneMKL 1.1 provisional rev 1
| oneMKL 1.1 provisional rev 2
| oneMKL 1.1 provisional rev 3
| oneMKL 1.1 rev 1

Specification version approval
==============================

Element specifications must be approved by its core team as well as
oneAPI spec core team. Overall spec requires approval of its core
team. Leads can approve updates which only change the revision.
