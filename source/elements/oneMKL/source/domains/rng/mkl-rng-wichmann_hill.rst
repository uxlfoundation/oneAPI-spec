.. _onemkl_rng_wichmann_hill:

wichmann_hill
=============

The wichmann_hill engine is the set of 273 Wichmann-Hill's combined multiplicative congruential generators from NAG Numerical Libraries :ref:`[NAG] <onemkl_rng_bibliography>`.

.. _onemkl_rng_wichmann_hill_description:

.. rubric:: Description

The set of 372 different basic pseudorandom number generators wichmann_hill is the second basig generator in the NAG libraries.

.. container:: section

    .. rubric:: Generation algorithm

    :math:`x_n=a_{1, j} x_{n-1} (mod \ m_{1, j})`

    :math:`y_n = a_{2, j} y_{n-1} (mod \ m_{2, j})`

    :math:`z_n = a_{3, j} z_{n-1} (mod \ m_{3, j})`

    :math:`w_n = a_{4, j} w_{n-1} (mod \ m_{4, j})`

    :math:`u_n = (x_n / m_{1, j} + y_n / m_{2, j} + z_n / m_{3, j} + w_n / m_{4, j}) mod \ 1`

    The constatns :math:`a_{i, j}` range from 112 to 127, the constatnts :math:`m_{i, j}` are prime numbers ranging from 16718909 to 16776917, close to :math:`2 ^ {24}`.


.. _onemkl_rng_wichmann_hill_description_syntax:

class wichmann_hill
-------------------

.. rubric:: Syntax

.. code-block:: cpp

    class wichmann_hill {
    public:
        wichmann_hill(sycl::queue& queue, std::uint32_t seed);
        wichmann_hill(sycl::queue& queue, std::uint32_t seed, std::uint32_t engine_idx);
        wichmann_hill(sycl::queue& queue, std::initializer_list<std::uint32_t> seed);
        wichmann_hill(sycl::queue& queue, std::initializer_list<std::uint32_t> seed, std::uint32_t engine_idx);
        wichmann_hill (const wichmann_hill& other);
        wichmann_hill& operator=(const wichmann_hill& other);
        ~wichmann_hill();
    };

.. cpp:class:: oneapi::mkl::rng::wichmann_hill

.. container:: section

    .. rubric:: Class Members

    .. list-table::
        :header-rows: 1

        * - Routine
          - Description
        * - `wichmann_hill(sycl::queue& queue, std::uint32_t seed)`_
          - Constructor for common seed initialization of the engine (for this case multiple generators of the set would be used)
        * - `wichmann_hill(sycl::queue& queue, std::uint32_t seed, std::uint32_t engine_idx)`_
          - Constructor for common seed initialization of the engine (for this case single generator of the set would be used)
        * - `wichmann_hill(sycl::queue& queue, std::initializer_list<std::uint32_t> seed)`_
          - Constructor for extended seed initialization of the engine (for this case multiple generators of the set would be used)
        * - `wichmann_hill(sycl::queue& queue, std::initializer_list<std::uint32_t> seed, std::uint32_t engine_idx)`_
          - Constructor for extended seed initialization of the engine (for this case single generator of the set would be used)
        * - `wichmann_hill(const wichmann_hill& other)`_
          - Copy constructor

