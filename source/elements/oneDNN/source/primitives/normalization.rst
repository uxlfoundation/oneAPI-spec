..
  Copyright 2019-2020 Intel Corporation

.. default-domain:: cpp

.. _normalization-label:

Normalization
-------------

Normalization primitives smoothen and center the data around statistics
computed for certain slices of the data. They use common
:any:`dnnl::normalization_flags` to control their behavior.

oneDNN supports the following normalization primitives:

.. toctree::

   batch_normalization.rst
   layer_normalization.rst

.. rubric:: Normalization primitives flags

.. doxygenenum:: dnnl::normalization_flags
   :project: oneDNN

.. vim: ts=3 sw=3 et spell spelllang=en
