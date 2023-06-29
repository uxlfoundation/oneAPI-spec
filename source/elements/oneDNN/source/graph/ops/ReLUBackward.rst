.. SPDX-FileCopyrightText: 2020-2022 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. include:: ../../replacements.inc.rst


ReLUBackward
############

ReLUBackward operation computes gradient for ReLU.

Operation Attributes
********************

+----------------+-------------+------------+------------+-------------+
|   Attribute    | Description | Value Type | Supported  | Required or |
|      Name      |             |            |   Values   |  Optional   |
+================+=============+============+============+=============+
| |attr_use_dst| | If true,    | bool       | ``true``   | Optional    |
|                | use \dst    |            | (default), |             |
|                | of ReLU     |            | ``false``  |             |
|                | operation   |            |            |             |
|                | to          |            |            |             |
|                | calculate   |            |            |             |
|                | the         |            |            |             |
|                | gradient.   |            |            |             |
|                | Otherwise,  |            |            |             |
|                | use         |            |            |             |
|                | \src.       |            |            |             |
+----------------+-------------+------------+------------+-------------+

Execution Arguments
*******************

The inputs and outputs must be provided according to the below index order
when constructing an operation.

Inputs
======


===== ================= ====================
Index Argument Name     Required or Optional
===== ================= ====================
0     ``src`` / ``dst`` Required
1     ``diff_dst``      Required
===== ================= ====================

Outputs
=======


===== ============= ====================
Index Argument Name Required or Optional
===== ============= ====================
0     ``diff_src``  Required
===== ============= ====================


Supported Data Types
********************

ReLUBackward operation supports the following data type combinations.

========= ======== ========
Src / Dst Diff_dst Diff_src
========= ======== ========
f32       f32      f32
f16       f16      f16
bf16      bf16     bf16
========= ======== ========
