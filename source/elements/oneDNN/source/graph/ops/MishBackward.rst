.. SPDX-FileCopyrightText: 2020-2022 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. include:: ../../replacements.inc.rst


MishBackward
############

MishBackward operation computes gradient for Mish.

.. math::
    
    \dst & = \diffdst * \frac{e^{\src} * \omega}{\delta^{2}}

where

.. math::
    \omega & = e^{3\src} + 4 * e^{2\src} + e^{\src} * (4 * \src + 6) + 4 * (\src + 1) \\
    \delta & = e^{2\src} + 2 * e^{\src} + 2 

Operation Attributes
********************

MishBackward operation does not support any attribute.

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

MishBackward operation supports the following data type combinations.

==== ======== ========
Src  Diff_dst Diff_src
==== ======== ========
f32  f32      f32
f16  f16      f16
bf16 bf16     bf16
==== ======== ========
