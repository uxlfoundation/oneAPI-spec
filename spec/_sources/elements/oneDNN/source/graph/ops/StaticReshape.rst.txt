.. SPDX-FileCopyrightText: 2020-2022 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. include:: ../../replacements.inc.rst


StaticReshape
#############

StaticReshape operation changes dimensions of \src tensor
according to the specified shape. The volume of \src is
equal to \dst, where volume is the product of dimensions.
\dst may have a different memory layout from
\src. StaticReshape operation is not guaranteed to return a
view or a copy of \src when \dst is in-placed
with the \src. StaticReshape can be used where if shape is
stored in a constant node or available during graph building stage. Then
shape can be passed via ``shape`` attribute.

Operation Attributes
********************

+---------------------+-------------------+------------+-----------+-------------+
|      Attribute      |    Description    | Value Type | Supported | Required or |
|        Name         |                   |            |  Values   |  Optional   |
+=====================+===================+============+===========+=============+
| |attr_shape|        | Specifies         | string     | ``none``, | Required    |
|                     | rules used        |            | ``numpy`` |             |
|                     | for               |            | (default) |             |
|                     | auto-broadcasting |            |           |             |
|                     | of src            |            |           |             |
|                     | tensors           |            |           |             |
+---------------------+-------------------+------------+-----------+-------------+
| |attr_special_zero| | Controls          | bool       | ``true``, | Required    |
|                     | how zero          |            | ``false`` |             |
|                     | values in         |            |           |             |
|                     | shape are         |            |           |             |
|                     | interpreted       |            |           |             |
|                     |                   |            |           |             |
+---------------------+-------------------+------------+-----------+-------------+

@note |attr_shape|: dimension ``-1`` means that this dimension is
calculated to keep the same overall elements count as the src tensor.
That case that more than one ``-1`` in the shape is not supported.

@note |attr_special_zero|: if false, ``0`` in the shape is interpreted
as-is (for example a zero-dimension tensor); if true, then all ``0``\ s
in shape implies the copying of corresponding dimensions from src into
dst.

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

StaticReshape operation supports the following data type combinations.

==== ====
Src  Dst
==== ====
f32  f32
bf16 bf16
f16  f16
==== ====
