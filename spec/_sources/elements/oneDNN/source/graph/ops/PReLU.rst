.. SPDX-FileCopyrightText: 2020-2022 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. include:: ../../replacements.inc.rst

.. _op_prelu-label:

PReLU
#####

PReLU operation performs element-wise parametric ReLU operation on a
given input tensor, based on the following mathematical formula:

.. math::

   \dst = \begin{cases} \src & \text{if}\ \src \ge 0 \\
       \alpha \src & \text{if}\ \src < 0 \end{cases}



Operation Attributes
********************

+------------------------------+-------------+------------+------------+-------------+
|          Attribute           | Description | Value Type | Supported  | Required or |
|             Name             |             |            |   Values   |  Optional   |
+==============================+=============+============+============+=============+
| |attr_data_format|           | Denotes the | string     | ``NCX``,   | Optional    |
|                              | data format |            | ``NXC``    |             |
|                              | of the      |            | (default)  |             |
|                              | input and   |            |            |             |
|                              | output      |            |            |             |
|                              | data.       |            |            |             |
+------------------------------+-------------+------------+------------+-------------+
| |attr_per_channel_broadcast| | Denotes     | bool       | ``false``, | Optional    |
|                              | whether to  |            | ``true``   |             |
|                              | apply       |            | (default)  |             |
|                              | per_channel |            |            |             |
|                              | broadcast   |            |            |             |
|                              | when slope  |            |            |             |
|                              | is 1D       |            |            |             |
|                              | tensor.     |            |            |             |
+------------------------------+-------------+------------+------------+-------------+

Broadcasting Rules
==================

Only slope tensor supports broadcasting semantics. Slope tensor is
uni-directionally broadcasted to \src if one of the
following rules is met:

-  1: slope is 1D tensor and ``per_channel_broadcast`` is set to
   ``true``, the length of slope tensor is equal to the length of
   \src of channel dimension.

-  2: slope is 1D tensor and ``per_channel_broadcast`` is set to
   ``false``, the length of slope tensor is equal to the length of
   \src of the rightmost dimension.

-  3: slope is nD tensor, starting from the rightmost dimension,
   :math:`input.shape_i == slope.shape_i` or
   :math:`slope.shape_i == 1` or slope dimension i is empty.


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
1     ``slope``     Required
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

PReLU operation supports the following data type combinations.

==== ==== =====
Src  Dst  Slope
==== ==== =====
f32  f32  f32
bf16 bf16 bf16
f16  f16  f16
==== ==== =====
