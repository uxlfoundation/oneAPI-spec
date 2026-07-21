.. SPDX-FileCopyrightText: 2019-2020 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. default-domain:: cpp

.. include:: ../../replacements.inc.rst

.. _post_ops-label:

########
Post-ops
########

*Post-ops* are operations that are appended after a primitive.  They are
implemented using the :ref:`attributes-link` mechanism. If there are multiple
post-ops, they are executed in the order they have been appended as follow:

.. math::

   \dst = po[n](po[n-1] (...(po[0](OP()))))

.. note::

   Post-ops does not preserve intermediate data during
   computation. This typically makes them suitable for inference only.

The post-ops are represented by |post_ops| which is copied once it
is attached to the attributes using |primitive_attr::set_post_ops|
function. The attributes then need to be passed to a primitive descriptor
creation function to take effect. Below is a simple sketch:

.. code:: cpp

   dnnl::post_ops po; // default empty post-ops
   assert(po.len() == 0); // no post-ops attached

   po.append_SOMETHING(params); // append some particular post-op
   po.append_SOMETHING_ELSE(other_params); // append one more post-op

   // (!) Note that the order in which post-ops are appended matters!
   assert(po.len() == 2);

   dnnl::primitive_attr attr; // default attributes
   attr.set_post_ops(po); // attach the post-ops to the attr
   // any changes to po after this point don't affect the value stored in attr

   primitive::primitive_desc op_pd(params, attr); // create a pd with the attr

.. note::

   Different primitives may have different post-ops support.  Moreover, the
   support might also depend on the actual implementation of a primitive. So
   robust code should be able to handle errors accordingly. See the
   :ref:`attributes_error_handling-link`.

.. note::
   Post-ops do not change memory format of the operation destination memory
   object.

The post-op objects can be inspected using the |post_ops::kind|
function that takes an index of the post-op to inspect (that must be less than
the value returned by |post_ops::len|), and returns its kind.

******************
Supported Post-ops
******************

.. _post_ops_eltwise-label:

Eltwise Post-op
===============

The eltwise post-op is appended using |post_ops::append_eltwise|
function. The |post_ops::kind| returns
|primitive::kind::eltwise| for such a post-op.

The eltwise post-op replaces:

.. math::
    \dst[:] = \operatorname{Op}(...)

with

.. math::
    \dst[:] = scale \cdot \operatorname{eltwise}(\operatorname{Op}(...))

The intermediate result of the :math:`\operatorname{Op}(...)` is not
preserved.

The :math:`scale` factor is supported in :ref:`int8
<int8-quantization-label>` inference only. For all other cases the
scale must be `1.0` (default value).
The scale parameter is set to :math:`1.0` by default, and can be set
using the |primitive_attr::set_scales_mask| attribute for the argument
|DNNL_ARG_ATTR_MULTIPLE_POST_OP(po_index)|.


.. _post_ops_sum-label:

Sum Post-op
===========

The sum post-op accumulates the result of a primitive with the existing data
and is appended using |post_ops::append_sum| function. The
|post_ops::kind| returns |primitive::kind::sum| for such
a post-op.

Prior to accumulating the result, the existing value is multiplied by
scale.  The :math:`scale` factor is supported in :ref:`int8
<attributes-quantization-label>` inference only and should be used
only when the result and the existing data have different magnitudes.
For all other cases the scale must be `1.0` (default value).
The scale parameter is set to :math:`1.0` by default, and can be set
using the |primitive_attr::set_scales_mask| attribute for the argument
|DNNL_ARG_ATTR_MULTIPLE_POST_OP(po_index)|.

Additionally, the sum post-op can reinterpret the destination values as a
different data type of the same size. This may be used to, for example,
reinterpret 8-bit signed data as unsigned or vice versa (which requires that
values fall within a common range to work).

The sum post-op replaces

.. math::
    \dst[:] = \operatorname{Op}(...)

with

.. math::
    \dst[:] = scale \cdot as_data_type(\dst[:]) + \operatorname{Op}(...)

.. _post_ops_binary-label:

Binary post-ops
============================

The binary post-op replaces:
.. math::

   \dst[:] = \operatorname{Op}(...)

with

.. math::

   \dst[:] = \operatorname{binary}(\operatorname{Op}(...), scale[:] \cdot Source\_1[:])

The binary post-op supports the same algorithms and broadcast semantic
as the :ref:`binary primitive<primitive_binary-link>`.

Furthermore, the binary post-op scale parameter is set to :math:`1.0`
by default, and can be set using the |primitive_attr::set_scales_mask|
attribute for the argument |DNNL_ARG_ATTR_MULTIPLE_POST_OP(po_index)|
| |DNNL_ARG_SRC_1|. For example:

.. code:: cpp

   primitive_attr attr;
   post_ops p_ops;
   p_ops.append_binary(algorithm::binary_add, summand_md);

   attr.set_post_ops(p_ops);
   attr.set_scales_mask(DNNL_ARG_ATTR_MULTIPLE_POST_OP(0) | DNNL_ARG_SRC_1,
           /* mask */ 0);


Examples of Chained Post-ops
============================

Post-ops can be chained together by appending one after another. Note that the
order matters: the post-ops are executed in the order they have been appended.

.. _post_ops_sum_relu-label:

Sum -> ReLU
-----------

This pattern is pretty common for the CNN topologies of the ResNet family.

.. code:: cpp

   dnnl::post_ops po;
   po.append_sum();
   po.append_eltwise(
           /* algorithm = */ dnnl::algorithm::eltwise_relu,
           /* neg slope = */ 0.f,
           /* unused for ReLU */ 0.f);

   dnnl::primitive_attr attr;
   attr.set_post_ops(po);

   convolution_forward::primitive_desc(conv_d, attr, engine);


This will lead to the following computations:

.. math::
    \dst[:] = \operatorname{ReLU}(\dst[:] + \operatorname{conv}(\src[:], \weights[:])

***
API
***

.. doxygenstruct:: dnnl::post_ops
   :project: oneDNN
   :members:

.. vim: ts=3 sw=3 et spell spelllang=en
