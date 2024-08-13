.. SPDX-FileCopyrightText: Contributors to the oneAPI Specification project.
..
.. SPDX-License-Identifier: CC-BY-4.0

Parallel Ranges API
-------------------

oneDPL provides variations of algorithms that work with ranges defined in the `C++ Standard`_, 6th edition (C++20).
These algorithms execute according to a oneDPL execution policy supplied as the first argument, similarly to other
oneDPL algorithms.

The oneDPL parallel range algorithms rely on the functionality of C++20 and are not available in the code
compiled for earlier editions of the standard.

The parallel range algorithms reside in ``namespace oneapi::dpl::ranges``. Same as the range algorithm functions
defined by the `C++ standard` in ``namespace std::ranges``, they cannot be found by argument-dependent name lookup.

The following differences to the standard C++ range algorithms apply:

- The execution policy parameter is added.
- Output data sequences are defined as ranges, not iterators.
- Both input and output ranges must support random access.
- For a given algorithm, at least one of the input ranges as well as the output range must be bounded.
- ``for_each`` does not return its function object.

.. _`C++ Standard`: https://isocpp.org/std/the-standard
.. _`SYCL`: https://registry.khronos.org/SYCL/specs/sycl-2020/html/sycl-2020.html
