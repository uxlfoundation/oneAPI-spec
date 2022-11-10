.. SPDX-FileCopyrightText: 2020-2022 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. include:: ../../replacements.inc.rst


Elu
###

Elu operation applies following formula on every element of
\src tensor (the variable names follow the standard :ref:`conventions-label`):

.. math::

   \dst = \begin{cases} \alpha(e^{\src} - 1) & \text{if}\ \src < 0 \\
       \src & \text{if}\ \src \ge 0 \end{cases}



Operation Attributes
********************

+--------------+-------------+------------+--------------+-------------+
|  Attribute   | Description | Value Type |  Supported   | Required or |
|     Name     |             |            |    Values    |  Optional   |
+==============+=============+============+==============+=============+
| |attr_alpha| | Scale for   | f32        | Arbitrary    | Required    |
|              | the         |            | non-negative |             |
|              | negative    |            | f32 value    |             |
|              | factor.     |            |              |             |
+--------------+-------------+------------+--------------+-------------+

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

Elu operation supports the following data type combinations.

==== ====
Src  Dst
==== ====
f32  f32
bf16 bf16
f16  f16
==== ====
