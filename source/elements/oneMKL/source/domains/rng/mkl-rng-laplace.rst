.. _mkl-rng-laplace:

onemkl::rng::laplace
====================


.. container::


   Generates random numbers with Laplace distribution.


   .. container:: section
      :name: GUID-776BC496-647B-44F4-92A8-2CA9DB391F1C


      .. rubric:: Syntax
         :class: sectiontitle


      ::
	 
        template<typename T = float, method Method =      inverse_function>
          class laplace {
          public:
            laplace(): laplace((T)0.0, (T)1.0){}
            laplace(T a, T b)
            laplace(const laplace<T, Method>& other)
            T a() const
            T b() const
            laplace<T, Method>& operator=(const laplace<T,      Method>& other)
          }

      .. rubric:: Include Files
         :class: sectiontitle


      -  mkl_sycl.hpp


      .. rubric:: Description
         :class: sectiontitle


      The onemkl::rng::laplace class object is used in the
      onemkl::rng::generate function to provide random numbers with Laplace
      distribution with mean value (or average) ``a`` and scalefactor (
      ``b``, β), where ``a, β∈R ; β > 0``. The scalefactor value
      determines the standard deviation as


      |image0|


      The probability density function is given by:


      | 
      | |image1|


      The cumulative distribution function is as follows:


      | 
      | |image2|


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
         * -     a    
           -     \ ``T (float, double)``\     
           -     Mean value ``a``.    
         * -     b    
           -     \ ``T (float, double)``\     
           -     Scalefactor b.    




.. container:: familylinks


   .. container:: parentlink


      **Parent
      topic:** `Distributions <distributions.html>`__



.. |image0| image:: ../equations/GUID-1D36B5CE-3BF3-4762-926B-05C5527FAE45-low.gif
   :class: .eq
.. |image1| image:: ../equations/GUID-9B0556B7-20F4-4EC9-875B-F6654CAC0C73-low.gif
   :class: .eq
.. |image2| image:: ../equations/GUID-E5BC391B-F8BC-45E0-9A58-84319AC0B246-low.gif
   :class: .eq

