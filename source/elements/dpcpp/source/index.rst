..
  Copyright 2019 Intel Corporation

.. _onedpcpp-section:

=========================
|dpcpp_full_name| (DPC++)
=========================

Overview
--------

DPC++ is the language of oneAPI.  It provides the features
needed to define data parallel functions and to launch them on 
devices.  The language is comprised of the following components:

- C++.  Every DPC++ program is also a C++ program.  A
  compliant DPC++ implementation must support C++11 or
  later.  See the `C++ Standard`_.

- SYCL.  DPC++ includes the SYCL language. SYCL enables
  the definition of data parallel functions that can be offloaded to
  devices and defines runtime APIs and classes that are used to
  orchestrate the offloaded functions.  A compliant DPC++
  implementation must also be a conformant SYCL 1.2.1 (or later)
  implementation, a process which includes Khronos* conformance testing
  and an adopter process.  (See the `SYCL Specification`_ and `SYCL
  Adopters`_.)

- DPC++ Language extensions. A compliant DPC++ implementation must
  support the specified language features.  These include
  unified shared memory (USM), ordered queues, and reductions. Some
  extensions are required only when the DPC++
  implementation supports a specific class of device, as summarized in the
  `Extensions Table`_. An implementation supports a class of device if
  it can target hardware that responds “true” for a DPC++
  device type query, either through explicit support built into the
  implementation, or by using a lower layer that can support those
  device classes such as the oneAPI Level Zero 
  (Level Zero).  A DPC++ implementation must pass the 
  conformance tests for all extensions that are required (`Extensions
  Table`_) for the classes of devices that the implementation can
  support.  (See `SYCL Extensions`_.)

This specification requires a minimum of C++11, SYCL 1.2.1, and 
DPC++ language features. These version and feature coverage requirements
will evolve over time, with newer versions of C++ and SYCL being required, 
some additional extensions being required, and some language features no longer
required if covered by newer C++ or SYCL versions directly.

.. table:: DPC++ Extensions Table: Support requirements for DPC++
           implementations supporting specific classes of devices
   :name: Extensions Table

   =====================   ================  ================  ================  =============
   Extension               CPU               GPU               FPGA              Test [#test]_
   =====================   ================  ================  ================  =============
   USM                     Required [#usm]_  Required [#usm]_  Required [#usm]_  usm
   In-order queues         Required          Required          Required          NA [#na]_
   Optional lambda name    Required          Required          Required          NA [#na]_
   Reduction               Required          Required          Required          NA [#na]_
   Subgroups               Required          Required          Not required      sub_group
   Data flow pipes         Not required      Not required      Required          fpga_tests
   =====================   ================  ================  ================  =============

.. [#test] Test directory within `extension tests`_
.. [#usm] Minimum explicit USM support
.. [#na] Not yet available.

Detailed API and Language Descriptions
--------------------------------------

The `SYCL Specification`_ describes the SYCL APIs and language.  DPC++ extensions on top of SYCL
are described in the `SYCL Extensions`_ repository.

A brief summary of the extensions is as follows:

-  Unified Shared Memory (USM) - defines pointer based memory accesses and management interfaces. Provides
   the ability to create allocations that are visible and have consistent pointer values across both
   host and device(s).  Different USM capability levels are defined, corresponding to different levels
   of device and implementation support.
-  In-order queues - defines simple in-order semantics for queues, to simplify common coding patterns.  Adds
   the *ordered_queue* class.
-  Optional lambda name - removes requirement to manually name lambdas that define kernels.
   Simplifies coding and enables composability with libraries.  Lambdas can still be manually named, if
   desired, such as when debugging.
-  Reduction -  provides a reduction abstraction to the ND-range form of *parallel_for*.  Improves productivity
   by providing the common reduction pattern without explicit coding, and enables optimized
   implementations to exist for combinations of device, runtime, and reduction properties.
-  Subgroups - defines a grouping of work-items within a work-group. Synchronization
   of work-items in a subgroup can occur independently of work-items in other subgroups, and
   subgroups expose communication operations across work-items in the group.  Subgroups commonly
   map to SIMD hardware where it exists.
-  Data flow pipes - enables efficient First-In, First-Out (FIFO) communication in DPC++, a mechanism commonly
   used when describing algorithms for spatial architectures such as FPGAs. 

Open Source Implementation
--------------------------

An `open source implementation`_ is available under
an LLVM license.  Details on incomplete features and known issues are
available in the `Release Notes`_ (and the `Getting Started Guide`_
until the release notes are available).

Testing
-------

A DPC++ implementation must pass:

  1. The Khronos SYCL 1.2.1 `conformance test suite`_ (SYCL-1.2.1/master branch).
  2. The `extension tests`_ for any extension implemented from the `Extensions Table`_.
     Each extension in the `Extensions Table`_ lists the name of the directory that contains
     corresponding tests, within the `extension tests`_ tree.

.. _`C++ Standard`: https://isocpp.org/std/the-standard
.. _`SYCL Specification`: https://www.khronos.org/registry/SYCL/specs/sycl-1.2.1.pdf
.. _`SYCL Adopters`: https://www.khronos.org/sycl/adopters/
.. _`SYCL Extensions`: https://github.com/intel/llvm/tree/sycl/sycl/doc/extensions
.. _`open source implementation`: https://github.com/intel/llvm/tree/sycl/
.. _`conformance test suite`: https://github.com/KhronosGroup/SYCL-CTS
.. _`extension tests`: https://github.com/intel/llvm/tree/sycl/sycl/test
.. _`Release Notes`: https://github.com/intel/llvm/tree/sycl/sycl/ReleaseNotes.md
.. _`Getting Started Guide`: https://github.com/intel/llvm/blob/sycl/sycl/doc/GetStartedWithSYCLCompiler.md#known-issues-and-limitations
.. _`joining the Khronos Group`: https://www.khronos.org/members/
.. _`Khronos SYCL GitHub project`: https://github.com/KhronosGroup/SYCL-Docs
