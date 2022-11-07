.. SPDX-FileCopyrightText: 2019-2020 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. default-domain:: cpp

.. include:: ../../replacements.inc.rst

.. _attributes-link:

##########
Attributes
##########

The parameters passed to create a primitive descriptor specify the
basic problem description: the operation kind, the propagation kind,
the input and output tensors descriptors (e.g. strides if
applicable...), as well as the engine where the primitive will be
executed.

*Attributes* specify some extra properties of the primitive. Users must create
them before use and must set required specifics using the corresponding setters.
The attributes are copied during primitive descriptor creation, so users can
change or destroy attributes right after that.

If not modified, attributes can stay empty, which is equivalent to the default
attributes. Primitive descriptors' constructors have empty attributes as default
parameters, so, unless required, users can simply omit them.

Attributes can also contain *post-ops*, which are computations executed after
the primitive.

.. toctree::
   :maxdepth: 1

   post-ops.rst

***************
Scratchpad Mode
***************

Some primitives might require a temporary buffer while performing their
computations. For instance, the operations that do not have enough independent
work to utilize all cores on a system might use parallelization over the
reduction dimension (the K dimension in the GEMM notation). In this case
different threads compute partial results in private temporary buffers, and then
the private results are added to produce the final result. Another example is
using matrix multiplication (GEMM) to implement convolution. Before calling
GEMM, the source activations need to be transformed using the ``im2col``
operation. The transformation result is written to a temporary buffer that is
then used as an input for the GEMM.

In both of these examples, the temporary buffer is no longer required once the
primitive computation is completed. oneDNN refers to such kind of a memory
buffer as a *scratchpad*.

Both types of implementation might need extra space for the reduction in case
there are too few independent tasks. The amount of memory required by the
``im2col`` transformation is proportional to the size of the source image
multiplied by the weights spatial size. The size of a buffer for reduction is
proportional to the tensor size to be reduced (e.g., ``diff_weights`` in the
case of backward by weights) multiplied by the number of threads in the
reduction groups (the upper bound is the total number of threads).

By contrast, some other primitives might require very little extra space. For
instance, one of the implementation of the |sum| primitive requires temporary
space only to store the pointers to data for each and every input array (that
is, the size of the scratchpad is ``n * sizeof(void *)``, where ``n`` is the
number of summands).

oneDNN supports two modes for handling scratchpads:

.. doxygenenum:: dnnl::scratchpad_mode
   :project: oneDNN

The scratchpad mode is controlled though the
|primitive_attr::set_scratchpad_mode| primitive attributes.

If the user provides scratchpad memory to a primitive, this memory must be
created using the same engine that the primitive uses.

All primitives support both scratchpad modes.

.. note::

   Primitives are not thread-safe by default. The only way to make the primitive
   execution fully thread-safe is to use the |scratchpad_mode::user| mode and
   not pass the same scratchpad memory to two primitives that are executed
   concurrently.

Examples
========

Library Manages Scratchpad
--------------------------

As mentioned above, this is a default behavior. We only want to highlight how a
user can query the amount of memory consumed by a primitive due to a scratchpad.

.. code:: cpp

    // Use default attr, hence the library allocates scratchpad
    dnnl::primitive::primitive_desc op_pd(params, /* other arguments */);

    // Print how much memory would be hold by a primitive due to scratchpad
    std::cout << "primitive will use "
              << op_pd.query_s64(dnnl::query::memory_consumption_s64)
              << " bytes" << std::endl;

    // In this case scratchpad is internal, hence user visible scratchpad memory
    // descriptor should be empty:
    auto zero_md = dnnl::memory::desc();

User Manages Scratchpad
-----------------------

