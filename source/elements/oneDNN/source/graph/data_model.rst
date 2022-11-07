.. SPDX-FileCopyrightText: 2020-2021 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. include:: ../replacements.inc.rst

==========
Data Model
==========

oneDNN Graph uses logical tensor to describe data type, shape, and layout.
Besides 32-bit IEEE single-precision floating-point data type, oneDNN Graph can
also support other data types. The shape contains multiple dimensions, and the
total dimension and the size of the dimension could be set as unknown.

oneDNN Graph uses the following enumeration to refer to data types it supports.
Different operation may support inputs and outputs with different data types, so
it's suggested to refer to the definition page of each operation.

.. rst-class:: enumlist

**enum** *dnnl::graph::logical_tensor::data_type*

    undef
        Undefined data type (used for empty logical tensor).
    f16
        `16-bit/half-precision floating point <https://en.wikipedia.org/wiki/Half-precision_floating-point_format>`__.
    bf16
        `non-standard 16-bit floating point with 7-bit mantissa <https://en.wikipedia.org/wiki/Bfloat16_floating-point_format>`__.
    
    f32
        `32-bit/single-precision floating point <https://en.wikipedia.org/wiki/Single-precision_floating-point_format>`__.

    s32
        32-bit signed integer.

    s8
        8-bit signed integer.
    
    u8
        8-bit unsigned integer.


oneDNN Graph supports both public layout and opaque layout. When the
|layout_type| of logical tensor is |strided|, it means that the tensor
layout is public which the user can identify each tensor element in the physical
memory.

For example, for :math:`dims[][][] = {x, y, z}`,
:math:`strides[][][] = {s0, s1, s2}`, the physical memory location should be in
:math:`s0*x+s1*y+s2*z`.

When the |layout_type| of logical tensor is |opaque|, users are not supposed
to interpret the memory buffer directly. An |opaque| tensor can only be output
from oneDNN Graph’s compiled partition and can only be fed to another compile
partition as an input tensor.
