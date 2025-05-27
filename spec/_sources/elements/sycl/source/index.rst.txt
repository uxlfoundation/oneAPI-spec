.. SPDX-FileCopyrightText: 2019-2022 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. _sycl-section:

====
SYCL
====

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

   ==================================================  ====================  ====================  ====================
   Extension                                           CPU                   GPU                   FPGA
   ==================================================  ====================  ====================  ====================
   `C-CXX-StandardLibrary`_                            Required              Required              Not required [#tmp]_
   `sycl_ext_oneapi_accessor_properties`_              Required              Required              Required
   `sycl_ext_oneapi_assert`_                           Required              Required              Required
   `sycl_ext_oneapi_backend_level_zero`_               Required [#lzero]_    Required [#lzero]_    Required [#lzero]_
   `sycl_ext_oneapi_default_context`_                  Required              Required              Required
   `sycl_ext_oneapi_discard_queue_events`_             Required              Required              Required
   `sycl_ext_oneapi_dot_accumulate`_                   Required              Required              Required
   `sycl_ext_oneapi_enqueue_barrier`_                  Required              Required              Required
   `sycl_ext_oneapi_filter_selector`_                  Required              Required              Required
   `sycl_ext_oneapi_local_memory`_                     Required              Required              Required
   `sycl_ext_oneapi_srgb`_                             Required              Required              Required
   `sycl_ext_oneapi_sub_group_mask`_                   Required              Required              Required
   `sycl_ext_oneapi_use_pinned_host_memory_property`_  Required              Required              Required
   `sycl_ext_oneapi_usm_device_read_only`_             Required              Required              Required
   `sycl_ext_intel_buffer_location`_                   Not required          Not required          Required
   `sycl_ext_intel_dataflow_pipes`_                    Not required          Not required          Required
   `sycl_ext_intel_device_info`_                       Required              Required              Required
   `sycl_ext_intel_fpga_device_selector`_              Required              Required              Required
   `sycl_ext_intel_fpga_lsu`_                          Not required          Not required          Required
   `sycl_ext_intel_fpga_reg`_                          Not required          Not required          Required
   `sycl_ext_intel_kernel_args_restrict`_              Required              Required              Required
   `sycl_ext_intel_mem_channel_property`_              Not required          Not required          Required
   `sycl_ext_intel_usm_address_spaces`_                Required              Required              Required
   ==================================================  ====================  ====================  ====================


.. _`C-CXX-StandardLibrary`: https://github.com/intel/llvm/blob/2022-06/sycl/doc/extensions/supported/C-CXX-StandardLibrary.rst
.. _`sycl_ext_oneapi_accessor_properties`: https://github.com/intel/llvm/blob/2022-06/sycl/doc/extensions/supported/sycl_ext_oneapi_accessor_properties.asciidoc
.. _`sycl_ext_oneapi_assert`: https://github.com/intel/llvm/blob/2022-06/sycl/doc/extensions/supported/sycl_ext_oneapi_assert.asciidoc
.. _`sycl_ext_oneapi_backend_level_zero`: https://github.com/intel/llvm/blob/2022-06/sycl/doc/extensions/supported/sycl_ext_oneapi_backend_level_zero.md
.. _`sycl_ext_oneapi_default_context`: https://github.com/intel/llvm/blob/2022-06/sycl/doc/extensions/supported/sycl_ext_oneapi_default_context.asciidoc
.. _`sycl_ext_oneapi_discard_queue_events`: https://github.com/intel/llvm/blob/2022-06/sycl/doc/extensions/supported/sycl_ext_oneapi_discard_queue_events.asciidoc
.. _`sycl_ext_oneapi_dot_accumulate`: https://github.com/intel/llvm/blob/2022-06/sycl/doc/extensions/supported/sycl_ext_oneapi_dot_accumulate.asciidoc
.. _`sycl_ext_oneapi_enqueue_barrier`: https://github.com/intel/llvm/blob/2022-06/sycl/doc/extensions/supported/sycl_ext_oneapi_enqueue_barrier.asciidoc
.. _`sycl_ext_oneapi_filter_selector`: https://github.com/intel/llvm/blob/2022-06/sycl/doc/extensions/supported/sycl_ext_oneapi_filter_selector.asciidoc
.. _`sycl_ext_oneapi_local_memory`: https://github.com/intel/llvm/blob/2022-06/sycl/doc/extensions/supported/sycl_ext_oneapi_local_memory.asciidoc
.. _`sycl_ext_oneapi_srgb`: https://github.com/intel/llvm/blob/2022-06/sycl/doc/extensions/supported/sycl_ext_oneapi_srgb.asciidoc
.. _`sycl_ext_oneapi_sub_group_mask`: https://github.com/intel/llvm/blob/2022-06/sycl/doc/extensions/supported/sycl_ext_oneapi_sub_group_mask.asciidoc
.. _`sycl_ext_oneapi_use_pinned_host_memory_property`: https://github.com/intel/llvm/blob/2022-06/sycl/doc/extensions/supported/sycl_ext_oneapi_use_pinned_host_memory_property.asciidoc
.. _`sycl_ext_oneapi_usm_device_read_only`: https://github.com/intel/llvm/blob/2022-06/sycl/doc/extensions/supported/sycl_ext_oneapi_usm_device_read_only.asciidoc
.. _`sycl_ext_intel_buffer_location`: https://github.com/intel/llvm/blob/2022-06/sycl/doc/extensions/supported/sycl_ext_intel_buffer_location.asciidoc
.. _`sycl_ext_intel_dataflow_pipes`: https://github.com/intel/llvm/blob/2022-06/sycl/doc/extensions/supported/sycl_ext_intel_dataflow_pipes.asciidoc
.. _`sycl_ext_intel_device_info`: https://github.com/intel/llvm/blob/2022-06/sycl/doc/extensions/supported/sycl_ext_intel_device_info.md
.. _`sycl_ext_intel_fpga_device_selector`: https://github.com/intel/llvm/blob/2022-06/sycl/doc/extensions/supported/sycl_ext_intel_fpga_device_selector.md
.. _`sycl_ext_intel_fpga_lsu`: https://github.com/intel/llvm/blob/2022-06/sycl/doc/extensions/supported/sycl_ext_intel_fpga_lsu.md
.. _`sycl_ext_intel_fpga_reg`: https://github.com/intel/llvm/blob/2022-06/sycl/doc/extensions/supported/sycl_ext_intel_fpga_reg.md
.. _`sycl_ext_intel_kernel_args_restrict`: https://github.com/intel/llvm/blob/2022-06/sycl/doc/extensions/supported/sycl_ext_intel_kernel_args_restrict.asciidoc
.. _`sycl_ext_intel_mem_channel_property`: https://github.com/intel/llvm/blob/2022-06/sycl/doc/extensions/supported/sycl_ext_intel_mem_channel_property.asciidoc
.. _`sycl_ext_intel_usm_address_spaces`: https://github.com/intel/llvm/blob/2022-06/sycl/doc/extensions/supported/sycl_ext_intel_usm_address_spaces.asciidoc


.. [#tmp] Likely to be required in the future
.. [#lzero] Required if the device backend is Level Zero.


.. _`SYCL 2020 Specification`: https://www.khronos.org/registry/SYCL/specs/sycl-2020/html/sycl-2020.html
