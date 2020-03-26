..
  Copyright 2019-2020 Intel Corporation

.. _onedpcpp-section:

=========================
|dpcpp_full_name| (DPC++)
=========================

Overview
--------

DPC++ is the direct programming language and associated direct
programming APIs of oneAPI.  It provides the features
needed to define data parallel functions and to launch them on 
devices.  The language is comprised of the following components:

- C++.  Every DPC++ program is also a C++ program.  A
  compliant DPC++ implementation must support the C++17 Core Language
  (as specified in Sections 1-19 of ISO/IEC 14882:2017) or
  newer.  See the `C++ Standard`_.

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

This specification requires a minimum of C++17 Core Language support, SYCL 1.2.1, and 
DPC++ extensions. These version and feature coverage requirements
will evolve over time, with newer versions of C++ and SYCL being required, 
some additional extensions being required, and some DPC++ extensions no longer
required if covered by newer C++ or SYCL versions directly.

.. table:: DPC++ Extensions Table: Support requirements for DPC++
           implementations supporting specific classes of devices
   :name: Extensions Table

   =======================    ================  ================  ====================  =============  =========================
   Extension                  CPU               GPU               FPGA                  Test [#test]_  `SYCL Extensions`_ folder
   =======================    ================  ================  ====================  =============  =========================
   Unified Shared Memory      Required [#USM]_  Required [#USM]_  Required [#USM]_      USM            USM
   In-order queues            Required          Required          Required              NA [#na]_      OrderedQueue
   Optional lambda name       Required          Required          Required              NA [#na]_      UnnamedKernelLambda
   Deduction guides           Required          Required          Required              NA [#na]_      deduction_guides
   Reductions                 Required          Required          Required              NA [#na]_      Reduction
   Sub-groups                 Required          Required          Not required [#tmp]_  sub_group      SubGroup
   Sub-group algorithms       Required          Required          Not required [#tmp]_  sub_group      SubGroupAlgorithms
   Enqueued barriers          Required          Required          Required              NA             EnqueueBarrier
   Extended atomics           Required          Required          Required              NA             ExtendedAtomics
   Group algorithms           Required          Required          Required              NA             GroupAlgorithms
   Group mask                 Required          Required          Required              NA             GroupMask
   Restrict all arguments     Required          Required          Required              NA             KernelRestrictAll
   Standard layout relaxed    Required          Required          Required              NA             RelaxStdLayout
   Queue shortcuts            Required          Required          Required              NA             QueueShortcuts
   Required work-group size   Required          Required          Required              NA             ReqdWorkGroupSize
   Data flow pipes            Not required      Not required      Required              FPGA_tests     DataFlowPipes
   =======================   ================  ================  ====================  =============   =========================

.. [#test] Test directory within `extension tests`_
.. [#USM] Minimum of explicit USM support
.. [#na] Not yet available.
.. [#tmp] Likely to be required in the future

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
   desired, such as when debugging or interfacing with a sycl::program object.
-  Deduction guides - simplifies common code patterns and reduces code length and verbosity by enabling
   Class Template Argument Deduction (CTAD) from modern C++.
-  Reductions - provides a reduction abstraction to the ND-range form of *parallel_for*.  Improves productivity
   by providing the common reduction pattern without explicit coding, and enables optimized
   implementations to exist for combinations of device, runtime, and reduction properties.
-  Subgroups - defines a grouping of work-items within a work-group. Synchronization
   of work-items in a subgroup can occur independently of work-items in other subgroups, and
   subgroups expose communication operations across work-items in the group.  Subgroups commonly
   map to SIMD hardware where it exists.
-  Subgroup algorithms - defines collective operations across work-items in a sub-group that are available
   only for sub-groups.  Also enables algorithms from the more generic "group algorithms" extension as sub-group
   collective operations.
-  Enqueued barriers - simplifies dependence creation and tracking for some common programming patterns by allowing
   coarser grained synchronization within a queue without manual creation of fine grained dependencies.
-  Extended atomics - provides atomic operations aligned with C++20, including support for floating-point types and
   shorthand operators
-  Group algorithms - defines collective operations that operate across groups of work-items, including broadcast,
   reduce, and scan.  Improves productivity by providing common algorithms without explicit coding, and enables optimized
   implementations to exist for combinations of device and runtime.
-  Group mask - defines a type that can represent a set of work-items from a group, and collective operations that create
   or operate on that type such as ballot and count.
-  Restrict all arguments - defines an attribute that can be applied to kernels (including lambda definitions of kernels)
   which signals that there will be no memory aliasing between any pointer arguments that are passed to or captured
   by a kernel.  This is an optimization attribute that can have large impact when the developer knows more about the
   kernel arguments than a compiler can infer or safely assume.
-  Standard layout relaxed - removes the requirement that data shared by a host and device(s) must be C++ standard layout
   types.  Requires device compilers to validate layout compatibility.
-  Queue shortcuts - defines kernel invocation functions directly on the queue classes, to simplify code patterns
   where dependencies and/or accessors do not need to be created within the additional command group scope.  Reduces
   code verbosity in some common patterns.
-  Required work-group size - defines an attribute that can be applied to kernels (including lambda definitions of kernels)
   which signals that the kernel will only be invoked with a specific work-group size.  This is an optimization attribute
   that enables optimizations based on additional user-driven information.
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
