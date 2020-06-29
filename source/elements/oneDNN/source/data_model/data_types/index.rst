..
  Copyright 2019-2020 Intel Corporation

.. default-domain:: cpp

.. _data_types-label:

##########
Data types
##########

.. namespace:: dnnl::memory::data_type

oneDNN supports multiple data types. However, the 32-bit IEEE floating-point
data type (:any:`f32`) is the fundamental type in oneDNN. It
is the only data type that must be supported by an implementation. All the
other types discussed below are optional.

Primitives operating on the :any:`f32` data type consume data, produce, and
store intermediate results in the :any:`f32` data type.

Moreover, the :any:`f32` data type is often used for intermediate results in
the mixed precision computations because it provides better accuracy. For
example, the elementwise primitive and elementwise post-ops always use
:any:`f32` internally.

..
   =================== ================================================================================================================================================================================
   Data type           Description
   =================== ================================================================================================================================================================================
   :any:`f32`          `IEEE single precision floating point <https://en.wikipedia.org/wiki/Single-precision_floating-point_format#IEEE_754_single-precision_binary_floating-point_format:_binary32>`__
   :any:`bf16`         `non-IEEE 16-bit floating point <https://software.intel.com/en-us/download/bfloat16-hardware-numerics-definition>`__
   :any:`f16`          `IEEE half precision floating point <https://en.wikipedia.org/wiki/Half-precision_floating-point_format#IEEE_754_half-precision_binary_floating-point_format:_binary16>`__
   :any:`s8`/:any:`u8` signed/unsigned 8-bit integer
   =================== ================================================================================================================================================================================

oneDNN defines the following data types:

.. namespace:: 0

.. doxygenenum:: dnnl::memory::data_type
   :project: oneDNN

.. namespace:: dnnl::memory::data_type

oneDNN supports training and inference with the following data types:

========== ========================================================
Usage mode Data types
========== ========================================================
Inference  :any:`f32`, :any:`bf16`, :any:`f16`, :any:`s8`/:any:`u8`
Training   :any:`f32`, :any:`bf16`
========== ========================================================

.. note::

   Using lower precision arithmetic may require changes in the deep learning
   model implementation.

Individual primitives may have additional limitations with respect to data
type support based on the precision requirements. The list of data types
supported by each primitive is included in the corresponding sections of the
specification guide.

.. toctree::
   :maxdepth: 1

   bfloat16.rst
   int8.rst

.. vim: ts=3 sw=3 et spell spelllang=en
