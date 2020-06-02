..
  Copyright 2019-2020 Intel Corporation

.. default-domain:: cpp

Int8
++++

To push higher performance during inference computations, recent work
has focused on computing at a lower precision (that is, shrinking the
size of data for activations and weights) to achieve higher throughput.
Eight-bit computations (referred to as int8) offer improved performance
over higher-precision types because they enable packing more data into a
single instruction, at the cost of reduced (but acceptable) accuracy.

Workflow
--------

There are different ways to use lower precision to perform inference. Please
go through the :ref:`attributes-quantization-label` page to get the initial
understanding of what kind of quantization model oneDNN supports.

Quantization
~~~~~~~~~~~~

To operate with int8 data types from a higher-precision format (for
example, 32-bit floating point), data must first be *quantized*. The
quantization process converts a given input into a lower-precision
format. The precision and accuracy factors are determined by the scaling
factors.

Scale
~~~~~

The scale is usually obtained from sampling the dataset of previous executions
in the original format (for example, the activations and weights from training
in f32) and is formulated as:

.. math::

   R_{\{\alpha,w\}} = max(abs(T_{\{\alpha,w\}})),

where :math:`T_{\{\alpha,w\}}` is a tensor corresponding to either the weights
:math:`w` or the activations :math:`\alpha`.

The purpose is to establish the range of values used in the computation,
where selecting a proper scaling factor prevents over- or underflows
during computation of the lower-precision results.

Quantization Factor
~~~~~~~~~~~~~~~~~~~

The next step is to calculate the *quantization factor* for converting
the values into the corresponding int8 range. This is also known as the
*scale* or *scaling factor* applied to the original high-precision
values and is calculated as:

-  :math:`Q_{\alpha} = \frac{255}{R_{\alpha}}` is the quantization factor
   for activations with non-negative values,

-  :math:`Q_{w} = \frac{127}{R_{w}}` is the quantization factor for weights.

The low-precision values, known as the *quantized* activation, weights, and
bias values, are calculated as:

-  :math:`\alpha_{u8} = \lceil Q_{\alpha} \alpha_{f32} \rceil \in [0,255]`,

-  :math:`W_{s8} = \lceil Q_{w} W_{f32} \rceil \in [-127,127]`,

-  :math:`b_{s32} = \lceil Q_{\alpha} Q_{w} b_{f32} \rceil \in [-2^{31},2^{31}-1]`.

where the :math:`\lceil \cdot \rceil` operator rounds according to a hardware
rounding mode.

When the destination value (for example, from a convolution) is stored as a
signed 32-bit integer, the result is bound to the same quantization *scaling*
factors:

-  :math:`X_{s32} = W_{s8} \times \alpha{u8} + b_{s32} \approx Q_{\alpha} Q_{\omega} X_{f32}`,

-  where :math:`X_{f32} = W_{f32} \times \alpha_{f32} + b_{f32}`,

where the approximated value is due to the rounded values. Inversely, the
dequantized value is calculated as:

-  :math:`X_{f32} \approx \frac{1}{Q_{\alpha} Q_{\omega}} X_{s32}`.

Quantization Example
~~~~~~~~~~~~~~~~~~~~

To show how the int8 parameters are obtained, suppose we first start off
with a set of arbitrary high-precision input and output values. These
values come from sampling a previously executed training run and are in
their original 32-bit floating point format as:

-  activations: :math:`T_{\alpha} = [15, 14, 15 \ldots, 8, 11 ]`,
   where :math:`max(abs(T_{\alpha})) = 15`;

-  weights: :math:`T_{\omega} = [-5.1 , 6.8, \ldots, -1.2, 9.8 ]`,
   where :math:`max(abs(T_{\omega})) = 9.8`;

-  bias: :math:`T_{\alpha} = [ 2.4, -5.2 \ldots, -8 ]` where
   :math:`max(abs(T_{\alpha})) = 8`.

The scaling factors are:

-  :math:`Q_{\alpha} = \frac{255}{R_{\alpha}} = \frac{255}{15} = 17`;

-  :math:`Q_{w} = \frac{127}{R_{w}} = \frac{127}{9.8} = 12.96`.

Finally, the quantized input values for the 8-bit operation are calculated as:

- :math:`\alpha_{u8} = \lceil Q_{\alpha} \alpha_{f32} \rceil = \lceil 17 \times [15, 14, \ldots, 11]\rceil = [255, 238, \ldots, 187]`,

- :math:`W_{s8} = \lceil Q_{w} W_{f32} \rceil
  = \lceil 12.96 \times [-5.1 , 6.8, ... -1.2, 9.8] \rceil
  = [-66, 88, \dots, -15, 127]`,

- :math:`b_{s32} = \lceil Q_{\alpha} Q_{w} b_{f32} \rceil  = \lceil 17 \times 12.96 \times [ 2.4, -5.2 ... -8 ] \rceil  = [528, -1145, \ldots, -1762]`.

These arrays are the new inputs for the int8 net.

Support
-------

oneDNN supports low-precision computations for inference through the int8
primitives. Int8 primitives are ordinary oneDNN primitives that have their
input memory objects store 8-bit integer data.

Attributes
~~~~~~~~~~

oneDNN primitive behavior may be extended for additional functionalities
involving output data transformation. These additional features are configured
via *primitive attributes*. The primitive attributes are used for passing
extra parameters to a primitive descriptor. The parameters include scaling
factors and fused post-ops. All operation primitives support the attributes
structure; however, some configurations are not implemented and result in
*failed primitive creation*.

The *scaling factor*, as previously described, is known prior to the
inference operation where the values are calculated from a set of
formulas. In oneDNN, the scaling factor is applied to the output of a
primitive. Moreover, to perform input transformations (for example,
source, bias, and weights), oneDNN performs quantizing and dequantizing
of data for int8 through the *Reorder Primitive*.

oneDNN has two formats for defining the output scaling factor. Depending
on the configuration set by the scaling mask, either the output is
scaled uniformly across all the dimensions (*mask = 0*) or a set of
scaling values is applied to specific dimensions, as explained below:

-  A *single floating point value* shared across the tensor:

.. image:: ../../_static/img_singlescalar.png
   :alt: Single-value scaling format

-  An array of floating point values each corresponding to a specific
   output channel:

.. image:: ../../_static/img_multiscalar.png
   :alt: Multi-value scaling format

The *mask* parameter determines the dimension to which the scales array is
applied. The :math:`i`-th bit of the mask selects the dimension :math:`D_i` of
an :math:`n`-dimensional tensor :math:`T[D_0, \ldots, D_{n-1}]`. For example:

-  The single-scale format always has mask = 0.

-  For a 5-dimensional tensor :math:`T[G_0, O_1, I_2, H_3, W_4]` where the
   indices correspond to the positions of bits in the mask:

   -  A :math:`mask = 2 = 2^1` selects the output channel for scaling.

   -  A :math:`mask = 3 = 2^1 | 2^0` selects the group and output channels.

The mask is always applied to the logical dimensions and thus is independent
of the memory format that the primitive might select.

Fused :ref:`post-ops <post_ops-label>` allow chaining computations. Note that
the resulting output value from post-ops is always affected by the scaling
factor.

.. vim: ts=3 sw=3 et spell spelllang=en
