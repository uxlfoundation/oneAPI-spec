.. SPDX-FileCopyrightText: 2020-2022 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. include:: ../../replacements.inc.rst


Clamp
#####

Clamp operation represents clipping activation function, it applies
following formula on every element of \src tensor (the
variable names follow the standard :ref:`conventions-label`):

.. math::
 clamp(src_i) = min(max(src_i, min\_value), max\_value)


Operation Attributes
********************

+------------+-------------+------------+-----------+-------------+
| Attribute  | Description | Value Type | Supported | Required or |
|    Name    |             |            |  Values   |  Optional   |
+============+=============+============+===========+=============+
| |attr_min| | The lower   | f32        | Arbitrary | Required    |
|            | bound of    |            | valid f32 |             |
|            | values in   |            | value     |             |
|            | the output. |            |           |             |
|            | Any value   |            |           |             |
|            | in the      |            |           |             |
|            | input that  |            |           |             |
|            | is smaller  |            |           |             |
|            | than the    |            |           |             |
|            | bound, is   |            |           |             |
|            | replaced    |            |           |             |
|            | with the    |            |           |             |
|            | ``min``     |            |           |             |
|            | value.      |            |           |             |
+------------+-------------+------------+-----------+-------------+
| |attr_max| | The upper   | f32        | Arbitrary | Required    |
|            | bound of    |            | valid f32 |             |
|            | values in   |            | value     |             |
|            | the output. |            |           |             |
|            | Any value   |            |           |             |
|            | in the      |            |           |             |
|            | input that  |            |           |             |
|            | is greater  |            |           |             |
|            | than the    |            |           |             |
|            | bound, is   |            |           |             |
|            | replaced    |            |           |             |
|            | with the    |            |           |             |
|            | ``max``     |            |           |             |
|            | value.      |            |           |             |
+------------+-------------+------------+-----------+-------------+

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

Clamp operation supports the following data type combinations.

==== ====
Src  Dst
==== ====
f32  f32
f16  f16
bf16 bf16
==== ====
