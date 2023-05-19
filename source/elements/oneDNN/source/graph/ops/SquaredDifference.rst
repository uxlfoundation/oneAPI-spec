.. SPDX-FileCopyrightText: 2020-2022 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. include:: ../../replacements.inc.rst


SquaredDifference
#################

SquaredDifference operation performs element-wise subtraction operation
with two given tensors applying multi-directional broadcast rules, after
that each result of the subtraction is squared.

Before performing arithmetic operation, :math:`src_0` and
:math:`src_1` are broadcasted if their shapes are different and
``auto_broadcast`` attributes is not ``none``. Broadcasting is performed
according to ``auto_broadcast`` value. After broadcasting
SquaredDifference does the following with the input tensors:

.. math::
    
    \dst_i = (\src\_0_i - \src\_1_i)^2

Operation Attributes
********************

+-------------------+-------------------+------------+------------+-------------+
|     Attribute     |    Description    | Value Type | Supported  | Required or |
|       Name        |                   |            |   Values   |  Optional   |
+===================+===================+============+============+=============+
| |attr_auto_bcast| | Specifies         | string     | ``none``,  | Optional    |
|                   | rules used        |            | ``numpy``, |             |
|                   | for               |            | (default)  |             |
|                   | auto-broadcasting |            |            |             |
|                   | of src            |            |            |             |
|                   | tensors           |            |            |             |
+-------------------+-------------------+------------+------------+-------------+

Execution Arguments
*******************

The inputs and outputs must be provided according to the below index order
when constructing an operation.

Inputs
======


===== ============= ====================
Index Argument Name Required or Optional
===== ============= ====================
0     ``src_0``     Required
1     ``src_1``     Required
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

SquaredDifference operation supports the following data type
combinations.

===== ===== ====
Src_0 Src_1 Dst
===== ===== ====
f32   f32   f32
bf16  bf16  bf16
f16   f16   f16
===== ===== ====
