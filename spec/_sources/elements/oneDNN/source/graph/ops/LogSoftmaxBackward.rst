.. SPDX-FileCopyrightText: 2020-2022 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. include:: ../../replacements.inc.rst


LogSoftmaxBackward
##################

LogSoftmaxBackward operation computes gradient for LogSoftmax.

Operation Attributes
********************

+-------------+-------------+------------+------------+-------------+
|  Attribute  | Description | Value Type | Supported  | Required or |
|    Name     |             |            |   Values   |  Optional   |
+=============+=============+============+============+=============+
| |attr_axis| | Represents  | s64        | Arbitrary  | Optional    |
|             | the axis of |            | s64 value  |             |
|             | which the   |            | (``-1`` in |             |
|             | LogSoftmax  |            | default)   |             |
|             | is          |            |            |             |
|             | calculated. |            |            |             |
+-------------+-------------+------------+------------+-------------+

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
1     ``dst``       Required
===== ============= ====================

Outputs
=======


===== ============= ====================
Index Argument Name Required or Optional
===== ============= ====================
0     ``diff_src``  Required
===== ============= ====================


Supported Data Types
********************

LogSoftmaxBackward operation supports the following data type combinations.

======== ==== ========
Diff_dst Dst  Diff_src
======== ==== ========
f32      f32  f32
bf16     bf16 bf16
f16      f16  f16
======== ==== ========
