.. SPDX-FileCopyrightText: 2019-2020 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. default-domain:: cpp

.. include:: ../replacements.inc.rst

Local Response Normalization
----------------------------

The LRN primitive performs a forward or backward local response normalization
operation defined by the following formulas. Variable names follow the
standard :ref:`conventions-label`.

Forward
~~~~~~~

LRN with algorithm |lrn_across_channels|:

.. math::

       \dst(n, c, h, w) =
           \left\{k + \frac{\alpha}{n_{l}}
               \sum\limits_{i=-(n_{l}-1)/2}^{(n_{l}+1)/2-1}
                   (\src(n, c+i, h, w))^2
           \right\}^{-\beta}
           \cdot
           \src(n, c, h, w),

LRN with algorithm |lrn_within_channel|:

.. math::

       \dst(n, c, h, w) =
           \left\{k + \frac{\alpha}{n_{l}}
               \sum\limits_{i=-(n_{l}-1)/2}^{(n_{l}+1)/2-1}
               \sum\limits_{j=-(n_{l}-1)/2}^{(n_{l}+1)/2-1}
                   (\src(n, c, h+i, w+j))^2
           \right\}^{-\beta}
           \cdot
           \src(n, c, h, w),

where :math:`n_{l}` is the ``local_size``. Formulas are provided for 2D
spatial data case.

Backward
~~~~~~~~

The backward propagation computes :math:`\diffsrc(n, c, h, w)`, based on
:math:`\diffdst(n, c, h, w)` and :math:`\src(n, c, h, w)`.

Execution Arguments
===================

When executed, the inputs and outputs should be mapped to an execution
argument index as specified by the following table.

====================== ========================
Primitive input/output Execution argument index
====================== ========================
:math:`\src`           |DNNL_ARG_SRC|
:math:`\dst`           |DNNL_ARG_DST|
workspace              |DNNL_ARG_WORKSPACE|
:math:`\diffsrc`       |DNNL_ARG_DIFF_SRC|
:math:`\diffdst`       |DNNL_ARG_DIFF_DST|
====================== ========================

*****************
Operation Details
*****************

1. During training, LRN might or might not require a workspace on forward and
   backward passes. The behavior is implementation specific. Optimized
   implementations typically require a workspace and use it to save some
   intermediate results from the forward pass that accelerate computations on
   the backward pass. To check whether a workspace is required, query the LRN
   primitive descriptor for the workspace. Success indicates that the
   workspace is required and its description will be returned.

*****************
Data Type Support
*****************

The LRN primitive supports the following combinations of data types.

.. note::

   Here we abbreviate data types names for readability. For example, |_f32| is
   abbreviated to |f32|.

================== ====================
Propagation        Source / Destination
================== ====================
forward / backward |f32|, |bf16|
forward            |f16|
================== ====================

*******************
Data Representation
*******************

Source, Destination, and Their Gradients
========================================

Like most other primitives, the LRN primitive expects the following tensors:

======= =============================================
Spatial Source / Destination
======= =============================================
0D      :math:`N \times C`
1D      :math:`N \times C \times W`
2D      :math:`N \times C \times H \times W`
3D      :math:`N \times C \times D \times H \times W`
======= =============================================

The LRN primitive is optimized for the following memory formats:

======= ============== =====================================================
Spatial Logical tensor Implementations optimized for memory formats
======= ============== =====================================================
2D      NCHW           |nchw| (|abcd|), |nhwc| (|acdb|), *optimized*
======= ============== =====================================================

Here *optimized* means the format chosen by the preceding compute-intensive
primitive.

***********************
Post-ops and Attributes
***********************

The LRN primitive does not support any post-ops or attributes.

***
API
***

.. doxygenstruct:: dnnl::lrn_forward
   :project: oneDNN
   :members:

.. doxygenstruct:: dnnl::lrn_backward
   :project: oneDNN
   :members:


.. vim: ts=3 sw=3 et spell spelllang=en
