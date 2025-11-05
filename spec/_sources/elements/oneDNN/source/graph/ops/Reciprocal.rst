.. SPDX-FileCopyrightText: 2020-2022 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. include:: ../../replacements.inc.rst


Reciprocal
##########

Reciprocal operation is element-wise Power operation where
exponent(power) equals to -1. Reciprocal of 0 is infinity.

.. math::
    
    \dst = \begin{cases} \src^{-1} & \text{if}\ \src \neq 0  \\
       \infty & \text{if}\ \src = 0 \end{cases}



Operation Attributes
********************

Reciprocal operation does not support any attribute.

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

Reciprocal operation supports the following data type combinations.

==== ====
Src  Dst
==== ====
f32  f32
bf16 bf16
f16  f16
==== ====
