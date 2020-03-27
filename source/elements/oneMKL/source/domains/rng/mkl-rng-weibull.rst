.. _mkl-rng-weibull:

onemkl::rng::weibull
====================


.. container::


   Generates Weibull distributed random numbers.


   .. container:: section
      :name: GUID-C14EA706-7349-4B76-A1D9-7B05B0A12622


      .. rubric:: Syntax
         :name: syntax
         :class: sectiontitle


      .. cpp:function::  template<typename T = float, method Method =      inverse_function>

      .. cpp:function::  class weibull {

      .. cpp:function::  public:

      .. cpp:function::  weibull(): weibull((T)0.0, (T)1.0){}

      .. cpp:function::  weibull(T alpha, T a, T beta)

      .. cpp:function::  weibull(const weibull<T, Method>& other)

      .. cpp:function::  T alpha() const

      .. cpp:function::  T a() const

      .. cpp:function::  T beta() const

      .. cpp:function::  weibull<T, Method>& operator=(const weibull<T,      Method>& other)

      .. cpp:function::  }

      .. rubric:: Include Files
         :name: include-files
         :class: sectiontitle


      -  mkl_sycl.hpp


      .. rubric:: Description
         :name: description
         :class: sectiontitle


      The onemkl::rng::weibull class object is used in the
      onemkl::rng::generate function to provide Weibull distributed random
      numbers with displacement ``a``, scalefactor β, and shape α, where
      ``α, β, a∈R ; α > 0, β > 0``.


      The probability density function is given by:


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
           -     Generation method. The specific values are as follows:             \ ``onemkl::rng::inverse_function``\       \ ``onemkl::rng::inverse_function | onemkl::rng::accurate``\       See      brief descriptions of the methods in `Distributions Template      Parameter onemkl::rng::method      Values <distributions-template-parameter-mkl-rng-method-values.html>`__.   
         * -     alpha    
           -     \ ``T (float, double)``\     
           -     Shape α    
         * -     a    
           -     \ ``T (float, double)``\     
           -     Displacement ``a``.    
         * -     beta    
           -     \ ``T (float, double)``\     
           -     Scalefactor β.    




.. container:: familylinks


   .. container:: parentlink


      **Parent
      topic:** `Distributions <distributions.html>`__



.. |image0| image:: ../equations/GUID-8F2DCE6A-CB54-4CEA-A5EB-937893A3DB34-low.gif
   :class: .eq
.. |image1| image:: ../equations/GUID-6F53C93C-0634-4E53-8874-5ACBD4C9AA3E-low.gif
   :class: .eq

