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

For each int8 tensor, the oneDNN library allows to specify scaling
factors and a zero-points (also refered to as quantization
parameters), and assumes the following mathematical relationship:

.. math::

    x_{f32}[:] = scale_{f32} \cdot (x_{int8}[:] - 0_{x_{int8}})

where :math:`scale_{f32}` is a *scaling factor* and :math:`[:]` is
used to denote elementwise application of the formula to the
arrays. In order to provide best performance, oneDNN does not
compute those scaling factors and zero-points as part of primitive
computation. Those should be provided by the user through the
:ref:`attribute mecanism<attributes-quantization-label>`.

These quantization parameters can either be computed ahead of time
using calibration tools (*static* quantization) or at runtime based on
the actual minimum and maximum values of a tensor (*dynamic*
quantization). Either method can be used in conjuction with oneDNN, as
the quantization parameters are passed to the oneDNN primitives
execution time.

To support int8 quantization, primitives should be created and
executed as follow:
- during primitive creation, if one or multiple inputs are int8
  (signed or not), then the primitive will behave as a quantized
  integer operation.
- still during primitive creation, the dimensionality of the scaling
  factors and zero-point should be provided using masks (e.g. one
  scale per tensor, one scale per channel, ...).
- finally, during primitive execution, the user must provide the
  actual quantization parameters as arguments to the execute function.
  Scales shall be f32 values, and zero-points shall be int32 values.
  
.. note::

   For performance reasons, each primitive implementation can support
   only a subset of quantization parameter masks. For example,
   convolution typically does not support zero-points for weights, and
   does not support per-channel scaling factor for activation.

.. note::

   Some primitives might use quantization parameters in order to
   dequantize/quantize intermediate values.  This is for example the
   case for the :ref:`rnn-label` primitive, which will dequantize
   before applying non linear functions, and will requantize because
   executing matrix multiplication operations.


Numerical behavior
__________________

Primitive implementations are allowed to convert int8 inputs to wider
datatypes (e.g. int16 or int32), as those conversions do not impact
accuracy.

During execution, primitives should avoid integer overflows and
maintain integer accuracy by using wider datatypes (e.g. int32) for
intermediate values and accumulators. Those are then converted as
necessary before the result is written to the output memory objects.
During that conversion, the behavior in case of underflow/overflow is
undefined (e.g. when converting `s32` to int8). However, it is highly
encouraged for implementations to saturate values.

When multiple operations are fused in a single primitive using the
:ref:`post-op mecanism<post_ops-label>`, it might be necessary to
apply new quantization parameters between each of these operations.
This can be achieved using the :ref:`binary
post-ops<post_ops_binary-label>`.

.. note::

   During post-ops computation, conversions to f32 might happen. In
   particular, it happens before applying scaling factors which are
   f32 values, or before some :ref:`element-wise
   functions<post_ops_eltwise-label>`.


Example: Convolution Quantization Workflow
------------------------------------------

Consider a convolution without bias. The tensors are represented as:

- :math:`\src_{f32}[:] = scale_{\src} \cdot (\src_{int8}[:] - \src_zp)`
- :math:`\weights_{f32}[:] = scale_{\weights} \cdot \weights_{int8}[:]`
- :math:`\dst_{f32}[:] = scale_{\dst} \cdot (\dst_{int8}[:] - \dst_zp)`

Here the :math:`\src_{f32}, \weights_{f32}, \dst_{f32}` are not
computed at all, the whole work happens with int8 tensors.So the task
is to compute the :math:`\dst_{int8}` tensor, using the `\src_{int8}`,
`\weights_{int8}` tensors passed at execution time, as well as the
corresponding quantization parameters `scale_{\src}, scale_{\weights},
scale_{\dst}` and `zero_point{\src},
zero_point_{\dst}`. Mathematically, the computations are:

.. math::

   \dst_{int8}[:] =
      \operatorname{f32\_to\_int8}(
         output\_scale \cdot
         \operatorname{s32\_to\_f32}(conv_{s32}(\src_{int8}, \weights_{int8}))
	   - \src\_zp \cdot comp\_s32
      ) + \dst\_zp,
      
where

- :math:`output\_scale := \frac{scale_{\src} \cdot scale_{\weights}}{scale_{\dst}}`;

- :math:`conv_{s32}` is just a regular convolution which takes source and
  weights with int8 data type and compute the result in int32 data type (int32
  is chosen to avoid overflows during the computations);

- :math:`comp\s32 = \sum_{k}` a compensation term to account for the
  fact that `\src` has a non-zero zero point. This term is computed by
  the oneDNN library and can typically be computed ahead of time, for
  example during weights reorder.

- :math:`\operatorname{f32\_to\_s8}()` converts an `f32` value to `s8` with
  potential saturation if the values are out of the range of the int8 data
  type.

- :math:`\operatorname{s32\_to\_f32}()` converts an `int8` value to
  `f32` with potential rounding. This conversion is typically
  necessary to apply `f32` scaling factors.

.. todo: put precomputing output_scales as a remark/optimization, in a
    separate note/sub-section.

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


.. vim: ts=3 sw=3 et spell spelllang=en
