.. _onemkl_stats_variation_user_mean:

variation with provided mean
============================

Entry point to compute variation with the provided mean values.

.. _onemkl_stats_variation_user_mean_description:

.. rubric:: Description and Assumptions

oneapi::mkl::stats::variation function is used to compute array of variation (variation for each dataset's dimension) with the provided mean values.

:ref:`onemkl_stats_variation_user_mean` supports the following precisions for data:

    .. list-table::
        :header-rows: 1

        * - T
        * - ``float``
        * - ``double``


.. _onemkl_stats_variation_user_mean_buffer:

oneapi::mkl::stats::variation (Buffer version)
----------------------------------------------

.. rubric:: Syntax

.. cpp:function:: template<oneapi::mkl::stats::method Method = oneapi::mkl::stats::method::fast, typename Type, \
                   oneapi::mkl::stats::layout ObservationsLayout> \
                   void oneapi::mkl::stats::variation(sycl::queue& queue, \
                   sycl::buffer<Type, 1> mean, \
                   const oneapi::mkl::stats::dataset<sycl::buffer<Type, 1>, ObservationsLayout>& data, \
                   sycl::buffer<Type, 1> variation);


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

    variation
        sycl::buffer array of variation values.

.. _onemkl_stats_variation_user_mean_usm:

variation with provided mean (USM version)
------------------------------------------

.. rubric:: Syntax

.. cpp:function:: template<oneapi::mkl::stats::method Method = oneapi::mkl::stats::method::fast, typename Type, \
                   oneapi::mkl::stats::layout ObservationsLayout> \
                   sycl::event oneapi::mkl::stats::variation(sycl::queue& queue, \
                   Type* mean, \
                   const dataset<Type*, ObservationsLayout>& data, \
                   Type* variation, \
                   const sycl::vector_class<sycl::event> &dependencies = {});

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

    variation
        Pointer to the array of the variation values.

.. container:: section

    .. rubric:: Return Value

    Output event to wait on to ensure computation is complete.

**Parent topic:** :ref:`onemkl_stats_routines`

