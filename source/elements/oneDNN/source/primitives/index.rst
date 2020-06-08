..
  Copyright 2019-2020 Intel Corporation

.. default-domain:: cpp

##########
Primitives
##########

*Primitives* are functor objects that encapsulates a particular computation
such as forward convolution, backward LSTM computations, or a data
transformation operation. A single primitive can sometimes represent more
complex fused computations such as a forward convolution followed by a ReLU.

The most important difference between a primitive and a pure function is
that a primitive can store state.

One part of the primitive's state is immutable. For example, convolution
primitives store parameters like tensor shapes and can pre-compute other
dependent parameters like cache blocking. This approach allows oneDNN
primitives to pre-generate code specifically tailored for the operation to be
performed. The oneDNN programming model assumes that the time it takes to
perform the pre-computations is amortized by reusing the same primitive to
perform computations multiple times.

The mutable part of the primitive's state is referred to as a scratchpad. It
is a memory buffer that a primitive may use for temporary storage only during
computations. The scratchpad can either be owned by a primitive object (which
makes that object non-thread safe) or be an execution-time parameter.

Each primitive is defined using several abstraction levels.

.. image:: ../_static/img_primitive.png
   :width: 600
   :alt: oneDNN primitive dependencies diagram

* Operation descriptors (one for each supported primitive) describe an
  operation's most basic properties without specifying, for example, which
  engine will be used to compute them. For example, convolution descriptor
  describes shapes of source, destination, and weights tensors, propagation
  kind (forward, backward with respect to data or weights), and other
  implementation-independent parameters. The shapes are usually described as
  memory descriptors (:struct:`dnnl::memory::desc`).

* Primitive descriptors (:struct:`dnnl::primitive_desc_base` is the base class
  and each of the supported primitives have their own version) are at an
  abstraction level in between operation descriptors and primitives and can be
  used to inspect details of a specific primitive implementation like expected
  memory formats via queries to implement memory format propagation (see
  Memory format propagation) without having to fully instantiate a primitive.

Hence, the sequence of actions to create a primitive is:

1. Create an operation descriptor via, for example,
   :any:`dnnl::convolution_forward::desc`. The operation descriptor can
   contain memory descriptors with placeholder
   :any:`dnnl::memory::format_tag::any` memory formats if the primitive
   supports it.
2. Create a primitive descriptor based on the operation descriptor, engine and
   attributes.
3. Create a primitive based on the primitive descriptor obtained in step 2.

.. note::

   Strictly speaking, not all the primitives follow this sequence. For
   example, the reorder primitive does not have an operation descriptor and
   thus does not require step 1 above.

.. toctree::
   :maxdepth: 2

   general.rst
   attributes/index.rst
   batch_normalization.rst
   binary.rst
   concat.rst
   convolution.rst
   eltwise.rst
   inner-product.rst
   layer_normalization.rst
   logsoftmax.rst
   lrn.rst
   matmul.rst
   pooling.rst
   reorder.rst
   resampling.rst
   rnn.rst
   shuffle.rst
   softmax.rst
   sum.rst

.. vim: ts=3 sw=3 et spell spelllang=en
