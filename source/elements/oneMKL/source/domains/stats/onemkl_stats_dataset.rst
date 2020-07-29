.. _onemkl_stats_dataset:

dataset
=======

The structure consolidates information of a multi-dimensional dataset.

.. _onemkl_stats_dataset_description:

.. rubric:: Description

The struct object is used in :ref:`onemkl_stats_routines` as a multi-dimensional data storage. ``dataset`` struct contains information about observations matrix and it's size (dimensions x observations), observations weights and indicies for dimensions (defines dimensions to be processed).

.. _onemkl_stats_dataset_syntax_buffer:

structure dataset (Buffer version)
----------------------------------

.. rubric:: Syntax

.. code-block:: cpp

    template<typename Type, oneapi::mkl::stats::layout ObservationsLayout>
	struct dataset<sycl::buffer<Type, 1>, ObservationsLayout> {

    	explicit dataset(std::int64_t n_dims_, std::int64_t n_observations_,
                    sycl::buffer<Type, 1> observations_, sycl::buffer<Type, 1> weights_ = {0},
                    sycl::buffer<std::int64_t, 1> indices_ = {0}) :
                    n_dims(n_dims_), n_observations(n_observations_),
                    observations(observations_),
                    weights(weights_), indices(indices_), layout(ObservationsLayout) {};

    	std::int64_t n_dims;
    	std::int64_t n_observations;
    	oneapi::stats::mkl::layout layout = ObservationsLayout;
    	sycl::buffer<Type, 1> observations;
    	sycl::buffer<Type, 1> weights;
    	sycl::buffer<std::int64_t, 1> indices;
	};

.. cpp:struct:: template<typename Type, oneapi::stats::mkl::layout ObservationsLayout> \
					oneapi::mkl::stats::dataset<sycl::buffer<Type, 1>, ObservationsLayout>

.. container:: section

    .. rubric:: Template parameters

    .. container:: section

        typename Type
            Type of the multi-dimensional data. Supported types:

                * ``float``
                * ``double``

    .. container:: section

        oneapi::mkl::stats::layout ObservationsLayout
            Type of the multi-dimensional data layout. Supported types:

                * ``oneapi::mkl::stats::layout::row_major``
                * ``oneapi::mkl::stats::layout::col_major``

.. container:: section

    .. rubric:: Struct Members

    .. list-table::
        :header-rows: 1

        * - Routine
          - Description
        * - `explicit dataset(std::int64_t n_dims_, std::int64_t n_observations_, sycl::buffer<Type, 1> observations_, sycl::buffer<Type, 1> weights_ = {0}, sycl::buffer<std::int64_t, 1> indices_ = {0})`_
          - Constructor


.. container:: section

    .. rubric:: Constructors

    .. container:: section

        .. _`explicit dataset(std::int64_t n_dims_, std::int64_t n_observations_, sycl::buffer<Type, 1> observations_, sycl::buffer<Type, 1> weights_ = {0}, sycl::buffer<std::int64_t, 1> indices_ = {0})`:

        .. cpp:function:: explicit dataset::dataset(std::int64_t n_dims_, std::int64_t n_observations_, \
                    sycl::buffer<Type, 1> observations_, \
                    sycl::buffer<Type, 1> weights_ = {0}, \
                    sycl::buffer<std::int64_t, 1> indices_ = {0})

        .. container:: section

            .. rubric:: Description

            Constructor with parameters.

            	* `n_dims_` is the number of dimensions
            	* `n_observations_` is the number of observations
            	* `observations_` is the matrix of observations
            	* `weights_` is an optional parameter, represents array of weights for obervations (of size n_observations). If the parameter is not specified, each observation is assigned a weight equal 1.
            	* `indices_` is an optional parameter, represents array of dimensions that are processed (of size n_dims). If the parameter is not specified, all dimensions are processed.

.. _onemkl_stats_dataset_syntax_usm:

structure dataset (USM version)
-------------------------------

.. rubric:: Syntax

.. code-block:: cpp

    template<typename Type, oneapi::stats::mkl::layout ObservationsLayout>
	 struct dataset<Type*, ObservationsLayout> {
    	explicit dataset(std::int64_t n_dims_, std::int64_t n_observations_, Type* observations_,
                    Type* weights_ = nullptr, std::int64_t* indices_ = nullptr) :
                    n_dims(n_dims_), n_observations(n_observations_),
                    observations(observations_),
                    weights(weights_), indices(indices_), layout(ObservationsLayout) {};

    	std::int64_t n_dims;
    	std::int64_t n_observations;
    	oneapi::stats::mkl::layout layout = ObservationsLayout;
    	Type* observations;
    	Type* weights;
    	std::int64_t* indices;
	};


.. cpp:struct:: template<typename Type, oneapi::stats::mkl::layout ObservationsLayout> \
					oneapi::mkl::stats::dataset<Type*, ObservationsLayout>

.. container:: section

    .. rubric:: Template parameters

    .. container:: section

        typename Type
            Type of the multi-dimensional data. Supported types:

                * ``float``
                * ``double``

    .. container:: section

        oneapi::mkl::stats::layout ObservationsLayout
            Type of the multi-dimensional data layout. Supported types:

                * ``oneapi::mkl::stats::layout::row_major``
                * ``oneapi::mkl::stats::layout::col_major``

.. container:: section

    .. rubric:: Struct Members

    .. list-table::
        :header-rows: 1

        * - Routine
          - Description
        * - `explicit dataset(std::int64_t n_dims_, std::int64_t n_observations_, Type* observations_, Type* weights_ =  nullptr, std::int64_t* indices_ = nullptr)`_
          - Constructor


.. container:: section

    .. rubric:: Constructors

    .. container:: section

        .. _`explicit dataset(std::int64_t n_dims_, std::int64_t n_observations_, Type* observations_, Type* weights_ = nullptr, std::int64_t* indices_ = nullptr)`:

        .. cpp:function:: explicit dataset::dataset(std::int64_t n_dims_, std::int64_t n_observations_, \
                    Type* observations_, \
                    Type* weights_ = nullptr, \
                    std::int64_t* indices_ = nullptr)

        .. container:: section

            .. rubric:: Description

            Constructor with parameters.

            	* `n_dims_` is the number of dimensions
            	* `n_observations_` is the number of observations
            	* `observations_` is the matrix of observations
            	* `weights_` is an optional parameter, represents array of weights for obervations (of size n_observations). If the parameter is not specified, each observation is assigned a weight equal 1.
            	* `indices_` is an optional parameter, represents array of dimensions that are processed (of size n_dims). If the parameter is not specified, all dimensions are processed.

**Parent topic:** :ref:`onemkl_stats`

