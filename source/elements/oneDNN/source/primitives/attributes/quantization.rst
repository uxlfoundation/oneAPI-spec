..
  Copyright 2019-2020 Intel Corporation

.. default-domain:: cpp

.. _attributes-quantization-label:

Quantization
------------

Primitives may support reduced precision computations which require
quantization.

Quantization Model
++++++++++++++++++

The primary quantization model that the library assumes is the following:

.. math::

    x_{f32}[:] = scale_{f32} \cdot (x_{int8}[:] - 0_{x_{int8}})

where :math:`scale_{f32}` is a *scaling factor* that is somehow known in
advance and :math:`[:]` is used to denote elementwise application of the
formula to the arrays. Typically, the process of computing scale factors is
called *calibration*. The library cannot compute any of the scale factors at
run-time dynamically.  Hence, the model is sometimes called a *static*
quantization model. The main rationale to support only *static* quantization
out-of-the-box is higher performance. To use *dynamic* quantization:

1. Compute the result in higher precision, like
   :enumerator:`dnnl::memory::data_type::s32`.
2. Find the required characteristics, like min and max values, and derive the
   scale factor.
3. Re-quantize to the lower precision data type.

oneDNN assumes a fixed zero position. For most of the primitives, the real
zero value is mapped to the zero for quantized values; that is,
:math:`0_{x_{int8}} = 0`. For example, this is the only model that
:ref:`convolution-label` and :ref:`inner_product-label` currently support.
The :ref:`rnn-label` primitives have limited support of shifted zero.

For the rest of this section we that :math:`0_{x_{int8}} = 0`.

Example: Convolution Quantization Workflow
++++++++++++++++++++++++++++++++++++++++++

Consider a convolution without bias. The tensors are represented as:

- :math:`\src_{f32}[:] = scale_{\src} \cdot \src_{int8}[:]`
- :math:`\weights_{f32}[:] = scale_{\weights} \cdot \weights_{int8}[:]`
- :math:`\dst_{f32}[:] = scale_{\dst} \cdot \dst_{int8}[:]`

Here the :math:`\src_{f32}, \weights_{f32}, \dst_{f32}` are not computed at
all, the whole work happens with int8 tensors.  As mentioned above, we also
somehow know all the scaling factors: `scale_{\src}, scale_{\weights},
scale_{\dst}`.

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

Note that in order to perform the operation, one doesn't need to know the
exact scaling factors for all the tensors; it is enough to know only the
`output\_scale`. The library utilizes this fact: a user needs to provide only
this one extra parameter to the convolution primitive (see the
:ref:`output_scaling-label` section below).

Per-Channel Scaling
+++++++++++++++++++

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

The user is responsible for preparing quantized weights accordingly. To do
that, oneDNN provides reorders that can perform per-channel scaling:

.. math::

    \weights_{int8}(oc, ic, kh, kw) =
        \operatorname{f32\_to\_int8}(
            output\_scale(oc) \cdot
            \weights_{f32}(oc, ic, kh, kw)
        ),

where

.. math::

   output\_scale(oc) := \frac{1}{\alpha_{\weights}(oc_{})}.

.. _output_scaling-label:

Output Scaling Attribute
++++++++++++++++++++++++

oneDNN provides :any:`dnnl::primitive_attr::set_output_scales` for setting
scaling factors for most of the primitives.

The primitives may not support output scales if source (and weights) tensors
are not of the int8 data type. In other words, convolution operating on the
single precision floating point data type may not scale the output result.

In the simplest case, when there is only one common scale the attribute
changes the op behavior from

.. math::
    \dst[:] = Op(...)

to

.. math::
    \dst[:] = scale \cdot Op(...).

To support scales per one or several dimensions, users must set the appropriate
mask.

Say the primitive destination is a :math:`D_0 \times ... \times D_{n-1}`
tensor and we want to have output scales per :math:`d_i` dimension (where
:math:`0 \le d_i < n`).

Then :math:`mask = \sum \limits_{d_i} 2^{d_i}` and the number of scales should be
math:`\mathtt{scales.size()} = \prod\limits_{d_i}D_{d_i}`.

The scaling happens in the single precision floating point data type
(:any:`data_type::f32`). Before storing, the result is converted to the
destination data type with saturation if required. The rounding happens
according to the current hardware setting.

