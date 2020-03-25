.. _mkl-rng-gumbel:

onemkl::rng::gumbel
================


.. container::


   Generates Gumbel distributed random values.


   .. container:: section
      :name: GUID-41C16785-78E0-4B3B-A698-11755BE7AC69


      .. rubric:: Syntax
         :name: syntax
         :class: sectiontitle


      .. cpp:function::  template<typename T = float, method Method =      inverse_function>

      .. cpp:function::  class gumbel {

      .. cpp:function::  public:

      .. cpp:function::  gumbel(): gumbel((T)0.0, (T)1.0){}

      .. cpp:function::  gumbel(T a, T b)

      .. cpp:function::  gumbel(const gumbel<T, Method>& other)

      .. cpp:function::  T a() const

      .. cpp:function::  T b() const

      .. cpp:function::  gumbel<T, Method>& operator=(const gumbel<T,      Method>& other)

      .. cpp:function::  }

      .. rubric:: Include Files
         :name: include-files
         :class: sectiontitle


      -  mkl_sycl.hpp


      .. rubric:: Description
         :name: description
         :class: sectiontitle


      The onemkl::rng::gumbel class object is used in the
      onemkl::rng::generate function to provide Gumbel distributed random
      numbers with displacement (a) and scalefactor (``b``, β), where a,
      β∈\ ``R`` ; β > 0.


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


.. container::


.. |image0| image:: ../equations/GUID-09FC1496-B5B3-4DF6-A3EE-E6410BE1EFD2-low.jpg
   :class: .eq
.. |image1| image:: ../equations/GUID-E3193631-248D-4D18-A094-30BB6FF50687-low.jpg
   :class: .eq

