.. SPDX-FileCopyrightText: 2020-2022 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. include:: ../../replacements.inc.rst


SoftPlusBackward
################

SoftPlusBackward operation computes gradient for SoftPlus.

Operation Attributes
********************

+-------------+--------------+------------+-----------+-------------+
|  Attribute  | Description  | Value Type | Supported | Required or |
|    Name     |              |            |  Values   |  Optional   |
+=============+==============+============+===========+=============+
| |attr_beta| | Value for    | s64        | Arbitrary | Optional    |
|             | the          |            | s64 value |             |
|             | SoftPlus     |            | (``1`` in |             |
|             | formulation. |            | default)  |             |
+-------------+--------------+------------+-----------+-------------+

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
1     ``diff_dst``  Required
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

SoftPlusBackward operation supports the following data type
combinations.

==== ======== ========
Src  Diff_dst Diff_src
==== ======== ========
f32  f32      f32
bf16 bf16     bf16
f16  f16      f16
==== ======== ========
