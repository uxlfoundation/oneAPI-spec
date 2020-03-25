.. _onemkl_rng:

Random Number Generators
-------------------------


.. container::


   Statistics Random Number Generators provide a set of routines implementing commonly
   used pseudorandom, quasi-random, and non-deterministic generators
   with continuous and discrete distributions.


   .. container:: section
      :name: GUID-8F8296EC-7E54-4796-A425-35C4347EA1D0


      .. rubric:: Definitions
         :name: definitions
         :class: sectiontitle


      Pseudo-random number generator is defined by a structure(``S``,
      ``μ``, ``f``, ``U``, ``g``), where:


      -  ``S`` is a finite set of states (the state space)
      -  ``μ`` is a probability distribution on S for the initial state
         (or seed) ``s``\ :sub:`0`
      -  ``f:S→S`` is the transition function
      -  ``U`` – a finite set of output symbols
      -  ``g∶S→U`` an output function


   The generation of random numbers is as follows:


   #. Generate the initial state (called the seed) ``s``\ :sub:`0`
      according to ``μ`` and compute
      ``u``\ :sub:`0`\ =g(``s``\ :sub:`0`).
   #. Iterate for ``i``\ =1,…,\ ``s``\ :sub:`i` =
      f(``s``\ :sub:`(``i``-1)`) and ``u``\ :sub:`i` =
      g(``s``\ :sub:`i`). Output values ``u``\ :sub:`i` are the
      so-called random numbers produced by the PRNG.


   In computational statistics, random variate generation is usually
   made in two steps:


   #. Generating imitations of independent and identically distributed
      (i.i.d.) random variables having the uniform distribution over the
      interval (0, 1)
   #. Applying transformations to these i.i.d. U(0, 1) random variates
      in order to generate (or imitate) random variates and random
      vectors from arbitrary distributions.


   All RNG routines can be classified into several categories:


   -  Engines (Basic random number generators) classes, which holds
      state of generator and is a source of i.i.d. random. Refer to
      `Engines (Basic Random Number
      Generators) <rng/engines-basic-random-number-generators.html>`__
      for a detailed description.
   -  Transformation classes for different types of statistical
      distributions, for example, uniform, normal (Gaussian), binomial,
      etc. These classes contain all of the distribution’s parameters
      (including generation method). Refer to `Distribution
      Generators <rng/distributions.html>`__ for
      a detailed description of the distributions.
   -  Generate function. The current routine is used to obtain random
      numbers from a given engine with proper statistics defined by a
      given distribution. Refer to the `Generate
      Routine <rng/generate-routine.html>`__
      section for a detailed description.
   -  Service routines to modify the engine state: skip ahead and
      leapfrog functions. Refer to `Service
      Routines <rng/service-routines.html>`__ for a
      description of these routines.

.. container::


   -  `oneMKL RNG Usage
      Model <rng/onemkl-rng-usage-model.html>`__

.. toctree::
    :hidden:
    
    rng/onemkl-rng-usage-model
    rng/generate-routine
    rng/engines-basic-random-number-generators
    rng/service-routines
    rng/distributions
    rng/bibliography
