.. SPDX-FileCopyrightText: 2022 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. default-domain:: cpp

.. include:: ../replacements.inc.rst

#########
Reduction
#########

The reduction primitive performs a reduction operation on one or
multiple arbitrary dimensions, with respect to a specified algorithm.
Variable names follow the standard :ref:`conventions-label`.

.. math::

   \dst(f) = \mathop{reduce\_op}\limits_{r \in R}\src(r),

where :math:`reduce\_op` can be max, min, sum, mul, mean, Lp-norm and
Lp-norm-power-p, :math:`f` is an index in an idle dimension and
:math:`r` is an index in a reduction dimension :math:`R`.

The reduction algorithms are specified as follow.

Mean:

.. math::

   \dst(f) = \frac{\sum\limits_{r \in R}\src(r)} {\|R\|},

where :math:`|R|` is the size of a reduction dimension.

Lp-norm:

.. math::

   \dst(f) = \root p \of {\mathop{eps\_op}(\sum\limits_{r \in R}|src(r)|^p, eps)},


where :math:`eps\_op` can be max and sum.

Lp-norm-power-p:

.. math::

   \dst(f) = \mathop{eps\_op}(\sum\limits_{r}|src(r)|^p, eps),


where :math:`eps\_op` can be max and sum.

.. note::

 * The reduction primitive requires the source and destination tensors to have
   the same number of dimensions.
 * Dimensions which are reduced are of size 1 in the destination tensor.
 * The reduction primitive does not have a notion of forward or backward
   propagations.

*******************
Execution Arguments
*******************

When executed, the inputs and outputs should be mapped to an execution
argument index as specified by the following table.

====================== ========================
Primitive input/output Execution argument index
====================== ========================
:math:`\src`           |DNNL_ARG_SRC|
:math:`\dst`           |DNNL_ARG_DST|
====================== ========================

*****************
Operation Details
*****************

The \dst memory format can be either specified explicitly or by
using the special format tag |any| (recommended), in which case the
primitive will derive the most appropriate memory format based on the
format of the source tensor.

******************
Data Types Support
******************

The reduction primitive supports the following combinations of data types:

================== =======================================
Propagation        Source / Destination
================== =======================================
forward / backward |f32|, |s32|, |bf16|, |f16|, |s8|, |u8|
================== =======================================

*******************
Data Representation
*******************

The reduction primitive works with arbitrary data tensors. There is no special
meaning associated with any of the dimensions of a tensor.


***********************
Attributes and Post-ops
***********************

+-----------+---------------------------------------------------------------------+-------------------------------------------------------------------------------+------------------------+
| Type      | Operation                                                           | Description                                                                   | Restrictions           |
+===========+=====================================================================+===============================================================================+========================+
| Attribute | :any:`Scales <dnnl::primitive_attr::set_scales_mask>`               | Sets scale(s) for the corresponding tensor(s)                                 | Int8 computations only |
+-----------+---------------------------------------------------------------------+-------------------------------------------------------------------------------+------------------------+
| Attribute | :any:`Zero points <dnnl::primitive_attr::set_zero_points_mask>`     | Sets zero point(s) for the corresponding tensors                              | Int8 computations only |
+-----------+---------------------------------------------------------------------+-------------------------------------------------------------------------------+------------------------+
| post-op   | :any:`Eltwise <dnnl::post_ops::append_eltwise>`                     | Applies an elementwise operation to the result                                |                        |
+-----------+---------------------------------------------------------------------+-------------------------------------------------------------------------------+------------------------+
| post-op   | :any:`Binary <dnnl::post_ops::append_binary>`                       | Applies a binary operation to the result                                      |                        |
+-----------+---------------------------------------------------------------------+-------------------------------------------------------------------------------+------------------------+

***
API
***

.. doxygenstruct:: dnnl::reduction
   :project: oneDNN
   :members:
