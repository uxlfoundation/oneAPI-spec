.. _onemkl_rng_r250:

r250
====

The 32-bit generalized feedback shift register pseudorandom number generator GFSR(250,103) :ref:`[Kirkpatrick81] <onemkl_rng_bibliography>`.

.. _onemkl_rng_r250_description:

.. rubric:: Description

Feedback shift register generators possess ample theoretical foundation and were initially intended for cryptographic and communication applications. The stream state is the array of 250 32-bit integers.

.. container:: section

    .. rubric:: Generation algorithm


    :math:`x_n=x_{n-103} \oplus x_{n-250}`

    :math:`u_n=x_n / 2 ^ {32}`


.. _onemkl_rng_r250_description_syntax:

class r250
----------

.. rubric:: Syntax

.. code-block:: cpp

    class r250 {
    public:
        r250(sycl::queue& queue, std::uint32_t seed);
        r250(sycl::queue& queue, std::vector<std::uint32_t> seed);
        r250(const r250& other);
        r250& operator=(const r250& other);
        ~r250();
    };

.. cpp:class:: oneapi::mkl::rng::r250

.. container:: section

    .. rubric:: Class Members

    .. list-table::
        :header-rows: 1

        * - Routine
          - Description
        * - `r250(sycl::queue& queue, std::uint32_t seed)`_
          - Constructor for common seed initialization of the engine
        * - `r250(sycl::queue& queue, std::vector<std::uint32_t> seed)`_
          - Constructor for extended seed initialization of the engine
        * - `r250(const r250& other)`_
          - Copy constructor

.. container:: section

    .. rubric:: Constructors

    .. _`r250(sycl::queue& queue, std::uint32_t seed)`:

    .. cpp:function:: r250::r250(sycl::queue& queue, std::uint32_t seed)

    .. container:: section

        .. rubric:: Input Parameters

        queue
            Valid sycl::queue object, calls of the :ref:`oneapi::mkl::rng::generate()<onemkl_rng_generate>` routine submits kernels in this queue to obtain random numbers from a given engine.

        seed
            The initial conditions of the generator state, assume :math:`x_{-250} = seed`. If :math:`seed = 0`, assume :math:`seed = 1`. Other values in state are initialized according to recurrent correlation :math:`x_{n+1} = 69069x_{n}(mod \ 2 ^ {32})`. Then the values :math:`x_{7k-247}, k = 0, 1, ..., 31` are interpreted as a binary matrix of size 32 x 32 and ``diagonalbits`` are set to 0, the under-diagonal bits to 0.

    .. _`r250(sycl::queue& queue, std::vector<std::uint32_t> seed)`:

    .. cpp:function:: r250::r250(sycl::queue& queue, std::vector<std::uint32_t> seed)

    .. container:: section

        .. rubric:: Input Parameters

        queue
            Valid ``sycl::queue object``, calls of the :ref:`oneapi::mkl::rng::generate()<onemkl_rng_generate>` routine submits kernels in this queue to obtain random numbers from a given engine.

        seed
            The initial conditions of the generator state
            if :math:`n \geqslant 0: x_{k-250} = seed[k], k = 0, 1, ..., 249`

    .. _`r250(const r250& other)`:

    .. cpp:function:: r250::r250(const r250& other)

    .. container:: section

        .. rubric:: Input Parameters

        other
            Valid ``r250`` object, state of current generator is changed to copy of other engine state, note: queue, which is hold by engine is also changing on other's one.

.. container:: section

    .. rubric:: Subsequence selection functions support

    .. list-table::
        :header-rows: 1

        * - Routine
          - Support
        * - :ref:`oneapi::mkl::rng::skip_ahead(EngineType& engine, std::uint64_t num_to_skip)<onemkl_rng_skip_ahead_common>`
          - Not supported
        * - :ref:`oneapi::mkl::rng::skip_ahead(EngineType& engine, std::initializer_list\<std::uint64_t\> num_to_skip)<onemkl_rng_skip_ahead_common>`
          - Not supported
        * - :ref:`oneapi::mkl::rng::leapfrog(EngineType& engine, std::uint64_t idx, std::uint64_t stride)<onemkl_rng_leapfrog>`
          - Not supported

**Parent topic:** :ref:`onemkl_rng_engines_basic_random_number_generators`
