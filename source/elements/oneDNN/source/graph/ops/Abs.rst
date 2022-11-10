.. SPDX-FileCopyrightText: 2020-2022 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. include:: ../../replacements.inc.rst


Abs
###

Abs operation performs element-wise the absolute value with given
tensor, it applies following formula on every element of
\src tensor (the variable names follow the standard :ref:`conventions-label`):

.. math::

   dst = \begin{cases}
      src  & \text{if}\ src \ge 0 \\
      -src & \text{if}\ src < 0
      \end{cases}



Operation Attributes
********************

Abs operation does not support any attribute.

Execution Arguments
*******************

Inputs
======


===== ============= ====================
Index Argument Name Required or Optional
===== ============= ====================
0     \src          Required
===== ============= ====================

Outputs
=======


===== ============= ====================
Index Argument Name Required or Optional
===== ============= ====================
0     \dst          Required
===== ============= ====================


Supported Data Types
********************

Abs operation supports the following data type combinations.

==== ====
Src  Dst
==== ====
f32  f32
f16  f16
bf16 bf16
==== ====
