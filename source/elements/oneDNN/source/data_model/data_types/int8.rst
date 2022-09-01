.. SPDX-FileCopyrightText: 2019-2020 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. default-domain:: cpp

####
Int8
####

To push higher performance during inference computations, recent work has
focused on computations that use activations and weights stored at lower
precision to achieve higher throughput. Int8 computations offer improved
performance over higher-precision types because they enable packing more
computations into a single instruction, at the cost of reduced (but
acceptable) accuracy.

********
Workflow
********

oneDNN support symmetric and assymetric quantization models.

.. _int8-quantization-label:

Quantization Model
==================

.. TODO: Add zero point support.
.. TODO: Add RNN support.
.. TODO: Put the v3 variant of quantization.

The primary quantization model that the library assumes is the following:

.. math::

    x_{f32}[:] = scale_{f32} \cdot (x_{int8}[:] - 0_{x_{int8}})

where :math:`scale_{f32}` is a *scaling factor* that is somehow known in advance
and :math:`[:]` is used to denote elementwise application of the formula to the
arrays. Typically, the process of computing scale factors is called
*calibration*. The library cannot compute any of the scale factors at run-time
dynamically.  Hence, the model is sometimes called a *static* quantization
model. The main rationale to support only *static* quantization out-of-the-box
is higher performance. To use *dynamic* quantization:

1. Compute the result in higher precision, like |_s32|.
2. Find the required characteristics, like min and max values, and derive the
   scale factor.
3. Re-quantize to the lower precision data type.

oneDNN assumes a fixed zero position. For most of the primitives, the real zero
value is mapped to the zero for quantized values; that is, :math:`0_{x_{int8}} =
0`. For example, this is the only model that :ref:`convolution-label` and
:ref:`inner_product-label` currently support. The :ref:`rnn-label` primitives
have limited support of shifted zero.

For the rest of this section we that :math:`0_{x_{int8}} = 0`.

Example: Convolution Quantization Workflow
------------------------------------------

Consider a convolution without bias. The tensors are represented as:

- :math:`\src_{f32}[:] = scale_{\src} \cdot \src_{int8}[:]`
- :math:`\weights_{f32}[:] = scale_{\weights} \cdot \weights_{int8}[:]`
- :math:`\dst_{f32}[:] = scale_{\dst} \cdot \dst_{int8}[:]`

Here the :math:`\src_{f32}, \weights_{f32}, \dst_{f32}` are not computed at all,
the whole work happens with int8 tensors.  As mentioned above, we also somehow
know all the scaling factors: `scale_{\src}, scale_{\weights}, scale_{\dst}`.

So the task is to compute the :math:`\dst_{int8}` tensor.

Mathematically, the computations are:

.. math::

   \dst_{int8}[:] =
      \operatorname{f32\_to\_int8}(
         output\_scale \cdot
         conv_{s32}(\src_{int8}, \weights_{int8})
      ),

where

- :math:`output\_scale := \frac{scale_{\src} \cdot scale_{\weights}}{scale_{\dst}}`;

- :math:`conv_{s32}` is just a regular convolution which takes source and
  weights with int8 data type and compute the result in int32 data type (int32
  is chosen to avoid overflows during the computations);

- :math:`\operatorname{f32\_to\_s8}()` converts an `f32` value to `s8` with
  potential saturation if the values are out of the range of the int8 data
  type.

Note that in order to perform the operation, one doesn't need to know the exact
scaling factors for all the tensors; it is enough to know only the
`output\_scale`. The library utilizes this fact: a user needs to provide only
this one extra parameter to the convolution primitive (see the
:ref:`output_scaling-label` section below).


Per-Channel Scaling
-------------------

Primitives may have limited support of multiple scales for a quantized tensor.
The most popular use case is the :ref:`convolution-label` primitives that
support per-output-channel scaling factors for the weights, meaning that the
actual convolution computations would need to scale different output channels
differently.

Let :math:`\alpha` denote scales:

- :math:`\src_{f32}(n, ic, ih, iw) = \alpha_{\src} \cdot \src_{int8}(n, ic, ih, iw)`

- :math:`\weights_{f32}(oc, ic, kh, kw) = \alpha_{\weights}(oc) \cdot \weights_{int8}(oc, ic, kh, kw)`

- :math:`\dst_{f32}(n, oc, oh, ow) = scale_{\dst} \cdot \dst_{int8}(n, oc, oh, ow)`

Note that now the weights' scaling factor depends on the :math:`oc`.

To compute the :math:`\dst_{int8}` we need to perform the following:

.. math::

    \dst_{int8}(n, oc, oh, ow) =
        \operatorname{f32\_to\_int8}(
            output\_scale(oc) \cdot
            conv_{s32}(\src_{int8}, \weights_{int8})|_{(n, oc, oh, ow)}
        ),

where

.. math::

   output\_scale(oc) :=
    \frac{\alpha_{\src} \cdot \alpha_{\weights}(oc)}{\alpha_{\dst}}.

The user is responsible for preparing quantized weights accordingly. To do that,
oneDNN provides reorders that can perform per-channel scaling:

.. math::

    \weights_{int8}(oc, ic, kh, kw) =
        \operatorname{f32\_to\_int8}(
            output\_scale(oc) \cdot
            \weights_{f32}(oc, ic, kh, kw)
        ),

where

.. math::

   output\_scale(oc) := \frac{1}{\alpha_{\weights}(oc_{})}.

The :ref:`attributes-quantization-label` describes what kind of quantization
model oneDNN supports.

*******
Support
*******

oneDNN supports int8 computations for inference by allowing to specify that
primitive input and output memory objects use int8 data types.

Note that primitive implementations are allowed to convert int8 values
to int16 or int32, as those conversions do not impact accuracy.

The behavior in case of overflow is undefined. However, it is highly
encouraged to saturate values upon overflow.

.. TODO clarify saturation behavior.
.. TODO clarify conversions to f32 are allowed in post-ops.


.. vim: ts=3 sw=3 et spell spelllang=en
