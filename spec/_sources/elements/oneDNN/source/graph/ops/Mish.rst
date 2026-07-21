.. SPDX-FileCopyrightText: 2020-2022 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. include:: ../../replacements.inc.rst


Mish
####

Mish performs element-wise activation function on a given input tensor,
based on the following mathematical formula: 

.. math::
    
    \dst = \src * \tanh(\operatorname{SoftPlus}(src)) = \src * \tanh(\ln(1 + e^{\src}))

Operation Attributes
********************

Mish operation does not support any attribute.

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

Mish operation supports the following data type combinations.

==== ====
Src  Dst
==== ====
f32  f32
bf16 bf16
f16  f16
==== ====
