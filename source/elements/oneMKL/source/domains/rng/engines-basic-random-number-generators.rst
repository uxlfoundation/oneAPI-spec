.. _engines-basic-random-number-generators:

Engines (Basic Random Number Generators)
========================================


.. container::


   oneMKL RNG provides pseudorandom, quasi-random, and non-deterministic
   random number generators for Data Parallel C++:


   .. container:: tablenoborder


      .. list-table:: 
         :header-rows: 1

         * -  Routine 
           -  Description 
         * -           \ `onemkl::rng::mrg32k3a <mkl-rng-mrg32k3a.html>`__\    
           -     The combined multiple recursive pseudorandom number       generator      ``MRG32k3a``\ `[L'Ecuyer99a] <bibliography.html>`__\    
         * -           \ `onemkl::rng::philox4x32x10 <mkl-rng-philox4x32x10.html>`__\    
           -     Philox4x32-10 counter-based pseudorandom number       generator with a period of      2\ :sup:`128`\ ``PHILOX4X32X10``\ `[Salmon11] <bibliography.html>`__\    
         * -           \ `onemkl::rng::mcg31m1 <mkl-rng-mcg31m1.html>`__\    
           -     The 31-bit multiplicative congruential pseudorandom       number generator MCG(1132489760, 231 -1)      `[L'Ecuyer99] <bibliography.html>`__\    
         * -           \ `onemkl::rng::r250 <mkl-rng-r250.html>`__\    
           -     The 32-bit generalized feedback shift register       pseudorandom number generator      ``GFSR(250,103)``\ `[Kirkpatrick81] <bibliography.html>`__\    
         * -           \ `onemkl::rng::mcg59 <mkl-rng-mcg59.html>`__\    
           -     The 59-bit multiplicative congruential pseudorandom       number generator ``MCG(13``\ :sup:`13`\ ``, 2``\ :sup:`59`) from      NAG Numerical Libraries      `[NAG] <bibliography.html>`__\    
         * -           \ `onemkl::rng::wichmann_hill <mkl-rng-wichmann_hill.html>`__\    
           -     Wichmann-Hill pseudorandom number generator (a set of       273 basic generators) from NAG Numerical Libraries      `[NAG] <bibliography.html>`__\    
         * -           \ `onemkl::rng::mt19937 <mkl-rng-mt19937.html>`__\    
           -     Mersenne Twister pseudorandom number generator       ``MT19937``\ `[Matsumoto98] <bibliography.html>`__      with period length 2\ :sup:`19937`-1 of the produced sequence         
         * -           \ `onemkl::rng::mt2203 <mkl-rng-mt2203.html>`__\    
           -     Set of 6024 Mersenne Twister pseudorandom number       generators      ``MT2203``\ `[Matsumoto98] <bibliography.html>`__,      `[Matsumoto00] <bibliography.html>`__.      Each of them generates a sequence of period length equal to      2\ :sup:`2203`-1. Parameters of the generators provide mutual      independence of the corresponding sequences.    
         * -           \ `onemkl::rng::sfmt19937 <mkl-rng-sfmt19937.html>`__\    
           -     SIMD-oriented Fast Mersenne Twister pseudorandom       number generator      ``SFMT19937``\ `[Saito08] <bibliography.html>`__      with a period length equal to 2\ :sup:`19937`-1 of the produced      sequence.    
         * -           \ `onemkl::rng::sobol <mkl-rng-sobol.html>`__\    
           -     Sobol quasi-random number generator       `[Sobol76] <bibliography.html>`__,      `[Bratley88] <bibliography.html>`__,      which works in arbitrary dimension.    
         * -           \ `onemkl::rng::niederreiter <mkl-rng-niederreiter.html>`__\    
           -     Niederreiter quasi-random number generator       `[Bratley92] <bibliography.html>`__,      which works in arbitrary dimension.    
         * -           \ `onemkl::rng::ars5 <mkl-rng-ars5.html>`__\    
           -     ARS-5 counter-based pseudorandom number generator with       a period of 2\ :sup:`128`, which uses instructions from the AES-NI      set      ``ARS5``\ `[Salmon11] <bibliography.html>`__.         
         * -           \ `onemkl::rng::nondeterministic <mkl-rng-nondeterministic.html>`__\    
           -     Non-deterministic random number generator       (RDRAND-based)      `[AVX] <bibliography.html>`__\ `[IntelSWMan] <bibliography.html>`__\    




   For some basic generators, oneMKL RNG provides two methods of
   creating independent states in multiprocessor computations, which are
   the leapfrog method and the block-splitting method. These sequence
   splitting methods are also useful in sequential Monte Carlo. The
   description of these functions can be found in the `Service
   Routines <service-routines.html>`__ section.


   In addition, MT2203 pseudorandom number generator is a set of 6024
   generators designed to create up to 6024 independent random
   sequences, which might be used in parallel Monte Carlo simulations.
   Another generator that has the same feature is Wichmann-Hill. It
   allows creating up to 273 independent random streams. The properties
   of the generators designed for parallel computations are discussed in
   detail in
   [`Coddington94 <bibliography.html>`__].


   See `VS Notes <bibliography.html>`__ for
   the detailed description.



   **Parent topic:** :ref:`onemkl_rng`


