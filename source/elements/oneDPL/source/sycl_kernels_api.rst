.. SPDX-FileCopyrightText: 2019-2022 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

SYCL Kernels API
----------------

Supported C++ Standard Library APIs and Algorithms
++++++++++++++++++++++++++++++++++++++++++++++++++

oneDPL defines a subset of the `C++ Standard`_ library APIs for use in DPC++ kernels. These APIs
can be employed in the kernels similarly to how they are employed in code for a typical
CPU-based platform.

.. _`C++ Standard`: https://isocpp.org/std/the-standard

Function Objects
++++++++++++++++

The oneDPL function objects are defined in the :code:`<oneapi/dpl/functional>` header,
in :code:`namespace oneapi::dpl`.

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