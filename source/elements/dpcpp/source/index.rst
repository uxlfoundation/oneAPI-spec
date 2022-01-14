.. SPDX-FileCopyrightText: 2019-2022 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. _onedpcpp-section:

=====
DPC++
=====

Overview
--------

Data Parallel C++ (DPC++) is an LLVM project to implement SYCL that provides direct programming
capabilities for C++ programmers, and oneAPI libraries such as oneMKL.  It provides the
features needed to define data parallel functions and to launch them
on devices.  DPC++ is made up of the following components:

- C++.  Every DPC++ program is also a C++ program.  A
  compliant DPC++ implementation must support the C++17 Core Language
  (as specified in Sections 1-19 of ISO/IEC 14882:2017) or
  newer.  See the `C++ Standard`_.

- SYCL.  DPC++ builds on the SYCL specification from The Khronos Group.
  The SYCL language enables
  the definition of data parallel functions that can be offloaded to
  devices and defines runtime APIs and classes that are used to
  orchestrate the offloaded functions.

- DPC++ Language extensions. A compliant DPC++ implementation must
  support the specified language features.  Some
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

This specification requires a minimum of C++17 Core Language support and
DPC++ extensions. These version and feature coverage requirements
will evolve over time, with specific versions of C++ and SYCL being required,
some additional extensions being required, and some DPC++ extensions no longer
required if covered by newer C++ or SYCL versions directly.

