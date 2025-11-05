.. SPDX-FileCopyrightText: 2020-2022 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. include:: ../../replacements.inc.rst


DynamicDequantize
#################

DynamicDequantize operation converts a quantized (s8 or u8) tensor to a
f32 tensor. It supports both per-tensor and per-channel asymmetric
linear de-quantization. Rounding mode is library-implementation defined.
Unlike the :ref:`op_dequantize-label`, DynamicDequantize takes scales
and zero-points as operator src tensors.

For per-tensor de-quantization

.. math::
   
   dst = (src - zps)*scales 

For per-channel de-quantization, taking channel axis = 1 as an example:

.. math::

   \dst_{\cdots,i,\cdots,\cdots} =
   (\src_{\cdots,i,\cdots,\cdots} - zps_i) * scales_i, i \in [0,channelNum-1] 

Operation Attributes
********************

+---------------+-----------------+------------+-----------------+-------------+
|   Attribute   |   Description   | Value Type |    Supported    | Required or |
|     Name      |                 |            |     Values      |  Optional   |
+===============+=================+============+=================+=============+
| |attr_qtype|  | Specifies       | string     | ``per_tensor``  | Optional    |
|               | which           |            | (default),      |             |
|               | de-quantization |            | ``per_channel`` |             |
|               | type is used    |            |                 |             |
+---------------+-----------------+------------+-----------------+-------------+
| |attr_axis|   | Specifies       | s64        | A s64 value     | Optional    |
|               | dimension       |            | in the          |             |
|               | on which        |            | range of        |             |
|               | per-channel     |            | [-r, r-1]       |             |
|               | de-quantization |            | where r =       |             |
|               | is applied      |            | rank(src),      |             |
|               |                 |            | ``1`` by        |             |
|               |                 |            | default         |             |
+---------------+-----------------+------------+-----------------+-------------+

Execution Arguments
*******************

The inputs and outputs must be provided according to the below index order
when constructing an operation.

Inputs
======


===== ============= ====================
Index Argument Name Required or Optional
===== ============= ====================
0     ``src``       Required
1     ``scales``    Required
2     ``zps``       Optional
===== ============= ====================

@note ``scales`` is a f32 1D tensor to be applied to the de-quantization
formula. For ``qtype`` = ``per-tensor``, there should be only one
element in the scales tensor. For ``qtype`` = ``per-channel``, the
element number should be equal to the element number of src tensor along
the dimension axis.

@note ``zps`` is a 1D tensor with offset values that map to zero. For
``qtype`` = ``per-tensor``, there should be only one element in the zps
tensor. For ``qtype`` = ``per-channel``, the element number should be
equal to the element number of input tensor along the dimension axis. If
not specified, the library can assume the operator is symmetric
de-quantization and perform kernel optimization accordingly.

Outputs
=======


===== ============= ====================
Index Argument Name Required or Optional
===== ============= ====================
0     ``dst``       Required
===== ============= ====================


Supported Data Types
********************

DynamicDequantize operation supports the following data type
combinations.

=== === ====== ===========
Src Dst Scales Zps
=== === ====== ===========
s8  f32 f32    s8, u8, s32
u8  f32 f32    s8, u8, s32
=== === ====== ===========
