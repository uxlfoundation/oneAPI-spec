..
  Copyright 2019-2020 Intel Corporation

.. default-domain:: cpp

Memory
------

Memory object is container that describes and stores data. Memory objects can
contain data of various data types and formats. There are two levels of
abstraction:

1. *Memory descriptor* -- engine-agnostic logical description of data (number
   of dimensions, dimension sizes, and data type), and, optionally, the
   information about the physical format of data in memory. If this
   information is not known yet, a memory descriptor can be created with
   :enum:`dnnl::memory::format_tag::any`. This allows compute-intensive
   primitives to chose the most appropriate format for the computations.  The
   user is then responsible for reordering their data into the new format if
   the formats do not match.

   A memory descriptor can be initialized either by specifying dimensions, and
   memory format tag or strides for each of them.

   User can query amount of memory required by a memory descriptor using the
   :func:`dnnl::memory::desc::get_size` function. The size of data in
   general cannot be computed as the product of dimensions multiplied by the
   size of the data type. So users are required to use this function for
   better code portability.

   Two memory descriptors can be compared using the equality and inequality
   operators.  The comparison is especially useful when checking whether it is
   necessary to reorder data from the user's data format to a primitive's
   format.

2. *Memory object* -- an engine-specific object that handles the data and its
   description (a memory descriptor). With USM, the data handle is simply a
   pointer to ``void``. The data handle can be queried using
   :func:`dnnl::memory::get_data_handle` and set using
   :func:`dnnl::memory::set_data_handle`. The underlying SYCL buffer, when
   used, can be queried using :func:`dnnl::memory::get_sycl_buffer` and
   and set using :func:`dnnl::memory::set_sycl_buffer`. A memory object
   can also be queried for the underlying memory descriptor and for its engine
   using :func:`dnnl::memory::get_desc` and
   :func:`dnnl::memory::get_engine`.

Along with ordinary memory descriptors with all dimensions being positive, the
library supports *zero-volume* memory descriptors with one or more dimensions
set to zero. This is used to support the NumPy\* convention. If a zero-volume
memory is passed to a primitive, the primitive typically does not perform any
computations with this memory. For example:

* A concatenation primitive would ignore all memory object with zeroes in the
  concat dimension / axis.

* A forward convolution with a source memory object with zero in the minibatch
  dimension would always produce a destination memory object with a zero in the
  minibatch dimension and perform no computations.

* However, a forward convolution with a zero in one of the weights dimensions
  is ill-defined and is considered to be an error by the library because there
  is no clear definition on what the output values should be.

Data handle of a zero-volume memory is never accessed.

.. doxygenstruct:: dnnl::memory
   :project: oneDNN
   :members:

