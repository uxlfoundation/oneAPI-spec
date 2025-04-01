.. SPDX-FileCopyrightText: 2019-2022 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. default-domain:: cpp

.. include:: ../replacements.inc.rst

#####
Prelu
#####

The prelu primitive (Leaky ReLU with trainable alpha parameter) performs
forward or backward operation on data tensor. Weights (alpha) tensor supports
broadcast-semantics.


Broadcast configuration is assumed based on src and
weights dimensions.

*******
Forward
*******

The prelu operation is defined by the following formulas.  We show
formulas only for 2D spatial data which are straightforward to
generalize to cases of higher and lower dimensions. Variable names
follow the standard :ref:`conventions-label`.

.. math::

    \dst(n, c, h, w) =
        \begin{cases}
        \src(n, c, h, w)  & \mbox{if } \src(n, c, h, w) > 0 \\
        \src(n, c, h, w) \cdot \weights(n, c, h, w) & \mbox{if }
        \src(n, c, h, w) \leq 0
        \end{cases}


Difference Between Forward Training and Forward Inference
=========================================================

There is no difference between the |forward_training| and |forward_inference|
propagation kinds.

********
Backward
********

The backward propagation computes :math:`\diffsrc` and :math:`\diffweights`.
For no broadcast case, results are calculated using formula:

.. math::

    \diffsrc(n, c, h, w) &=
        \begin{cases}
        \diffdst(n, c, h, w)  & if \src(n, c, h, w) > 0 \\
        \diffdst(n, c, h, w) \cdot \weights(n, c, h, w) &
        if  \src(n, c, h, w) \leq 0
        \end{cases}\\\\

.. math::

   \diffweights(n, c, h, w) =
        \min(\src(n, c, h, w), 0) \cdot \diffdst(n, c, h, w)

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
:math:`\weights`       |DNNL_ARG_WEIGHTS|
:math:`\diffsrc`       |DNNL_ARG_DIFF_SRC|
:math:`\diffdst`       |DNNL_ARG_DIFF_DST|
:math:`\diffweights`   |DNNL_ARG_DIFF_WEIGHTS|
====================== ========================

*****************
Operation Details
*****************

1. All input and output tensors must have the same number of
   dimensions.

2. :math:`\weights` tensor dimensions must follow broadcast semantics.
   Each dimension can either be equal to the corresponding data dimension or
   equal to 1 to indicate a broadcasted dimension.

***********************
Post-ops and Attributes
***********************

The prelu primitive does not have to support any post-ops or attributes.

******************
Data Types Support
******************

The PReLU primitive supports the following combinations of data types:

.. note::

   Here we abbreviate data types names for readability. For example, |_f32| is
   abbreviated to |f32|.


================== =======================================
Propagation        Source / Destination
================== =======================================
forward / backward |f32|, |s32|, |bf16|, |f16|, |s8|, |u8|
================== =======================================

*******************
Data Representation
*******************

Source, Destination, and Their Gradients
========================================

The PReLU primitive works with arbitrary data tensors. There is no special
meaning associated with any logical dimensions.


***
API
***

.. doxygenstruct:: dnnl::prelu_forward
   :project: oneDNN
   :members:

.. doxygenstruct:: dnnl::prelu_backward
   :project: oneDNN
   :members:


