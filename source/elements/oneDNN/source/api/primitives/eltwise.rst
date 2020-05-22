..
  Copyright 2019-2020 Intel Corporation

.. default-domain:: cpp

Element-wise
~~~~~~~~~~~~

A primitive to perform element-wise operations such as the rectifier linear unit
(ReLU).

Both forward and backward propagation primitives support in-place operation;
that is, ``src`` and ``dst`` can refer to the same memory for forward
propagation, and ``diff_dst`` and ``diff_src`` can refer to the same memory for
backward propagation.

.. warning::

   Because the original source data is required for backward propagation,
   in-place forward propagation is not generally supported in the training mode.
   However, for ReLU with the alpha parameter set to 0, either ``dst`` or
   ``src`` can be used for the backward propagation, which makes possible a
   performance benefit even in the training mode.

API
+++

.. doxygenstruct:: dnnl::eltwise_forward
   :project: oneDNN
   :members:

.. doxygenstruct:: dnnl::eltwise_backward
   :project: oneDNN
   :members:

