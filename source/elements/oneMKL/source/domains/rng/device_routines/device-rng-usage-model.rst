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

    #include <iostream>
    #include <sycl/sycl.hpp>

    #include "oneapi/mkl/rng/device.hpp"

    int main() {
        sycl::queue queue;
        const int n = 1000;
        const int seed = 1;
        // Prepare an array for random numbers
        std::vector<float> r(n);

        sycl::buffer<floats> r_buf(r.data(), r.size());
        // Submit a kernel to generate on device
        queue.submit([&](sycl::handler& cgh) {
            auto r_acc = r_buf.template get_access<sycl::access::mode::write>(cgh);
            cgh.parallel_for(sycl::range<1>(n), [=](sycl::item<1> item) {
                // Create an engine object
                oneapi::mkl::rng::device::philox4x32x10<> engine(seed, item.get_id(0));
                // Create a distribution object
                oneapi::mkl::rng::device::uniform<> distr;
                // Call generate function to obtain scalar random number
                float res = oneapi::mkl::rng::device::generate(distr, engine);

                r_acc[item.get_id(0)] = res;
            });
        });

        auto r_acc = r_buf.template get_access<sycl::access::mode::read>();
        std::cout << "Samples of uniform distribution" << std::endl;
        for(int i = 0; i < 10; i++) {
            std::cout << r_acc[i] << std::endl;
        }

        return 0;
    }

Example of Vector Random Numbers Generation
-------------------------------------------

.. code-block:: cpp

    #include <iostream>
    #include <sycl/sycl.hpp>

    #include "oneapi/mkl/rng/device.hpp"

    int main() {
        sycl::queue queue;
        const int n = 1000;
        const int seed = 1;
        const int vec_size = 4;
        // Prepare an array for random numbers
        std::vector<float> r(n);

        sycl::buffer<float> r_buf(r.data(), r.size());
        // Submit a kernel to generate on device
        sycl::queue{}.submit([&](sycl::handler& cgh) {
            auto r_acc = r_buf.template get_access<sycl::access::mode::write>(cgh);
            cgh.parallel_for(sycl::range<1>(n / vec_size), [=](sycl::item<1> item) {
                // Create an engine object
                oneapi::mkl::rng::device::philox4x32x10<vec_size> engine(seed, item.get_id(0) * vec_size);
                // Create a distribution object
                oneapi::mkl::rng::device::uniform<> distr;
                // Call generate function to obtain sycl::vec<float, 4> with random numbers
                auto res = oneapi::mkl::rng::device::generate(distr, engine);

                res.store(ite.get_id(0), r_acc);
            });
        });

        auto r_acc = r_buf.template get_access<sycl::access::mode::read>();
        std::cout << "Samples of uniform distribution" << std::endl;
        for(int i = 0; i < 10; i++) {
            std::cout << r_acc[i] << std::endl;
        }

        return 0;
    }

**Parent topic:** :ref:`onemkl_device_rng_routines`