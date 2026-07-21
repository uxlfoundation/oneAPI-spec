.. SPDX-FileCopyrightText: 2020-2022 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. include:: ../../replacements.inc.rst


LogSoftmax
##########

LogSoftmax operation applies the :math:`\log(softmax(src))`` function to an n-dimensional input Tensor. The formulation can be
simplified as:

.. math::
    
    \dst_i = \log\Big( \frac{e^(\src_i)}{\sum_{j}^{ } e^(\src_j)} \Big) 

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

LogSoftmax operation supports the following data type combinations.

==== ====
Src  Dst
==== ====
f32  f32
bf16 bf16
f16  f16
==== ====
