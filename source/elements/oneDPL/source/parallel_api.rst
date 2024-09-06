.. SPDX-FileCopyrightText: 2019-2022 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

Parallel API
------------

oneDPL provides the set of parallel algorithms as defined by the `C++ Standard`_,
including parallel algorithms added in the 6th edition known as C++20.
All those algorithms work with *C++ Standard aligned execution policies* and with
*device execution policies*.

Additionally, oneDPL provides wrapper functions for `SYCL`_ buffers, special iterators, and
a set of non-standard parallel algorithms.

.. toctree::

   parallel_api/execution_policies.rst
   parallel_api/buffer_wrappers.rst
   parallel_api/iterators.rst
   parallel_api/algorithms.rst

.. _`C++ Standard`: https://isocpp.org/std/the-standard
.. _`SYCL`: https://registry.khronos.org/SYCL/specs/sycl-2020/html/sycl-2020.html
