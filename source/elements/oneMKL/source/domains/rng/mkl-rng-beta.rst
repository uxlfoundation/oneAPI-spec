.. _mkl-rng-beta:

onemkl::rng::beta
=================


.. container::


   Generates beta distributed random values.


   .. container:: section
      :name: GUID-7EE1A888-9D53-4736-B07A-356034DBF3E0


      .. rubric:: Syntax
         :name: syntax
         :class: sectiontitle


      .. cpp:function::  template<typename T = float, method Method =      cheng_johnk_atkinson>

      .. cpp:function::  class beta {

      .. cpp:function::  public:

      .. cpp:function::  beta(): beta((T)1.0, (T)1.0, (T)(0.0),      (T)(1.0)){}

      .. cpp:function::  beta(T p, T q, T a, T b)

      .. cpp:function::  beta(const beta<T, Method>& other)

      .. cpp:function::  T p() const

      .. cpp:function::  T q() const

      .. cpp:function::  T a() const

      .. cpp:function::  T b() const

      .. cpp:function::  beta<T, Method>& operator=(const beta<T, Method>&      other)

      .. cpp:function::  }

      .. rubric:: Include Files
         :name: include-files
         :class: sectiontitle


      -  mkl_sycl.hpp


      .. rubric:: Description
         :name: description
         :class: sectiontitle


      The onemkl::rng::beta class object is used in the onemkl::rng::generate
      function to provide random numbers with beta distribution that has
      shape parameters p and ``q``, displacement ``a``, and scale
      parameter (``b``, β), where ``p``, ``q``, ``a``, and
      ``β∈R ; p > 0, q > 0, β > 0``.


      The probability density function is given by:


      |image0|


      where ``B``\ (``p``, ``q``) is the complete beta function.


      The cumulative distribution function is as follows:


      |image1|


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
           -     Generation method. The specific values are as follows:             \ ``onemkl::rng::cheng_johnk_atkinson``\       \ ``onemkl::rng::cheng_johnk_atkinson | onemkl::rng::accurate``\       See      brief descriptions of the methods in `Distributions Template      Parameter onemkl::rng::method      Values <distributions-template-parameter-mkl-rng-method-values.html>`__.   
         * -     p    
           -     \ ``T (float, double)``\     
           -      Shape ``p``\     
         * -     q    
           -     \ ``T (float, double)``\     
           -      Shape ``q``\     
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



.. |image0| image:: ../equations/GUID-CD24FF51-197B-40A1-83A8-514788192ee1.png
   :class: img-middle
.. |image1| image:: ../equations/GUID-CD24FF51-197B-40A1-83A8-514788192ee2.png
   :class: img-middle

