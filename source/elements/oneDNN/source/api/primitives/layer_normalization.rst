..
  Copyright 2019 Intel Corporation

.. default-domain:: cpp

Layer Normalization
~~~~~~~~~~~~~~~~~~~

A primitive to perform layer normalization. Normalization is performed within
the last logical dimension of data tensor. Both forward and backward propagation
primitives support in-place operation; that is, ``src`` and ``dst`` can refer to
the same memory for forward propagation, and ``diff_dst`` and ``diff_src`` can
refer to the same memory for backward propagation. You can control the layer
normalization primitives' computations by specifying different
``dnnl::normalization_flags`` values. For example, you can configure layer
normalization forward propagation to either compute the mean and variance or
take them as arguments. Layer normalization can either perform scaling and
shifting using gamma and beta parameters or not. Optionally, it can also perform
a fused ReLU, which in case of training would also require a workspace.

API
+++

.. doxygenstruct:: dnnl::layer_normalization_forward
   :project: oneDNN
   :members:

.. doxygenstruct:: dnnl::layer_normalization_backward
   :project: oneDNN
   :members:

