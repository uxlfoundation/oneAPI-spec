..
  Copyright 2019-2020 Intel Corporation

.. default-domain:: cpp

.. cpp:namespace:: dnnl::memory

.. |N| replace:: :math:`N`
.. |C| replace:: :math:`C`
.. |D| replace:: :math:`D`
.. |H| replace:: :math:`H`
.. |W| replace:: :math:`W`
.. |G| replace:: :math:`G`
.. |I| replace:: :math:`I`
.. |O| replace:: :math:`O`

.. |A| replace:: :math:`A`
.. |M| replace:: :math:`M`
.. |LDA| replace:: :math:`LDA`

.. |n| replace:: :math:`n`
.. |c| replace:: :math:`c`
.. |d| replace:: :math:`d`
.. |h| replace:: :math:`h`
.. |w| replace:: :math:`w`

.. |dimensions| replace:: :math:`\operatorname{dimensions}`
.. |strides| replace:: :math:`\operatorname{strides}`
.. |offset| replace:: :math:`\operatorname{offset}`

.. _memory_formats-label:

Memory Formats
--------------

In oneDNN memory format is how a multidimensional tensor is stored in
1-dimensional linear memory address space. oneDNN specifies two kinds of
memory formats: *plain* which correspond to traditional multidimensional
arrays, and *optimized* which are completely opaque.

Plain Memory Formats
~~~~~~~~~~~~~~~~~~~~

Plain memory formats describe how multidimensional tensors are laid out in
memory using an array of |dimensions| and an array of |strides| both of which
have length equal to the rank of the tensor. In oneDNN the order of dimensions
is fixed and different dimensions can have certain canonical interpretation
depending on the primitive. For example, for CNN primitives the order for
activation tensors is :math:`\{N, C, ..., D, H, W\}`, where |N| stands for
minibatch, |C| stands for channels, and |D|, |H|, and |W| stand for image
spatial dimensions: depth, height and width respectively. Spatial dimensions
may be omitted in the order from outermost to innermost; for example, it is
not possible to omit |H| when |D| is present and it is never possible to omit
|W|. Canonical interpretation is documented for each primitive. However, this
means that the |strides| array plays an important role defining the order in
which different dimension are laid out in memory. Moreover, the |strides| need
to agree with |dimensions|.

More precisely, let :math:`T` be a tensor of rank :math:`n` and let
:math:`\sigma` be the permutation of the |strides| array that sorts it, i.e.
:math:`\operatorname{strides}[i] \geq
\operatorname{strides}[j]` if :math:`\sigma(i) < \sigma(j)` for all
:math:`0 \leq i, j < n`. Then the following must hold:

.. math::
   \operatorname{stides}[i] \geq
   \operatorname{strides}[j] * \operatorname{dimensions}[j]
   \text{ if } \sigma(i) < \sigma(j) \text{ for all } 0 \leq i, j < n.

For an element with coordinates :math:`(i_0, \ldots, i_{n-1})` such that
:math:`0 \leq i_j < \operatorname{dimensions}[j]` for :math:`0 \leq j < n`, its
offset in memory is computed as:

.. math::

   \operatorname{offset}(i_0, \ldots, i_{n-1})
   = \sum_{j=0}^{n-1} i_j * \operatorname{strides}[j].

As an example, consider an :math:`M \times N` matrix |A| (|M| rows times |N|
columns). Regardless of whether |A| is stored transposed or not,
:math:`\operatorname{dimensions}_A = \{M, N\}`. However,
:math:`\operatorname{strides}_A = \{LDA, 1\}` if it is not transposed and
:math:`\operatorname{strides}_A = \{1, LDA\}` if it is, where |LDA| is such
that :math:`LDA \geq N` if |A| is not transposed, and :math:`LDA \geq M` if it
is. This also shows that |A| does not have to be stored *densly* in memory.

.. note::

   The example above shows that oneDNN assumes data to be stored in row-major
   order.

Code example:

.. code:: cpp

   int M, N;
   dnnl::memory::dims dims {M, N}; // Dimensions always stay the same

   // Non-transposed matrix
   dnnl::memory::dims strides_non_transposed {N, 1};
   dnnl::memory::desc A_non_transposed {dims, dnnl::memory::data_type::f32,
           strides_non_transposed};

   // Transposed matrix
   dnnl::memory::dims strides_transposed {1, M};
   dnnl::memory::desc A_transposed {dims, dnnl::memory::data_type::f32,
           strides_transposed};

Format Tags
~~~~~~~~~~~

In addition to strides, oneDNN provides named *format tags* via the
:any:`dnnl::memory::format_tag` enum type. The enumerators of this type can be
used instead of strides for dense plain layouts.

The format tag names for :math:`N`-dimensional memory formats use first
:math:`N` letters of the English alphabet which can be arbitrarily permuted.
This permutation is used to compute strides for tensors with up to 6
dimensions. The resulting strides specify dense storage, in other words, using
the nomenclature from the previous section, the following equality holds:

.. math::

   \operatorname{stides}[i] =
   \operatorname{strides}[j] * \operatorname{dimensions}[j]
   \text{ if } \sigma(i) + 1 = \sigma(j) \text{ for all } 0 \leq i, j < n - 1.

