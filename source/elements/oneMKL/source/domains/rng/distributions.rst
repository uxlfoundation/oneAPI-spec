.. _distributions:

Distributions
=============


.. container::


   oneAPI Math Kernel LibraryRNG routines are used to generate random
   numbers with different types of distribution. Each function group is
   introduced below by the type of underlying distribution and contains
   a short description of its functionality, as well as specifications
   of the call sequence and the explanation of input and output
   parameters. `Table "Continuous Distribution Generators" <#TBL10-8>`__
   and `Table "Discrete Distribution Generators" <#TBL10-9>`__ list the
   random number generator routines with data types and output
   distributions, and sets correspondence between data types of the
   generator routines and the basic random number generators.


   .. container:: tablenoborder


      .. list-table:: 
         :header-rows: 1

         * -     Type of Distribution     
           -     Data Types     
           -     BRNG Data Type     
           -     Description     
         * -           \ `onemkl::rng::uniform <mkl-rng-uniform-continuous.html>`__\    
           -     s, d    
           -     s, d    
           -     Uniform continuous distribution on the interval       [``a,b``)    
         * -           \ `onemkl::rng::gaussian <mkl-rng-gaussian.html>`__\    
           -     s, d    
           -     s, d    
           -     Normal (Gaussian) distribution     
         * -           \ `onemkl::rng::exponential <mkl-rng-exponential.html>`__\    
           -     s, d    
           -     s, d    
           -     Exponential distribution     
         * -           \ `onemkl::rng::laplace <mkl-rng-laplace.html>`__\    
           -     s, d    
           -     s, d    
           -     Laplace distribution (double exponential distribution)          
         * -           \ `onemkl::rng::weibull <mkl-rng-weibull.html>`__\    
           -     s, d    
           -     s, d    
           -     Weibull distribution     
         * -           \ `onemkl::rng::cauchy <mkl-rng-cauchy.html>`__\    
           -     s, d    
           -     s, d    
           -     Cauchy distribution     
         * -           \ `onemkl::rng::rayleigh <mkl-rng-rayleigh.html>`__\    
           -     s, d    
           -     s, d    
           -     Rayleigh distribution     
         * -           \ `onemkl::rng::lognormal <mkl-rng-lognormal.html>`__\    
           -     s, d    
           -     s, d    
           -     Lognormal distribution     
         * -           \ `onemkl::rng::gumbel <mkl-rng-gumbel.html>`__\    
           -     s, d    
           -     s, d    
           -     Gumbel (extreme value) distribution     
         * -           \ `onemkl::rng::gamma <mkl-rng-gamma.html>`__\    
           -     s, d    
           -     s, d    
           -     Gamma distribution     
         * -           \ `onemkl::rng::beta <mkl-rng-gamma.html>`__\    
           -     s, d    
           -     s, d    
           -     Beta distribution     
         * -           \ `onemkl::rng::chi_square <mkl-rng-chi_square.html>`__\    
           -     s, d    
           -     s, d    
           -     Chi-Square distribution     




    



   .. container:: tablenoborder


      .. list-table:: 
         :header-rows: 1

         * -     Type of Distribution     
           -     Data Types     
           -     BRNG Data Type     
           -     Description     
         * -           \ `onemkl::rng::uniform <mkl-rng-uniform-discrete.html>`__\    
           -     i    
           -     d    
           -     Uniform discrete distribution on the interval       [``a,b``)    
         * -           \ `onemkl::rng::uniform_bits <mkl-rng-uniform_bits.html>`__\    
           -     i    
           -     i    
           -     Uniformly distributed bits in 32-bit chunks     
         * -  
           -     i    
           -     i    
           -     Uniformly distributed bits in 64-bit chunks     
         * -           \ `onemkl::rng::bits <mkl-rng-bits.html>`__\    
           -     i    
           -     i    
           -     Bits of underlying BRNG integer recurrence     
         * -           \ `onemkl::rng::bernoulli <mkl-rng-bernoulli.html>`__\    
           -     i    
           -     s    
           -     Bernoulli distribution     
         * -           \ `onemkl::rng::geometric <mkl-rng-geometric.html>`__\    
           -     i    
           -     s    
           -     Geometric distribution     
         * -           \ `onemkl::rng::binomial <mkl-rng-binomial.html>`__\    
           -     i    
           -     d    
           -     Binomial distribution     
         * -           \ `onemkl::rng::hypergeometric <mkl-rng-hypergeometric.html>`__\    
           -     i    
           -     d    
           -     Hypergeometric distribution     
         * -           \ `onemkl::rng::poisson <mkl-rng-poisson.html>`__\    
           -     i    
           -     s (for ) onemkl::rng::gaussian_inverse      s       (for distribution parameter λ≥ 27) and d (for λ < 27) (for      onemkl::rng::ptpe)    
           -     Poisson distribution     
         * -           \ `onemkl::rng::poisson_v <mkl-rng-poisson_v.html>`__\    
           -     i    
           -     s    
           -     Poisson distribution with varying mean     
         * -           \ `onemkl::rng::negbinomial <mkl-rng-negbinomial.html>`__\    
           -     i    
           -     d    
           -     Negative binomial distribution, or Pascal distribution          
         * -           \ `onemkl::rng::multinomial <mkl-rng-multinomial.html>`__\    
           -     i    
           -     d    
           -     Multinomial distribution     




   .. container:: section
      :name: GUID-290E2BFD-AAD2-4AD4-9691-27F18A6CA131


      .. rubric:: Modes of random number generation
         :name: modes-of-random-number-generation
         :class: sectiontitle


      The library provides two modes of random number generation,
      accurate and fast. Accurate generation mode is intended for the
      applications that are highly demanding to accuracy of
      calculations. When used in this mode, the generators produce
      random numbers lying completely within definitional domain for all
      values of the distribution parameters. For example, random numbers
      obtained from the generator of continuous distribution that is
      uniform on interval [``a``,\ ``b``] belong to this interval
      irrespective of what ``a`` and ``b`` values may be. Fast mode
      provides high performance of generation and also guarantees that
      generated random numbers belong to the definitional domain except
      for some specific values of distribution parameters. The
      generation mode is set by specifying relevant value of the method
      parameter in generator routines. List of distributions that
      support accurate mode of generation is given in the table below.


    
   **Parent topic:** :ref:`onemkl_rng`



.. toctree::
    :hidden:

    distributions-template-parameter-mkl-rng-method-values
    mkl-rng-uniform-continuous
    mkl-rng-gaussian
    mkl-rng-exponential
    mkl-rng-laplace
    mkl-rng-weibull
    mkl-rng-cauchy
    mkl-rng-rayleigh
    mkl-rng-lognormal
    mkl-rng-gumbel
    mkl-rng-gamma
    mkl-rng-beta
    mkl-rng-chi_square
    mkl-rng-uniform-discrete
    mkl-rng-uniform_bits
    mkl-rng-bits
    mkl-rng-bernoulli
    mkl-rng-geometric
    mkl-rng-binomial
    mkl-rng-hypergeometric
    mkl-rng-poisson
    mkl-rng-poisson_v
    mkl-rng-negbinomial
    mkl-rng-multinomial
