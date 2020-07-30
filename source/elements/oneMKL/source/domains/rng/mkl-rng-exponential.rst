.. _onemkl_rng_exponential:

exponential
===========

Class is used for generation of exponentially distributed real types random numbers.

.. _onemkl_rng_exponential_description:

.. rubric:: Description

The class object is used in :ref:`oneapi::mkl::rng::generate()<onemkl_rng_generate>` function to provide random numbers exponentially distributed with displacement :math:`a` and scalefactor :math:`\beta`, where :math:`a, \beta \in R; \beta > 0`.

The probability distribution is given by:

.. math::

    f_{a, \beta}(x) = \left\{ \begin{array}{rcl} \frac{1}{\beta}exp(-\frac{x - a}{\beta}), x \ge a \\ 0, x < a \end{array}\right.

The cumulative distribution function is as follows:

.. math::

    F_{a, \beta}(x) = \left\{ \begin{array}{rcl} 1 - exp(-\frac{x - a}{\beta}), x \ge a \\ 0, x < a \end{array}\right.

.. _onemkl_rng_exponential_syntax:

class exponential
-----------------

.. rubric:: Syntax

.. code-block:: cpp

    template<typename RealType = float, typename Method = exponential_method::by_default>
    class exponential {
    public:
        using method_type = Method;
        using result_type = RealType;
        exponential();
        explicit exponential(RealType a, RealType beta);
        RealType a() const;
        RealType beta() const;
    };

.. cpp:class:: template<typename RealType = float, typename Method = oneapi::mkl::rng::exponential_method::by_default> \
                oneapi::mkl::rng::exponential

.. container:: section

    .. rubric:: Template parameters

    .. container:: section

        typename RealType
            Type of the produced values. Supported types:
                * ``float``
                * ``double``

    .. container:: section

        typename Method = oneapi::mkl::rng::exponential_method::by_default
            Transformation method, which will be used for generation. Supported types:

                * ``oneapi::mkl::rng::exponential_method::by_default``
                * ``oneapi::mkl::rng::exponential_method::icdf``
                * ``oneapi::mkl::rng::exponential_method::icdf_accurate``

            See description of the methods in :ref:`Distributions methods template parameter<onemkl_rng_distributions_template_parameter_mkl_rng_method_values>`

.. container:: section

    .. rubric:: Class Members

    .. list-table::
        :header-rows: 1

        * - Routine
          - Description
        * - `exponential()`_
          - Default constructor
        * - `explicit exponential(RealType a, RealType beta)`_
          - Constructor with parameters
        * - `RealType a() const`_
          - Method to obtain displacement value
        * - `RealType beta() const`_
          - Method to obtain scalefactor

.. container:: section

    .. rubric:: Member types

    .. container:: section

        .. cpp:type:: exponential::method_type = Method

        .. container:: section

            .. rubric:: Description

            Type which defines transformation method for generation.

    .. container:: section

        .. cpp:type:: exponential::result_type = RealType

        .. container:: section

            .. rubric:: Description

            Type which defines type of generated random numbers.

.. container:: section

    .. rubric:: Constructors

    .. container:: section

        .. _`exponential()`:

        .. cpp:function:: exponential::exponential()

        .. container:: section

            .. rubric:: Description

            Default constructor for distribution, parameters set as `a` = 0.0, `beta` = 1.0.

    .. container:: section

        .. _`explicit exponential(RealType a, RealType beta)`:

        .. cpp:function:: explicit exponential::exponential(RealType a, RealType beta)

        .. container:: section

            .. rubric:: Description

            Constructor with parameters. `a` is a displacement, `beta` is a scalefactor.


.. container:: section

    .. rubric:: Characteristics

    .. container:: section

        .. _`RealType a() const`:

        .. cpp:function:: RealType exponential::a() const

        .. container:: section

            .. rubric:: Return Value

            Returns the distribution parameter `a` - displacement.

    .. container:: section

        .. _`RealType beta() const`:

        .. cpp:function:: RealType exponential::beta() const

        .. container:: section

            .. rubric:: Return Value

            Returns the distribution parameter `beta` - scalefactor value.

**Parent topic:** :ref:`onemkl_rng_distributions`
