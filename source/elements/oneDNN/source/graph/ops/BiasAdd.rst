.. SPDX-FileCopyrightText: 2020-2022 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. include:: ../../replacements.inc.rst


BiasAdd
#######

Add bias to channel dimension of input. This is a special ``Add`` with
bias restricted to be 1-D. Broadcasting is supported.

.. math::

   \dst(n,c,h,w) = \src(n,c,h,w) + \bias(c) 

Operation Attributes
********************

+--------------------+-------------+------------+-----------+-------------+
|     Attribute      | Description | Value Type | Supported | Required or |
|        Name        |             |            |  Values   |  Optional   |
+====================+=============+============+===========+=============+
| |attr_data_format| | Controls    | string     | ``NCX`` , | Optional    |
|                    | how to      |            | ``NXC``   |             |
|                    | interpret   |            | (default) |             |
|                    | the shape   |            |           |             |
|                    | of ``src``  |            |           |             |
|                    | and         |            |           |             |
|                    | ``dst``.    |            |           |             |
+--------------------+-------------+------------+-----------+-------------+

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
1     ``bias``      Required
===== ============= ====================

@note ``bias`` is a 1D tensor to be added to ``src`` tensor. The size
should be the same as size of channel dimension of ``src`` tensor.

Outputs
=======


===== ============= ====================
Index Argument Name Required or Optional
===== ============= ====================
0     ``dst``       Required
===== ============= ====================


Supported Data Types
********************

BiasAdd operation supports the following data type combinations.

==== ==== ====
Src  Bias Dst
==== ==== ====
f32  f32  f32
bf16 bf16 bf16
f16  f16  f16
==== ==== ====
