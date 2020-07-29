.. _onemkl_rng_mcg59:

mcg59
=====

The 59-bit multiplicative congruential pseudorandom number generator.

.. _onemkl_rng_mcg59_description:

.. rubric:: Description

mcg59 engine is a 59-bit multiplicative congruential generator from NAG Numerical Libraries :ref:`NAG <onemkl_rng_bibliography>`. mcg59 belongs to linear congruential generators with the period length of approximately :math:`2^{57}`.

.. container:: section

    .. rubric:: Generation algorithm

    :math:`x_n=ax_{n-1}(mod \ m)`

    :math:`u_n = x_n / m`

    :math:`a = 13^{13}, m=2^{59}`

.. _onemkl_rng_mcg59_description_syntax:

class mcg59
-----------

.. rubric:: Syntax

.. code-block:: cpp

    class mcg59 {
    public:
        mcg59(sycl::queue& queue, std::uint64_t seed);
        mcg59 (const mcg59& other);
        mcg59& operator=(const mcg59& other);
        ~mcg59();
    };

.. cpp:class:: oneapi::mkl::rng::mcg59

.. container:: section

    .. rubric:: Class Members

    .. list-table::
        :header-rows: 1

        * - Routine
          - Description
        * - `mcg59(sycl::queue& queue, std::uint64_t seed)`_
          - Constructor for common seed initialization of the engine
        * - `mcg59(const mcg59& other)`_
          - Copy constructor

.. container:: section

    .. rubric:: Constructors

    .. _`mcg59(sycl::queue& queue, std::uint64_t seed)`:

    .. cpp:function:: mcg59::mcg59(sycl::queue& queue, std::uint64_t seed)

    .. container:: section

        .. rubric:: Input Parameters

        queue
            Valid sycl::queue object, calls of the :ref:`oneapi::mkl::rng::generate()<onemkl_rng_generate>` routine submits kernels in this queue to obtain random numbers from a given engine.

        seed
            The initial conditions of the generator state, assume :math:`x_0 = seed \ mod \ 2^{59}`, if :math:`x_0 = 0`, assume :math:`x_0 = 1`.

    .. _`mcg59(const mcg59& other)`:

    .. cpp:function:: mcg59::mcg59(const mcg59& other)

    .. container:: section

        .. rubric:: Input Parameters

        other
            Valid ``mcg59`` object, state of current generator is changed to copy of other engine state, note: queue, which is hold by engine is also changing on other's one.

.. container:: section

    .. rubric:: Subsequence selection functions support

    .. list-table::
        :header-rows: 1

        * - Routine
          - Support
        * - :ref:`oneapi::mkl::rng::skip_ahead(EngineType& engine, std::uint64_t num_to_skip)<onemkl_rng_skip_ahead_common>`
          - Supported
        * - :ref:`oneapi::mkl::rng::skip_ahead(EngineType& engine, std::initializer_list\<std::uint64_t\> num_to_skip)<onemkl_rng_skip_ahead_common>`
          - Not supported
        * - :ref:`oneapi::mkl::rng::leapfrog(EngineType& engine, std::uint64_t idx, std::uint64_t stride)<onemkl_rng_leapfrog>`
          - Supported

**Parent topic:** :ref:`onemkl_rng_engines_basic_random_number_generators`
