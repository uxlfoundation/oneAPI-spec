.. SPDX-FileCopyrightText: 2023 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0
.. include:: ../../replacements.inc.rst


Select
######

Select operation returns a tensor filled with the elements from the second or
the third input, depending on the condition (the first input) value.

.. math::
    \dst[i] = cond[i] ? \src\_0[i] : \src\_1[i]

Broadcasting is supported.

If the auto_broadcast attribute is not none, the select operation takes a
two-step broadcast before performing the selection:

- **Step 1**: Input tensors \src\_0 and \src\_1 are broadcasted to dst_shape
  according to the Numpy broadcast rules.

- **Step 2**: Then, the cond tensor will be one-way broadcasted to the
  dst_shape of broadcasted \src\_0 and \src\_1. To be more specific, we align
  the two shapes to the right and compare them from right to left. Each 
  dimension should be either equal or the dimension of cond should be 1.

- **example**:

  - cond={4, 5}, dst_shape={2, 3, 4, 5} => dst = {2, 3, 4, 5}
  - cond={3, 1, 5}, dst_shape={2, 3, 4, 5} => dst = {2, 3, 4, 5}
  - cond={3,5}, dst_shape={2, 3, 4, 5} => dst = invalid_shape

Operation Attributes
********************

+-------------------+-------------------+------------+------------+-------------+
|     Attribute     |    Description    | Value Type | Supported  | Required or |
|       Name        |                   |            |   Values   |  Optional   |
+===================+===================+============+============+=============+
| |attr_auto_bcast| | Specifies         | string     | ``none``,  | Optional    |
|                   | rules used        |            | ``numpy``, |             |
|                   | for               |            | (default)  |             |
|                   | auto-broadcasting |            |            |             |
|                   | of src            |            |            |             |
|                   | tensors           |            |            |             |
+-------------------+-------------------+------------+------------+-------------+


Execution Arguments
*******************

The inputs and outputs must be provided according to the below index order
when constructing an operation.

Inputs
======


===== ============= ====================
Index Argument Name Required or Optional
===== ============= ====================
0     ``cond``      Required
1     ``src_0``     Required
2     ``src_1``     Required
===== ============= ====================

@note All input shapes should match and no broadcasting is allowed if the
`auto_broadcast` attribute is set to `none`, or can be broadcasted according to 
the  broadcasting rules mentioned above if `auto_broadcast` attribute set to 
`numpy`.

Outputs
=======


===== ============= ====================
Index Argument Name Required or Optional
===== ============= ====================
0     ``dst``       Required
===== ============= ====================

Supported Data Types
********************

Select operation supports the following data type combinations.

======= ===== ===== ====
Cond    Src_0 Src_1 Dst 
======= ===== ===== ====
boolean f32   f32   f32
boolean bf16  bf16  bf16
boolean f16   f16   f16 
======= ===== ===== ====
