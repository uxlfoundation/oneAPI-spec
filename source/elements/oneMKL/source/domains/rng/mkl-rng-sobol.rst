.. _onemkl_rng_sobol:

sobol
=====

The sobol is a 32-bit Gray code-based quasi-random number generator.

.. _onemkl_rng_sobol_description:

.. rubric:: Description

Bratley and Fox :ref:`[Bratley88] <onemkl_rng_bibliography>` provide an implementation of the SOBOL quasi-random number generator. The default dimensions of quasi-random vectors can vary from 1 to 40 inclusive. It is also allowed to register user-defined parameters (direction numbers).

.. container:: section

    .. rubric:: Generation algorithm


    :math:`x_n=x_{n_1} \oplus v_c`

    :math:`u_n=x_n / 2 ^ {32}`

    The value :math:`c` is the right-most zero bit in :math:`n-1`; :math:`x_n` is s-dimensional vector of 32-bit values. The s-dimensional vectors (calculated during engine initialization) :math:`v_i, i = 1, 32` are called direction numbers. The vector :math:`u_n` is the generator output normalized to the unit hypercube :math:`(0, 1) ^ s`.

.. _onemkl_rng_sobol_description_syntax:

class sobol
-----------

.. rubric:: Syntax

.. code-block:: cpp

    class sobol {
    public:
        sobol(sycl::queue& queue, std::uint32_t dimensions);
        sobol(sycl::queue& queue, std::vector<std::uint32_t>& direction_numbers);
        sobol(const sobol& other);
        sobol& operator=(const sobol& other);
        ~sobol();
    };

.. cpp:class:: oneapi::mkl::rng::sobol

.. container:: section

    .. rubric:: Class Members

    .. list-table::
        :header-rows: 1

        * - Routine
          - Description
        * - `sobol(sycl::queue& queue, std::uint32_t dimensions)`_
          - Constructor with specified number of dimensions. The value should be :math:`1..40`.
        * - `sobol(sycl::queue& queue, std::vector<std::uint32_t>& direction_numbers)`_
          - Constructor for extended use-case, when it's needed to use the number of dimensions greater than 40 or obtain another sequence.
        * - `sobol(const sobol& other)`_
          - Copy constructor

.. container:: section

    .. rubric:: Constructors

    .. _`sobol(sycl::queue& queue, std::uint32_t dimensions)`:

    .. cpp:function:: sobol::sobol(sycl::queue& queue, std::uint32_t dimensions)

    .. container:: section

        .. rubric:: Input Parameters

        queue
            Valid sycl::queue object, calls of the :ref:`oneapi::mkl::rng::generate()<onemkl_rng_generate>` routine submits kernels in this queue to obtain random numbers from a given engine.

        dimensions
            Number of dimensions. If :math:`dimen < 1` or :math:`dimen > 40`, assume :math:`dimen = 1`.

    .. _`sobol(sycl::queue& queue, std::vector<std::uint32_t>& direction_numbers)`:

    .. cpp:function:: sobol::sobol(sycl::queue& queue, std::vector<std::uint32_t>& direction_numbers)

    .. container:: section

        .. rubric:: Input Parameters

        queue
            Valid ``sycl::queue object``, calls of the :ref:`oneapi::mkl::rng::generate()<onemkl_rng_generate>` routine submits kernels in this queue to obtain random numbers from a given engine.

        direction_numbers
            If you want to generate quasi-random vectors of greater dimension or obtain another sequence, you can register a set of your own direction_numbers. The number of dimensions corresponds to direction_numbers.size() / 32.

    .. _`sobol(const sobol& other)`:

    .. cpp:function:: sobol::sobol(const sobol& other)

    .. container:: section

        .. rubric:: Input Parameters

        other
            Valid ``sobol`` object, state of current generator is changed to copy of other engine state, note: queue, which is hold by engine is also changing on other's one.

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
