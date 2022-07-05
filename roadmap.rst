.. SPDX-FileCopyrightText: 2019-2020 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

=========
 Roadmap
=========

1.2 Schedule
============

=====================  ==========  ===========
Version                Date        Notes
=====================  ==========  ===========
1.2-provisional-rev-1  2022-09-08
1.2-rev-1              2022-11-10
=====================  ==========  ===========

Details
-------

1.2-provisional-rev-1
+++++++++++++++++++++

==========  ================
Date        Milestone
==========  ================
2022-09-06  Component freeze
2022-09-08  Release
==========  ================

1.2-rev-1
+++++++++

==========  ================
Date        Milestone
==========  ================
2022-09-22  Feedback cutoff
2022-10-20  Complete, final review
2022-11-03  Cutoff for all edits
2022-11-10  Release
==========  ================


1.1 Schedule
============

=====================  ==========  ===========
Version                Date        Notes
=====================  ==========  ===========
1.1-provisional-rev-1  2021-03-25
1.1-provisional-rev-2  2021-06-24
1.1-provisional-rev-3  2021-09-21
1.1-rev-1              2021-11-12
=====================  ==========  ===========


Details:
========

1.1-provisional-rev-1
---------------------

==========  ================
Date        Milestone
==========  ================
2021-03-23  Component freeze
2021-03-25  Release
==========  ================


1.1-provisional-rev-2
---------------------

==========  ================
Date        Milestone
==========  ================
2021-06-22  Component freeze
2021-06-24  Release
==========  ================


1.1-provisional-rev-3
---------------------

==========  ================
Date        Milestone
==========  ================
2021-09-23  Component freeze
2021-09-21  Release
==========  ================


1.1-rev-1
---------

==========  ================
Date        Milestone
==========  ================
2021-09-24  Feedback cutoff
2021-10-22  Complete, final review
2021-11-05  Cutoff for all edits
2021-11-12  Release
==========  ================


1.0 Schedule
============

========   ==========  ===========
Version    Date        Notes
========   ==========  ===========
0.5.0      11/17/2019  First Public Release
0.6.0_     01/30/2020  Open source Release
0.7.0_     03/26/2020  50% content
0.8.0_     05/28/2020  80% content
0.8.5_     06/26/2020  85% content
0.9.0_     07/30/2020  Final Gold Preview
1.0.0_     10/29/2020  Gold Release
========   ==========  ===========

Details:
========


0.6.0
-----

We will publish:

- HTML and PDF on spec.oneapi.org
- Sources in github

No public announcement until we can ensure we are addressing earlier
feedback.

- Overall

  - New

    - Unified into single doc
    - PDF of unified doc available online
    - Sources in github.com/oneapi-src/oneapi-spec
    - HTML doc links back to github
    - CI builds and publishes on commits to master
- DPC++

  - New

    - Editing updates

  - Future

- oneDPL

  - New

    - Editing updates
  - Future
- oneDNN

  - New

    - API document inline
    - API document sources in oneapi-spec repo
  - Future

    - more structured API description
- oneCCL

  - New

    - API document inline
    - API document sources in oneapi-spec repo
- Level Zero

  - New

    - API document inline
    - Sources in separate repo on github
  - Future
- oneDAL

  - New
  - Future

    - API document included inline
    - API document sources in oneapi-spec repo
- oneTBB

  - New

    - API document inline
    - Sources in separate repo on github
  - Future
- oneVPL

  - New

    - API descriptions moved to single section
  - Future

    - Content?
- oneMKL

  - New
  - Future

    - Transition from far html to rst
    - API document inline
    - rst sources included in oneapi-spec repo

0.7.0
-----

Summary
+++++++

50% content.

Schedule
++++++++

=========  ==========
Date       Milestone
=========  ==========
3/12/2020  Cutoff date for accepting feedback for inclusion in this version
3/24/2020  Code freeze
3/26/2020  Release
=========  ==========

- Overall

  - All documents inline, no tarballs
  - Built from source from single repo
  - CI moved to public infrastructure, internal fork with CI for testing

- DPC++

  - Updated extensions table and description
  - TODO: more specific about extensions

- oneDPL

  - Rework the section for execution policies and buffer wrappers
  - Add API descriptions for oneDPL specific algorithms
  - Add API descriptions for iterator and functor classes

