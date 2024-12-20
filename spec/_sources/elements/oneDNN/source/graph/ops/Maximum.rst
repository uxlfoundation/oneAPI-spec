.. SPDX-FileCopyrightText: 2020-2022 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. include:: ../../replacements.inc.rst


Maximum
#######

Maximum operation performs element-wise maximum operation with two given
tensors applying multi-directional broadcast rules.

.. math::

   \dst(\overline{x}) = \max(\src\_0(\overline{x}), \src\_1(\overline{x})) 

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
0     ``src_0``     Required
1     ``src_1``     Required
===== ============= ====================

@note Both src shapes should match and no auto-broadcasting is allowed
if ``auto_broadcast`` attributes is ``none``. ``src_0`` and ``src_1``
shapes can be different and auto-broadcasting is allowed if
``auto_broadcast`` attributes is ``numpy``. Broadcasting is performed
according to auto_broadcast value.

Outputs
=======


===== ============= ====================
Index Argument Name Required or Optional
===== ============= ====================
0     ``dst``       Required
===== ============= ====================


Supported Data Types
********************

Maximum operation supports the following data type combinations.

============= ====
Src_0 / Src_1 Dst
============= ====
f32           f32
bf16          bf16
f16           f16
============= ====
