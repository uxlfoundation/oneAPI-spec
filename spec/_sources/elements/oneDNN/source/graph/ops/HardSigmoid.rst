.. SPDX-FileCopyrightText: 2020-2023 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. include:: ../../replacements.inc.rst


HardSigmoid
###########

HardSigmoid operation applies the following formula on every element of \src
tensor (the variable names follow the standard @ref dev_guide_conventions):

.. math::

    \dst = \max(0, \min(1, \alpha \src + \beta))

Operation Attributes
********************

+--------------+----------------+------------+--------------+-------------+
|  Attribute   | Description    | Value Type |  Supported   | Required or |
|     Name     |                |            |    Values    |  Optional   |
+==============+================+============+==============+=============+
| |attr_alpha| | :math:`\alpha` | f32        | Arbitrary    | Required    |
|              | in the         |            | f32 value    |             |
|              | formula.       |            |              |             |
+--------------+----------------+------------+--------------+-------------+
| |attr_beta|  | :math:`\beta`  | f32        | Arbitrary    | Required    |
|              | in the         |            | f32 value    |             |
|              | formula.       |            |              |             |
+--------------+----------------+------------+--------------+-------------+

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

HardSigmoid operation supports the following data type combinations.

==== ====
Src  Dst
==== ====
f32  f32
bf16 bf16
f16  f16
==== ====