Example 1: weights quantization with per-output-channel-and-group scaling
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. code:: cpp

   // weights dimensions
   const int G, OC, IC, KH, KW;

   // original f32 weights in plain format
   dnnl::memory::desc wei_plain_f32_md(
           {G, OC/G, IC/G, KH, KW},          // dims
           dnnl::memory::data_type::f32,     // the data originally in f32
           dnnl::memory::format_tag::hwigo   // the plain memory format
           );

   // the scaling factors for quantized weights
   // An unique scale for each group and output-channel.
   std::vector<float> wei_scales(G * OC/G) = { /* values */ };

   // int8 convolution primitive descriptor
   dnnl::convolution_forward::primitive_desc conv_pd(/* see the next example */);

   // query the convolution weights memory descriptor
   dnnl::memory::desc wei_conv_s8_md = conv_pd.weights_desc();

   // prepare the inverse of the scales
   // (f32 = scale * int8 --> int8 = 1/scale * f32)
   std::vector<float> inv_wei_scales(wei_scales.size());
   for (size_t i = 0; i < wei_scales.size(); ++i)
       inv_wei_scales[i] = 1.f / wei_scales[i];

   // prepare the attributes for the reorder
   dnnl::primitive_attr attr;
   const int mask = 0
       | (1 << 0)  // scale per  G dimension, which is the dim #0
       | (1 << 1); // scale per OC dimension, which is the dim #1
   attr.set_output_scales(mask, inv_wei_scales);

   // create reorder that would perform:
   //   wei_s8(g, oc, ic, kh, kw) <- 1/scale(g, oc) * wei_f32(g, oc, ic, kh, kw)
   // including the data format transformation.
   auto wei_reorder_pd = dnnl::reorder::primitive_desc(
           wei_plain_f32_md, engine, // source
           wei_conv_s8_md, engine, // destination,
           attr);
   auto wei_reorder = dnnl::reorder(wei_reorder_pd);


Example 2: convolution with groups, with per-output-channel quantization
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

This example is complementary to the previous example (which should ideally be
the first one). Let's say we want to create an int8 convolution with
per-output channel scaling.

.. code:: cpp

   const float src_scale; // src_f32[:] = src_scale * src_s8[:]
   const float dst_scale; // dst_f32[:] = dst_scale * dst_s8[:]

   // the scaling factors for quantized weights (as declared above)
   // An unique scale for each group and output-channel.
   std::vector<float> wei_scales(G * OC/G) = {...};


   // Src, weights, and dst memory descriptors for convolution,
   // with memory format tag == any to allow a convolution implementation
   // to chose the appropriate memory format

   dnnl::memory::desc src_conv_s8_any_md(
           {BATCH, IC, IH, IW},            // dims
           dnnl::memory::data_type::s8,  // the data originally in s8
           dnnl::memory::format_tag::any // let convolution to choose
           );

   dnnl::memory::desc wei_conv_s8_any_md(
           {G, OC/G, IC/G, KH, KW},        // dims
           dnnl::memory::data_type::s8,  // the data originally in s8
           dnnl::memory::format_tag::any // let convolution to choose
           );

   dnnl::memory::desc dst_conv_s8_any_md(...);  // ditto

   // Create a convolution operation descriptor
   dnnl::convolution_forward::desc conv_d(
           dnnl::prop_kind::forward_inference,
           dnnl::algorithm::convolution_direct,
           src_conv_s8_any_md,                     // what's important is that
           wei_conv_s8_any_md,                     // we specified that we want
           dst_conv_s8_any_md,                     // computations in s8
           strides, padding_l, padding_r,
           dnnl::padding_kind::zero
           );

   // prepare the attributes for the convolution
   dnnl::primitive_attr attr;
   const int mask = 0
       | (1 << 1); // scale per OC dimension, which is the dim #1 on dst tensor:
                   // (BATCH, OC, OH, OW)
                   //    0     1   2   3
   std::vector<float> conv_output_scales(G * OC/G);
   for (int g_oc = 0; G * OC/G; ++g_oc)
       conv_output_scales[g_oc] = src_scale * wei_scales(g_oc) / dst_scale;
   attr.set_output_scales(mask, conv_output_scales);

   // create a convolution primitive descriptor with the scaling factors
   auto conv_pd = dnnl::convolution_forward::primitive_desc(
           conv_d, // general (non-customized) operation descriptor
           attr,   // the attributes contain the output scaling
           engine);


Interplay of Output Scales with Post-ops
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

In general, the :ref:`post_ops-label` are independent from the output scales.
The output scales are applied to the result first; then post-ops will take
effect.

That has an implication on the scaling factors passed to the library, however.
Consider the following example of a convolution with :math:`\tanh` post-op:

.. math::
    \dst_{s8}[:] =
        \frac{1}{scale_{\dst}}
        \cdot
        \tanh(
                scale_{\src}
                \cdot
                scale_{\weights}
                \cdot
                conv_{s32}(\src_{s8}, wei_{s8})
        )

- The convolution output scales are
  :math:`conv\_output\_scale = scale_{\src} \cdot scale_{\weights}`,
  i.e. there is no division by :math:`scale_{\dst}`.
- And the post-ops scale for :math:`\tanh` is set to
  :math:`scale\_tanh\_post\_op = \frac{1}{scale_{\dst}}`.

.. vim: ts=3 sw=3 et spell spelllang=en

