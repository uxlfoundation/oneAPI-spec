.. SPDX-FileCopyrightText: 2024 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. _onemkl_device_rng_beta:

beta
====


Generates beta distributed random numbers.

.. rubric:: Description

The ``beta`` class object is used in the ``generate`` function to provide
random numbers with beta distribution that has shape parameters :math:`p` and :math:`q`,
displacement :math:`\alpha` and scale parameter :math:`(b, \beta)`, where :math:`p`, :math:`q`.
:math:`\alpha`, :math:`\beta` :math:`\in R; p > 0; q > 0; \beta > 0`.

The probability distribution is given by:

.. math::

    f_{p, q, \alpha, \beta}(x) = \left\{ \begin{array}{rcl} \frac{1}{B(p, q) * \beta^{p + q - 1}}(x - a)^{p - 1}*(\beta + \alpha - x)^{q - 1}, \alpha \leq x < \alpha + \beta \\ 0, x < \alpha, x \ge \alpha + \beta \end{array}\right.

The cumulative distribution function is as follows:

.. math::

    F_{a, b}(x) = \left\{ \begin{array}{rcl} 0, x < \alpha \\ \int^x_{\alpha}\frac{1}{B(p, q) * \beta^{p + q - 1}}(y - \alpha)^{p - 1}*(\beta + \alpha - y)^{q - 1}dy, \alpha \leq x < \alpha + \beta, x \in R \\ 1, x \ge \alpha + \beta \end{array}\right.


Where :math:`B(p, 1)` is the complete beta function.

class beta
----------

.. rubric:: Syntax

.. code-block:: cpp

   namespace oneapi::mkl::rng::device {
     template<typename RealType, typename Method>
     class beta {
     public:
       using method_type = Method;
       using result_type = RealType;

       beta();
       explicit beta(RealType p, RealType q, RealType a, RealType b);

       RealType p() const;
       RealType q() const;
       RealType a() const;
       RealType b() const;
       std::size_t count_rejected_numbers() const;
     };
   }


.. container:: section

    .. rubric:: Template parameters

    .. container:: section

        typename RealType
            Type of the produced values. Supported types:

                * ``float``
                * ``double``

    .. container:: section

        typename Method
            Generation method. The type is unspecified.


.. container:: section

    .. rubric:: Class Members

    .. list-table::
        :header-rows: 1

        * - Routine
          - Description
        * - `beta()`_
          - Default constructor
        * - `explicit beta(RealType p, RealType q, RealType a, RealType b)`_
          - Constructor with parameters
        * - `RealType p() const`_
          - Method to obtain shape ``p``
        * - `RealType q() const`_
          - Method to obtain shape ``q``
        * - `RealType a() const`_
          - Method to obtain displacement :math:`\alpha`
        * - `RealType b() const`_
          - Method to obtain scale parameter :math:`\beta`
        * - `size_t count_rejected_numbers() const`_
          - Method to obtain amount of random numbers that were rejected during
            the last ``generate`` function call. If no ``generate`` calls, ``0`` is returned.

.. container:: section

    .. rubric:: Member types

    .. container:: section

        .. code-block:: cpp

            beta::method_type = Method

        .. container:: section

            .. rubric:: Description

            The type which defines transformation method for generation.

    .. container:: section

        .. code-block:: cpp

            beta::result_type = RealType

        .. container:: section

            .. rubric:: Description

            The type which defines type of generated random numbers.

.. container:: section

    .. rubric:: Constructors

    .. container:: section

        .. _`beta()`:

        .. code-block:: cpp

            beta::beta()

        .. container:: section

            .. rubric:: Description

            Default constructor for distribution, parameters set as
            ``p`` = 1.0, ``q`` = 1.0, :math:`\alpha` = 0.0, :math:`\beta` = 1.0.

    .. container:: section

        .. _`explicit beta(RealType p, RealType q, RealType a, RealType b)`:

        .. code-block:: cpp

            explicit beta::beta(RealType p, RealType q, RealType a, RealType b)

        .. container:: section

            .. rubric:: Description

            Constructor with parameters. ``p`` and ``q`` are shapes, :math:`\alpha` is a displacement, :math:`\beta` is a scale parameter.

        .. container:: section

            .. rubric:: Throws

            oneapi::mkl::invalid_argument
                Exception is thrown when :math:`p \leq 0`, or :math:`q \leq 0`, or :math:`\beta \leq 0`

.. container:: section

    .. rubric:: Characteristics

    .. container:: section

        .. _`RealType p() const`:

        .. code-block:: cpp

            RealType beta::p() const

        .. container:: section

            .. rubric:: Return Value

            Returns the distribution parameter ``p`` - shape.

    .. container:: section

        .. _`RealType q() const`:

        .. code-block:: cpp

            RealType beta::q() const

        .. container:: section

            .. rubric:: Return Value

            Returns the distribution parameter ``q`` - shape.

    .. container:: section

        .. _`RealType a() const`:

        .. code-block:: cpp

            RealType beta::a() const

        .. container:: section

            .. rubric:: Return Value

            Returns the distribution parameter :math:`\alpha` - displacement.

    .. container:: section

        .. _`RealType b() const`:

        .. code-block:: cpp

            RealType beta::b() const

        .. container:: section

            .. rubric:: Return Value

            Returns the distribution parameter :math:`\beta` - scale parameter value.

    .. container:: section

        .. _`size_t count_rejected_numbers() const`:

        .. code-block:: cpp

            std::size_t beta::count_rejected_numbers() const

        .. container:: section

            .. rubric:: Return Value

            Returns the amount of random numbers that were rejected during
            the last ``generate`` function call. If no ``generate`` calls, ``0`` is returned.

**Parent topic:** :ref:`onemkl_device_rng_distributions`
