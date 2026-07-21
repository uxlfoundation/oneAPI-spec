.. SPDX-FileCopyrightText: 2020-2022 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. include:: ../../replacements.inc.rst


LeakyReLU
#########

LeakyReLU operation is a type of activation function based on ReLU. It
has a small slope for negative values with which LeakyReLU can produce
small, non-zero, and constant gradients with respect to the negative
values. The slope is also called the coefficient of leakage.

Unlike :ref:`op_prelu-label`, the coefficient :math:`\alpha` is
constant and defined before training.

LeakyReLU operation applies following formula on every element of
\src tensor (the variable names follow the standard :ref:`conventions-label`):

.. math::
 
   \dst = \begin{cases} \src & \text{if}\ \src \ge 0 \\
       \alpha \src & \text{if}\ \src < 0 \end{cases}



Operation Attributes
********************

+--------------+-------------+------------+-------------+-------------+
|  Attribute   | Description | Value Type |  Supported  | Required or |
|     Name     |             |            |   Values    |  Optional   |
+==============+=============+============+=============+=============+
| |attr_alpha| | Alpha is    | f32        | Arbitrary   | Required    |
|              | the         |            | f32 value   |             |
|              | coefficient |            | but usually |             |
|              | of leakage. |            | a small     |             |
|              |             |            | positive    |             |
|              |             |            | value.      |             |
+--------------+-------------+------------+-------------+-------------+

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

LeakyReLU operation supports the following data type combinations.

==== ====
Src  Dst
==== ====
f32  f32
bf16 bf16
f16  f16
==== ====
