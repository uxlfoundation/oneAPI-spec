.. _onemkl_rng_generate:

generate
========

Entry point to obtain random numbers from a given engine with proper statistics of a given distribution.

.. _onemkl_rng_generate_description:

.. rubric:: Description and Assumptions

oneapi::mkl::rng::generate function produces random numbers sequence from the given engine object and applied transformation from a given distribution object.

.. _onemkl_rng_generate_buffer:

generate (Buffer version)
-------------------------

.. rubric:: Syntax

.. cpp:function:: template<typename DistrType, typename EngineType> void generate (const DistrType& distr, EngineType& engine, std::int64_t n, cl::sycl::buffer<typename DistrType::result_type, 1>& r);

.. container:: section

    .. rubric:: Template Parameters

    DistrType
        Type of distribution which is used for random number generation.

    EngineType
        Type of engine which is used for random number generation.

.. container:: section

    .. rubric:: Input Parameters

    distr
        Distribution object. See :ref:`onemkl_rng_distributions` for details.

    engine
        Engine object. See :ref:`onemkl_rng_engines_basic_random_number_generators` for details.

    n
        Number of random values to be generated.

.. container:: section

    .. rubric:: Output Parameters

    r
        sycl::buffer of generated values.

.. _onemkl_rng_generate_usm:

generate (USM version)
----------------------

.. rubric:: Syntax

.. cpp:function:: template<typename DistrType, typename EngineType> cl::sycl::event generate (const DistrType& distr, EngineType& engine, std::int64_t n, typename DistrType::result_type* r, const cl::sycl::vector_class<cl::sycl::event> & dependencies);

.. container:: section

    .. rubric:: Template Parameters

    DistrType
        Type of distribution which is used for random number generation.

    EngineType
        Type of engine which is used for random number generation.

.. container:: section

    .. rubric:: Input Parameters

    distr
        Distribution object. See :ref:`onemkl_rng_distributions` for details.

    engine
        Engine object. See :ref:`onemkl_rng_engines_basic_random_number_generators` for details.

    n
        Number of random values to be generated.

    dependencies
        Optional parameter. List of events to wait for before starting computation, if any.

.. container:: section

    .. rubric:: Output Parameters

    r
        pointer to generated values.

.. container:: section

    .. rubric:: Return Value

    Output event to wait on to ensure computation is complete.


**Parent topic:** :ref:`onemkl_rng_generate_routine`

