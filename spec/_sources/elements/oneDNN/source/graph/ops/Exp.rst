.. SPDX-FileCopyrightText: 2020-2022 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. include:: ../../replacements.inc.rst


Exp
###

Exp operation is an exponential element-wise activation function, it
applies following formula on every element of \src tensor
(the variable names follow the standard :ref:`conventions-label`):

.. math::

   dst = e^{src}


Operation Attributes
********************

Exp operation does not support any attribute.

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

Exp operation supports the following data type combinations.

==== ====
Src  Dst
==== ====
f32  f32
f16  f16
bf16 bf16
==== ====