.. container:: section

    .. rubric:: Constructors

    .. _`wichmann_hill(sycl::queue& queue, std::uint32_t seed)`:

    .. cpp:function:: wichmann_hill::wichmann_hill(sycl::queue& queue, std::uint32_t seed)

    .. container:: section

        .. rubric:: Input Parameters

        queue
            Valid sycl::queue object, calls of the :ref:`oneapi::mkl::rng::generate()<onemkl_rng_generate>` routine submits kernels in this queue to obtain random numbers from a given engine.

        seed
            The initial conditions of the generator state. Assume :math:`x_0=seed \ mod \ m_1, y_0 = z_0 = w_0 = 1`. If :math:`x_0 = 0`, assume :math:`x_0 = 1`.

    .. _`wichmann_hill(sycl::queue& queue, std::uint32_t seed, std::uint32_t engine_idx)`:

    .. cpp:function:: wichmann_hill::wichmann_hill(sycl::queue& queue, std::uint32_t seed, std::uint32_t engine_idx)

    .. container:: section

        .. rubric:: Input Parameters

        queue
            Valid sycl::queue object, calls of the :ref:`oneapi::mkl::rng::generate()<onemkl_rng_generate>` routine submits kernels in this queue to obtain random numbers from a given engine.

        seed
            The initial conditions of the generator state. Assume :math:`x_0=seed \ mod \ m_1, y_0 = z_0 = w_0 = 1`. If :math:`x_0 = 0`, assume :math:`x_0 = 1`.

        engine_idx
            The index of the set 1, ..., 273.

    .. _`wichmann_hill(sycl::queue& queue, std::initializer_list<std::uint32_t> seed)`:

    .. cpp:function:: wichmann_hill::wichmann_hill(sycl::queue& queue, std::initializer_list<std::uint32_t> seed)

    .. container:: section

        .. rubric:: Input Parameters

        queue
            Valid ``sycl::queue object``, calls of the :ref:`oneapi::mkl::rng::generate()<onemkl_rng_generate>` routine submits kernels in this queue to obtain random numbers from a given engine.

        seed
            The initial conditions of the generator state, assume:
            if :math:`n = 0: x_{0} = y_{0} = z_{0} = w_{0} = 1`

            if :math:`n = 1: x_{0} = seed[0] \ mod \ m_1, y_{0} = z_{0} = w_{0} = 1`. If :math:`x_0 = 0`, assume :math:`x_0 = 1`.

            if :math:`n = 2: x_{0} = seed[0] \ mod \ m_1, y_{0} = seed[1] \ mod \ m_2, z_{0} = w_{0} = 1`.

            if :math:`n = 3: x_{0} = seed[0] \ mod \ m_1, y_{0} = seed[1] \ mod \ m_2, z_{0} = seed[2] \ mod \ m_3, w_{0} = 1`.

            if :math:`n \geqslant 4: x_{0} = seed[0] \ mod \ m_1, y_{0} = seed[1] \ mod \ m_2`

                :math:`z_{0} = seed[2] \ mod \ m_3, w_{0} = seed[3] \ mod \ m_4`.


    .. _`wichmann_hill(sycl::queue& queue, std::initializer_list<std::uint32_t> seed, std::uint32_t engine_idx)`:

    .. cpp:function:: wichmann_hill::wichmann_hill(sycl::queue& queue, std::initializer_list<std::uint32_t> seed, std::uint32_t engine_idx)

    .. container:: section

        .. rubric:: Input Parameters

        queue
            Valid ``sycl::queue object``, calls of the :ref:`oneapi::mkl::rng::generate()<onemkl_rng_generate>` routine submits kernels in this queue to obtain random numbers from a given engine.

        seed
            The initial conditions of the generator state, assume:
            if :math:`n = 0: x_{0} = y_{0} = z_{0} = w_{0} = 1`

            if :math:`n = 1: x_{0} = seed[0] \ mod \ m_1, y_{0} = z_{0} = w_{0} = 1`. If :math:`x_0 = 0`, assume :math:`x_0 = 1`.

            if :math:`n = 2: x_{0} = seed[0] \ mod \ m_1, y_{0} = seed[1] \ mod \ m_2, z_{0} = w_{0} = 1`.

            if :math:`n = 3: x_{0} = seed[0] \ mod \ m_1, y_{0} = seed[1] \ mod \ m_2, z_{0} = seed[2] \ mod \ m_3, w_{0} = 1`.

            if :math:`n \geqslant 4: x_{0} = seed[0] \ mod \ m_1, y_{0} = seed[1] \ mod \ m_2`

                :math:`z_{0} = seed[2] \ mod \ m_3, w_{0} = seed[3] \ mod \ m_4`.

        engine_idx
            The index of the set 1, ..., 273.

    .. _`wichmann_hill(const wichmann_hill& other)`:

    .. cpp:function:: wichmann_hill::wichmann_hill(const wichmann_hill& other)

    .. container:: section

        .. rubric:: Input Parameters

        other
            Valid ``wichmann_hill`` object, state of current generator is changed to copy of other engine state, note: queue, which is hold by engine is also changing on other's one.

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
