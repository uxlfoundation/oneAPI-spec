.. SPDX-FileCopyrightText: 2019-2022 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

SYCL Kernels API
----------------

Supported C++ Standard Library APIs and Algorithms
++++++++++++++++++++++++++++++++++++++++++++++++++

oneDPL defines a subset of the C++ standard library APIs for use in DPC++ kernels. These APIs
can be employed in the kernels similarly to how they are employed in code for a typical
CPU-based platform.

For all C++ algorithms accepting execution policies (as defined by `C++ Standard`_), oneDPL provides
an implementation for oneAPI devices via :code:`oneapi::dpl::execution::device_policy`. These algorithms
must be capable of processing data in SYCL buffers (passed via :code:`oneapi::dpl::begin/end`)
and in unified shared memory (USM). (See :doc:`Parallel API <parallel_api>`.)

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