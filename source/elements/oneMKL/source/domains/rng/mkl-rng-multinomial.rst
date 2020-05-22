.. _mkl-rng-multinomial:

onemkl::rng::multinomial
========================


.. container::


   Generates multinomially distributed random numbers.


   .. container:: section
      :name: GUID-6E025ECB-EC40-43D4-91E6-D30F7FA11F54


      .. rubric:: Syntax
         :class: sectiontitle


      ::
	 
        template<typename T = std::int32_t, method Method      = poisson_inverse>
          class multinomial {
          public:
            multinomial(double ntrial, std::vector<double>      p)
            multinomial(const multinomial<T, Method>& other)
            std::int32_t ntrial() const
            std::vector<double> p() const
            multinomial<T, Method>& operator=(const      multinomial<T, Method>& other)
          }

      .. rubric:: Include Files
         :class: sectiontitle


      -  mkl_sycl.hpp


      .. rubric:: Description
         :class: sectiontitle


      The onemkl::rng::multinomial class object is used in the
      onemkl::rng::generate function to provide multinomially distributed
      random numbers with ``ntrial`` independent trials and ``k``
      possible mutually exclusive outcomes, with corresponding
      probabilities ``pi``, where ``pi∈R; 0 ≤pi≤ 1, m∈N, k∈N``.


      The probability distribution is given by:


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
           -     Generation method. The specific values are as follows:             \ ``onemkl::rng::poisson_inverse``\       See      brief descriptions of the methods in `Distributions Template      Parameter onemkl::rng::method      Values <distributions-template-parameter-mkl-rng-method-values.html>`__.   
         * -     ntrial    
           -     \ ``std::int32_t``\     
           -     Number of independent trials ``m``.    
         * -     p    
           -     \ ``std::vector<double>``\     
           -     Probability vector of possible outcomes (``k``       length).   




.. container:: familylinks


   .. container:: parentlink


      **Parent
      topic:** `Distributions <distributions.html>`__



.. |image0| image:: ../equations/GUID-749B9421-ABAF-41EA-B8B9-3C9941EF5B72-low.png
   :class: .eq

