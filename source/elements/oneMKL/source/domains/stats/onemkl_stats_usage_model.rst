.. SPDX-FileCopyrightText: 2019-2020 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. _onemkl_stats_usage_model:

oneMKL Summary Statistics Usage Model
=====================================


.. rubric:: Description

A typical algorithm for summary statistics is as follows:


#. Create and initialize an object for dataset.
#. Call the summary statistics routine to calculate the appropriate estimate.


The following example demonstrates how to calculate mean values for a 3-dimensional dataset filled with random numbers. For dataset creation, the :ref:`onemkl_stats_make_dataset` helper function is used.


USM-based example
-----------------

.. code-block:: cpp

    #include "oneapi/mkl/stats.hpp"

    int main() {
        sycl::queue queue;

        constexpr std::size_t n_observations = 1000;
        constexpr std::size_t n_dims = 3;

        // allocate Unified Shared Memory for the dataset of the size n_observations * n_dims and fill it with any data
        // allocate Unified Shared Memory for the mean output of the size n_dims

        // create oneapi::mkl::stats::dataset
        auto dataset = oneapi::mkl::stats::make_dataset<oneapi::mkl::stats::layout::row_major>(n_dims, n_observations, dataset_ptr);

        // call statistics computation routine
        auto event = oneapi::mkl::stats::mean(queue, dataset, mean_ptr);

        // wait until computations are completed
        event.wait();

        // ...
    }

**Parent topic:** :ref:`onemkl_stats`
