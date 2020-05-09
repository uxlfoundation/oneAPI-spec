..
  Copyright 2019-2020 Intel Corporation

.. default-domain:: cpp

.. _oneDNN-section:

====================
oneDNN |dnn_version|
====================

|dnn_full_name| (oneDNN) is a performance library containind building blocks
for for deep learning applications and frameworks. oneDNN supports:

* CNN primitives (Convolutions, Inner product, Pooling, etc.)
* RNN primitives (LSTM, Vanilla, RNN, GRU)
* Normalizations (LRN, Batch, Layer)
* Elementwise operations (ReLU, Tanh, ELU, Abs, etc.)
* Softmax, Sum, Concat, Shuffle
* Reorders from/to optimized data layouts
* 16- and 32-bit and bfloat16 floating point, and 8-bit integer data types

The oneDNN API is based on four main abstractions:

+---------------+-------------------------------------------------------------+
| Abstraction   | Description                                                 |
+===============+=============================================================+
| **Engine**    | A hardware processing unit. An Engine encapsulates a        |
|               | user-provided DPC++ device and context.                     |
+---------------+-------------------------------------------------------------+
| **Stream**    | A queue of operations on an Engine.                         |
+---------------+-------------------------------------------------------------+
| **Primitive** | A compute or a data transformation operation.               |
+---------------+-------------------------------------------------------------+
| **Memory**    | A multi-dimensional array (not necessarily contiguous) with |
|               | elements of certain type allocated on a particular Engine,  |
|               | constructed from a buffer or from a unified shared memory   |
|               | (USM) pointer.                                              |
+---------------+-------------------------------------------------------------+

.. literalinclude:: example.cpp
   :language: cpp
   :lines: 60-

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

.. _`open source implementation`: https://github.com/oneapi-src/oneDNN/tree/dev-v2
.. _`README`: https://github.com/oneapi-src/oneDNN/blob/dev-v2/README.md

.. vim: ts=3 sw=3 et
