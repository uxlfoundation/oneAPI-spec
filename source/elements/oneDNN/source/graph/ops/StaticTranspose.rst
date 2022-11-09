.. SPDX-FileCopyrightText: 2020-2022 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. include:: ../../replacements.inc.rst


StaticTranspose
###############

StaticTranspose operation rearranges the dimensions of
\src. \dst may have a different memory layout
from \src. StaticTranspose operation is not guaranteed to
return a view or a copy of \src when \dst is
in-placed with the \src.

.. math::

   \dst[\src(order[0]), \src(order[1]),\cdots, \src(order[N-1])] = \src[\src(0), \src(1),\cdots, \src(N-1)]



Operation Attributes
********************

+--------------+-------------+------------+-------------+-------------+
|  Attribute   | Description | Value Type |  Supported  | Required or |
|     Name     |             |            |   Values    |  Optional   |
+==============+=============+============+=============+=============+
| |attr_order| | Specifies   | s64        | A s64 list  | Required    |
|              | permutation |            | containing  |             |
|              | to be       |            | the element |             |
|              | applied on  |            | in the      |             |
|              | \src        |            | range of    |             |
|              |             |            | [-N, N-1],  |             |
|              |             |            | negative    |             |
|              |             |            | value means |             |
|              |             |            | counting    |             |
|              |             |            | from last   |             |
|              |             |            | axis        |             |
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

StaticTranspose operation supports the following data type combinations.

==== ====
Src  Dst
==== ====
f32  f32
bf16 bf16
f16  f16
==== ====
