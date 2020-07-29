.. _onemkl_rng_uniform_discrete:

uniform (discrete)
==================

Class is used for generation of uniformly distributed integer types random numbers.

.. _onemkl_rng_uniform_discrete_description:

.. rubric:: Description

The class object is used in :ref:`oneapi::mkl::rng::generate()<onemkl_rng_generate>` function to provide random numbers uniformly distributed over the interval :math:`[a, b)`, where :math:`a`, :math:`b` are the left and right bounds of the
interval, respectively, and :math:`a, b \in R; a < b`

The probability distribution is given by:

.. math::

    P(X = k) = \frac{1}{b - a}, k \in \{a, a + 1, ... , b - 1\}

The cumulative distribution function is as follows:

.. math::

    F_{a, b}(x) = \left\{ \begin{array}{rcl} 0, x < a \\ \frac{\lfloor x - a + 1 \rfloor}{b-a}, a \leq x < b, x \in R \\ 1, x \ge b \end{array}\right.


.. _onemkl_rng_uniform_discrete_syntax:

class uniform
-------------

.. rubric:: Syntax

.. code-block:: cpp

    template<typename Method = uniform_method::by_default>
    class uniform<std::int32_t, Method> {
    public:
        using method_type = Method;
        using result_type = std::int32_t;
        uniform();
        explicit uniform(std::int32_t a, std::int32_t b);
        std::int32_t a() const;
        std::int32_t b() const;
    };

.. cpp:class:: template<typename Method = oneapi::mkl::rng::uniform_method::by_default> \
                oneapi::mkl::rng::uniform

.. container:: section

    .. rubric:: Template parameters

    .. container:: section

        typename Method = oneapi::mkl::rng::uniform_method::by_default
            Transformation method, which will be used for generation. Supported types:

                * ``oneapi::mkl::rng::uniform_method::by_default``
                * ``oneapi::mkl::rng::uniform_method::standard``

            See description of the methods in :ref:`Distributions methods template parameter<onemkl_rng_distributions_template_parameter_mkl_rng_method_values>`

.. container:: section

    .. rubric:: Class Members

    .. list-table::
        :header-rows: 1

        * - Routine
          - Description
        * - `uniform()`_
          - Default constructor
        * - `explicit uniform(std::int32_t a, std::int32_t b)`_
          - Constructor with parameters
        * - `std::int32_t a() const`_
          - Method to obtain left bound `a`
        * - `std::int32_t b() const`_
          - Method to obtain right bound `b`

.. container:: section

    .. rubric:: Member types

    .. container:: section

        .. cpp:type:: method_type = Method

        .. container:: section

            .. rubric:: Description

            Type which defines transformation method for generation

    .. container:: section

        .. cpp:type:: result_type = std::int32_t

        .. container:: section

            .. rubric:: Description

            Type which defines type of generated random numbers

.. container:: section

    .. rubric:: Constructors

    .. container:: section

        .. _`uniform()`:

        .. cpp:function:: uniform()

        .. container:: section

            .. rubric:: Description

            Default constructor for distribution, parameters set as `a` = 0, `b` = std::numeric_limits<std::int32_t>::max()

    .. container:: section

        .. _`explicit uniform(std::int32_t a, std::int32_t b)`:

        .. cpp:function:: uniform(std::int32_t a, std::int32_t b)

        .. container:: section

            .. rubric:: Description

            Constructor with parameters. `a` is a left bound, `b` is a right bound, assume :math:`a < b`.


.. container:: section

    .. rubric:: Characteristics

    .. container:: section

        .. _`std::int32_t a() const`:

        .. cpp:function:: a() const

        .. container:: section

            .. rubric:: Return Value

            Returns the distribution parameter `a` - left bound

    .. container:: section

        .. _`std::int32_t b() const`:

        .. cpp:function:: b() const

        .. container:: section

            .. rubric:: Return Value

            Returns the distribution parameter `b` - right bound

**Parent topic:** :ref:`onemkl_rng_distributions`
