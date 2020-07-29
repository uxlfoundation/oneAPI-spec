.. _onemkl_rng_multinomial:

multinomial
===========

Class is used for generation of multinomially distributed integer types random numbers.

.. _onemkl_rng_multinomial_description:

.. rubric:: Description

The class object is used in :ref:`oneapi::mkl::rng::generate()<onemkl_rng_generate>` function to provide n random numbers multinomially distributed, with independent trials :math:`(ntrial, m)` and possible mutually exclusive outcomes :math:`k`, with corresponding probabilities :math:`p_i`, where :math:`p_i \in R; 0 \leq p_i \leq 1; m, k \in N`.

The probability distribution is given by:

.. math::

    P(X_1 = x_1, ..., X_k = x_k) = \frac{m!}{\Pi^k_{i = 1}x_i!}\Pi^k_{i = 1}p_i^{x_i}, 0 \leq x_i \leq m, \sum^{k}_{i = 1}x_i = m

.. _onemkl_rng_multinomial_syntax:

class multinomial
-----------------

.. rubric:: Syntax

.. code-block:: cpp

    template<typename IntType = std::int32_t, typename Method = multinomial_method::by_default>
    class multinomial {
    public:
        using method_type = Method;
        using result_type = IntType;
        explicit multinomial(double ntrial, std::vector<double> p);
        multinomial(const multinomial<IntType, Method> & other);
        std::int32_t ntrial() const;
        std::vector<double> p() const;
    };

.. cpp:class:: template<typename IntType = std::int32_t, typename Method = oneapi::mkl::rng::multinomial_method::by_default> \
                oneapi::mkl::rng::multinomial

.. container:: section

    .. rubric:: Template parameters

    .. container:: section

        typename IntType
            Type of the produced values. Supported types:
                * ``std::int32_t``
                * ``std::uint32_t``

    .. container:: section

        typename Method = oneapi::mkl::rng::multinomial_method::by_default
            Transformation method, which will be used for generation. Supported types:

                * ``oneapi::mkl::rng::multinomial_method::by_default``
                * ``oneapi::mkl::rng::multinomial_method::poisson_icdf_based``

            See description of the methods in :ref:`Distributions methods template parameter<onemkl_rng_distributions_template_parameter_mkl_rng_method_values>`

.. container:: section

    .. rubric:: Class Members

    .. list-table::
        :header-rows: 1

        * - Routine
          - Description
        * - `explicit multinomial(double ntrial, std::vector<double> p)`_
          - Constructor with parameters
        * - `multinomial(const multinomial<IntType, Method> & other)`_
          - Copy constructor
        * - `std::int32_t ntrial() const`_
          - Method to obtain number of independent trials
        * - `std::vector<double> p() const`_
          - Method to obtain probability vector of possible outcomes

.. container:: section

    .. rubric:: Member types

    .. container:: section

        .. cpp:type:: multinomial::method_type = Method

        .. container:: section

            .. rubric:: Description

            Type which defines transformation method for generation.

    .. container:: section

        .. cpp:type:: multinomial::result_type = IntType

        .. container:: section

            .. rubric:: Description

            Type which defines type of generated random numbers.

.. container:: section

    .. rubric:: Constructors

    .. container:: section

        .. _`explicit multinomial(double ntrial, std::vector<double> p)`:

        .. cpp:function:: explicit multinomial::multinomial(double ntrial, std::vector<double> p)

        .. container:: section

            .. rubric:: Description

            Constructor with parameters. `ntrial` is a number of independent trials, `p` is a probability vector.

    .. container:: section

        .. _`multinomial(const multinomial<IntType, Method> & other)`:

        .. cpp:function:: multinomial::multinomial(const multinomial<IntType, Method> & other)

        .. container:: section

            .. rubric:: Description

            Copy constructor.

.. container:: section

    .. rubric:: Characteristics

    .. container:: section

        .. _`std::int32_t ntrial() const`:

        .. cpp:function:: std::int32_t multinomial::ntrial() const

        .. container:: section

            .. rubric:: Return Value

            Returns the distribution parameter `ntrial`.

    .. container:: section

        .. _`std::vector<double> p() const`:

        .. cpp:function:: std::vector<double> multinomial::p() const

        .. container:: section

            .. rubric:: Return Value

            Returns the distribution parameter `p`.

**Parent topic:** :ref:`onemkl_rng_distributions`
