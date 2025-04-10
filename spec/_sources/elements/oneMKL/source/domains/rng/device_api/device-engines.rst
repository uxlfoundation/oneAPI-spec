.. SPDX-FileCopyrightText: 2023 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. _onemkl_device_rng_engines:

Device Engines (Basic Random Number Generators)
===============================================

oneMKL RNG provides following device pseudorandom number generators:

.. tabularcolumns:: |\Y{0.4}|\Y{0.6}|

.. list-table::
   :header-rows: 1
   :class: longtable

   * -  Routine
     -  Description

   * -  :ref:`onemkl_device_rng_mrg32k3a`
     -  The combined multiple recursive pseudorandom number generator ``MRG32k3a`` [:ref:`L'Ecuyer99 <onemkl_rng_bibliography>`]

   * -  :ref:`onemkl_device_rng_philox4x32x10`
     -  Philox4x32-10 counter-based pseudorandom number generator with a period of :math:`2^{128}` ``PHILOX4X32X10`` [:ref:`Salmon11 <onemkl_rng_bibliography>`]

   * -  :ref:`onemkl_device_rng_mcg31m1`
     -  The 31-bit multiplicative congruential pseudorandom number generator MCG(:math:`1132489760, 2^{32}-1`) :ref:`[L'Ecuyer99a] <onemkl_rng_bibliography>`.

   * -  :ref:`onemkl_device_rng_mcg59`
     -  The 59-bit multiplicative congruential pseudorandom number generator MCG(:math:`13^{13}, 2^{59}`) from NAG Numerical Libraries :ref:`[NAG] <onemkl_rng_bibliography>`.

**Parent topic:** :ref:`onemkl_device_rng_routines`

.. toctree::
   :maxdepth: 1
   :hidden:

   device-rng-mrg32k3a.rst
   device-rng-philox4x32x10.rst
   device-rng-mcg31m1.rst
   device-rng-mcg59.rst