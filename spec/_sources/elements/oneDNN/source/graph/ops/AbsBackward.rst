.. SPDX-FileCopyrightText: 2020-2022 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. include:: ../../replacements.inc.rst


AbsBackward
###########

AbsBackward operation computes gradient for Abs operation.

.. math::

   \dst =
   \begin{cases} \diffdst & \text{if}\ src > 0 \\
       -\diffdst & \text{if}\ src < 0 \\
       0 & \text{if}\ src = 0 \\
       \end{cases}



Operation Attributes
********************

AbsBackward operation does not support any attribute.

Execution Arguments
*******************

The inputs and outputs must be provided according to the below index order
when constructing an operation.

Inputs
======


===== ============= ====================
Index Argument Name Required or Optional
===== ============= ====================
0     \src          Required
1     \diff_dst     Required
===== ============= ====================

Outputs
=======


===== ============= ====================
Index Argument Name Required or Optional
===== ============= ====================
0     \diff_src     Required
===== ============= ====================


Supported Data Types
********************

AbsBackward operation supports the following data type combinations.

==== ======== ========
Src  Diff_dst Diff_src
==== ======== ========
f32  f32      f32
f16  f16      f16
bf16 bf16     bf16
==== ======== ========
