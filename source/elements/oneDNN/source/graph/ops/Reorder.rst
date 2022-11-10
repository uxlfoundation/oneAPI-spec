.. SPDX-FileCopyrightText: 2020-2022 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. include:: ../../replacements.inc.rst


Reorder
#######

Reorder operation converts \src tensor to
\dst tensor with different layout. It supports the
conversion between:

-  two different opaque layouts
-  two different strided layouts
-  one strided layout and another opaque layout

Reorder operation does not support layout conversion cross different
backends or different engines. Unlike `reorder
primitive :ref:`reorder-label`, Reorder operation cannot be
used to cast the data type from \src to \dst.
Please check the usage of `TypeCast :ref:`op_typecast-label`
and `Dequantize :ref:`op_dequantize-label` operation.

Operation Attributes
********************

Reorder operation does not support any attribute.

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

Reorder operation supports the following data type combinations.

==== ====
Src  Dst
==== ====
f32  f32
bf16 bf16
f16  f16
==== ====
