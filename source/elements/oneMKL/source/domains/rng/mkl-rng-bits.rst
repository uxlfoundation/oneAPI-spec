.. _onemkl_rng_bits:

bits
====

Class is used for generation of underlying engine integer recurrence.

.. _onemkl_rng_bits_description:

.. rubric:: Description

The class object is used in :ref:`oneapi::mkl::rng::generate()<onemkl_rng_generate>` function to provide integer random numbers. Each integer can be treated as a vector of several bits. In a truly random generator, these bits are random, while in pseudorandom generators this randomness can be violated.

class bits
----------

.. rubric:: Syntax

.. code-block:: cpp

    template<typename UIntType = std::uint32_t>
    class bits {
    public:
        using result_type = UIntType;
    };

.. cpp:class:: template<typename UIntType = std::uint32_t> \
                oneapi::mkl::rng::bits

.. container:: section

    .. rubric:: Template parameters

    .. container:: section

        typename UIntType
            Type of the produced values. Supported types:
                * ``std::uint32_t``

.. container:: section

    .. rubric:: Member types

    .. container:: section

        .. cpp:type:: bits::result_type = UIntType

        .. container:: section

            .. rubric:: Description

            Type which defines type of generated random numbers.

**Parent topic:** :ref:`onemkl_rng_distributions`
