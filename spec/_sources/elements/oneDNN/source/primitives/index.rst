.. SPDX-FileCopyrightText: 2019-2020 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. default-domain:: cpp

.. include:: ../replacements.inc.rst

##########
Primitives
##########

*Primitives* are functor objects that encapsulate a particular computation such
as forward convolution, backward LSTM computations, or a data transformation
operation. A single primitive can sometimes represent more complex fused
computations such as a forward convolution followed by a ReLU.

The most important difference between a primitive and a pure function is that a
primitive can store state.

One part of the primitive's state is immutable. For example, convolution
primitives store parameters like tensor shapes and can pre-compute other
dependent parameters like cache blocking. This approach allows oneDNN primitives
to pre-generate code specifically tailored for the operation to be performed.
The oneDNN programming model assumes that the time it takes to perform the
pre-computations is amortized by reusing the same primitive to perform
computations multiple times.

The mutable part of the primitive's state is referred to as a scratchpad. It is
a memory buffer that a primitive may use for temporary storage only during
computations. The scratchpad can either be owned by a primitive object (which
makes that object non-thread safe) or be an execution-time parameter.

Conceptually, oneDNN establishes several layers of how to describe a computation
from more abstract to more concrete:

* Primitives descriptors fully defines an operations's computation
  using the memory descriptors (|memory::desc|) passed at
  construction, as well as the attributes. It also dispatches specific
  implementation based on the engine. Primitive descriptors can be
  used to query various primitive implementation details and, for
  example, to implement :ref:`memory format propagation
  <memory_format_propagation-label>` by inspecting expected memory
  formats via queries without having to fully instantiate a primitive.
  oneDNN may contain multiple implementations for the same primitive
  that can be used to perform the same particular
  computation. Primitive descriptors allow one-way iteration which
  allows inspecting multiple implementations. The library is expected
  to order the implementations from most to least preferred, so it
  should always be safe to use the one that is chosen by default.

* Primitives, which are the most concrete, and embody the actual
  executable code that will be run to perform the primitive computation.

On the API level:

* Primitives are represented as a class on the top level of the ``dnnl``
  namespace that have |primitive| as their base class, for
  example |convolution_forward|

* Primitive descriptors are represented as classes named
  ``primitive_desc`` and nested within the corresponding primitive
  classes that have |primitive_desc_base| as their base class (except
  for RNN primitives that derive from |rnn_primitive_desc_base|), for
  example |convolution_forward::primitive_desc|. The
  |primitive_desc::next_impl| member function provides a way to
  iterate over implementations.

.. code-block:: c++

   namespace dnnl {
      struct something_forward : public primitive {
         struct desc {
            // Primitive-specific constructors.
         }
         struct primitive_desc : public primitive_desc_base {
            // Constructors and primitive-specific memory descriptor queries.
         }
      };
   }

The sequence of actions to create a primitive is:

1. Create a primitive descriptor with the proper memory descriptors,
   engine and attributes. The primitive descriptor can contain memory
   descriptors with placeholder |memory::format_tag::any| memory
   formats if the primitive supports it.
2. Create a primitive based on the primitive descriptor obtained in step 1.


.. toctree::
   :maxdepth: 1

   general.rst
   attributes/index.rst
   batch_normalization.rst
   binary.rst
   concat.rst
   convolution.rst
   eltwise.rst
   inner-product.rst
   layer_normalization.rst
   lrn.rst
   matmul.rst
   pooling.rst
   prelu.rst
   reduction.rst
   reorder.rst
   resampling.rst
   rnn.rst
   shuffle.rst
   softmax.rst
   sum.rst

.. vim: ts=3 sw=3 et spell spelllang=en
