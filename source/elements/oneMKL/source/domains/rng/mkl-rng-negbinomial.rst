.. _mkl-rng-negbinomial:

onemkl::rng::negbinomial
========================


.. container::


   Generates random numbers with negative binomial distribution.


   .. container:: section
      :name: GUID-EE6FB7D3-1C1A-4094-82F6-C2643A39B2CE


      .. rubric:: Syntax
         :class: sectiontitle


      ::
	 
        template<typename T = std::int32_t, method Method      = nbar>
          class negbinomial {
          public:
            negbinomial(): negbinomial(0.1, 0.5){}
            negbinomial(double a, double p)
            negbinomial(const negbinomial<T, Method>& other)
            double a() const
            double p() const
            negbinomial<T, Method>& operator=(const      negbinomial<T, Method>& other)
          }

      .. rubric:: Include Files
         :class: sectiontitle


      -  mkl_sycl.hpp


      .. rubric:: Description
         :class: sectiontitle


      The onemkl::rng::negbinomial class object is used in the
      onemkl::rng::generate function to provide random numbers with
      negative binomial distribution and distribution parameters ``a``
      and ``p``, where ``p``, ``a``\ ∈\ ``R``; 0 < ``p`` < 1; ``a`` > 0.


      If the first distribution parameter ``a``\ ∈\ ``N``, this
      distribution is the same as Pascal distribution. If
      ``a``\ ∈\ ``N``, the distribution can be interpreted as the
      expected time of ``a``-th success in a sequence of Bernoulli
      trials, when the probability of success is ``p``.


      The probability distribution is given by:


      | 
      | |image0|


      The cumulative distribution function is as follows:


      | 
      | |image1|


      .. rubric:: Input Parameters
         :class: sectiontitle


      .. list-table:: 
         :header-rows: 1

         * -     Name    
           -     Type    
           -     Description    
         * -     method    
           -     \ ``onemkl::rng::method``\     
           -     Generation method. The specific values are as follows:             \ ``onemkl::rng::nbar``\       See brief      descriptions of the methods in `Distributions Template Parameter      onemkl::rng::method      Values <distributions-template-parameter-mkl-rng-method-values.html>`__.   
         * -     a    
           -     \ ``double``\     
           -     The first distribution parameter ``a``.    
         * -     p    
           -     \ ``double``\     
           -     The second distribution parameter ``p``.    




.. container:: familylinks


   .. container:: parentlink


      **Parent
      topic:** `Distributions <distributions.html>`__



.. |image0| image:: ../equations/GUID-A7CA23B7-756F-45C6-85B3-3A8924939D7D-low.jpg
   :class: .eq
.. |image1| image:: ../equations/GUID-2BEFE049-EB3B-4FC9-AD75-ABA053617238-low.jpg
   :class: .eq

