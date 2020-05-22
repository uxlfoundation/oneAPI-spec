.. _mkl-rng-bernoulli:

onemkl::rng::bernoulli
======================


.. container::


   Generates Bernoulli distributed random values.


   .. container:: section
      :name: GUID-DBB02CF3-C214-4063-87CC-ECF75333D92D


      .. rubric:: Syntax
         :class: sectiontitle


      ::
	 
        template<typename T = std::int32_t, method Method = inverse_function>
          class bernoulli {
          public:
            bernoulli(): bernoulli(0.5){}
            bernoulli(double p)
            bernoulli(const bernoulli<T, Method>& other)
            double p() const
            bernoulli<T, Method>& operator=(const  bernoulli<T, Method>& other)
          }

      .. rubric:: Include Files
         :class: sectiontitle


      -  mkl_sycl.hpp


      .. rubric:: Description
         :class: sectiontitle


      The onemkl::rng::bernoulli class object is used in the
      onemkl::rng::generate function to provide Bernoulli distributed
      random numbers with probability ``p`` of a single trial success,
      where


      ::


         p∈R; 0 ≤ p ≤ 1.


      A variate is called Bernoulli distributed, if after a trial it is
      equal to 1 with probability of success ``p``, and to 0 with
      probability 1 - ``p``.


      The probability distribution is given by:


      ::


         P(X = 1) = p


      ::


         P(X = 0) = 1 - p


      The cumulative distribution function is as follows:


      | 
      | |image0|


      .. rubric:: Input Parameters
         :class: sectiontitle


      .. list-table:: 
         :header-rows: 1

         * -     Name    
           -     Type    
           -     Description    
         * -     method    
           -     \ ``onemkl::rng::method``\     
           -     Generation method. The specific values are as follows:             \ ``onemkl::rng::inverse_function``\       See      brief descriptions of the methods in `Distributions Template      Parameter onemkl::rng::method      Values <distributions-template-parameter-mkl-rng-method-values.html>`__.   
         * -     p    
           -     \ ``double``\     
           -     Success probability ``p`` of a trial.    




.. container:: familylinks


   .. container:: parentlink


      **Parent
      topic:** `Distributions <distributions.html>`__



.. |image0| image:: ../equations/GUID-7F65198B-719A-44FB-8983-BBD3C196A663-low.jpg
   :class: .eq

