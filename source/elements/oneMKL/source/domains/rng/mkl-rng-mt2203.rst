.. _onemkl_rng_mt2203:

mt2203
======

The mt2203 engine is the set of 6024 Mersenne Twister pseudorandom number generators MT2203 [:ref:`Matsumoto98 <onemkl_rng_bibliography>`], [:ref:`Matsumoto00 <onemkl_rng_bibliography>`].

.. _onemkl_rng_mt2203_description:

.. rubric:: Description

The set of 6024 basic pseudorandom number generators MT2203 is a natural addition to MT19937 generator. MT2203 generators are intended for use in large scale Monte Carlo simulations performed on multi-processor computer systems.

.. container:: section

    .. rubric:: Generation algorithm

    For :math:`j = 1,..., 6024`:

    :math:`x_{n, j} =x_{n - (69 - 34), j} \oplus ( (x_{n - 69, j} \& 0xFFFFFFE0) | (x_{n + 69 + 1, j} \& 0x1F) ) A_{j}`

    :math:`y_{n, j} = x_{n, j}`

    :math:`y_{n, j} = y_{n, j} \oplus (y_{n, j} >> 12)`

    :math:`y_{n, j} = y_{n, j} \oplus ( (y_{n, j} << 7) \& b_j)`

    :math:`y_{n, j} = y_{n, j} \oplus ( (y_{n, j} << 15) \& c_j)`

    :math:`y_{n, j} = y_{n, j} \oplus (y_{n, j} >> 18)`


.. container:: section

    Matrix :math:`A_j(32x32)` has the following format:

.. math::

    \left [ \begin{array}{ccccc} 0 & 1 & 0 & ... & ... \\ 0 & 0 & ... & 0 & ... \\ ... & ... & ... & ... & ... \\ 0 & ... & 0 & 0 & 1 \\ a_{31, j} & a_{30, j} & ... & ... & a_{0, 1} \end{array}\right ]


.. _onemkl_rng_mt2203_description_syntax:

class mt2203
------------

.. rubric:: Syntax

.. code-block:: cpp

    class mt2203 {
    public:
        mt2203(sycl::queue& queue, std::uint32_t seed);
        mt2203(sycl::queue& queue, std::uint32_t seed, std::uint32_t engine_idx);
        mt2203(sycl::queue& queue, std::initializer_list<std::uint32_t> seed);
        mt2203(sycl::queue& queue, std::initializer_list<std::uint32_t> seed, std::uint32_t engine_idx);
        mt2203 (const mt2203& other);
        mt2203& operator=(const mt2203& other);
        ~mt2203();
    };

.. cpp:class:: oneapi::mkl::rng::mt2203

.. container:: section

    .. rubric:: Class Members

    .. list-table::
        :header-rows: 1

        * - Routine
          - Description
        * - `mt2203(sycl::queue& queue, std::uint32_t seed)`_
          - Constructor for common seed initialization of the engine (for this case multiple generators of the set would be used)
        * - `mt2203(sycl::queue& queue, std::uint32_t seed, std::uint32_t engine_idx)`_
          - Constructor for common seed initialization of the engine (for this case single generator of the set would be used)
        * - `mt2203(sycl::queue& queue, std::initializer_list<std::uint32_t> seed)`_
          - Constructor for extended seed initialization of the engine (for this case multiple generators of the set would be used)
        * - `mt2203(sycl::queue& queue, std::initializer_list<std::uint32_t> seed, std::uint32_t engine_idx)`_
          - Constructor for extended seed initialization of the engine (for this case single generator of the set would be used)
        * - `mt2203(const mt2203& other)`_
          - Copy constructor

.. container:: section

    .. rubric:: Constructors

    .. _`mt2203(sycl::queue& queue, std::uint32_t seed)`:

    .. cpp:function:: mt2203::mt2203(sycl::queue& queue, std::uint32_t seed)

    .. container:: section

        .. rubric:: Input Parameters

        queue
            Valid sycl::queue object, calls of the :ref:`oneapi::mkl::rng::generate()<onemkl_rng_generate>` routine submits kernels in this queue to obtain random numbers from a given engine.

        seed
            The initial conditions of the generator state. The initialization algorithm described in [:ref:`MT2203 <onemkl_rng_bibliography>`].

    .. _`mt2203(sycl::queue& queue, std::uint32_t seed, std::uint32_t engine_idx)`:

    .. cpp:function:: mt2203::mt2203(sycl::queue& queue, std::uint32_t seed, std::uint32_t engine_idx)

    .. container:: section

        .. rubric:: Input Parameters

        queue
            Valid sycl::queue object, calls of the :ref:`oneapi::mkl::rng::generate()<onemkl_rng_generate>` routine submits kernels in this queue to obtain random numbers from a given engine.

        seed
            The initial conditions of the generator state. The initialization algorithm described in [:ref:`MT2203 <onemkl_rng_bibliography>`].

        engine_idx
            The index of the set 1, ..., 6024.

    .. _`mt2203(sycl::queue& queue, std::initializer_list<std::uint32_t> seed)`:

    .. cpp:function:: mt2203::mt2203(sycl::queue& queue, std::initializer_list<std::uint32_t> seed)

    .. container:: section

        .. rubric:: Input Parameters

        queue
            Valid ``sycl::queue object``, calls of the :ref:`oneapi::mkl::rng::generate()<onemkl_rng_generate>` routine submits kernels in this queue to obtain random numbers from a given engine.

        seed
            The initial conditions of the generator state. The initialization algorithm described in [:ref:`MT2203 <onemkl_rng_bibliography>`].

    .. _`mt2203(sycl::queue& queue, std::initializer_list<std::uint32_t> seed, std::uint32_t engine_idx)`:

    .. cpp:function:: mt2203::mt2203(sycl::queue& queue, std::initializer_list<std::uint32_t> seed, std::uint32_t engine_idx)

    .. container:: section

        .. rubric:: Input Parameters

        queue
            Valid ``sycl::queue object``, calls of the :ref:`oneapi::mkl::rng::generate()<onemkl_rng_generate>` routine submits kernels in this queue to obtain random numbers from a given engine.

        seed
            The initial conditions of the generator state. The initialization algorithm described in [:ref:`MT2203 <onemkl_rng_bibliography>`].

        engine_idx
            The index of the set 1, ..., 6024.

    .. _`mt2203(const mt2203& other)`:

    .. cpp:function:: mt2203::mt2203(const mt2203& other)

    .. container:: section

        .. rubric:: Input Parameters

        other
            Valid ``mt2203`` object, state of current generator is changed to copy of other engine state, note: queue, which is hold by engine is also changing on other's one.

.. container:: section

    .. rubric:: Subsequence selection functions support

    .. list-table::
        :header-rows: 1

        * - Routine
          - Not support
        * - :ref:`oneapi::mkl::rng::skip_ahead(EngineType& engine, std::uint64_t num_to_skip)<onemkl_rng_skip_ahead_common>`
          - Not supported
        * - :ref:`oneapi::mkl::rng::skip_ahead(EngineType& engine, std::initializer_list\<std::uint64_t\> num_to_skip)<onemkl_rng_skip_ahead_common>`
          - Supported
        * - :ref:`oneapi::mkl::rng::leapfrog(EngineType& engine, std::uint64_t idx, std::uint64_t stride)<onemkl_rng_leapfrog>`
          - Not supported

**Parent topic:** :ref:`onemkl_rng_engines_basic_random_number_generators`
