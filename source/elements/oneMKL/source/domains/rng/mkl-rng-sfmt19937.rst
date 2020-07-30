.. _onemkl_rng_sfmt19937:

sfmt19937
=========

The SIMD-oriented Mersenne Twister pseudorandom number generator.

.. _onemkl_rng_sfmt19937_description:

.. rubric:: Description

SIMD-oriented Fast Mersenne Twister pseudorandom number generator SFMT19937 [:ref:`Saito08 <onemkl_rng_bibliography>`] with a period length equal to :math:`2 ^ {19937}-1` of the produced sequence. The state of engine contains the array of 156 128-bit integers.

.. container:: section

    .. rubric:: Generation algorithm

    :math:`w_n = w_0 A \oplus w_M B \oplus w_{n-2} C \oplus w_{n-1} D`

    Where :math:`w_0, w_M, w_{n-2}, ...` are the 128-bit integers, and :math:`wA, wB, wC, wD` operations are defined as follows:

    :math:`wA = (w << 8) \oplus w`, left shift of 128-bit integer :math:`w` by :math:`a` followed by exclusive-or operation

    :math:`wB = (w >> 8) \& mask`, right shift of each 32-bit integer in quadruple :math:`w` by and-operator with quadruple of 32-bit masks :math:`mask = (0xBFFFFFF6, 0xDFFAFFFF, 0xDDFECB7F, 0xDFFFFFEF)`

    :math:`wC = (w >> 8) \oplus w`, right shift of 128-bit integer :math:`w`

    :math:`wD = (w << 8)`, left shift of each 32-bit integer in quadruple :math:`w`

    Integer output: :math:`r_{4n+k} = w_{n}(k)`, where :math:`w_{n}(k)` is the k-th 32-bit integer in quadruple :math:`w_{n}, k = 0, 1, 2, 3`

    :math:`u_n = (int) r_n / 2^{32} + 1/2`


.. _onemkl_rng_sfmt19937_description_syntax:

class sfmt19937
---------------

.. rubric:: Syntax

.. code-block:: cpp

    class sfmt19937 {
    public:
        sfmt19937(sycl::queue& queue, std::uint32_t seed);
        sfmt19937(sycl::queue& queue, std::initializer_list<std::uint32_t> seed);
        sfmt19937(const sfmt19937& other);
        sfmt19937& operator=(const sfmt19937& other);
        ~sfmt19937();
    };

.. cpp:class:: oneapi::mkl::rng::sfmt19937

.. container:: section

    .. rubric:: Class Members

    .. list-table::
        :header-rows: 1

        * - Routine
          - Description
        * - `sfmt19937(sycl::queue& queue, std::uint32_t seed)`_
          - Constructor for common seed initialization of the engine
        * - `sfmt19937(sycl::queue& queue, std::initializer_list<std::uint32_t> seed)`_
          - Constructor for extended seed initialization of the engine
        * - `sfmt19937(const sfmt19937& other)`_
          - Copy constructor

.. container:: section

    .. rubric:: Constructors

    .. _`sfmt19937(sycl::queue& queue, std::uint32_t seed)`:

    .. cpp:function:: sfmt19937::sfmt19937(sycl::queue& queue, std::uint32_t seed)

    .. container:: section

        .. rubric:: Input Parameters

        queue
            Valid sycl::queue object, calls of the :ref:`oneapi::mkl::rng::generate()<onemkl_rng_generate>` routine submits kernels in this queue to obtain random numbers from a given engine.

        seed
            The initial conditions of the generator state. The initialization algorithm described in [:ref:`Saito08 <onemkl_rng_bibliography>`].

    .. _`sfmt19937(sycl::queue& queue, std::initializer_list<std::uint32_t> seed)`:

    .. cpp:function:: sfmt19937::sfmt19937(sycl::queue& queue, std::initializer_list<std::uint32_t> seed)

    .. container:: section

        .. rubric:: Input Parameters

        queue
            Valid ``sycl::queue object``, calls of the :ref:`oneapi::mkl::rng::generate()<onemkl_rng_generate>` routine submits kernels in this queue to obtain random numbers from a given engine.

        seed
            The initial conditions of the generator state. The initialization algorithm described in [:ref:`Saito08 <onemkl_rng_bibliography>`].

    .. _`sfmt19937(const sfmt19937& other)`:

    .. cpp:function:: sfmt19937::sfmt19937(const sfmt19937& other)

    .. container:: section

        .. rubric:: Input Parameters

        other
            Valid ``sfmt19937`` object, state of current generator is changed to copy of other engine state, note: queue, which is hold by engine is also changing on other's one.

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
          - Not supported

**Parent topic:** :ref:`onemkl_rng_engines_basic_random_number_generators`
