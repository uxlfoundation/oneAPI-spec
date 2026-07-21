.. SPDX-FileCopyrightText: 2020-2022 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. include:: ../../replacements.inc.rst


ConvTransposeBackwardWeights
############################

ConvTransposeBackwardWeights operation takes :math:`\diffdst`,
\src and optional :math:`weights\_shape` computes
:math:`\diffweights`.

Operation Attributes
********************

+-----------------------+-------------------+------------+-----------------+-------------+
|       Attribute       |    Description    | Value Type |    Supported    | Required or |
|         Name          |                   |            |     Values      |  Optional   |
+=======================+===================+============+=================+=============+
| |attr_strides|        | Controls          | s64        | A s64 list      | Required    |
|                       | the strides       |            | containing      |             |
|                       | the weights       |            | positive        |             |
|                       | tensor is         |            | values          |             |
|                       | moved when        |            |                 |             |
|                       | computing         |            |                 |             |
|                       | convolution       |            |                 |             |
+-----------------------+-------------------+------------+-----------------+-------------+
| |attr_pads_begin|     | Controls          | s64        | A s64 list      | Required    |
|                       | number of         |            | containing      |             |
|                       | zeros to be       |            | non-negative    |             |
|                       | add to the        |            | values          |             |
|                       | front/top/left    |            |                 |             |
|                       | of spatial        |            |                 |             |
|                       | dimensions        |            |                 |             |
+-----------------------+-------------------+------------+-----------------+-------------+
| |attr_pads_end|       | Controls          | s64        | A s64 list      | Required    |
|                       | number of         |            | containing      |             |
|                       | zeros to be       |            | non-negative    |             |
|                       | add to the        |            | values          |             |
|                       | back/bottom/right |            |                 |             |
|                       | of spatial        |            |                 |             |
|                       | dimensions        |            |                 |             |
+-----------------------+-------------------+------------+-----------------+-------------+
| |attr_dilations|      | Controls          | s64        | A s64 list      | Required    |
|                       | the amount        |            | containing      |             |
|                       | of                |            | positive        |             |
|                       | stretching        |            | values (>1      |             |
|                       | the kernel        |            | means           |             |
|                       | before            |            | dilated         |             |
|                       | convolution       |            | convolution)    |             |
+-----------------------+-------------------+------------+-----------------+-------------+
| |attr_auto_pad|       | Controls          | string     | ``none``        | Optional    |
|                       | how the           |            | (default),      |             |
|                       | padding is        |            | ``same_upper``, |             |
|                       | calculated        |            | ``same_lower``, |             |
|                       |                   |            | ``valid``       |             |
+-----------------------+-------------------+------------+-----------------+-------------+
| |attr_output_padding| | Adds              | s64        | A s64 list      | Optional    |
|                       | additional        |            | containing      |             |
|                       | amount of         |            | non-negative    |             |
|                       | padding per       |            | values, all     |             |
|                       | each              |            | zeros by        |             |
|                       | spatial           |            | default         |             |
|                       | axis in           |            |                 |             |
|                       | ``dst``           |            |                 |             |
+-----------------------+-------------------+------------+-----------------+-------------+
| |attr_groups|         | Controls          | s64        | A positive      | Optional    |
|                       | how input         |            | s64 value,      |             |
|                       | channels          |            | ``1`` by        |             |
|                       | and output        |            | default         |             |
|                       | channels          |            |                 |             |
|                       | are divided       |            |                 |             |
|                       | into              |            |                 |             |
+-----------------------+-------------------+------------+-----------------+-------------+
| |attr_data_format|    | Controls          | string     | ``NCX``,        | Optional    |
|                       | how to            |            | ``NXC``         |             |
|                       | interpret         |            | (default)       |             |
|                       | the shape         |            |                 |             |
|                       | of ``src``        |            |                 |             |
|                       | and               |            |                 |             |
|                       | ``dst``.          |            |                 |             |
+-----------------------+-------------------+------------+-----------------+-------------+
| |attr_weights_format| | Controls          | string     | ``IOX``,        | Optional    |
|                       | how to            |            | ``XOI``         |             |
|                       | interpret         |            | (default)       |             |
|                       | the shape         |            |                 |             |
|                       | of                |            |                 |             |
|                       | ``weights``       |            |                 |             |
+-----------------------+-------------------+------------+-----------------+-------------+
| |attr_weights_shape|  | Denotes the       | s64        | A s64 list      | Optional    |
|                       | shape of          |            | containing      |             |
|                       | the               |            | positive        |             |
|                       | ``weights``       |            | values          |             |
|                       | tensor            |            |                 |             |
|                       |                   |            |                 |             |
+-----------------------+-------------------+------------+-----------------+-------------+

Execution Arguments
*******************

The inputs and outputs must be provided according to the below index order
when constructing an operation.

Inputs
======


===== ================= ====================
Index Argument Name     Required or Optional
===== ================= ====================
0     ``src``           Required
1     ``diff_dst``      Required
2     ``weights_shape`` Optional
===== ================= ====================

@note The shape of \weights is
:math:`(in\_channels / groups, out\_channels, spatial\_shape)`
for ``IOX`` format or
:math:`(spatial\_shape, out\_channels, in\_channels / groups)`
for ``XOI`` format. Both :math:`in\_channels` and
:math:`out\_channels` must be divisible by |attr_groups| attribute.

@note Either ``weights_shape`` input or |attr_weights_shape| attribute
should be provided. If both provided, ``weights_shape`` input will
precede over the |attr_weights_shape| attribute.

Outputs
=======


===== ================ ====================
Index Argument Name    Required or Optional
===== ================ ====================
0     ``diff_weights`` Required
===== ================ ====================


Supported Data Types
********************

ConvTransposeBackwardWeights operation supports the following data type
combinations.

==== ======== ============ =============
Src  Diff_dst Diff_weights Weights_shape
==== ======== ============ =============
f32  f32      f32          s32
bf16 bf16     bf16         s32
f16  f16      f16          s32
==== ======== ============ =============
