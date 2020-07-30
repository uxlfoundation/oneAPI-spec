.. _onemkl_rng_ars5:

ars5
====

The ars5 counter-based pseudorandom number generator.

.. _onemkl_rng_ars5_description:

.. rubric:: Description

Ars5 engine is a keyed family of counter-based BRNG. The state consists of 128-bit integer counter :math:`c` and 128-bits key :math:`k`. The BRNG is based on the AES encryption algorithm [:ref:`FIPS-197 <onemkl_rng_bibliography>`].

.. container:: section

    .. rubric:: Generation algorithm

    The generator has 32-bit integer output obtained in the following way [:ref:`Salmon11 <onemkl_rng_bibliography>`]:

    1. The i-th number is defined by the following formula :math:`r_i=(f(i/ 4) >> ((i \ mod \ 4) * 32)) \ mod \ 2 ^ {32}`
    2. Function :math:`f(c)` takes 128-bit argument and returns a 128-bit number. The returned number is obtained as follows:
        2.1. :math:`c_0 = c \oplus k` and :math:`k_0 = k`.
        
        2.2. The following recurrence is calculated N = 5 times:

        :math:`c_{i+1} = SubBytes(c)`

        :math:`c_{i+1} = ShiftRows(c_{i+1})`

        :math:`c_{i+1} = MixColumns(c_{i+1})`, this step is omitted if :math:`i+1 = N`

        :math:`c_{i+1} = AddRoundKey(c_{i+1}, k_j)`

        :math:`Lo(k_{i+1}) = Lo(k) + 0x9E3779B97F4A7C15`

        :math:`Hi(k_{i+1}) = Hi(k) + 0xBB67AE8584CAA73B`

        Specification for :math:`SubBytes, ShiftRows, MixColumns, AddRoundKey` functions can be found in [:ref:`FIPS-197 <onemkl_rng_bibliography>`].

        2.3. Put :math:`f(c) = c_N`, where :math:`N = 10`

    3. Real output: :math:`u_n=(int)r_n / 2^{32} + 1/2`

.. _onemkl_rng_ars5_description_syntax:

class ars5
----------

.. rubric:: Syntax

.. code-block:: cpp

    class ars5 {
    public:
        ars5(sycl::queue& queue, std::uint64_t seed);
        ars5(sycl::queue& queue, std::initializer_list<std::uint64_t> seed);
        ars5 (const ars5& other);
        ars5& operator=(const ars5& other);
        ~ars5();
    };

.. cpp:class:: oneapi::mkl::rng::ars5

.. container:: section

    .. rubric:: Class Members

    .. list-table::
        :header-rows: 1

        * - Routine
          - Description
        * - `ars5(sycl::queue& queue, std::uint64_t seed)`_
          - Constructor for common seed initialization of the engine
        * - `ars5(sycl::queue& queue, std::initializer_list<std::uint64_t> seed)`_
          - Constructor for extended seed initialization of the engine
        * - `ars5(const ars5& other)`_
          - Copy constructor

.. container:: section

    .. rubric:: Constructors

    .. _`ars5(sycl::queue& queue, std::uint64_t seed)`:

    .. cpp:function:: ars5::ars5(sycl::queue& queue, std::uint64_t seed)

    .. container:: section

        .. rubric:: Input Parameters

        queue
            Valid sycl::queue object, calls of the :ref:`oneapi::mkl::rng::generate()<onemkl_rng_generate>` routine submits kernels in this queue to obtain random numbers from a given engine.

        seed
            The initial conditions of the generator state, assume :math:`k = seed, c = 0`, where :math:`k` is 128-bit key, :math:`c` is 128-bit counter.

    .. _`ars5(sycl::queue& queue, std::initializer_list<std::uint64_t> seed)`:

    .. cpp:function:: ars5::ars5(sycl::queue& queue, std::initializer_list<std::uint64_t> seed)

    .. container:: section

        .. rubric:: Input Parameters

        queue
            Valid ``sycl::queue object``, calls of the :ref:`oneapi::mkl::rng::generate()<onemkl_rng_generate>` routine submits kernels in this queue to obtain random numbers from a given engine.

        seed
            The initial conditions of the generator state, assume
            if :math:`n = 0: k = 0, c = 0`

            if :math:`n = 1: k = seed[0], c = 0`

            if :math:`n = 2: k = seed[0] + seed[1] \cdot 2^{64}, c = 0`

            if :math:`n = 3: k = seed[0] + seed[1] \cdot 2^{64}, c = seed[2]`

            if :math:`n = 4: k = seed[0] + seed[1] \cdot 2^{64}, c = seed[2] + seed[3] \cdot 2^{64}`

            for :math:`n > 4` following arguments are ignored

    .. _`ars5(const ars5& other)`:

    .. cpp:function:: ars5::ars5(const ars5& other)

    .. container:: section

        .. rubric:: Input Parameters

        other
            Valid ``ars5`` object, state of current generator is changed to copy of other engine state, note: queue, which is hold by engine is also changing on other's one.


.. container:: section

    .. rubric:: Subsequence selection functions support

    .. list-table::
        :header-rows: 1

        * - Routine
          - Support
        * - :ref:`oneapi::mkl::rng::skip_ahead(EngineType& engine, std::uint64_t num_to_skip)<onemkl_rng_skip_ahead_common>`
          - Supported
        * - :ref:`oneapi::mkl::rng::skip_ahead(EngineType& engine, std::initializer_list\<std::uint64_t\> num_to_skip)<onemkl_rng_skip_ahead_common>`
          - Supported
        * - :ref:`oneapi::mkl::rng::leapfrog(EngineType& engine, std::uint64_t idx, std::uint64_t stride)<onemkl_rng_leapfrog>`
          - Not supported


**Parent topic:** :ref:`onemkl_rng_engines_basic_random_number_generators`