In the matrix example, we could have used :any:`format_tag::ab` for the
non-transposed matrix above, and :any:`format_tag::ba` for the transposed:

.. code:: cpp

   int M, N;
   dnnl::memory::dims dims {M, N}; // Dimensions always stay the same

   // Non-transposed matrix
   dnnl::memory::desc A_non_transposed {dims, dnnl::memory::data_type::f32,
           dnnl::memory::format_tag::ab};

   // Transposed matrix
   dnnl::memory::desc A_transposed {dims, dnnl::memory::data_type::f32,
           dnnl::memory::format_tag::ba};

In addition to abstract format tag names, oneDNN also provides convenience
aliases. Some examples for CNNs and RNNs:

- :any:`format_tag::nchw` is an alias for :any:`format_tag::abcd` (see the
  canonical order order of dimensions for CNNs discussed above).
- :any:`format_tag::oihw` is an alias for :any:`format_tag::abcd`.
- :any:`format_tag::nhwc` is an alias for :any:`format_tag::acdb`.
- :any:`format_tag::tnc` is an alias for :any:`format_tag::abc`.
- :any:`format_tag::ldio` is an alias for :any:`format_tag::abcd`.
- :any:`format_tag::ldoi` is an alias for :any:`format_tag::abdc`.

Optimized Format 'any'
~~~~~~~~~~~~~~~~~~~~~~

Another kind of format that oneDNN supports is an opaque _optimized_ memory
format that cannot be created directly from |strides| and |dimensions| arrays.
A memory descriptor for an optimized memory format can only be created by
passing :any:`format_tag::any` when creating certain operation descriptors,
using them to create corresponding primitive descriptors and then querying
them for memory descriptors. Data in plain memory format should then be
reordered into the data in optimized data format before computations. Since
reorders are expensive, the optimized memory format needs to be _propagated_
through computations graph.

.. _memory_format_propagation-label:

Memory Format Propagation
^^^^^^^^^^^^^^^^^^^^^^^^^

Memory format propagation is one of the central notions that needs to be
well-understood to use oneDNN correctly.

Convolution and inner product primitives choose the memory format when you
create them with the placeholder memory format :any:`format_tag::any` for
input or output. The memory format chosen is based on different circumstances
such as hardware and convolution parameters. Using the placeholder memory
format is the recommended practice for convolutions, since they are the most
compute-intensive operations in most topologies where they are present.

Other primitives, such as Elementwise, LRN, batch normalization and other, on
forward propagation should use the same memory format as the preceding layer
thus propagating the memory format through multiple oneDNN primitives. This
avoids unnecessary reorders which may be expensive and should be avoided
unless a compute-intensive primitive requires a different format. For
performance reasons, backward computations of such primitives requires
consistent memory format with the corresponding forward computations. Hence,
when initializing there primitives for backward computations you should use
dnnl::memory::format_tag::any memory format tag as well.

Below is the short summary when to use and not to use memory format
:any:`format_tag::any` during operation description initialization:

+-----------------------------------------------------------------------------------------------------------------------------------+---------------------------------------------------------------------------------------------------------------+---------------------------------------------------------------------------------------------+---------------------------------------------------------------------------------------------------------------+
| Primitive Kinds                                                                                                                   | Forward Propagation                                                                                           | Backward Propagation                                                                        | No Propagation                                                                                                |
+===================================================================================================================================+===============================================================================================================+=============================================================================================+===============================================================================================================+
| **Compute intensive**: (De-)convolution, Inner product, RNN                                                                       | Use :any:`format_tag::any`                                                                                    | Use :any:`format_tag::any`                                                                  | N/A                                                                                                           |
+-----------------------------------------------------------------------------------------------------------------------------------+---------------------------------------------------------------------------------------------------------------+---------------------------------------------------------------------------------------------+---------------------------------------------------------------------------------------------------------------+
| **Memory-bandwidth limited**: Pooling, Layer and Batch Normalization, Local Response Normalization, Elementwise, Shuffle, Softmax | Use memory format from preceding layer for source tensors, and :any:`format_tag::any` for destination tensors | Use :any:`format_tag::any` for gradient tensors, and actual memory formats for data tensors | N/A                                                                                                           |
+-----------------------------------------------------------------------------------------------------------------------------------+---------------------------------------------------------------------------------------------------------------+---------------------------------------------------------------------------------------------+---------------------------------------------------------------------------------------------------------------+
| **Memory-bandwidth limited**: Reorder, Concat, Sum, Binary                                                                        | N/A                                                                                                           | N/A                                                                                         | Use memory format from preceding layer for source tensors, and :any:`format_tag::any` for destination tensors |
+-----------------------------------------------------------------------------------------------------------------------------------+---------------------------------------------------------------------------------------------------------------+---------------------------------------------------------------------------------------------+---------------------------------------------------------------------------------------------------------------+

Additional format synchronization is required between forward and backward
propagation when running training workloads. This is achieved via the
``hint_pd`` arguments of primitive descriptor constructors for primitives that
implement backward propagation.

.. rubric:: API

.. namespace:: 0

.. doxygenenum:: dnnl::memory::format_tag
   :project: oneDNN

.. vim: ts=3 sw=3 et spell spelllang=en