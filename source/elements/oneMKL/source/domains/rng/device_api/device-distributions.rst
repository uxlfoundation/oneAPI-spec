.. SPDX-FileCopyrightText: 2023 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. _onemkl_device_rng_distributions:

Device Distributions
====================

oneMKL RNG routines are used to generate random numbers with different types of distributions. Each function group is
introduced below by the type of underlying distribution and contains a short description of its functionality, as well
as specifications of the call sequence and the explanation of input and output parameters. The Device Continuous
Distribution Generators table and Device Discrete Distribution Generators table mention random number generator routines
with data types and output distributions, and sets correspondence between data types of the generator routines and the
basic random number generators.

**Device Continuous Distribution Generators**

.. list-table::
   :header-rows: 1

   * -     Type of Distribution
     -     Data Types
     -     BRNG Data Type
     -     Description
   * -     :ref:`onemkl_device_rng_uniform_continuous`
     -     float, double
     -     float, double
     -     Uniform continuous distribution on the interval [``a,b``)
   * -     :ref:`onemkl_device_rng_gaussian`
     -     float, double
     -     float, double
     -     Normal (Gaussian) distribution
   * -     :ref:`onemkl_device_rng_exponential`
     -     float, double
     -     float, double
     -     Exponential distribution
   * -     :ref:`onemkl_device_rng_lognormal`
     -     float, double
     -     float, double
     -     Lognormal distribution
   * -     :ref:`onemkl_device_rng_beta`
     -     float, double
     -     float, double
     -     Beta distribution
   * -     :ref:`onemkl_device_rng_gamma`
     -     float, double
     -     float, double
     -     Gamma distribution


**Device Discrete Distribution Generators**

.. list-table::
   :header-rows: 1

   * -     Type of Distribution
     -     Data Types
     -     BRNG Data Type
     -     Description
   * -     :ref:`onemkl_device_rng_uniform_discrete`
     -     integer
     -     float
     -     Uniform discrete distribution on the interval [``a,b``)
   * -     :ref:`onemkl_device_rng_bits`
     -     integer
     -     integer
     -     Bits of underlying BRNG integer sequence
   * -     :ref:`onemkl_device_rng_uniform_bits`
     -     integer
     -     integer
     -     Uniformly distributed bits in 32/64-bit chunks
   * -     :ref:`onemkl_device_rng_poisson`
     -     integer
     -     integer
     -     Poisson distribution
   * -     :ref:`onemkl_device_rng_bernoulli`
     -     integer
     -     integer
     -     Bernoulli distribution

`NOTE:` In case of ``integer`` check desired distribution for supported data types.

**Parent topic:** :ref:`onemkl_device_rng_routines`

.. toctree::
   :maxdepth: 1
   :hidden:

   device-distributions-template-parameter-method.rst
   device-rng-uniform-continuous.rst
   device-rng-gaussian.rst
   device-rng-lognormal.rst
   device-rng-exponential.rst
   device-rng-uniform-discrete.rst
   device-rng-bits.rst
   device-rng-uniform-bits.rst
   device-rng-poisson.rst
   device-rng-bernoulli.rst
   device-rng-beta.rst
   device-rng-gamma.rst

