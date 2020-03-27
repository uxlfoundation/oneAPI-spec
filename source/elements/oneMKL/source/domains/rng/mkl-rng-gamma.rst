.. _mkl-rng-gamma:

onemkl::rng::gamma
==================


.. container::


   Generates gamma distributed random values.


   .. container:: section
      :name: GUID-EDB0E0C5-B8D7-4494-8C52-BEEC84A0C324


      .. rubric:: Syntax
         :name: syntax
         :class: sectiontitle


      .. cpp:function::  template<typename T = float, method Method =      marsaglia>

      .. cpp:function::  class gamma {

      .. cpp:function::  public:

      .. cpp:function::  gamma(): gamma((T)1.0, (T)0.0, (T)1.0){}

      .. cpp:function::  gamma(T alpha, T a, T beta)

      .. cpp:function::  gamma(const gamma<T, Method>& other)

      .. cpp:function::  T alpha() const

      .. cpp:function::  T a() const

      .. cpp:function::  T beta() const

      .. cpp:function::  gamma<T, Method>& operator=(const gamma<T,      Method>& other)

      .. cpp:function::  }

      .. rubric:: Include Files
         :name: include-files
         :class: sectiontitle


      -  mkl_sycl.hpp


      .. rubric:: Description
         :name: description
         :class: sectiontitle


      The onemkl::rng::gamma class object is used in the onemkl::rng::generate
      function to provide random numbers with gamma distribution that
      has shape parameter α, displacement ``a``, and scale parameter β,
      where α, β, and ``a∈R ; α > 0, β > 0``.


      The probability density function is given by:


      where Γ(α) is the complete gamma function.


      The cumulative distribution function is as follows:


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
           -     Generation method. The specific values are as follows:             \ ``onemkl::rng::marsaglia``\       \ ``onemkl::rng::marsaglia | onemkl::rng::accurate``\       See      brief descriptions of the methods in `Distributions Template      Parameter onemkl::rng::method      Values <distributions-template-parameter-mkl-rng-method-values.html>`__.   
         * -     alpha    
           -     \ ``T (float, double)``\     
           -      Shape α    
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

