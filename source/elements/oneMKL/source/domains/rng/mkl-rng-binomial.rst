.. _mkl-rng-binomial:

onemkl::rng::binomial
==================


.. container::


   Generates binomially distributed random numbers.


   .. container:: section
      :name: GUID-6E025ECB-EC40-43D4-91E6-D30F7FA11F54


      .. rubric:: Syntax
         :name: syntax
         :class: sectiontitle


      .. cpp:function::  template<typename T = std::int32_t, method Method      = btpe>

      .. cpp:function::  class binomial {

      .. cpp:function::  public:

      .. cpp:function::  binomial(): binomial(5, 0.5){}

      .. cpp:function::  binomial(std::int32_t ntrial, double p)

      .. cpp:function::  binomial(const binomial<T, Method>& other)

      .. cpp:function::  std::int32_t ntrial() const

      .. cpp:function::  double p() const

      .. cpp:function::  binomial<T, Method>& operator=(const binomial<T,      Method>& other)

      .. cpp:function::  }

      .. rubric:: Include Files
         :name: include-files
         :class: sectiontitle


      -  mkl_sycl.hpp


      .. rubric:: Description
         :name: description
         :class: sectiontitle


      The onemkl::rng::binomial class object is used in the
      onemkl::rng::generate function to provide binomially distributed
      random numbers with number of independent Bernoulli trials ``m``,
      and with probability ``p`` of a single trial success, where
      ``p∈R; 0 ≤p≤ 1, m∈N``.


      A binomially distributed variate represents the number of
      successes in ``m`` independent Bernoulli trials with probability
      of a single trial success ``p``.


      The probability distribution is given by:


      | 
      | |image0|


      The cumulative distribution function is as follows:


      | 
      | |image1|


       



      .. rubric:: Input Parameters
         :name: input-parameters
         :class: sectiontitle


      .. list-table:: 
         :header-rows: 1

         * -     Name    
           -     Type    
           -     Description    
         * -     method    
           -     \ ``onemkl::rng::method``\     
           -     Generation method. The specific values are as follows:             \ ``onemkl::rng::btpe``\       See brief      descriptions of the methods in `Distributions Template Parameter      onemkl::rng::method      Values <distributions-template-parameter-mkl-rng-method-values.html>`__.   
         * -     ntrials    
           -     \ ``std::int32_t``\     
           -     Number of independent trials.    
         * -     p    
           -     \ ``double``\     
           -     Success probability ``p`` of a single trial.    




.. container:: familylinks


   .. container:: parentlink


      **Parent
      topic:** `Distributions <distributions.html>`__


.. container::


.. |image0| image:: ../equations/GUID-D703292D-2A37-42C6-B713-E38B801F0114-low.gif
   :class: .eq
.. |image1| image:: ../equations/GUID-081A19C4-609F-4736-BCCF-D680013A2775-low.gif
   :class: .eq

