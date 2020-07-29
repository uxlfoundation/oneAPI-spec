.. _onemkl_stats_make_dataset:

make_dataset
============

Entry point to create a dataset from the provided parameters.

.. _onemkl_stats_make_dataset_description:

.. rubric:: Description and Assumptions

oneapi::mkl::stats::make_dataset function is used to create dataset from the provided storage of observations matrix, number of dimensions and obesrvations, and other parameters.

:ref:`onemkl_stats_make_dataset` supports the following precisions for data:

    .. list-table::
        :header-rows: 1

        * - T
        * - ``float``
        * - ``double``


.. _onemkl_stats_make_dataset_buffer:

make_dataset (Buffer version)
-----------------------------

.. rubric:: Syntax

.. cpp:function:: template<oneapi::mkl::stats::layout ObservationsLayout = oneapi::mkl::stats::layout::row_major, \
                  typename Type> \
                  oneapi::mkl::stats::dataset<sycl::buffer<Type, 1>, ObservationsLayout> \
                  oneapi::mkl::stats::make_dataset(\
                  std::int64_t n_dims, \
                  std::int64_t n_observations, \
                  sycl::buffer<Type, 1> observations, \
                  sycl::buffer<Type, 1> weights = {0}, \
                  sycl::buffer<std::int64_t, 1> indices = {0});

.. container:: section

    .. rubric:: Template Parameters

    ObservationsLayout
        Data layout. The specific values are described in :ref:`onemkl_stats_dataset`.

    Type
        Data precision.

.. container:: section

    .. rubric:: Input Parameters

    n_dims
        The number of dimensions.

    n_observations
        The number of observations.

    observations
        Matrix of observations.

    weights
        Optional parameter. Array of weights of size n_observations. Elements of the array are non-negative members.  If the parameter is not specified, each observation has weight equal 1.

    indicies
        Optional parameter. Array of vector components that are processed. Size of array is n_dims. If the parameter is not specified, all components are processed.

.. container:: section

    .. rubric:: Return Value

    Dataset holding specified parameters,


.. _onemkl_stats_make_dataset_usm:

make_dataset (USM version)
--------------------------

.. rubric:: Syntax

.. cpp:function:: template<oneapi::mkl::stats::layout ObservationsLayout = oneapi::mkl::stats::layout::row_major, \
                    typename Type> \
                    oneapi::mkl::stats::dataset<Type*, ObservationsLayout> oneapi::mkl::stats::make_dataset(std::int64_t \
                    n_dims, std::int64_t n_observations, \
                    Type* observations, Type* weights = nullptr, std::int64_t* indices = nullptr);

.. container:: section

    .. rubric:: Template Parameters

    ObservationsLayout
        Data layout. The specific values are described in :ref:`onemkl_stats_dataset`.

    Type
        Data precision.

.. container:: section

    .. rubric:: Input Parameters

    n_dims
        The number of dimensions.

    n_observations
        The number of observations.

    observations
        Matrix of observations.

    weights
        Optional parameter. Array of weights of size n_observations. Elements of the array are non-negative     mbers.  If   the parameter is not specified, each observation has weight equal 1.

    indicies
        Optional parameter. Array of vector components that are processed. Size of array is n_dims. If the    parameter  is   not specified, all components are processed.

.. container:: section

    .. rubric:: Return Value

    Dataset holding specified parameters.


**Parent topic:** :ref:`onemkl_stats_service_routines`

