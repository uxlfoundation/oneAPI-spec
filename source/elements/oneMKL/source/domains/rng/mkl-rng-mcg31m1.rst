.. _onemkl_rng_mcg31m1:

mcg31m1
=======

The 31-bit multiplicative congruential pseudorandom number generator MCG(1132489760, 231 -1).

.. _onemkl_rng_mcg31m1_description:

.. rubric:: Description

Mcg31m1 engine is a 31-bit multiplicative congruential generator :ref:`[L'Ecuyer99] <onemkl_rng_bibliography>`. Mcg31m1 belongs to linear congruential generators with the period length of approximately :math:`2^{31}`. Such generators are still used as default random number generators in various software systems, mainly due to the simplicity of the portable versions implementation, speed and compatibility with the earlier systems versions. However, their period length does not meet the requirements for modern basic generators. Still, the mcg31m1 generator possesses good statistic properties and you may successfully use it to generate random numbers of different distributions for small samplings.

.. container:: section

    .. rubric:: Generation algorithm

    :math:`x_n=ax_{n-1}(mod \ m)`

    :math:`u_n = x_n / m`

    :math:`a = 1132489760, m=2^{31} - 1`

.. _onemkl_rng_mcg31m1_description_syntax:

class mcg31m1
-------------

.. rubric:: Syntax

.. code-block:: cpp

    class mcg31m1 {
    public:
        mcg31m1(sycl::queue& queue, std::uint32_t seed);
        mcg31m1 (const mcg31m1& other);
        mcg31m1& operator=(const mcg31m1& other);
        ~mcg31m1();
    };

.. cpp:class:: oneapi::mkl::rng::mcg31m1

.. container:: section

    .. rubric:: Class Members

    .. list-table::
        :header-rows: 1

        * - Routine
          - Description
        * - `mcg31m1(sycl::queue& queue, std::uint32_t seed)`_
          - Constructor for common seed initialization of the engine
        * - `mcg31m1(const mcg31m1& other)`_
          - Copy constructor

.. container:: section

    .. rubric:: Constructors

    .. _`mcg31m1(sycl::queue& queue, std::uint32_t seed)`:

    .. cpp:function:: mcg31m1::mcg31m1(sycl::queue& queue, std::uint32_t seed)

    .. container:: section

        .. rubric:: Input Parameters

        queue
            Valid sycl::queue object, calls of the :ref:`oneapi::mkl::rng::generate()<onemkl_rng_generate>` routine submits kernels in this queue to obtain random numbers from a given engine.

        seed
            The initial conditions of the generator state, assume :math:`x_0 = seed \ mod \ 0x7FFFFFFF`, if :math:`x_0 = 0`, assume :math:`x_0 = 1`.

    .. _`mcg31m1(const mcg31m1& other)`:

    .. cpp:function:: mcg31m1::mcg31m1(const mcg31m1& other)

    .. container:: section

        .. rubric:: Input Parameters

        other
            Valid ``mcg31m1`` object, state of current generator is changed to copy of other engine state, note: queue, which is hold by engine is also changing on other's one.

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
