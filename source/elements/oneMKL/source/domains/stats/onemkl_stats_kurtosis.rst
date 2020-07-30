.. _onemkl_stats_kurtosis:

kurtosis
========

Entry point to compute kurtosis.

.. _onemkl_stats_kurtosis_description:

.. rubric:: Description and Assumptions

oneapi::mkl::stats::kurtosis function is used to compute kurtosis array (kurtosis for each dataset's dimension).

:ref:`onemkl_stats_kurtosis` supports the following precisions for data:

    .. list-table::
        :header-rows: 1

        * - T
        * - ``float``
        * - ``double``


.. _onemkl_stats_kurtosis_buffer:

kurtosis (Buffer version)
-------------------------

.. rubric:: Syntax

.. cpp:function:: template<oneapi::mkl::stats::method Method = oneapi::mkl::stats::method::fast, typename Type, \
                   oneapi::mkl::stats::layout ObservationsLayout> \
                   void oneapi::mkl::stats::kurtosis(sycl::queue& queue, \
                   const oneapi::mkl::stats::dataset<sycl::buffer<Type, 1>, ObservationsLayout>& data, \
                   sycl::buffer<Type, 1> kurtosis);

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

    kurtosis
        sycl::buffer array of kurtosis values.


.. _onemkl_stats_kurtosis_usm:

kurtosis (USM version)
----------------------

.. rubric:: Syntax

.. cpp:function:: template<oneapi::mkl::stats::method Method = oneapi::mkl::stats::method::fast, typename Type, \
                   oneapi::mkl::stats::layout ObservationsLayout> \
                   sycl::event oneapi::mkl::stats::kurtosis(sycl::queue& queue, \
                   const dataset<Type*, ObservationsLayout>& data, \
                   Type* kurtosis, \
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

    kurtosis
        Pointer to the array of kurtosis values.

.. container:: section

    .. rubric:: Return Value

    Output event to wait on to ensure computation is complete.


**Parent topic:** :ref:`onemkl_stats_routines`

