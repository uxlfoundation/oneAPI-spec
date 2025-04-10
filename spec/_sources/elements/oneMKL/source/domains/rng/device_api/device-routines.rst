.. SPDX-FileCopyrightText: 2023 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. _onemkl_device_rng_routines:

Random Number Generators Device Routines
========================================

The main purpose of Device routines is to make them callable from your SYCL kernels; however, there are no limitations to be called from the Host. For example:

.. code-block::

   sycl::queue queue;

   queue.submit([&](sycl::handler& cgh) {
     cgh.parallel_for(range,[=](...) {
        oneapi::mkl::rng::device::routine(...); // calling routine from user's kernel code
     });
   });

   oneapi::mkl::rng::device::routine(...); // calling routine from host

.. rubric:: Structure

RNG domain contains two classes types:

   -  Engines (basic random number generators) classes, which holds
      the state of generator and is a source of independent and identically distributed random variables. 
      Refer to :ref:`onemkl_rng_engines_basic_random_number_generators`
      for a detailed description.
   -  Distribution classes templates (transformation classes) for different types of statistical
      distributions, for example, uniform, normal (Gaussian), binomial,
      etc. These classes contain all of the distribution’s parameters
      (including generation method). Refer to :ref:`onemkl_device_rng_distributions` for
      a detailed description of the distributions.

The RNG domain also contains two types of free functions:

   -  Generation routines. The current routines are used to obtain random
      numbers from a given engine with proper statistics defined by a
      given distribution. Refer to the :ref:`onemkl_device_rng_generate_routines`
      section for a detailed description.
   -  Service routines. The routines are used to modify the engine state. Refer to :ref:`onemkl_device_rng_service_routines` for a
      description of these routines.


Engine classes work with both generation and service routines. Distribution classes are used in
generation routines only. Refer to the :ref:`onemkl_device_rng_usage_model`
section for the description of typical RNG scenario.

.. toctree::
   :hidden:

   device-rng-usage-model.rst
   device-rng-generate-routines.rst
   device-engines.rst
   device-distributions.rst
   device-service-routines.rst
   ../bibliography.rst

**Parent topic:** :ref:`onemkl_rng`
