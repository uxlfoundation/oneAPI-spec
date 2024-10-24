.. SPDX-FileCopyrightText: 2020-2022 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. include:: ../../replacements.inc.rst


MaxPool
#######

MaxPool operation performs the computation following the below formulas.
Variable names follow the standard :ref:`conventions-label`.

.. math::
 
   \dst(n, c, oh, ow) = \max\limits_{kh, kw}
      \left( \src(n, c, oh \cdot SH + kh \cdot (DH + 1) - PH_L,
      ow \cdot SW + kw \cdot (DW + 1) - PW_L) \right)


Operation Attributes
********************

+----------------------+-------------------+------------+-----------------+-------------+
|      Attribute       |    Description    | Value Type |    Supported    | Required or |
|         Name         |                   |            |     Values      |  Optional   |
+======================+===================+============+=================+=============+
| |attr_strides|       | Controls          | s64        | A s64 list      | Required    |
|                      | the strides       |            | containing      |             |
|                      | the window        |            | positive        |             |
|                      | is moved          |            | values          |             |
+----------------------+-------------------+------------+-----------------+-------------+
| |attr_pads_begin|    | Controls          | s64        | A s64 list      | Required    |
|                      | number of         |            | containing      |             |
|                      | zeros to be       |            | non-negative    |             |
|                      | add to the        |            | values          |             |
|                      | front/top/left    |            |                 |             |
|                      | of spatial        |            |                 |             |
|                      | dimensions,       |            |                 |             |
|                      | the               |            |                 |             |
|                      | attribute         |            |                 |             |
|                      | will be           |            |                 |             |
|                      | ignored           |            |                 |             |
|                      | when              |            |                 |             |
|                      | |attr_auto_pad|   |            |                 |             |
|                      | attribute         |            |                 |             |
|                      | is                |            |                 |             |
|                      | specified         |            |                 |             |
|                      | to                |            |                 |             |
|                      | ``same_upper``,   |            |                 |             |
|                      | ``same_lower``    |            |                 |             |
|                      | or                |            |                 |             |
|                      | ``valid``         |            |                 |             |
+----------------------+-------------------+------------+-----------------+-------------+
| |attr_pads_end|      | Controls          | s64        | A s64 list      | Required    |
|                      | number of         |            | containing      |             |
|                      | zeros to be       |            | non-negative    |             |
|                      | add to the        |            | values          |             |
|                      | back/bottom/right |            |                 |             |
|                      | of spatial        |            |                 |             |
|                      | dimensions,       |            |                 |             |
|                      | the               |            |                 |             |
|                      | attribute         |            |                 |             |
|                      | will be           |            |                 |             |
|                      | ignored           |            |                 |             |
|                      | when              |            |                 |             |
|                      | |attr_auto_pad|   |            |                 |             |
|                      | attribute         |            |                 |             |
|                      | is                |            |                 |             |
|                      | specified         |            |                 |             |
|                      | to                |            |                 |             |
|                      | ``same_upper``,   |            |                 |             |
|                      | ``same_lower``    |            |                 |             |
|                      | or                |            |                 |             |
|                      | ``valid``         |            |                 |             |
+----------------------+-------------------+------------+-----------------+-------------+
| |attr_kernel|        | Size of           | s64        | A s64 list      | Required    |
|                      | pooling           |            | containing      |             |
|                      | window            |            | positive        |             |
|                      |                   |            | values          |             |
|                      |                   |            |                 |             |
+----------------------+-------------------+------------+-----------------+-------------+
| |attr_dilations|     | Denotes the       | s64        | A s64 list      | Optional    |
|                      | distance in       |            | containing      |             |
|                      | width and         |            | positive        |             |
|                      | height            |            | values, a       |             |
|                      | between           |            | list of         |             |
|                      | elements.         |            | ``1`` s         |             |
|                      |                   |            | (default)       |             |
|                      |                   |            | means no        |             |
|                      |                   |            | dilation        |             |
+----------------------+-------------------+------------+-----------------+-------------+
| |attr_rounding_type| | Controls          | string     | ``floor``       | Optional    |
|                      | how to do         |            | (default),      |             |
|                      | rounding          |            | ``ceil``        |             |
|                      |                   |            |                 |             |
|                      |                   |            |                 |             |
|                      |                   |            |                 |             |
+----------------------+-------------------+------------+-----------------+-------------+
| |attr_auto_pad|      | Controls          | string     | ``none``        | Optional    |
|                      | how the           |            | (default),      |             |
|                      | paddings          |            | ``same_upper``, |             |
|                      | are               |            | ``same_lower``, |             |
|                      | calculated        |            | ``valid``       |             |
|                      |                   |            |                 |             |
|                      |                   |            |                 |             |
+----------------------+-------------------+------------+-----------------+-------------+
| |attr_data_format|   | Controls          | string     | ``NCX``,        | Optional    |
|                      | how to            |            | ``NXC``         |             |
|                      | interpret         |            | (default)       |             |
|                      | the shape         |            |                 |             |
|                      | of ``src``        |            |                 |             |
|                      | and ``dst``.      |            |                 |             |
+----------------------+-------------------+------------+-----------------+-------------+


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

MaxPool operation supports the following data type combinations.

==== ====
Src  Dst
==== ====
f32  f32
bf16 bf16
f16  f16
==== ====
