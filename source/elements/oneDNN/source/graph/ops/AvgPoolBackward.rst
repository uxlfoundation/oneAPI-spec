.. SPDX-FileCopyrightText: 2020-2022 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. include:: ../../replacements.inc.rst


AvgPoolBackward
###############

AvgPoolBackward operation accepts \diffdst tensor and \srcshape tensor
(optional), and calculates \diffsrc tensor.

Operation Attributes
********************

+--------------------+-------------------+------------+-----------------+-------------+
|     Attribute      |    Description    | Value Type |    Supported    | Required or |
|        Name        |                   |            |     Values      |  Optional   |
+====================+===================+============+=================+=============+
| |attr_strides|     | Controls          | s64        | A s64 list      | Required    |
|                    | the strides       |            | containing      |             |
|                    | the window        |            | positive        |             |
|                    | is moved          |            | values          |             |
|                    |                   |            |                 |             |
+--------------------+-------------------+------------+-----------------+-------------+
| |attr_pads_begin|  | Controls          | s64        | A s64 list      | Required    |
|                    | number of         |            | containing      |             |
|                    | zeros to be       |            | n               |             |
|                    | add to the        |            | on-negative     |             |
|                    | front/top/left    |            | values          |             |
|                    | of spatial        |            |                 |             |
|                    | dimensions,       |            |                 |             |
|                    | the               |            |                 |             |
|                    | attribute         |            |                 |             |
|                    | will be           |            |                 |             |
|                    | ignored           |            |                 |             |
|                    | when              |            |                 |             |
|                    | |attr_auto_pad|   |            |                 |             |
|                    | attribute         |            |                 |             |
|                    | is                |            |                 |             |
|                    | specified         |            |                 |             |
|                    | to                |            |                 |             |
|                    | ``same_upper``,   |            |                 |             |
|                    | ``same_lower``    |            |                 |             |
|                    | or                |            |                 |             |
|                    | ``valid``         |            |                 |             |
+--------------------+-------------------+------------+-----------------+-------------+
| |attr_pads_end|    | Controls          | s64        | A s64 list      | Required    |
|                    | number of         |            | containing      |             |
|                    | zeros to be       |            | n               |             |
|                    | add to the        |            | on-negative     |             |
|                    | back/bottom/right |            | values          |             |
|                    | of spatial        |            |                 |             |
|                    | dimensions,       |            |                 |             |
|                    | the               |            |                 |             |
|                    | attribute         |            |                 |             |
|                    | will be           |            |                 |             |
|                    | ignored           |            |                 |             |
|                    | when              |            |                 |             |
|                    | |attr_auto_pad|   |            |                 |             |
|                    | attribute         |            |                 |             |
|                    | is                |            |                 |             |
|                    | specified         |            |                 |             |
|                    | to                |            |                 |             |
|                    | ``same_upper``,   |            |                 |             |
|                    | ``same_lower``    |            |                 |             |
|                    | or                |            |                 |             |
|                    | ``valid``         |            |                 |             |
+--------------------+-------------------+------------+-----------------+-------------+
| |attr_kernel|      | Size of           | s64        | A s64 list      | Required    |
|                    | pooling           |            | containing      |             |
|                    | window            |            | positive        |             |
|                    |                   |            | values          |             |
|                    |                   |            |                 |             |
+--------------------+-------------------+------------+-----------------+-------------+
| |attr_exclude_pad| | Controls          | bool       | True, False     | Required    |
|                    | whether the       |            |                 |             |
|                    | padded            |            |                 |             |
|                    | values are        |            |                 |             |
|                    | counted           |            |                 |             |
|                    |                   |            |                 |             |
+--------------------+-------------------+------------+-----------------+-------------+
| |attr_auto_pad|    | Controls          | string     | ``none``        | Optional    |
|                    | how the           |            | (default),      |             |
|                    | paddings are      |            | ``same_upper``, |             |
|                    | calculated        |            | ``same_lower``, |             |
|                    |                   |            | ``valid``       |             |
+--------------------+-------------------+------------+-----------------+-------------+
| |attr_data_format| | Controls          | string     | ``NCX``,        | Optional    |
|                    | how to            |            | ``NXC``         |             |
|                    | interpret         |            | (default)       |             |
|                    | the shape         |            |                 |             |
|                    | of ``src``        |            |                 |             |
|                    | and               |            |                 |             |
|                    | ``dst``.          |            |                 |             |
+--------------------+-------------------+------------+-----------------+-------------+
| |attr_src_shape|   | Denotes the       | string     | ``NCX``,        | Optional    |
|                    | shape of          |            | ``NXC``         |             |
|                    | input of          |            | (default)       |             |
|                    | forward op        |            |                 |             |
|                    |                   |            |                 |             |
+--------------------+-------------------+------------+-----------------+-------------+

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
1     ``src_shape`` Optional
===== ============= ====================

@note Either ``src_shape`` input or |attr_src_shape| attribute should be
provided. If both provided, ``src_shape`` input will precede over
|attr_src_shape| attribute.

Outputs
=======


===== ============= ====================
Index Argument Name Required or Optional
===== ============= ====================
0     ``diff_src``  Required
===== ============= ====================


Supported Data Types
********************

AvgPoolBackward operation supports the following data type combinations.

======== ======== =========
Diff_dst Diff_src Src_shape
======== ======== =========
f32      f32      s64
bf16     bf16     s64
f16      f16      s64
======== ======== =========