- oneDNN

  - API's 95% complete
  - Rework API presentation into multiple sections
  - Add introduction, execution, primitive lifecycle, and programming model
    sections

- Level Zero

  - Switched to RST as format, using oneapi-spec as upstream repo

- oneDAL

  - Add overall spec skeleton, introduction and algorithm classes
    sections
  - Add initial version for sections on data structures (descriptors
    algorithms/tables, numeric tables), compute modes(batch/online),
    distributed algorithms and generic building blocks(train/predict)
  - Add API for 3 oneDAL algorithms

- oneTBB

  - Integrate sources to the oneapi-spec repository
  - Rework sections for general information, memory allocation,
    synchronization, and timing

- oneVPL

  - 80% content

- oneMKL

  - USM support
  - Skeleton of spec, breadown by domain
  - Sections that apply to all domains
  - subset of domains with high-level description and APIs, as
    determined by open source schedule

0.8.0
-----

Summary
+++++++

80% content. All document structuring issues resolved. Content mostly
complete with placeholders for missing sections.

Schedule
++++++++

=========  ==========
Date       Milestone
=========  ==========
5/14/2020  Cutoff date for accepting feedback for inclusion in this version
5/26/2020  Code freeze
5/28/2020  Release
=========  ==========

- DPC++

  - Updated extensions table and description
  - TODO: more specific about extensions

- oneDPL

  - Specify USM support
  - Specify range-based API to the algorithms

- oneDNN

  - Add sections on primitive attributes, data types, and memory formats
  - Start extending individual primitives' pages with detailed information
    about underlying math and with usage examples

- oneCCL

  - Add page with API for multi-GPU
  - Add page with multi-GPU programming model
  - Extend page with collective operations

- Level Zero

  - Command queue groups, module linking, extensions, and improved
    profiling support

- oneDAL

  - Extend API description to kNN classification
  - Add first version for sections on error handling, namespaces,
    terminology, math notations
  - Extend numeric tables and data structure sections

- oneTBB

  - Rework sections for algorithms, flow graph, thread local storage

- oneVPL

  - Updates deferred to 0.8.5_

- oneMKL

  - All domains complete
  - Finalized BLAS, LAPACK domains
  - Draft suitable for review so we can distribute to reviewers before
    ISC (6/28/2020).

0.8.5
-----

Summary
+++++++

- oneVPL

  - Breaking changes introduced.

=========  ==========
Date       Milestone
=========  ==========
6/25/2020  All components have merged to master
6/26/2020  Release
=========  ==========

0.9.0
-----

Summary
+++++++

Final Gold Preview. Expectation is that everything is done and only
small edits will be made. Incorporates all external feedback.

Schedule
++++++++

=========  ==========
Date       Milestone
=========  ==========
7/16/2020  Cutoff date for accepting feedback for inclusion in this version
7/28/2020  Code freeze
7/30/2020  Release
=========  ==========

Elements
++++++++

- DPC++

  - Updated extensions table and description
  - TODO: more specific about extensions

- oneDPL

  - Specify C++ standard library APIs (or analogues) supported in DPC++ kernels
  - Specify all remaining and late-added extension APIs
  - Integrate all known feedback

- oneDNN

  - Finish extending individual primitives' pages with detailed information
    about underlying math and with usage examples
  - explanation of principles complete

- oneCCL

  - Finalize on sections content and details

- Level Zero

  - 1.0 release, support for OpenCL interoperability

- oneDAL

  - Extend algorithms section to cover Random Forest, K-Means, SVM,
    PCA algorithms
  - Finalize on sections content and details

- oneTBB

  - Rework sections for containers, task scheduler controls, exceptions
  - Integrate all known feedback

- oneVPL

- oneMKL

  - finalize FFT, sparse BLAS, RNG, and VM domains

1.0.0
-----

Summary
+++++++

API's frozen: backwards compatible changes at discretion of project
owner, non-backwards compatible change by exception only

Schedule
++++++++

==========  ==========
Date        Milestone
==========  ==========
10/27/2020  Code freeze
10/29/2020  Release
==========  ==========

- Overall

  - Minor cleanup and integration of remaining feedback if any
