.. _onemkl_stats_mean:

mean
====

Entry point to compute mean values.

.. _onemkl_stats_mean_description:

.. rubric:: Description and Assumptions

oneapi::mkl::stats::mean function is used to compute mean array (mean value for each dataset's dimension).

:ref:`onemkl_stats_mean` supports the following precisions for data:

    .. list-table::
        :header-rows: 1

        * - T
        * - ``float``
        * - ``double``


.. _onemkl_stats_mean_buffer:

mean (Buffer version)
---------------------

.. rubric:: Syntax

.. cpp:function:: template<oneapi::mkl::stats::method Method = oneapi::mkl::stats::method::fast, typename Type, \
                   oneapi::mkl::stats::layout ObservationsLayout> \
                   void oneapi::mkl::stats::mean(sycl::queue& queue, \
                   const oneapi::mkl::stats::dataset<sycl::buffer<Type, 1>, ObservationsLayout>& data, \
                   sycl::buffer<Type, 1> mean);

.. container:: section

    .. rubric:: Template Parameters

    Method
        Method which is used for estimate computation. The specific values are as follows:

        *  ``oneapi::mkl::stats::method::fast``
        *  ``oneapi::mkl::stats::method::one_pass``

    Type
        Data precision.

    ObservationsLayout
        Data layout. The specific values are described in :ref:`onemkl_stats_dataset`.

.. container:: section

    .. rubric:: Input Parameters

    queue
        The queue where the routine should be executed.

    data
        Dataset which is used for computation.

.. container:: section

    .. rubric:: Output Parameters

    mean
        sycl::buffer array of mean values.

.. _onemkl_stats_mean_usm:

mean (USM version)
------------------

.. rubric:: Syntax

.. cpp:function:: template<oneapi::mkl::stats::method Method = oneapi::mkl::stats::method::fast, typename Type, \
                   oneapi::mkl::stats::layout ObservationsLayout> \
                   sycl::event oneapi::mkl::stats::mean(sycl::queue& queue, \
                   const dataset<Type*, ObservationsLayout>& data, \
                   Type* mean, \
                   const sycl::vector_class<sycl::event> &dependencies = {});

.. container:: section

    .. rubric:: Template Parameters

    Method
        Method which is used for estimate computation. The specific values are as follows:

        *  ``oneapi::mkl::stats::method::fast``
        *  ``oneapi::mkl::stats::method::one_pass``

    Type
        Data precision.

    ObservationsLayout
        Data layout. The specific values are described in :ref:`onemkl_stats_dataset`.

.. container:: section

    .. rubric:: Input Parameters

    queue
        The queue where the routine should be executed.

    data
        Dataset which is used for computation.

    dependencies
        Optional parameter. List of events to wait for before starting computation, if any.

.. container:: section

    .. rubric:: Output Parameters

    mean
        Pointer to the array of mean values.

.. container:: section

    .. rubric:: Return Value

    Output event to wait on to ensure computation is complete.


**Parent topic:** :ref:`onemkl_stats_routines`

