.. _mkl-rng-lognormal:

onemkl::rng::lognormal
======================


.. container::


   Generates log-normally distributed random numbers.


   .. container:: section
      :name: GUID-331ADDE0-71FC-423E-AFC5-A53BDE66AEAB


      .. rubric:: Syntax
         :class: sectiontitle


      ::
	 
        template<typename T = float, method Method =      box_muller2>
          class lognormal {
          public:
            lognormal(): lognormal((T)0.0, (T)1.0, (T) 0.0,      (T)1.0){}
            lognormal(Tm, T s, T displ, T scale)
            lognormal(const lognormal<T, Method>& other)
            T m() const
            T s() const
            T displ() const
            T scale() const
            lognormal<T, Method>& operator=(const      lognormal<T, Method>& other)
          }

      .. rubric:: Include Files
         :class: sectiontitle


      -  mkl_sycl.hpp


      .. rubric:: Description
         :class: sectiontitle


      The onemkl::rng::lognormal class object is used in the
      onemkl::rng::generate function to provide random numbers with average
      of distribution (``m``, ``a``) and standard deviation (``s``, σ)
      of subject normal distribution, displacement (``displ``, ``b``),
      and scalefactor (``scale``, β), where
      ``a, σ, b, β ∈ R ; σ > 0 , β > 0``.


      The probability density function is given by:


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
           -     Generation method. The specific values are as follows:             \ ``onemkl::rng::box_muller2``\       \ ``onemkl::rng::inverse_function``\       See      brief descriptions of the methods in `Distributions Template      Parameter onemkl::rng::method      Values <distributions-template-parameter-mkl-rng-method-values.html>`__.   
         * -     m    
           -     \ ``T (float, double)``\     
           -     Average ``a`` of the subject normal       distribution.   
         * -     s    
           -     \ ``T (float, double)``\     
           -     Standard deviation σ of the subject normal       distribution.   
         * -     displ    
           -     \ ``T (float, double)``\     
           -     Displacement ``displ``.    
         * -     scale    
           -     \ ``T (float, double)``\     
           -     Scalefactor scale.    




.. container:: familylinks


   .. container:: parentlink


      **Parent
      topic:** `Distributions <distributions.html>`__



.. |image0| image:: ../equations/GUID-4D962DF4-16F2-438B-8866-4F105DC41242-low.jpg
   :class: .eq
.. |image1| image:: ../equations/GUID-428BFB7A-6E88-4D12-9707-885C02A93A8E-low.jpg
   :class: .eq

