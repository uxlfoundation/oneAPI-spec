.. _mkl-rng-rayleigh:

onemkl::rng::rayleigh
=====================


.. container::


   Generates Rayleigh distributed random values.


   .. container:: section
      :name: GUID-7AE7A028-213A-48BA-B291-15B651349F6C


      .. rubric:: Syntax
         :class: sectiontitle


      .. cpp:function::  template<typename T = float, method Method =      inverse_function>

      .. cpp:function::  class rayleigh {

      .. cpp:function::  public:

      .. cpp:function::  rayleigh(): rayleigh((T)0.0, (T)1.0){}

      .. cpp:function::  rayleigh(T a, T b)

      .. cpp:function::  rayleigh(const rayleigh<T, Method>& other)

      .. cpp:function::  T a() const

      .. cpp:function::  T b() const

      .. cpp:function::  rayleigh<T, Method>& operator=(const rayleigh<T,      Method>& other)

      .. cpp:function::  }

      .. rubric:: Include Files
         :class: sectiontitle


      -  mkl_sycl.hpp


      .. rubric:: Description
         :class: sectiontitle


      The onemkl::rng::rayleigh class object is used by the
      onemkl::rng::generate function to provide Rayleigh distributed random
      numbers with displacement (``a``) and scalefactor (``b``, β),
      where ``a, β∈R ; β > 0.``


      The Rayleigh distribution is a special case of the
      `Weibull <mkl-rng-weibull.html>`__
      distribution, where the shape parameter ``α = 2``.


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
           -     Generation method. The specific values are as follows:             \ ``onemkl::rng::inverse_function``\       \ ``onemkl::rng::inverse_function | onemkl::rng::accurate``\       See      brief descriptions of the methods in `Distributions Template      Parameter onemkl::rng::method      Values <distributions-template-parameter-mkl-rng-method-values.html>`__.   
         * -     a    
           -     \ ``T (float, double)``\     
           -     Displacement ``a``.    
         * -     b    
           -     \ ``T (float, double)``\     
           -     Scalefactor ``b``.    




.. container:: familylinks


   .. container:: parentlink


      **Parent
      topic:** `Distributions <distributions.html>`__



.. |image0| image:: ../equations/GUID-96DF4ACE-8587-423F-B50A-E9A58BE272F9-low.gif
   :class: .eq
.. |image1| image:: ../equations/GUID-F85E385E-ACAD-4DC6-95EC-7C8A85836AAD-low.gif
   :class: .eq

