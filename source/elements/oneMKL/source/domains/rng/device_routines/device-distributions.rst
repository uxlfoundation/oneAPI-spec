.. SPDX-FileCopyrightText: 2023 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. _onemkl_device_rng_distributions:

Device Distributions
====================


oneMKL RNG routines are used to generate random numbers with different types of distribution. Each function group is 
introduced below by the type of underlying distribution and contains a short description of its functionality, as well 
as specifications of the call sequence and the explanation of input and output parameters. The Device Continuous 
Distribution Generators table and Device Discrete Distribution Generators table list the random number generator routines 
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
     -     s, d
     -     s, d
     -     Uniform continuous distribution on the interval [``a,b``)
   * -     :ref:`onemkl_device_rng_uniform_gaussian`
     -     s, d
     -     s, d
     -     Normal (Gaussian) distribution
   * -     :ref:`onemkl_device_rng_uniform_exponential`
     -     s, d
     -     s, d
     -     Exponential distribution
   * -     :ref:`onemkl_device_rng_uniform_lognormal`
     -     s, d
     -     s, d
     -     Lognormal distribution


**Device Discrete Distribution Generators**

.. list-table::
   :header-rows: 1

   * -     Type of Distribution
     -     Data Types
     -     BRNG Data Type
     -     Description
   * -     :ref:`onemkl_device_rng_uniform_discrete`
     -     i
     -     s
     -     Uniform discrete distribution on the interval [``a,b``)
   * -     :ref:`onemkl_device_rng_bits`
     -     i
     -     i
     -     Bits of underlying BRNG integer recurrence
   * -     :ref:`onemkl_device_rng_uniform_bits`
     -     i
     -     i
     -     Uniformly distributed bits in 32-bit chunks
   * -
     -     i
     -     i
     -     Uniformly distributed bits in 64-bit chunks
   * -     :ref:`onemkl_device_rng_poisson`
     -     i
     -     i
     -     Poisson distribution
   * -     :ref:`onemkl_device_rng_bernoulli`
     -     i
     -     i
     -     Bernoulli distribution

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

