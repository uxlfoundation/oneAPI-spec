..
  Copyright 2020 Intel Corporation

.. _oneDPL-section:

======
oneDPL
======

The |dpl_full_name| (oneDPL) provides the functionality
specified in the C++ standard, with extensions to support data parallelism
and offloading to devices, and with extensions to simplify its usage for 
implementing data parallel algorithms.

The library is comprised of the following components:

- The C++ standard library.  (See `C++ Standard`_.)  oneDPL
  defines a subset of the C++ standard library which you can use with
  buffers and data parallel kernels.  (See `Supported C++
  Standard Library APIs and Algorithms`_.)

- Parallel STL. (See `Supported C++ Standard Library APIs and
  Algorithms`_.)  oneDPL extends Parallel STL with execution
  policies and companion APIs for running algorithms on oneAPI
  devices.  (See :doc:`Extensions to Parallel STL <pstl>`.)

- Extensions. An additional set of library classes and functions that
  are known to be useful in practice but are not (yet) included into
  C++ or SYCL specifications. (See :doc:`Specific API of oneDPL <extensions>`.)

Namespaces
----------

oneDPL uses :code:`namespace std` for the `Supported C++ Standard
Library APIs and Algorithms`_ including Parallel STL algorithms
and the subset of the standard C++ library for kernels,
and uses :code:`namespace dpstd` for its extended functionality.

Supported C++ Standard Library APIs and Algorithms
---------------------------------------------------

For all C++ algorithms accepting execution policies (as defined by C++17),
oneDPL provides an implementation supporting
:code:`dpstd::execution::device_policy` and SYCL buffers (via :code:`dpstd::begin/end`).
(See :doc:`Extensions to Parallel STL <pstl>`.)

.. toctree::

   pstl.rst
   extensions.rst

.. _`C++ Standard`: https://isocpp.org/std/the-standard
