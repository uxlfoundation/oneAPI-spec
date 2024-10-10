.. SPDX-FileCopyrightText: 2020-2022 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. include:: ../../replacements.inc.rst


Softmax
#######

Softmax operation applies following formula on every element of
\src tensor (the variable names follow the standard :ref:`conventions-label`):

.. math::
    
    \dst_i = \frac{e^{(\src_i)}}{\sum_{j=1}^{C} e^{\src_j}}

where \$ C \$ is a size of tensor along axis dimension.

Operation Attributes
********************

+-------------+-------------+------------+-----------+-------------+
|  Attribute  | Description | Value Type | Supported | Required or |
|    Name     |             |            |  Values   |  Optional   |
+=============+=============+============+===========+=============+
| |attr_axis| | Represents  | s64        | Arbitrary | Optional    |
|             | the axis of |            | s64 value |             |
|             | which the   |            | (``1`` in |             |
|             | Softmax is  |            | default)  |             |
|             | calculated. |            |           |             |
+-------------+-------------+------------+-----------+-------------+

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

Softmax operation supports the following data type combinations.

==== ====
Src  Dst
==== ====
f32  f32
bf16 bf16
f16  f16
==== ====
