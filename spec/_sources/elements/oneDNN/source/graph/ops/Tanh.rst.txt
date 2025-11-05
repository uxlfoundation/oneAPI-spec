.. SPDX-FileCopyrightText: 2020-2022 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. include:: ../../replacements.inc.rst


Tanh
####

Tanh operation applies following formula on every element of
\src tensor (the variable names follow the standard :ref:`conventions-label`):

.. math::
    
    \dst = \tanh(\src)

Operation Attributes
********************

Tanh operation does not support any attribute.

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

Tanh operation supports the following data type combinations.

==== ====
Src  Dst
==== ====
f32  f32
bf16 bf16
f16  f16
==== ====
