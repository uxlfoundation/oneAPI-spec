.. SPDX-FileCopyrightText: 2023 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. _onemkl_device_rng_bits:

bits
====

Generates bits of underlying engine (BRNG) integer recurrence.

.. rubric:: Description

The ``bits`` class object is used in ``generate`` and ``generate_single`` functions to provide integer 
random values. Each integer can be treated as a vector of several bits. In a truly random generator, these 
bits are random, while in pseudorandom generators this randomness can be violated. 
See :ref:`VS Notes<onemkl_device_rng_bibliography>` for details.


class bits
----------

.. rubric:: Syntax

.. code-block:: cpp

   namespace oneapi::mkl::rng::device {
     template<typename UIntType = std::uint32_t>
     class bits {
       using result_type = UIntType;
     };
   }


.. container:: section

    .. rubric:: Template parameters

    .. container:: section

        typename UIntType
            Type of the produced values. Supported types:
                * ``std::uint32_t``

.. container:: section

    .. rubric:: Member types

    .. container:: section

        .. code-block:: cpp

            bits::result_type = UIntType

        .. container:: section

            .. rubric:: Description

            The type which defines type of generated random numbers.

**Parent topic:** :ref:`onemkl_device_rng_distributions`
