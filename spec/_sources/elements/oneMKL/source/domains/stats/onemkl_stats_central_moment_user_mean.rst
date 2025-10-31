.. SPDX-FileCopyrightText: 2019-2020 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. _onemkl_stats_central_moment_user_mean:

central_moment with provided mean
=================================

Entry point to compute central moments up to the 4th order with the provided mean values.

.. _onemkl_stats_central_moment_user_mean_description:

.. rubric:: Description and Assumptions

The oneapi::mkl::stats::central_moment function is used to compute an array of central moments up to the 4th order (central moments for each dataset's dimension) with the provided mean values.

:ref:`onemkl_stats_central_moment_user_mean` supports the following precisions for data:

    .. list-table::
        :header-rows: 1

        * - T
        * - ``float``
        * - ``double``


.. _onemkl_stats_central_moment_user_mean_buffer:

central_moment with provided mean (buffer version)
--------------------------------------------------

.. rubric:: Syntax

.. code-block:: cpp

    namespace oneapi::mkl::stats {
    template<method Method = method::fast, typename Type, layout ObservationsLayout>
        void central_moment(sycl::queue& queue,
        sycl::buffer<Type, 1> mean,
        const dataset<ObservationsLayout, sycl::buffer<Type, 1>>& data,
        sycl::buffer<Type, 1> central_moment_2,
        sycl::buffer<Type, 1> central_moment_3 = {0},
        sycl::buffer<Type, 1> central_moment_4 = {0});
    }

.. container:: section

    .. rubric:: Template Parameters

    Method
        Method which is used for estimate computation. The specific values are as follows:

        *  ``oneapi::mkl::stats::method::fast``

    Type
        Data precision.

    ObservationsLayout
        Data layout. The specific values are described in :ref:`onemkl_stats_dataset`.

.. container:: section

    .. rubric:: Input Parameters

    queue
        The queue where the routine should be executed.

    mean
        sycl::buffer to the array of provided mean values.

    data
        Dataset which is used for computation.

.. container:: section

    .. rubric:: Output Parameters

    central_moment_2
        sycl::buffer array of 2nd order central moment values.

    central_moment_3
        Optional parameter. sycl::buffer array of 3rd order central moment values.

    central_moment_4
        Optional parameter. sycl::buffer array of 4th order central moment values.

.. container:: section

    .. rubric:: Throws

    oneapi::mkl::invalid_argument
        Exception is thrown when central_moment_2.get_count() == 0 & central_moment_3.get_count() == 0 & central_moment_4.get_count() == 0, or mean.get_count() == 0, or dataset object is invalid


.. _onemkl_stats_central_moment_user_mean_usm:

central_moment with provided mean (USM version)
-----------------------------------------------

.. rubric:: Syntax

.. code-block:: cpp

    namespace oneapi::mkl::stats {
    template<method Method = method::fast, typename Type, layout ObservationsLayout>
        sycl::event central_moment(sycl::queue& queue,
        Type* mean,
        const dataset<ObservationsLayout, Type*>& data,
        Type* central_moment_2,
        Type* central_moment_3 = nullptr,
        Type* central_moment_4 = nullptr,
        const std::vector<sycl::event> &dependencies = {});
    }

.. container:: section

    .. rubric:: Template Parameters

    Method
        Method which is used for estimate computation. The specific values are as follows:

        *  ``oneapi::mkl::stats::method::fast``

    Type
        Data precision.

    ObservationsLayout
        Data layout. The specific values are described in :ref:`onemkl_stats_dataset`.

.. container:: section

    .. rubric:: Input Parameters

    queue
        The queue where the routine should be executed.

    mean
        Pointer to the array of provided mean values.

    data
        Dataset which is used for computation.

    dependencies
        Optional parameter. List of events to wait for before starting computation, if any.

.. container:: section

    .. rubric:: Output Parameters

    central_moment_2
        Pointer to the array of the 2nd order central moment values.

    central_moment_3
        Optional parameter. Pointer to the array of the 3rd order central moment values.

    central_moment_4
        Optional parameter. Pointer to the array of the 2nd order central moment values.

.. container:: section

    .. rubric:: Throws

    oneapi::mkl::invalid_argument
        Exception is thrown when central_moment_2 == nullptr & central_moment_3 == nullptr & central_moment_4 == nullptr or mean == nullptr, or dataset object is invalid

.. container:: section

    .. rubric:: Return Value

    Output event to wait on to ensure computation is complete.


**Parent topic:** :ref:`onemkl_stats_routines`