.. container::


   -  `onemkl::rng::mrg32k3a <mkl-rng-mrg32k3a.html>`__
      The combined multiple recursive pseudorandom number generator
      MRG32k3a [ L'Ecuyer99a]
   -  `onemkl::rng::philox4x32x10 <mkl-rng-philox4x32x10.html>`__
      A Philox4x32-10 counter-based pseudorandom number generator.
      [Salmon11].
   -  `onemkl::rng::mcg31m1 <mkl-rng-mcg31m1.html>`__
      The 31-bit multiplicative congruential pseudorandom number
      generator MCG(1132489760, 231 -1) [L'Ecuyer99]
   -  `onemkl::rng::mcg59 <mkl-rng-mcg59.html>`__
      The 59-bit multiplicative congruential pseudorandom number
      generator MCG(1313, 259) from NAG Numerical Libraries [NAG].
   -  `onemkl::rng::r250 <mkl-rng-r250.html>`__
      The 32-bit generalized feedback shift register pseudorandom number
      generator GFSR(250,103)[Kirkpatrick81].
   -  `onemkl::rng::wichmann_hill <mkl-rng-wichmann_hill.html>`__
      Wichmann-Hill pseudorandom number generator (a set of 273 basic
      generators) from NAG Numerical Libraries [NAG].
   -  `onemkl::rng::mt19937 <mkl-rng-mt19937.html>`__
      Mersenne Twister pseudorandom number generator MT19937
      [Matsumoto98] with period length 2\ :sup:`19937`-1 of the produced
      sequence.
   -  `onemkl::rng::sfmt19937 <mkl-rng-sfmt19937.html>`__
      SIMD-oriented Fast Mersenne Twister pseudorandom number generator
      SFMT19937 [Saito08] with a period length equal to
      2\ :sup:`19937`-1 of the produced sequence.
   -  `onemkl::rng::mt2203 <mkl-rng-mt2203.html>`__
      Set of 6024 Mersenne Twister pseudorandom number generators MT2203
      [Matsumoto98], [Matsumoto00]. Each of them generates a sequence of
      period length equal to 2\ :sup:`2203`-1. Parameters of the
      generators provide mutual independence of the corresponding
      sequences..
   -  `onemkl::rng::ars5 <mkl-rng-ars5.html>`__
      ARS-5 counter-based pseudorandom number generator with a period of
      2\ :sup:`128`, which uses instructions from the AES-NI set
      ARS5[Salmon11].
   -  `onemkl::rng::sobol <mkl-rng-sobol.html>`__
      Sobol quasi-random number generator [Sobol76], [Bratley88], which
      works in arbitrary dimension.
   -  `onemkl::rng::niederreiter <mkl-rng-niederreiter.html>`__
      Niederreiter quasi-random number generator [Bratley92], which
      works in arbitrary dimension.
   -  `onemkl::rng::nondeterministic <mkl-rng-nondeterministic.html>`__
      Non-deterministic random number generator (RDRAND-based)
      [AVX][IntelSWMan].

.. toctree::
    :hidden:

    mkl-rng-mrg32k3a
    mkl-rng-philox4x32x10
    mkl-rng-mcg31m1
    mkl-rng-mcg59
    mkl-rng-r250
    mkl-rng-wichmann_hill
    mkl-rng-mt19937
    mkl-rng-sfmt19937
    mkl-rng-mt2203
    mkl-rng-ars5
    mkl-rng-sobol
    mkl-rng-niederreiter
    mkl-rng-nondeterministic
