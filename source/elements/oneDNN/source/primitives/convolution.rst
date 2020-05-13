..
  Copyright 2019-2020 Intel Corporation

.. default-domain:: cpp

.. _convolution-label:

Convolution and Deconvolution
-----------------------------

Convolution and deconvolution primitives performs 1D, 2D or 3D convolution.
Supported variants are forward propagation, backward propagation, and weights
gradient with or without bias.

.. rubric:: API

.. doxygenstruct:: dnnl::convolution_forward
   :project: oneDNN
   :members:

.. doxygenstruct:: dnnl::convolution_backward_data
   :project: oneDNN
   :members:

.. doxygenstruct:: dnnl::convolution_backward_weights
   :project: oneDNN
   :members:

.. doxygenstruct:: dnnl::deconvolution_forward
   :project: oneDNN
   :members:

.. doxygenstruct:: dnnl::deconvolution_backward_data
   :project: oneDNN
   :members:

.. doxygenstruct:: dnnl::deconvolution_backward_weights
   :project: oneDNN
   :members:

.. vim: ts=3 sw=3 et spell spelllang=en
