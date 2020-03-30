..
  Copyright 2019 Intel Corporation

.. default-domain:: cpp

.. _oneDNN-section:

====================
oneDNN |dnn_version|
====================

|dnn_full_name| (oneDNN) is an open-source performance library for
deep learning applications.  The library includes building blocks for
deep learning applications and frameworks.

oneDNN supports:

* CNN primitives (Convolutions, Inner product, Pooling, etc.)
* RNN primitives (LSTM, Vanilla, RNN, GTU)
* Normalizations (LRN, Batch, Layer)
* Elementwise operations (ReLU, Tanh, ELU, Abs, etc.)
* Softmax, Sum, Concat, Shuffle
* Reorders from/to optimized data layouts
* 16- and 32-bit and bfloat16 floating point, and 8-bit integer data types

The oneDNN API is based on four main abstractions:

===========  ===========
Abstraction  Description
===========  ===========
Primitive    A compute or a data transformation operation
Engine       | A hardware processing unit.  An engine encapsulates
             | a user-provided DPC++ device and context.
Memory       | A memory object allocated on a particular Engine,
             | constructed from a buffer or from a unified shared
             | memory (USM) pointer.
Stream       A queue of primitives' operations on an Engine
===========  ===========

.. code:: cpp

  // User-defined DPCPP objects
  sycl::device dev;
  sycl::context ctx;
  sycl::queue queue;

  // This engine will operate on the specified device in the specified context
  dnnl::engine engine{dnnl::engine::kind::gpu, dev, ctx};

  // This Stream will use the specified DPC++ queue
  dnnl::stream stream{engine, queue};

  // Tensor dimensions
  int N, C, H, W;

  // Allocate DPC++ buffers for input and output memory objects
  sycl::buffer<float, 1> buf_in{sycl::range<1>{N * C * H * W}};
  sycl::buffer<float, 1> buf_out{sycl::range<1>{N * C * H * W}};

  // These memory objects will use buf_in and buf_out DPC++ buffers as the
  // underlying storage
  dnnl::memory mem_in{{N, C, H, W}, dnnl::memory::data_type::f32,
              dnnl::memory::format_tag::nwhc}, engine, buf_in};
  dnnl::memory mem_out{{N, C, H, W}, dnnl::memory::data_type::f32,
              dnnl::memory::format_tag::nwhc}, engine, buf_out};

  // Create a ReLU operation using elementwise primitive
  dnnl::eltwise_forward relu{{{dnnl::prop_kind::forward_inference,
              dnnl::algorithm::eltwise_relu, mem_in.get_desc(), 0.f, 0.f},
              engine}};

  // User-defined input dependency events
  std::vector<sycl::event> dependencies;

  // Execute ReLU in the stream (i.e. in the queue) passing input dependencies
  // and retrieving the output dependency
  sycl::event event = relu.execute_sycl(stream,
              {{DNNL_ARG_SRC, mem_in}, {DNNL_ARG_DST, mem_out}},
              dependencies);

--------------------------
Open Source Implementation
--------------------------

Intel has published an `open source implementation`_ with the Apache
license.

---
API
---

.. toctree::
   :maxdepth: 2

   api/engine.rst
   api/stream.rst
   api/memory.rst
   api/primitives.rst
   api/utilities.rst

-------
Testing
-------

Intel's binary distribution of oneDNN contains example code that you
can be used to test library functionality.

The `open source implementation`_ includes a comprehensive test suite.
Consult the `README`_ for directions.

.. _`open source implementation`: https://github.com/intel/mkl-dnn
.. _`README`: https://github.com/intel/mkl-dnn/blob/master/README.md

.. vim: ts=3 sw=3 et
