.. SPDX-FileCopyrightText: 2020-2022 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. include:: ../../replacements.inc.rst


EluBackward
###########

EluBackward operation computes gradient for Elu operation.

Operation Attributes
********************

+----------------+-------------+------------+--------------+-------------+
|   Attribute    | Description | Value Type |  Supported   | Required or |
|      Name      |             |            |    Values    |  Optional   |
+================+=============+============+==============+=============+
| |attr_alpha|   | Scale for   | f32        | Arbitrary    | Required    |
|                | the         |            | non-negative |             |
|                | negative    |            | f32 value    |             |
|                | factor.     |            |              |             |
|                |             |            |              |             |
+----------------+-------------+------------+--------------+-------------+
| |attr_use_dst| | If true,    | bool       | ``true``     | Optional    |
|                | use         |            | (default),   |             |
|                | \dst        |            | ``false``    |             |
|                | of Elu      |            |              |             |
|                | operation   |            |              |             |
|                | to          |            |              |             |
|                | calculate   |            |              |             |
|                | the         |            |              |             |
|                | gradient.   |            |              |             |
|                | Otherwise,  |            |              |             |
|                | use         |            |              |             |
|                | \src.       |            |              |             |
+----------------+-------------+------------+--------------+-------------+

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

EluBackward operation supports the following data type combinations.

========= ======== ========
Src / Dst Diff_dst Diff_src
========= ======== ========
f32       f32      f32
f16       f16      f16
bf16      bf16     bf16
========= ======== ========
