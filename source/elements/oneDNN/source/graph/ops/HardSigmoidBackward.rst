.. SPDX-FileCopyrightText: 2020-2023 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. include:: ../../replacements.inc.rst

HardSigmoidBackward
###################

HardSigmoidBackward operation computes gradient for HardSigmoid. The formula is
defined as follows:

.. math::

    \diffsrc = \begin{cases} \diffdst \cdot \alpha & \text{if}\ 0 < \alpha \src + \beta < 1 \\ 0 & \text{otherwise}\ \end{cases}

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
1     ``diff_dst``  Required
===== ============= ====================

Outputs
=======


===== ============= ====================
Index Argument Name Required or Optional
===== ============= ====================
0     ``diff_src``  Required
===== ============= ====================


Supported Data Types
********************

HardSigmoidBackward operation supports the following data type combinations.

======== ======== =========
Src      Diff_dst Diff_src
======== ======== =========
f32      f32      f32
f16      f16      f16
bf16     bf16     bf16
======== ======== =========