.. table:: DPC++ Extensions Table: Support requirements for DPC++
           implementations above SYCL 2020
   :name: Extensions Table

   ===========================  ====================  ====================  ====================  =============
   Feature                      CPU                   GPU                   FPGA                  Test [#test]_
   ===========================  ====================  ====================  ====================  =============
   `Accessor properties`_       Required              Required              Required              NA [#na]_
   `CXX standard library`_      Required              Required              Not required [#tmp]_  NA [#na]_
   `Data flow pipes`_           Not required          Not required          Required              `fpga_tests <https://github.com/intel/llvm/tree/sycl/sycl/test/fpga_tests>`__
   `Enqueued barriers`_         Required              Required              Required              NA [#na]_
   `Extended atomics`_          Required              Required              Required              NA [#na]_
   `Filter selector`_           Required              Required              Required              NA [#na]_
   `FPGA LSU controls`_         Not required          Not required          Required              NA [#na]_
   `FPGA memory channel`_       Not required          Not required          Required              NA [#na]_
   `FPGA register`_             Not required          Not required          Required              NA [#na]_
   `FPGA selector`_             Required              Required              Required              NA [#na]_
   `GPU device info`_           Required              Required              Required              NA [#na]_
   `Level zero backend`_        Required [#lzero]_    Required [#lzero]_    Required [#lzero]_    NA [#na]_
   `Local memory allocations`_  Required              Required              Required              NA [#na]_
   `Pinned memory property`_    Required              Required              Required              NA [#na]_
   `Platform context`_          Required              Required              Required              NA [#na]_
   `Restrict all arguments`_    Required              Required              Required              NA [#na]_
   `Sub-group mask`_            Required              Required              Required              NA [#na]_
   ===========================  ====================  ====================  ====================  =============


..   ==========================  ================  ================  ====================  =============

.. _`Accessor properties`: https://github.com/intel/llvm/tree/sycl/sycl/doc/extensions/accessor_properties/SYCL_ONEAPI_accessor_properties.asciidoc
.. _`CXX standard library`: https://github.com/intel/llvm/tree/sycl/sycl/doc/extensions/C-CXX-StandardLibrary/C-CXX-StandardLibrary.rst
.. _`Data flow pipes`: https://github.com/intel/llvm/tree/sycl/sycl/doc/extensions/DataFlowPipes/data_flow_pipes.asciidoc
.. _`Enqueued barriers`: https://github.com/intel/llvm/tree/sycl/sycl/doc/extensions/EnqueueBarrier/enqueue_barrier.asciidoc
.. _`Extended atomics`: https://github.com/intel/llvm/blob/sycl/sycl/doc/extensions/ExtendedAtomics/SYCL_INTEL_extended_atomics.asciidoc
.. _`Filter selector`: https://github.com/intel/llvm/blob/sycl/sycl/doc/extensions/FilterSelector/FilterSelector.adoc
.. _`FPGA LSU controls`: https://github.com/intel/llvm/blob/sycl/sycl/doc/extensions/IntelFPGA/FPGALsu.md
.. _`FPGA memory channel`: https://github.com/intel/llvm/blob/sycl/sycl/doc/extensions/MemChannel/MemChannel.asciidoc
.. _`FPGA register`: https://github.com/intel/llvm/blob/sycl/sycl/doc/extensions/IntelFPGA/FPGAReg.md
.. _`FPGA selector`: https://github.com/intel/llvm/blob/sycl/sycl/doc/extensions/IntelFPGA/FPGASelector.md
.. _`GPU device info`: https://github.com/intel/llvm/blob/sycl/sycl/doc/extensions/IntelGPU/IntelGPUDeviceInfo.md
.. _`Level zero backend`: https://github.com/intel/llvm/blob/sycl/sycl/doc/extensions/LevelZeroBackend/LevelZeroBackend.md
.. _`Local memory allocations`: https://github.com/intel/llvm/blob/sycl/sycl/doc/extensions/LocalMemory/LocalMemory.asciidoc
.. _`Pinned memory property`: https://github.com/intel/llvm/blob/sycl/sycl/doc/extensions/UsePinnedMemoryProperty/UsePinnedMemoryPropery.adoc
.. _`Platform context`: https://github.com/intel/llvm/blob/sycl/sycl/doc/extensions/PlatformContext/PlatformContext.adoc
.. _`Restrict all arguments`: https://github.com/intel/llvm/tree/sycl/sycl/doc/extensions/KernelRestrictAll/SYCL_INTEL_kernel_restrict_all.asciidoc
.. _`Sub-group mask`: https://github.com/intel/llvm/blob/sycl/sycl/doc/extensions/SubGroupMask/SubGroupMask.asciidoc


.. [#test] Test directory within `extension tests`_
.. [#na] Not yet available.
.. [#tmp] Likely to be required in the future
.. [#lzero] Required if the device backend is Level Zero.


Detailed API and Language Descriptions
--------------------------------------

The `SYCL 2020 Specification`_ describes the SYCL APIs and language.  DPC++ extensions on top of SYCL
are described in the `SYCL Extensions`_ repository.

A brief summary of the extensions is as follows:

-  Accessor properties - compile-time accessor properties that are visible to the compiler.
-  CXX standard library - enable subset of the C and C++ standard libraries in device code.
-  Data flow pipes - enable efficient First-In, First-Out (FIFO) communication in DPC++, a mechanism commonly
   used when describing algorithms for spatial architectures such as FPGAs. 
-  Enqueued barriers - simplifies dependence creation and tracking for some common programming patterns by allowing
   coarser grained synchronization within a queue without manual creation of fine grained dependencies.
-  Extended atomics - adds *atomic_accessor* on top of SYCL 2020 atomics.
-  Filter selector - adds a device selector which consumes a string of filter definitions, and that can be used to
   easily restrict the set of devices which are passed to the usual device selection mechanisms.
-  FPGA LSU controls - tuning controls for FPGA load/store operations.
-  FPGA memory channel - placement controls for data with external memory banks (e.g. DDR channel) for tuning
   FPGA designs.
-  FPGA register - tuning control for FPGA high performance pipelining.
-  FPGA selector - adds a set of device selectors that make it easy to acquire an FPGA hardware or emulation device.
-  GPU device info - adds GPU-specific queries around SIMD width, memory bandwidth, unique identifiers, and
   topology of the compute structures.
-  Level zero backend - defines interoperability with Level Zero as a backend to SYCL.
-  Local memory allocations - adds ability for local memory allocations to be declared within a kernel, as opposed
   to through an accessor that is passed to a kernel.  Makes kernels more self contained and easier to read and optimize.
-  Pinned memory property - optimization indicating that a buffer should use a specific memory resource if possible,
   to accelerate movement of data between host and devices in some implementations.
-  Platform context - adds a default context per SYCL platform, which simplifies and improves performance in common
   coding patterns.
-  Restrict all arguments - defines an attribute that can be applied to kernels (including lambda definitions of kernels)
   which signals that there will be no memory aliasing between any pointer arguments that are passed to or captured
   by a kernel.  This is an optimization attribute that can have large impact when the developer knows more about the
   kernel arguments than a compiler can infer or safely assume.
-  Sub-group mask - adds a new opaque type and operations on it, which can be used to represent and manage sets of
   work-items within a sub-group.

Open Source Implementation
--------------------------

An `open source implementation`_ is available under
an LLVM license.  Details on incomplete features and known issues are
available in the `Release Notes`_ (and the `Getting Started Guide`_
until the release notes are available).

Testing
-------

A DPC++ implementation must pass the `extension tests`_ for any
extension implemented from the `Extensions Table`_.  Each extension in
the `Extensions Table`_ lists the name of the directory that contains
corresponding tests, within the `extension tests`_ tree.

Acknowledgment
---------------

We thank the DPC++ and oneDPL `Technical Advisory Board <https://github.com/oneapi-src/oneAPI-tab>`__ for their valuable feedback,
and the Khronos SYCL working group for their efforts defining and evolving the SYCL specification.


.. _`C++ Standard`: https://isocpp.org/std/the-standard
.. _`SYCL 2020 Specification`: https://www.khronos.org/registry/SYCL/specs/sycl-2020/html/sycl-2020.html
.. _`SYCL Extensions`: https://github.com/intel/llvm/tree/sycl/sycl/doc/extensions
.. _`open source implementation`: https://github.com/intel/llvm/tree/sycl/
.. _`conformance test suite`: https://github.com/KhronosGroup/SYCL-CTS
.. _`extension tests`: https://github.com/intel/llvm/tree/sycl/sycl/test
.. _`Release Notes`: https://github.com/intel/llvm/tree/sycl/sycl/ReleaseNotes.md
.. _`Getting Started Guide`: https://github.com/intel/llvm/blob/sycl/sycl/doc/GetStartedGuide.md#known-issues-and-limitations
.. _`joining the Khronos Group`: https://www.khronos.org/members/
.. _`Khronos SYCL GitHub project`: https://github.com/KhronosGroup/SYCL-Docs
