.. _onemkl_rng_uniform_bits:

uniform_bits
============

Class is used for generation of uniformly distibuted bits in 32/64-bit chunks.

.. _onemkl_rng_uniform_bits_description:

.. rubric:: Description

The class object is used in :ref:`oneapi::mkl::rng::generate()<onemkl_rng_generate>` function to provide uniformly distibuted bits in 32/64-bit chunks. It is designed to ensure each bit in the 32/64-bit chunk is uniformly distributed. Can be not supported by the specific engine.

class uniform_bits
------------------

.. rubric:: Syntax

.. code-block:: cpp

    template<typename UIntType = std::uint32_t>
    class uniform_bits {
    public:
        using result_type = UIntType;
    };

.. cpp:class:: template<typename UIntType = std::uint32_t> \
                oneapi::mkl::rng::uniform_bits

.. container:: section

    .. rubric:: Template parameters

    .. container:: section

        typename UIntType
            Type of the produced values. Supported types:
                * ``std::uint32_t``
                * ``std::uint64_t``

.. container:: section

    .. rubric:: Member types

    .. container:: section

        .. cpp:type:: uniform_bits::result_type = UIntType

        .. container:: section

            .. rubric:: Description

            Type which defines type of generated random numbers.

**Parent topic:** :ref:`onemkl_rng_distributions`
