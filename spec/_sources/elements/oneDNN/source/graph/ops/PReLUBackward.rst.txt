.. SPDX-FileCopyrightText: 2020-2022 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. include:: ../../replacements.inc.rst


PReLUBackward
#############

PReLUBackward operation computes gradient for PReLU.

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

Broadcasting Rules
==================

Only slope tensor supports broadcasting semantics. Slope tensor is
uni-directionally broadcasted to \src if one of the
following rules is met:

-  1: PyTorch case: slope is 1D tensor and broadcast per channel, length
   of slope is equal to the length of \src in channel
   dimension.

-  2: PyTorch case: slope is 1D tensor and broadcast per tensor, length
   of slope is equal to 1.

-  3: Tensorflow case: slope is nD tensor and its dimensions must be
   equal to the \src dimensions starting from the second
   element: \$ slope_shape = input_forward_shape[1:] \$

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
2     ``diff_dst``  Required
===== ============= ====================

Outputs
=======


===== ============== ====================
Index Argument Name  Required or Optional
===== ============== ====================
0     ``diff_src``   Required
1     ``diff_slope`` Required
===== ============== ====================


Supported Data Types
********************

PReLUBackward operation supports the following data type combinations.

==== ===== ======== ======== ==========
Src  Slope Diff_dst Diff_src Diff_slope
==== ===== ======== ======== ==========
f32  f32   f32      f32      f32
bf16 bf16  bf16     bf16     bf16
f16  f16   f16      f16      f16
==== ===== ======== ======== ==========
