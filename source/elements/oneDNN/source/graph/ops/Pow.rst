.. SPDX-FileCopyrightText: 2023 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. include:: ../../replacements.inc.rst

Pow
###

## General

Pow operation performs an element-wise power operation on a given input tensor
with a single value attribute beta as its exponent. It is based on the following
mathematical formula:

.. math::

  \dst_i = \src_i ^ \beta

## Operation attributes

+--------------+----------------+------------+--------------+-------------+
|  Attribute   | Description    | Value Type |  Supported   | Required or |
|     Name     |                |            |    Values    |  Optional   |
+==============+================+============+==============+=============+
| |attr_beta|  | exponent,      | f32        | Arbitrary    |  Required   |
|              | :math:`\beta`  |            | f32 value    |             |
|              | in the         |            |              |             |
|              | formula.       |            |              |             |
+--------------+----------------+------------+--------------+-------------+

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

Pow operation supports the following data type combinations.

==== ====
Src  Dst
==== ====
f32  f32
bf16 bf16
f16  f16
==== ====
