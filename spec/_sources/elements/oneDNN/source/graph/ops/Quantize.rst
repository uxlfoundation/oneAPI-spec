.. SPDX-FileCopyrightText: 2020-2022 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. include:: ../../replacements.inc.rst

.. _op_quantize-label:

Quantize
########

Quantize operation converts a f32 tensor to a quantized (u8/s8) tensor.
It supports both per-tensor and per-channel asymmetric linear
quantization. Output data type is specified in output tensor data type.
Rounding mode is library-implementation defined.

For per-tensor quantization:

.. math::

   \dst_{i} = round(\src_{i} / scale + zp) 

For per-channel quantization, taking channel axis = 1 as an example:

.. math::

   \dst_{\cdots,i,\cdots,\cdots} =
       round(\src_{\cdots,i,\cdots,\cdots} / scale_i + zp_i),
       i \in {[0, ic-1]} 

where :math:`ic` is the number of channels.

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
| |attr_scales| | Scalings        | f32        | A f32 list      | Required    |
|               | applied on      |            | (only           |             |
|               | the src         |            | contain one     |             |
|               | data            |            | element if      |             |
|               |                 |            | qtype is        |             |
|               |                 |            | ``per_tensor``) |             |
+---------------+-----------------+------------+-----------------+-------------+
| |attr_zps|    | Offset          | s64        | A s64 list      | Required    |
|               | values that     |            | (only           |             |
|               | maps to         |            | contain one     |             |
|               | float zero      |            | element if      |             |
|               |                 |            | qtype is        |             |
|               |                 |            | ``per_tensor``) |             |
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
===== ============= ====================

Outputs
=======


===== ============= ====================
Index Argument Name Required or Optional
===== ============= ====================
0     ``dst``       Required
===== ============= ====================


Supported Data Types
********************

Quantize operation supports the following data type combinations.

=== ======
Src Dst
=== ======
f32 s8, u8
=== ======

@note This operation is to support :ref:`int8
quantization<graph_quantization_model-label>` model.