.. code:: cpp

    // Create an empty (default) attributes
    dnnl::primitive_attr attr;

    // Default scratchpad mode is `library`:
    assert(attr.get_scratchpad_mode() == dnnl::scratchpad_mode::library);

    // Set scratchpad mode to `user`
    attr.set_scratchpad_mode(dnnl::scratchpad_mode::user);

    // Create a primitive descriptor with custom attributes
    dnnl::primitive::primitive_desc op_pd(op_d, attr, engine);

    // Query the scratchpad memory descriptor
    dnnl::memory::desc scratchpad_md = op_pd.scratchpad_desc();

    // Note, that a primitive doesn't consume memory in this configuration:
    assert(op_pd.query_s64(dnnl::query::memory_consumption_s64) == 0);

    // Create a primitive
    dnnl::primitive prim(op_pd);

    // ... more code ..

    // Create a scratchpad memory
    // NOTE: if scratchpad is not required for a particular primitive the
    //       scratchpad_md.get_size() will return 0. It is fine to have
    //       scratchpad_ptr == nullptr in this case.
    void *scratchpad_ptr = user_memory_manager::allocate(scratchpad_md.get_size());
    // NOTE: engine here must much the engine of the primitive
    dnnl::memory scratchpad(scratchpad_md, engine, scratchpad_ptr);

    // Pass a scratchpad memory to a primitive
    prim.execute(stream, { /* other arguments */,
            {DNNL_ARG_SCRATCHPAD, scratchpad}});


.. _attributes-quantization-label:

************
Quantization
************

Primitives may support reduced precision computations which require
quantization. This process is explained in more details in the
:ref:`int8-quantization-label` section.

Quantization Attributes (scales and zero-points)
================================================

oneDNN provides |primitive_attr::set_scales_mask| and
|primitive_attr::set_zero_points_mask| for setting the quantization
parameter for a given argument of a primitive.

The primitives may not support passing quantization parameters if
source (and weights) tensors are not of the int8 data type. In other
words, convolution operating on the single precision floating point
data type may not scale and/or shift its inputs and outputs.

Broadcast semantic for quantization parameters is handled through
masks that are explicitly passed to the |primitive_attr::set_scales_mask|
and |primitive_attr::set_zero_points_mask| methods.  For example, if the
primitive destination is a :math:`D_0 \times ... \times D_{n-1}`
tensor and we want to have a scale per :math:`d_i` dimension (where
:math:`0 \le d_i < n`), then :math:`mask = \sum \limits_{d_i} 2^{d_i}`
and the number of scales should be :math:`\mathtt{scales.size()} =
\prod \limits_{d_i} D_{d_i}`. The mask should be set in attributes
during primitive creation, and the actual scales and zero-points are
passed as argument to the primitive execution function.

The quantization parameters are applied in the single precision
floating point data type (|_f32|).  Before it is stored, the result is
converted to the destination data type with saturation if
required. The rounding happens according to the current hardware
setting.


When using :ref:`post_ops-label`, the same
|primitive_attr::set_scales_mask| and |primitive_attr::set_zero_points_mask| are
used to pass quantization parameters to a given post-ops arguments.

Example 1: weights quantization with per-output-channel scaling
---------------------------------------------------------------

.. code:: cpp

   // weights dimensions
   const int OC, IC, KH, KW;

   // original f32 weights in plain format
   dnnl::memory::desc wei_plain_f32_md(
           {OC, IC, KH, KW},                 // dims
           dnnl::memory::data_type::f32,     // the data originally in f32
           dnnl::memory::format_tag::hwigo   // the plain memory format
           );

   // the scaling factors for quantized weights
   // An unique scale for each output-channel.
   std::vector<float> wei_scales(OC) = { /* values */ };
   dnnl::memory();

   // int8 convolution primitive descriptor
   dnnl::convolution_forward::primitive_desc conv_pd(/* see the next example */);

   // query the convolution weights memory descriptor
   dnnl::memory::desc wei_conv_s8_md = conv_pd.weights_desc();

   // prepare the attributes for the reorder
   dnnl::primitive_attr attr;
   const int quantization_mask = 0
       | (1 << 0);  // scale per  OC dimension, which is the dim #0
   attr.set_scales_mask(DNNL_ARG_DST, quantization_mask);

   // create reorder that would perform:
   //   wei_s8(oc, ic, kh, kw) <- wei_f32(oc, ic, kh, kw) / scale(oc)
   // including the data format conversion.
   auto wei_reorder_pd = dnnl::reorder::primitive_desc(
           wei_plain_f32_md, engine, // source
           wei_conv_s8_md, engine, // destination,
           attr);
   auto wei_reorder = dnnl::reorder(wei_reorder_pd);



Example 2: convolution with groups, with per-output-channel quantization
------------------------------------------------------------------------

