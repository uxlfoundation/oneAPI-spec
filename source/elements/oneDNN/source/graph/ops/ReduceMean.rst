.. SPDX-FileCopyrightText: 2020-2022 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. include:: ../../replacements.inc.rst


ReduceMean
##########
ReduceMean operation performs the reduction with finding the arithmetic
mean on a given \src data along dimensions specified by axes.

Take channel axis = 0 and keep_dims = True as an example:

.. math::
  
  \dst_{0,\cdots,\cdots} = \frac{1}{channelNum} \cdot \sum\limits_{i}{\src_{i,\cdots,\cdots}} ,i \in [0,channelNum-1]

Operation Attributes
********************

+------------------+---------------+------------+---------------------+-------------+
|    Attribute     |  Description  | Value Type |      Supported      | Required or |
|       Name       |               |            |       Values        |  Optional   |
+==================+===============+============+=====================+=============+
| |attr_axes|      | Specify       | s64        | A s64 list          | Optional    |
|                  | indices of    |            | values              |             |
|                  | src tensor,   |            | which is in         |             |
|                  | along which   |            | the range           |             |
|                  | the           |            | of [-r,r-1]         |             |
|                  | reduction     |            | where               |             |
|                  | is            |            | r = rank(src).      |             |
|                  | performed.    |            | Empty list(default) |             |
|                  | If axes is    |            |                     |             |
|                  | a list,       |            |                     |             |
|                  | reduce over   |            |                     |             |
|                  | all of        |            |                     |             |
|                  | them. If      |            |                     |             |
|                  | axes is       |            |                     |             |
|                  | empty,        |            |                     |             |
|                  | corresponds   |            |                     |             |
|                  | to the        |            |                     |             |
|                  | identity      |            |                     |             |
|                  | operation.    |            |                     |             |
|                  | If axes       |            |                     |             |
|                  | contains      |            |                     |             |
|                  | all           |            |                     |             |
|                  | dimensions    |            |                     |             |
|                  | of src        |            |                     |             |
|                  | tensor, a     |            |                     |             |
|                  | single        |            |                     |             |
|                  | reduction     |            |                     |             |
|                  | value is      |            |                     |             |
|                  | calculated    |            |                     |             |
|                  | for the       |            |                     |             |
|                  | entire src    |            |                     |             |
|                  | tensor.       |            |                     |             |
|                  | Exactly one   |            |                     |             |
|                  | of            |            |                     |             |
|                  | attribute     |            |                     |             |
|                  | |attr_axes|   |            |                     |             |
|                  | and the       |            |                     |             |
|                  | second        |            |                     |             |
|                  | input         |            |                     |             |
|                  | tensor        |            |                     |             |
|                  | ``axes``      |            |                     |             |
|                  | should be     |            |                     |             |
|                  | available.    |            |                     |             |
+------------------+---------------+------------+---------------------+-------------+
| |attr_keep_dims| | If set to     | bool       | ``true``,           | Optional    |
|                  | ``true`` it   |            | ``false``           |             |
|                  | holds axes    |            | (default)           |             |
|                  | that are      |            |                     |             |
|                  | used for      |            |                     |             |
|                  | reduction.    |            |                     |             |
|                  | For each      |            |                     |             |
|                  | such axes,    |            |                     |             |
|                  | dst           |            |                     |             |
|                  | dimension     |            |                     |             |
|                  | is equal to   |            |                     |             |
|                  | 1.            |            |                     |             |
+------------------+---------------+------------+---------------------+-------------+

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
1     ``axes``      Optional
===== ============= ====================

@note ``axes`` is an 1-D tensor specifying the axis along which the
reduction is performed. 1D tensor of unique elements. The range of
elements is [-r, r-1], where r is the rank of src tensor. Exactly one of
attribute axes and the second input tensor axes should be available.

Outputs
=======


===== ============= ====================
Index Argument Name Required or Optional
===== ============= ====================
0     ``dst``       Required
===== ============= ====================

@note The result of ReduceMean function applied to src tensor. shape[i]
= shapeOf(data)[i] for all i that is not in the list of axes from the
second input. For dimensions from axes, shape[i] == 1 if keep_dims ==
True, or i-th dimension is removed from the dst otherwise.


Supported Data Types
********************

ReduceMean operation supports the following data type combinations.

==== ==== ====
Src  Dst  Axes
==== ==== ====
f32  f32  s32
bf16 bf16 s32
f16  f16  s32
==== ==== ====
