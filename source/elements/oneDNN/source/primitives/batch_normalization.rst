..
  Copyright 2019-2020 Intel Corporation

.. default-domain:: cpp

Batch normalization
-------------------

Both forward and backward propagation primitives support in-place operation;
that is, ``src`` and ``dst`` can refer to the same memory for forward
propagation, and ``diff_dst`` and ``diff_src`` can refer to the same memory
for backward propagation. You can control the batch normalization primitives'
computations by specifying different :any:`dnnl::normalization_flags` values.
For example, batch normalization can compute the mean and variance on its own
or take them as inputs. It can either perform scaling and shifting using gamma
and beta parameters or not. Optionally, it can also perform a fused ReLU,
which in case of training would also require a workspace.

.. rubric:: API

.. doxygenstruct:: dnnl::batch_normalization_forward
   :project: oneDNN
   :members:

.. doxygenstruct:: dnnl::batch_normalization_backward
   :project: oneDNN
   :members:

.. vim: ts=3 sw=3 et spell spelllang=en
