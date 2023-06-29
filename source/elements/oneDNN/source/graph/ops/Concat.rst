.. SPDX-FileCopyrightText: 2020-2022 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. include:: ../../replacements.inc.rst


Concat
######

Concat operation concatenates :math:`N` tensors over ``axis``
(here designated :math:`C`) and is defined as (the variable names
follow the standard :ref:`conventions-label`):

.. math::

   \dst(\overline{ou}, c, \overline{in}) = \src\_i(\overline{ou}, c’, \overline{in}), 

where :math:`c = C_1 + .. + C_{i-1} {}_{} + c'`.

Operation Attributes
********************

+-------------+---------------+------------+-------------+-------------+
|  Attribute  |  Description  | Value Type |  Supported  | Required or |
|    Name     |               |            |   Values    |  Optional   |
+=============+===============+============+=============+=============+
| |attr_axis| | Specifies     | s64        | A s64 value | Required    |
|             | dimension     |            | in the      |             |
|             | along which   |            | range of    |             |
|             | concatenation |            | [-r, r-1]   |             |
|             | happens       |            | where r =   |             |
|             |               |            | rank(src)   |             |
+-------------+---------------+------------+-------------+-------------+

Execution Arguments
*******************

The inputs and outputs must be provided according to the below index order
when constructing an operation.

Inputs
======


===== ============= ====================
Index Argument Name Required or Optional
===== ============= ====================
0     ``src_i``     Required
===== ============= ====================

@note At least one input tensor is required. Data types and ranks of all
input tensors should match. The dimensions of all input tensors should
be the same except for the dimension specified by ``axis`` attribute.

Outputs
=======


===== ============= ====================
Index Argument Name Required or Optional
===== ============= ====================
0     ``dst``       Required
===== ============= ====================


Supported Data Types
********************

Concat operation supports the following data type combinations.

===== ====
Src_i Dst
===== ====
f32   f32
bf16  bf16
f16   f16
===== ====
