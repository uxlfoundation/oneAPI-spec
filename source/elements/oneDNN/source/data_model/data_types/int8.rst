..
  Copyright 2019-2020 Intel Corporation

.. default-domain:: cpp

Int8
++++

To push higher performance during inference computations, recent work has
focused on computing at a lower precision (that is, shrinking the size of data
for activations and weights) to achieve higher throughput. Eight-bit
computations (referred to as int8) offer improved performance over
higher-precision types because they enable packing more data into a single
instruction, at the cost of reduced (but acceptable) accuracy.

Workflow
--------

There are different ways to use lower precision to perform inference. Please
go through the :ref:`attributes-quantization-label` page to get the initial
understanding of what kind of quantization model oneDNN supports.

Quantization
~~~~~~~~~~~~

To operate with int8 data types from a higher-precision format (for example,
32-bit floating point), data must first be *quantized*. The quantization
process converts a given input into a lower-precision format. The precision
and accuracy factors are determined by the scaling factors.

Range of the data
~~~~~~~~~~~~~~~~~

The data range is usually obtained by sampling the dataset of previous
executions in the original data type (for example, the activations and weights
from training in f32):

.. math::

   R = max(abs(T)).

Here :math:`T` is a tensor corresponding to either the weights or the
activations. Establishing the range of values used in the computation, and
selecting a proper scaling factor prevents over- or underflows during
computation of the lower-precision results.

Scaling Factor
~~~~~~~~~~~~~~

The *quantization factor* is used to convert the original values into the
corresponding int8 range and is calculated as:

-  :math:`Q_{\alpha} = \frac{255}{R_{\alpha}}` is the quantization factor
   for activations with non-negative values,

-  :math:`Q_{w} = \frac{127}{R_{w}}` is the quantization factor for weights.

The *quantized* activation, weights, and bias values are calculated as:

-  :math:`\alpha_{u8} = \lceil Q_{\alpha} \alpha_{f32} \rceil \in [0,255]`,

-  :math:`W_{s8} = \lceil Q_{w} W_{f32} \rceil \in [-127,127]`,

-  :math:`b_{s32} = \lceil Q_{\alpha} Q_{w} b_{f32} \rceil \in [-2^{31},2^{31}-1]`.

Here the :math:`\lceil \cdot \rceil` operator rounds according to the hardware
rounding mode.

When the destination value is stored as a signed 32-bit integer, the result is
bound to the same quantization *scaling factors*:

-  :math:`X_{s32} = W_{s8} \times \alpha{u8} + b_{s32} \approx Q_{\alpha} Q_{\omega} X_{f32}`,

-  where :math:`X_{f32} = W_{f32} \times \alpha_{f32} + b_{f32}`,

Here the approximation is used to denote rounding. The dequantized value is
calculated as

-  :math:`X_{f32} \approx \frac{1}{Q_{\alpha} Q_{\omega}} X_{s32}`.

Quantization Example
~~~~~~~~~~~~~~~~~~~~

To show how the quantization parameters are obtained, suppose we first start
with a set of high-precision input and output values. These values come from
sampling a previously executed training run and are stored as 32-bit floating
point values:

-  activations: :math:`T_{\alpha} = [15, 14, 15 \ldots, 8, 11 ]`,
   where :math:`max(abs(T_{\alpha})) = 15`;

-  weights: :math:`T_{\omega} = [-5.1 , 6.8, \ldots, -1.2, 9.8 ]`,
   where :math:`max(abs(T_{\omega})) = 9.8`;

-  bias: :math:`T_{\alpha} = [ 2.4, -5.2 \ldots, -8 ]` where
   :math:`max(abs(T_{\alpha})) = 8`.

The scaling factors are:

-  :math:`Q_{\alpha} = \frac{255}{R_{\alpha}} = \frac{255}{15} = 17`;

-  :math:`Q_{w} = \frac{127}{R_{w}} = \frac{127}{9.8} = 12.96`.

Finally, the quantized input values for the int8 operation are calculated as:

- :math:`\alpha_{u8} = \lceil Q_{\alpha} \alpha_{f32} \rceil = \lceil 17 \times [15, 14, \ldots, 11]\rceil = [255, 238, \ldots, 187]`,

- :math:`W_{s8} = \lceil Q_{w} W_{f32} \rceil
  = \lceil 12.96 \times [-5.1 , 6.8, ... -1.2, 9.8] \rceil
  = [-66, 88, \dots, -15, 127]`,

- :math:`b_{s32} = \lceil Q_{\alpha} Q_{w} b_{f32} \rceil  = \lceil 17 \times 12.96 \times [ 2.4, -5.2 ... -8 ] \rceil  = [528, -1145, \ldots, -1762]`.

These arrays are the new inputs for the int8 net.

Support
-------

oneDNN supports int8 computations for inference by allowing to specify that
primitives input and output memory objects use int8 data types.

Attributes
~~~~~~~~~~

Scaling factors can be configured using **primitive attributes**. It is also
possible to specify fused post-ops. All primitives support the attributes but,
not all combinations of parameters may be supported, in which case the library
returns an error.

In oneDNN, the scaling factor is applied to the output of a primitive.
Moreover, to perform input transformations (for example, source, bias, and
weights), oneDNN performs quantizing and dequantizing of data for int8 through
the *reorder primitive*.

oneDNN uses *mask* to describe dimensions to which the scales array is
applied. For an :math:`n`-dimensional tensor :math:`T[D_0, \ldots, D_{n-1}]`,
each :math:`i`-th bit of the mask selects the corresponding dimension
:math:`D_i` of an :math:`n`-dimensional tensor. The :math:`mask = 0` implies
that there is a single scaling factor for the whole tensor.

For example, for a 5-dimensional tensor :math:`T[G_0, O_1, I_2, H_3, W_4]`
where the indices denote positions of bits in the mask

- a :math:`mask = 2 = 2^1` implies that there is a scaling factor per output
  channel as the corresponding dimension index is :math:`1`;

- a :math:`mask = 3 = 2^1 | 2^0` selects the group and output channels.

The mask is always applied to the logical dimensions and thus is independent
of the memory format that the primitive might select.

Fused :ref:`post-ops <post_ops-label>` allow chaining computations. Note that
the resulting output value from post-ops is always affected by the scaling
factor.

.. vim: ts=3 sw=3 et spell spelllang=en
