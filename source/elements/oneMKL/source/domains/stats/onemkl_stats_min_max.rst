.. _onemkl_stats_min_max:

min_max
=======

Entry point to compute min and max values.

.. _onemkl_stats_min_max_description:

.. rubric:: Description and Assumptions

oneapi::mkl::stats::min_max function is used to compute min and max arrays (min and max values for each dataset's dimension).

:ref:`onemkl_stats_min_max` supports the following precisions for data:

    .. list-table::
        :header-rows: 1

        * - T
        * - ``float``
        * - ``double``


.. _onemkl_stats_min_max_buffer:

min_max (Buffer version)
------------------------

.. rubric:: Syntax

.. cpp:function:: template<oneapi::mkl::stats::method Method = oneapi::mkl::stats::method::fast, typename Type, \
                   oneapi::mkl::stats::layout ObservationsLayout> \
                   void oneapi::mkl::stats::min_max(sycl::queue& queue, \
                   const oneapi::mkl::stats::dataset<sycl::buffer<Type, 1>, ObservationsLayout>& data, \
                   sycl::buffer<Type, 1> min, \
                   sycl::buffer<Type, 1> max);

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

    data
        Dataset which is used for computation.

.. container:: section

    .. rubric:: Output Parameters

    min
        sycl::buffer array of min values.

    max
        sycl::buffer array of max values.

.. _onemkl_stats_min_max_usm:

min_max (USM version)
---------------------

.. rubric:: Syntax

.. cpp:function:: template<oneapi::mkl::stats::method Method = oneapi::mkl::stats::method::fast, typename Type, \
                   oneapi::mkl::stats::layout ObservationsLayout> \
                   sycl::event oneapi::mkl::stats::min_max(sycl::queue& queue, \
                   const dataset<Type*, ObservationsLayout>& data, \
                   Type* min, \
                   Type* max, \
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

    data
        Dataset which is used for computation.

    dependencies
        Optional parameter. List of events to wait for before starting computation, if any.

.. container:: section

    .. rubric:: Output Parameters

    min
        Pointer to the array of min values.

    max
        Pointer to the array of max values.

.. container:: section

    .. rubric:: Return Value

    Output event to wait on to ensure computation is complete.


**Parent topic:** :ref:`onemkl_stats_routines`

