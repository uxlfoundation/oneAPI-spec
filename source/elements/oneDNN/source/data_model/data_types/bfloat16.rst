..
  Copyright 2019-2020 Intel Corporation

.. default-domain:: cpp
.. cpp:namespace:: dnnl::memory::data_type

########
Bfloat16
########

Bfloat16 (:any:`bf16`) is a 16-bit floating point data type based on the IEEE
32-bit single-precision floating point data type (:any:`f32`).

Both :any:`bf16` and :any:`f32` have an 8-bit exponent. However, while
:any:`f32` has a 23-bit mantissa, :any:`bf16` has only a 7-bit one, keeping
only the most significant bits. As a result, while these data types support a
very close numerical range of values, :any:`bf16` has a significantly reduced
precision. Therefore, :any:`bf16` occupies a spot between :any:`f32` and the
IEEE 16-bit half-precision floating point data type, :any:`f16`.  Compared
directly to :any:`f16`, which has a 5-bit exponent and a 10-bit mantissa,
:any:`bf16` trades increased range for reduced precision.

.. image:: ../../_static/img_bf16_diagram.png
   :width: 600
   :alt: Diagram depicting the bit-wise layout of f32, bf16, and f16 floating point data types

More details of the bfloat16 data type can be found `here
<https://en.wikipedia.org/wiki/Bfloat16_floating-point_format>`__.

One of the advantages of using :any:`bf16` versus :any:`f32` is reduced memory
footprint and, hence, increased memory access throughput.

********
Workflow
********

The main difference between implementing training with the :any:`f32` data
type and with the :any:`bf16` data type is the way the weights updates are
treated. With the :any:`f32` data type, the weights gradients have the same
data type as the weights themselves. This is not necessarily the case with the
:any:`bf16` data type as oneDNN allows some flexibility here. For example, one
could maintain a master copy of all the weights, computing weights gradients
in :any:`f32` and converting the result to :any:`bf16` afterwards.

*******
Support
*******

Most of the primitives can support the :any:`bf16` data type for source and
weights tensors. Destination tensors can be specified to have either the
:any:`bf16` or :any:`f32` data type. The latter is intended for cases in which
the output is to be fed to operations that do not support bfloat16 or require
better precision.

.. vim: ts=3 sw=3 et spell spelllang=en
