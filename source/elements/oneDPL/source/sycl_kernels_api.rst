.. SPDX-FileCopyrightText: 2019-2022 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

SYCL Kernels API
================

Supported C++ Standard Library APIs and Algorithms
++++++++++++++++++++++++++++++++++++++++++++++++++

oneDPL defines a subset of the `C++ Standard`_ library APIs for use in SYCL kernels. These APIs
can be employed in the kernels similarly to how they are employed in code for a typical
CPU-based platform.

.. _`C++ Standard`: https://isocpp.org/std/the-standard

Random Number Generation
++++++++++++++++++++++++

oneDPL provides a subset of the standard C++ pseudo-random number generation functionality
suitable to use within SYCL kernels. The APIs are defined in the :code:`<oneapi/dpl/random>` header. 

Supported functionality:
------------------------
- Engine class templates:
   - ``linear_congruential_engine``
   - ``subtract_with_carry_engine``
- Engine adaptor class templates:
   - ``discard_block_engine``
- Engines and engine adaptors with predefined parameters:
   - ``minstd_rand0``
   - ``minstd_rand``
   - ``ranlux24_base``
   - ``ranlux48_base``
   - ``ranlux24``
   - ``ranlux48``
- Distribution class templates:
   - ``uniform_int_distribution``
   - ``uniform_real_distribtuon``
   - ``normal_distribution``
   - ``exponential_distribution``
   - ``bernoulli_distribution``
   - ``geometric_distribution``
   - ``weibull_distribuion``
   - ``lognormal_distribution``
   - ``cauchy_distribution``
   - ``extreme_value_distribution``

Additionally, ``sycl::vec<>`` can be used as the result type for engines, engine adaptors, and distributions.

Limitations:
------------
The following deviations from the `C++ Standard`_ may apply:

- ``random_device`` and ``seed_seq`` classes and related APIs in other classes are not required;
- ``operator>>()``, ``operator<<()``, ``operator==()`` are not required;
- specifying the size of a random number engine's state is not required;
- distributions are only required to operate with floating point types applicable to supported SYCL devices.

Function Objects
++++++++++++++++

The oneDPL function objects are defined in the :code:`<oneapi/dpl/functional>` header.

.. code:: cpp

    namespace oneapi {
    namespace dpl {
        struct identity
        {
            template <typename T>
            constexpr T&&
            operator()(T&& t) const noexcept;
        };
    }
    }

The :code:`oneapi::dpl::identity` class implements an identity operation. Its function operator 
receives an instance of a type and returns the argument unchanged.
