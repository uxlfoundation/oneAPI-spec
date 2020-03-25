.. _mkl-rng-gaussian:

onemkl::rng::gaussian
==================


.. container::


   Generates normally distributed random numbers.


   .. container:: section
      :name: GUID-D1F58E4A-D95B-49A1-A6F4-5DC5B3F9942D


      .. rubric:: Syntax
         :name: syntax
         :class: sectiontitle


      .. cpp:function::  template<typename T = float, method Method =      box_muller2>

      .. cpp:function::  class gaussian {

      .. cpp:function::  public:

      .. cpp:function::  gaussian(): gaussian((T)0.0, (T)1.0){}

      .. cpp:function::  gaussian(T mean, T stddev)

      .. cpp:function::  gaussian(const gaussian<T, Method>& other)

      .. cpp:function::  T mean() const

      .. cpp:function::  T stddev() const

      .. cpp:function::  gaussian<T, Method>& operator=(const gaussian<T,      Method>& other)

      .. cpp:function::  }

      .. rubric:: Include Files
         :name: include-files
         :class: sectiontitle


      -  mkl_sycl.hpp


      .. rubric:: Description
         :name: description
         :class: sectiontitle


      The class object is used in onemkl::rng::generate function to provide
      random numbers with normal (Gaussian) distribution with mean
      (``a``) and standard deviation (``stddev, σ``), where ``a``,
      ``σ ∈ R`` ; ``σ`` > 0.


      The probability density function is given by:


      | 
      | |image0|


      The cumulative distribution function is as follows:


      | 
      | |image1|


      The cumulative distribution function ``Fa,σ(x)`` can be expressed
      in terms of standard normal distribution ``Φ(x)`` as


      ::


                        F
                         

                             a,σ
                         (x) = Φ((x - a)/σ)


   .. container:: section
      :name: GUID-801CDE34-0E9F-455F-8C48-F05082D19D44


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
           -     Generation method. The specific values are as follows:             \ ``onemkl::rng::box_muller``\       \ ``onemkl::rng::box_muller2``\       \ ``onemkl::rng::inverse_function``\       See      brief descriptions of the methods in `Distributions Template      Parameter onemkl::rng::method      Values <distributions-template-parameter-mkl-rng-method-values.html>`__.   
         * -     mean    
           -     \ ``T (float, double)``\     
           -     Mean value ``a``.    
         * -     stddev    
           -     \ ``T (float, double)``\     
           -     Standard deviation σ.    




.. container:: familylinks


   .. container:: parentlink


      **Parent
      topic:** `Distributions <distributions.html>`__


.. container::


.. |image0| image:: ../equations/GUID-281DBA27-691A-4B62-A255-FC33EA28D8D5-low.jpg
   :class: .eq
.. |image1| image:: ../equations/GUID-3A9C1154-2E42-416F-8865-06E7382A3AA7-low.jpg
   :class: .eq

