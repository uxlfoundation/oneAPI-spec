.. _mkl-rng-cauchy:

onemkl::rng::cauchy
===================


.. container::


   Generates Cauchy distributed random values.


   .. container:: section
      :name: GUID-00E31852-3752-4F63-81D0-EF47CF676F30


      .. rubric:: Syntax
         :class: sectiontitle


      .. cpp:function::  template<typename T = float, method Method =      inverse_function>

      .. cpp:function::  class cauchy {

      .. cpp:function::  public:

      .. cpp:function::  cauchy(): cauchy((T)0.0, (T)1.0){}

      .. cpp:function::  cauchy(T a, T b)

      .. cpp:function::  cauchy(const cauchy<T, Method>& other)

      .. cpp:function::  T a() const

      .. cpp:function::  T b() const

      .. cpp:function::  cauchy<T, Method>& operator=(const cauchy<T,      Method>& other)

      .. cpp:function::  }

      .. rubric:: Include Files
         :class: sectiontitle


      -  mkl_sycl.hpp


      .. rubric:: Description
         :class: sectiontitle


      The onemkl::rng::cauchy class object is used in the
      onemkl::rng::generate function to provide Cauchy distributed random
      numbers with displacement (``a``) and scalefactor (``b``, β),
      where ``a, β∈R ; β > 0``.


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
           -     Generation method. The specific values are as follows:             \ ``onemkl::rng::inverse_function``\       See      brief descriptions of the methods in `Distributions Template      Parameter onemkl::rng::method      Values <distributions-template-parameter-mkl-rng-method-values.html>`__.   
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



.. |image0| image:: ../equations/GUID-04615D14-A026-4BF0-ACD6-0FC822FEC64E-low.gif
   :class: .eq
.. |image1| image:: ../equations/GUID-5FAAD02F-09F5-4B78-B404-384F1270FA1C-low.jpg
   :class: .eq

