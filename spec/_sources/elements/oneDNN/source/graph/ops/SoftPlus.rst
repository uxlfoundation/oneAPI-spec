.. SPDX-FileCopyrightText: 2020-2022 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. include:: ../../replacements.inc.rst


SoftPlus
########

SoftPlus operation applies following formula on every element of
\src tensor (the variable names follow the standard :ref:`conventions-label`):

.. math::
    
    \dst = 1 / \operatorname{beta} \* \ln(e^{\operatorname{beta}*\src} + 1.0)


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

SoftPlus operation supports the following data type combinations.

==== ====
Src  Dst
==== ====
f32  f32
bf16 bf16
f16  f16
==== ====
