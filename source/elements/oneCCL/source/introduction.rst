..
  Copyright 2020 Intel Corporation

==============
 Introduction
==============

The |ccl_full_name| (oneCCL) provides primitives for the
communication patterns that occur in deep learning applications.
oneCCL supports both scale-up for platforms with multiple
oneAPI devices and scale-out for clusters with multiple compute nodes.

oneCCL supports the following communication patterns used in
deep learning (DL) algorithms:

- Allreduce
- Allgatherv
- Broadcast
- Reduce
- Alltoall

oneCCL exposes controls over additional optimizations and
capabilities such as:

* User-defined pre-/post-processing of incoming buffers and reduction
  operation
* Prioritization for communication operations
* Persistent communication operations (enables de-coupling one-time
  initialization and repetitive execution)
* Fusion of multiple communication operations into the single one
* Unordered communication operations
* :code:`Allreduce` on sparse data

Intel has published an `open source implementation`_ with the Apache
license. The `open source implementation`_ includes a comprehensive
test suite.  Consult the `README`_ for directions.

.. _`open source implementation`: https://github.com/oneapi-src/oneCCL
.. _`README`: https://github.com/oneapi-src/oneCCL/blob/master/README.md

