.. _mkl-rng-exponential:

onemkl::rng::exponential
=====================


.. container::


   Generates exponentially distributed random numbers.


   .. container:: section
      :name: GUID-5F8D109F-B058-4CFD-B468-8FD7F1549FF0


      .. rubric:: Syntax
         :name: syntax
         :class: sectiontitle


      .. cpp:function::  template<typename T = float, method Method =      inverse_function>

      .. cpp:function::  class exponential {

      .. cpp:function::  public:

      .. cpp:function::  exponential(): exponential((T)0.0, (T)1.0){}

      .. cpp:function::  exponential(T a, T beta)

      .. cpp:function::  exponential(const exponential<T, Method>& other)

      .. cpp:function::  T a() const

      .. cpp:function::  T beta() const

      .. cpp:function::  exponential<T, Method>& operator=(const      exponential<T, Method>& other)

      .. cpp:function::  }

      .. rubric:: Include Files
         :name: include-files
         :class: sectiontitle


      -  mkl_sycl.hpp


      .. rubric:: Description
         :name: description
         :class: sectiontitle


      The onemkl::rng::exponential class object is used in
      onemkl::rng::generate function to provide random numbers with
      exponential distribution that has displacement a and scalefactor
      β, where ``a, β∈R ; β > 0``.


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


.. container::


.. |image0| image:: ../equations/GUID-12315BD9-4F4D-42B0-A9B5-68A22D40756D-low.jpg
   :class: .eq
.. |image1| image:: ../equations/GUID-0EDD2BB7-A284-495A-84F6-8A210AC499CD-low.gif
   :class: .eq

