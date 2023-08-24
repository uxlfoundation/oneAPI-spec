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
   - ``uniform_real_distribution``
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

Extensions:
------------
The following extensions from the `C++ Standard`_ may apply:

- ``linear_congruential_engine`` and ``subtract_with_carry_engine`` satisfy the requirements of UniformRandomBitGenerator
  for all cases except when ``UIntType`` template parameter equals ``sycl::vec<>``.
  When ``UIntType`` equals ``sycl::vec<>``

  - ``G::result_type`` is ``sycl::vec<UIntElemType, N>`` , where ``UIntElemType`` is one of unsigned integers type supported by SYCL devices, ``N`` is a number of elements
  - ``G::min()`` returns the smallest scalar value of ``UIntElemType`` type that G's operator() may return.
  - ``G::min()`` returns the largest scalar value of ``UIntElemType`` type that G's operator() may return.
  - ``g()`` returns a ``sycl::vec<UIntElemType, N>`` filled with ``N`` values in the closed interval ``[G::min(), G::max()]``

- Next engines and engine adaptors with predefined parameters may be implemented:

.. code:: cpp

   template <int _N>
   using minstd_rand0_vec = linear_congruential_engine<sycl::vec<::std::uint_fast32_t, _N>, 16807, 0, 2147483647>;``

Required behavior: The 10000th consecutively produced random number value of a default-constructed object
of type ``minstd_rand0_vec<>`` is the same as for ``minstd_rand0`` and equals 1043618065.

.. code:: cpp

    template <int _N>
    using minstd_rand_vec = linear_congruential_engine<sycl::vec<uint_fast32_t, _N>, 48271, 0, 2147483647>;

Required behavior: The 10000th consecutively produced random number value of a default-constructed object
of type ``minstd_rand_vec<>`` is the same as for ``minstd_rand`` and equals 399268537.

.. code:: cpp

    template <int _N>
    using ranlux24_base_vec = subtract_with_carry_engine<sycl::vec<uint_fast32_t, _N>, 24, 10, 24>

Required behavior: The 10000th consecutively produced random number value of a default-constructed object
of type ``ranlux24_base_vec<>`` is the same as for ``ranlux24_base`` and equals 7937952.

.. code:: cpp

    template <int _N>
    using ranlux48_base_vec = subtract_with_carry_engine<sycl::vec<uint_fast64_t, _N>, 48, 5, 12>;

Required behavior: The 10000th consecutively produced random number value of a default-constructed object
of type ``ranlux48_base_vec<>`` is the same as for ``ranlux48_base`` and equals 61839128582725.

.. code:: cpp

    template <int _N>
    using ranlux24_vec = discard_block_engine<ranlux24_base_vec<_N>, 223, 23>;

Required behavior: The 10000th consecutively produced random number value of a default-constructed object
of type ``ranlux24_vec<>`` is the same as for ``ranlux24`` and equals 9901578.

.. code:: cpp

    template <int _N>
    using ranlux48_vec = discard_block_engine<ranlux48_base_vec<_N>, 389, 11>;

Required behavior: The 10000th consecutively produced random number value of a default-constructed object
of type ``ranlux48_vec<>`` is the same as for ``ranlux48`` and equals 1112339016.

- ``linear_congruential_engine<>`` class template has the UIntScalarType type for template parameters ``a``, ``c``, ``m``
  Template type parameter ``UIntScalarType``

  - equals appropriate ``UIntType`` if the last one is scalar
  - equals ``T`` if the ``UIntType`` is of ``sycl::vec<T, N>`` type

- distribution class templates uses a scalar_type as a type for input arguments in costructors that is

  - equals appropriate ``IntType`` or ``RealType`` distribution template parameter if the last one is scalar
  - equals ``T`` if the ``UIntType`` or ``RealType`` distribution template parameter is of ``sycl::vec<T, N>`` type

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
