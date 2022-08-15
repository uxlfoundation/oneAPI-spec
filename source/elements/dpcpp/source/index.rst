.. SPDX-FileCopyrightText: 2019-2022 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. _onedpcpp-section:

=====
DPC++
=====

Overview
--------

The oneAPI programming language is a combination of SYCL and a set of SYCL
extensions that are listed below.  The SYCL programming language is based on
standard C++ and provides features to define data parallel functions and to
launch them on accelerator devices.  Unlike some other parallel languages, SYCL
allows an application to mix both host code and device code together in the
same source file, which provides a more intuitive parallel programming
environment.

A conformant oneAPI implementation must implement the
`SYCL 2020 Specification`_, which is published by The Khronos Group.

A conformant oneAPI implementation must also implement the set of SYCL
extensions listed in the `Extensions Table`_.  These extensions provide
additional functionality beyond what is specified in the SYCL language.  Some
of these extensions are required only on certain devices types, as indicated in
the table.

.. table:: Table of SYCL Extensions
   :name: Extensions Table

   ===========================  ====================  ====================  ====================
   Extension                    CPU                   GPU                   FPGA
   ===========================  ====================  ====================  ====================
   `Accessor properties`_       Required              Required              Required
   `CXX standard library`_      Required              Required              Not required [#tmp]_
   `Data flow pipes`_           Not required          Not required          Required
   `Enqueued barriers`_         Required              Required              Required
   `Extended atomics`_          Required              Required              Required
   `Filter selector`_           Required              Required              Required
   `FPGA LSU controls`_         Not required          Not required          Required
   `FPGA memory channel`_       Not required          Not required          Required
   `FPGA register`_             Not required          Not required          Required
   `FPGA selector`_             Required              Required              Required
   `GPU device info`_           Required              Required              Required
   `Level zero backend`_        Required [#lzero]_    Required [#lzero]_    Required [#lzero]_
   `Local memory allocations`_  Required              Required              Required
   `Pinned memory property`_    Required              Required              Required
   `Platform context`_          Required              Required              Required
   `Restrict all arguments`_    Required              Required              Required
   `Sub-group mask`_            Required              Required              Required
   ===========================  ====================  ====================  ====================


..   ==========================  ================  ================  ====================

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


.. [#tmp] Likely to be required in the future
.. [#lzero] Required if the device backend is Level Zero.


.. _`SYCL 2020 Specification`: https://www.khronos.org/registry/SYCL/specs/sycl-2020/html/sycl-2020.html