This example is complementary to the previous example (which should ideally be
the first one). Let's say we want to create an int8 convolution with per-output
channel scaling.

.. code:: cpp

   const float src_scale; // src_f32[:] = src_scale * src_s8[:]
   const float dst_scale; // dst_f32[:] = dst_scale * dst_s8[:]

   // the scaling factors for quantized weights (as declared above)
   // An unique scale for each group and output-channel.
   std::vector<float> wei_scales(OC) = {...};


   // Src, weights, and dst memory descriptors for convolution,
   // with memory format tag == any to allow a convolution implementation
   // to chose the appropriate memory format

   dnnl::memory::desc src_conv_s8_any_md(
           {BATCH, IC, IH, IW},          // dims
           dnnl::memory::data_type::s8,  // the data originally in s8
           dnnl::memory::format_tag::any // let convolution to choose
           );

   dnnl::memory::desc wei_conv_s8_any_md(
           {OC, IC, KH, KW},             // dims
           dnnl::memory::data_type::s8,  // the data originally in s8
           dnnl::memory::format_tag::any // let convolution to choose
           );

   dnnl::memory::desc dst_conv_s8_any_md(...);  // ditto

   // prepare the attributes for the convolution
   dnnl::primitive_attr attr;
   const int data_mask = 0; // scale and zero-point per tensor for source and destination
   const int wei_mask = 0
       | (1 << 1); // scale per OC dimension, which is the dim #0 on weights tensor:
                   // (   OC, IC, KH, KW)
                   //      0   1   2   3

   attr.set_scales_mask(DNNL_ARG_SRC, data_mask);
   attr.set_zero_points_mask(DNNL_ARG_SRC, data_mask);

   attr.set_scales_mask(DNNL_ARG_WEIGHTS, wei_mask);

   attr.set_scales_mask(DNNL_ARG_DST, data_mask);
   attr.set_zero_points_mask(DNNL_ARG_DST, data_mask);

   // create a convolution primitive descriptor
   auto conv_pd = dnnl::convolution_forward::primitive_desc(
           dnnl::prop_kind::forward_inference,
           dnnl::algorithm::convolution_direct,
           src_conv_s8_any_md,                     // what's important is that
           wei_conv_s8_any_md,                     // we specified that we want
           dst_conv_s8_any_md,                     // computations in s8
           strides, padding_l, padding_r,
           dnnl::padding_kind::zero
           attr);   // the attributes describe the quantization flow

.. _attributes_fpmath_mode-label:

*****************************************************
Implicit downconversions and floating-point math mode
*****************************************************

oneDNN provides |primitive_attr::set_fpmath_mode| to allow implicit
downconversions from fp32 to lower accuracy datatypes during primitive
execution. For some applications, it allows to speedup computations
without noticeable impact on accuracy.

The |primitive_attr::set_fpmath_mode| primitive attribute specifies
which implicit down-conversions are allowed for that given
primitive. Only down-conversions from f32 to narrower data-types (f16,
bf16, or tf32) are currently allowed. Furthermore these
down-conversions are allowed only during computation, and do not
affect the storage datatype (which must remain f32).

The |primitive_attr::set_fpmath_mode| primitive attribute can take 3 types of values:

- the `strict` mode disables any down-conversion (default).
- the `any` mode allows all conversions from f32 to a smaller
  floating-point datatype (f16, bf16, or tf32).
- a specific datatype (f16, bf16, or tf32) which specifically allows
  down-conversion only from f32 to a datatype at least as accurate as
  the specified data-type (at least same number of exponent and
  mantissa bits).

The default value for this attribute shall be `strict`. However, it is
allowed to expose global functions or environment variables to change
this default value.

This attribute is ignored if a primitive computation data-type is
integral.

.. _attributes_error_handling-link:

********************************
Attribute Related Error Handling
********************************

Since the attributes are created separately from the corresponding primitive
descriptor, consistency checks are delayed.  Users can successfully set
attributes in whatever configuration they want.  However, when they try to
create a primitive descriptor with the attributes they set, it might happen that
there is no primitive implementation that supports such a configuration. In this
case the library will throw the |error| exception.

***
API
***

.. doxygenstruct:: dnnl::primitive_attr
   :project: oneDNN
   :members:

.. vim: ts=3 sw=3 et spell spelllang=en
