.. SPDX-FileCopyrightText: 2020-2022 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. include:: ../../replacements.inc.rst


ConvolutionBackwardData
#######################


ConvolutionBackwardData operation accepts :math:`\diffdst`,
\weights and optional dst shape as inputs, and compute the
:math:`\diffsrc`.

If |attr_auto_pad| attribute is specified to one of ``valid``,
``same_upper`` and ``same_lower``, |attr_pads_begin| and ``pads_end``
attributes will be ignored. The paddings will be calculated by following
the below formula:

Let the parameters be:

+-------------+--------------+--------------+--------------+-------------------+
|  Parameter  |    Depth     |    Height    |    Width     |      Comment      |
+=============+==============+==============+==============+===================+
| Paddings:   | :math:`PD_L` | :math:`PH_L` | :math:`PW_L` | In the            |
| Front, top, |              |              |              | attributes        |
| and left    |              |              |              | we use            |
|             |              |              |              | |attr_pads_begin| |
|             |              |              |              | to indicate       |
|             |              |              |              | the               |
|             |              |              |              | corresponding     |
|             |              |              |              | vector of         |
|             |              |              |              | paddings          |
+-------------+--------------+--------------+--------------+-------------------+
| Padding:    | :math:`PD_R` | :math:`PH_R` | :math:`PW_R` | In the            |
| Back,       |              |              |              | attributes        |
| bottom, and |              |              |              | we use            |
| right       |              |              |              | |attr_pads_end|   |
|             |              |              |              | to indicate       |
|             |              |              |              | the               |
|             |              |              |              | corresponding     |
|             |              |              |              | vector of         |
|             |              |              |              | paddings          |
+-------------+--------------+--------------+--------------+-------------------+
| Stride      | :math:`SD`   | :math:`SH`   | :math:`SW`   | In the            |
|             |              |              |              | attributes        |
|             |              |              |              | we use            |
|             |              |              |              | |attr_strides|    |
|             |              |              |              | to indicate       |
|             |              |              |              | the               |
|             |              |              |              | corresponding     |
|             |              |              |              | vector of         |
|             |              |              |              | strides           |
+-------------+--------------+--------------+--------------+-------------------+
| Dilation    | :math:`DD`   | :math:`DH`   | :math:`DW`   | In the            |
|             |              |              |              | attributes        |
|             |              |              |              | we use            |
|             |              |              |              | |attr_dilations|  |
|             |              |              |              | to indicate       |
|             |              |              |              | the               |
|             |              |              |              | corresponding     |
|             |              |              |              | vector of         |
|             |              |              |              | dilations         |
+-------------+--------------+--------------+--------------+-------------------+

Firstly, :math:`total\_padding` is calculated according to
:math:`src\_shape` and :math:`dst\_shape`. Let
:math:`src\_h` be height dimension of :math:`src\_shape`
and :math:`dst\_h` be height dimension of
:math:`dst\_shape`.

.. math::
 
   total\_padding_h = SH \times (src_h - 1) + ((KH -1 ) \times DH + 1) - \dst_h + output\_padding_h


If |attr_auto_pad| attribute is specified as ``valid``:

.. math::
 PD_L = 0 \\ PD_R = 0 

If |attr_auto_pad| attribute is specified as ``same_lower``:

.. math::
 PD_L = floor(total\_padding / 2) \\ PD_R = total\_padding - PD_L

If |attr_auto_pad| attribute is specified as ``same_upper``:

.. math::
 PD_L = total\_padding - PD_R \\ PD_R = floor(total\_padding / 2)

where:

-  :math:`dst\_shape` is either an attribute or an input tensor,

-  :math:`output\_padding` is an optional attribute.

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
|                       | dimensions,       |            |                 |             |
|                       | the               |            |                 |             |
|                       | attribute         |            |                 |             |
|                       | will be           |            |                 |             |
|                       | ignored           |            |                 |             |
|                       | when              |            |                 |             |
|                       | |attr_auto_pad|   |            |                 |             |
|                       | attribute         |            |                 |             |
|                       | is                |            |                 |             |
|                       | specified         |            |                 |             |
|                       | to                |            |                 |             |
|                       | ``same_upper``,   |            |                 |             |
|                       | ``same_lower``    |            |                 |             |
|                       | or                |            |                 |             |
|                       | ``valid``         |            |                 |             |
+-----------------------+-------------------+------------+-----------------+-------------+
| |attr_pads_end|       | Controls          | s64        | A s64 list      | Required    |
|                       | number of         |            | containing      |             |
|                       | zeros to be       |            | non-negative    |             |
|                       | add to the        |            | values          |             |
|                       | back/bottom/right |            |                 |             |
|                       | of spatial        |            |                 |             |
|                       | dimensions,       |            |                 |             |
|                       | the               |            |                 |             |
|                       | attribute         |            |                 |             |
|                       | will be           |            |                 |             |
|                       | ignored           |            |                 |             |
|                       | when              |            |                 |             |
|                       | |attr_auto_pad|   |            |                 |             |
|                       | attribute         |            |                 |             |
|                       | is                |            |                 |             |
|                       | specified         |            |                 |             |
|                       | to                |            |                 |             |
|                       | ``same_upper``,   |            |                 |             |
|                       | ``same_lower``    |            |                 |             |
|                       | or                |            |                 |             |
|                       | ``valid``         |            |                 |             |
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
|                       | padding per       |            |                 |             |
|                       | each              |            | values, all     |             |
|                       | spatial           |            | zeros by        |             |
|                       | axis in           |            | default         |             |
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
| |attr_weights_format| | Controls          | string     | ``OIX``,        | Optional    |
|                       | how to            |            | ``XIO``         |             |
|                       | interpret         |            | (default)       |             |
|                       | the shape         |            |                 |             |
|                       | of                |            |                 |             |
|                       | ``weights``       |            |                 |             |
+-----------------------+-------------------+------------+-----------------+-------------+
| |attr_dst_shape|      | Denotes the       | s64        | A s64 list      | Optional    |
|                       | shape of          |            | containing      |             |
|                       | the ``dst``       |            | positive        |             |
|                       | tensor            |            | values          |             |
|                       |                   |            |                 |             |
+-----------------------+-------------------+------------+-----------------+-------------+

Execution Arguments
*******************

The inputs and outputs must be provided according to the below index order
when constructing an operation.

Inputs
======

===== ============= ====================
Index Argument Name Required or Optional
===== ============= ====================
0     ``diff_dst``  Required
1     ``weights``   Required
2     ``dst_shape`` Optional
===== ============= ====================

@note The shape of \weights is
:math:`(out\_channels, in\_channels / groups, spatial\_shape)`
for ``OIX`` format or
:math:`(spatial\_shape, in\_channels / groups, out\_channels)`
for ``XIO`` format. Both :math:`in\_channels` and
:math:`out\_channels` must be divisible by *groups* attribute.

@note Either ``dst_shape`` input or ``dst_shape`` attribute should be
provided. If both provided, ``dst_shape`` input will precede over
``dst_shape`` attribute.

Outputs
=======


===== ============= ====================
Index Argument Name Required or Optional
===== ============= ====================
0     ``diff_src``  Required
===== ============= ====================


Supported Data Types
********************

ConvolutionBackwardData operation supports the following data type
combinations.

======== ======= ======== =========
Diff_dst Weights Diff_src Dst_shape
======== ======= ======== =========
f32      f32     f32      s32
bf16     bf16    bf16     s32
f16      f16     f16      s32
======== ======= ======== =========
