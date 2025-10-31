.. SPDX-FileCopyrightText: 2023 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. _onemkl_device_rng_usage_model:

oneMKL RNG Device Usage Model
=============================

.. contents::
    :local:
    :depth: 1

A typical usage model for device routines is the same as described in
:ref:`onemkl_rng_usage_model`:


#. Create and initialize the object for basic random number generator.

#. Create and initialize the object for distribution generator.

#. Call the generate routine to get random numbers with appropriate statistical distribution.


Example of Scalar Random Numbers Generation
-------------------------------------------

.. code-block:: cpp

    #include "oneapi/mkl/rng/device.hpp"

    int main() {
        sycl::queue q;
        // Prepare a memory for random numbers
        // Submit a kernel to generate on device
        q.submit([&](sycl::handler& cgh) {
            // ...
            cgh.parallel_for(n, [=](size_t idx) {
                // Create an engine object
                oneapi::mkl::rng::device::philox4x32x10<> engine(seed, idx);
                // Create a distribution object
                oneapi::mkl::rng::device::uniform<float> distr;
                // Call generate function to obtain scalar random number
                float res = oneapi::mkl::rng::device::generate(distr, engine);
                // ...
            });
        });
        // ...
    }

Example of Vector Random Numbers Generation
-------------------------------------------

.. code-block:: cpp

    #include "oneapi/mkl/rng/device.hpp"

    int main() {
        sycl::queue q;
        // Prepare an array for random numbers
        // Submit a kernel to generate on device
        q.submit([&](sycl::handler& cgh) {
            // ...
            cgh.parallel_for((n / vec_size), [=](size_t idx) {
                // Create an engine object
                oneapi::mkl::rng::device::philox4x32x10<vec_size> engine(seed, idx * vec_size);
                // Create a distribution object
                oneapi::mkl::rng::device::uniform<float> distr;
                // Call generate function to obtain random numbers
                sycl::vec<float, vec_size> res = oneapi::mkl::rng::device::generate(distr, engine);
                // ...
            });
        });
        // ...
    }

**Parent topic:** :ref:`onemkl_device_rng_routines`
