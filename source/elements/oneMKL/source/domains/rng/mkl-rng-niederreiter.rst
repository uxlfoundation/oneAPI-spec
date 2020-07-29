.. _onemkl_rng_niederreiter:

niederreiter
============

The niederreiter is a 32-bit Gray code-based quasi-random number generator.

.. _onemkl_rng_niederreiter_description:

.. rubric:: Description

According to results of Bratley, Fox and Niederreiter :ref:`[Bratley92] <onemkl_rng_bibliography>` Niederreiter sequences have the best known theoretical asymptotic properties. The default dimension of quasi-random vectors can vary from 1 to 318 inclusive. It is also allowed to register user-defined parameters (irreducible polynomials).

.. container:: section

    .. rubric:: Generation algorithm


    :math:`x_n=x_{n_1} \oplus v_c`

    :math:`u_n=x_n / 2 ^ {32}`

    The value :math:`c` is the right-most zero bit in :math:`n-1`; :math:`x_n` is s-dimensional vector of 32-bit values. The s-dimensional vectors (calculated during engine initialization) :math:`v_i, i = 1, 32` are called direction numbers. The vector :math:`u_n` is the generator output normalized to the unit hypercube :math:`(0, 1) ^ s`.

.. _onemkl_rng_niederreiter_description_syntax:

class niederreiter
------------------

.. rubric:: Syntax

.. code-block:: cpp

    class niederreiter {
    public:
        niederreiter(sycl::queue& queue, std::uint32_t dimensions);
        niederreiter(sycl::queue& queue, std::vector<std::uint32_t>& irred_polynomials);
        niederreiter(const niederreiter& other);
        niederreiter& operator=(const niederreiter& other);
        ~niederreiter();
    };

.. cpp:class:: oneapi::mkl::rng::niederreiter

.. container:: section

    .. rubric:: Class Members

    .. list-table::
        :header-rows: 1

        * - Routine
          - Description
        * - `niederreiter(sycl::queue& queue, std::uint32_t dimensions)`_
          - Constructor with specified number of dimensions. The value should be :math:`1..318`.
        * - `niederreiter(sycl::queue& queue, std::vector<std::uint32_t>& irred_polynomials)`_
          - Constructor for extended use-case, when it's needed to use the number of dimensions greater than 318 or obtain another sequence.
        * - `niederreiter(const niederreiter& other)`_
          - Copy constructor

.. container:: section

    .. rubric:: Constructors

    .. _`niederreiter(sycl::queue& queue, std::uint32_t dimensions)`:

    .. cpp:function:: niederreiter::niederreiter(sycl::queue& queue, std::uint32_t dimensions)

    .. container:: section

        .. rubric:: Input Parameters

        queue
            Valid sycl::queue object, calls of the :ref:`oneapi::mkl::rng::generate()<onemkl_rng_generate>` routine submits kernels in this queue to obtain random numbers from a given engine.

        dimensions
            Number of dimensions. If :math:`dimen < 1` or :math:`dimen > 318`, assume :math:`dimen = 1`.

    .. _`niederreiter(sycl::queue& queue, std::vector<std::uint32_t>& irred_polynomials)`:

    .. cpp:function:: niederreiter::niederreiter(sycl::queue& queue, std::vector<std::uint32_t>& irred_polynomials)

    .. container:: section

        .. rubric:: Input Parameters

        queue
            Valid ``sycl::queue object``, calls of the :ref:`oneapi::mkl::rng::generate()<onemkl_rng_generate>` routine submits kernels in this queue to obtain random numbers from a given engine.

        irred_polynomials
            If you want to generate quasi-random vectors of greater dimension or obtain another sequence, you can register a set of your own irreducible polynomials. The number of dimmensions corresponds to the length of the vector.

    .. _`niederreiter(const niederreiter& other)`:

    .. cpp:function:: niederreiter::niederreiter(const niederreiter& other)

    .. container:: section

        .. rubric:: Input Parameters

        other
            Valid ``niederreiter`` object, state of current generator is changed to copy of other engine state, note: queue, which is hold by engine is also changing on other's one.

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
