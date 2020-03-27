.. _mkl-rng-geometric:

onemkl::rng::geometric
======================


.. container::


   Generates geometrically distributed random values.


   .. container:: section
      :name: GUID-C5319AC4-9A75-4DC6-90C4-DCFA4008CE5D


      .. rubric:: Syntax
         :name: syntax
         :class: sectiontitle


      .. cpp:function::  template<typename T = std::int32_t, method Method      = inverse_function>

      .. cpp:function::  class geometric {

      .. cpp:function::  public:

      .. cpp:function::  geometric(): geometric(0.5){}

      .. cpp:function::  geometric(double p)

      .. cpp:function::  geometric(const geometric<T, Method>& other)

      .. cpp:function::  double p() const

      .. cpp:function::  geometric<T, Method>& operator=(const      geometric<T, Method>& other)

      .. cpp:function::  }

      .. rubric:: Include Files
         :name: include-files
         :class: sectiontitle


      -  mkl_sycl.hpp


      .. rubric:: Description
         :name: description
         :class: sectiontitle


      The onemkl::rng::geometric class object is used in the
      onemkl::rng::generate function to provide geometrically distributed
      random numbers with probability ``p`` of a single trial success,
      where ``p∈R; 0 <  p <  1.``


      A geometrically distributed variate represents the number of
      independent Bernoulli trials preceding the first success. The
      probability of a single Bernoulli trial success is ``p``.


      The probability distribution is given by:


      ``P``\ (``X`` = ``k``) = ``p``\ ·(1 - ``p``)\ :sup:`k`, ``k``\ ∈
      {0,1,2, ... }.


      The cumulative distribution function is as follows:


      | 
      | |image0|


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
         * -     p    
           -     \ ``double``\     
           -     Success probability ``p`` of a trial.    




.. container:: familylinks


   .. container:: parentlink


      **Parent
      topic:** `Distributions <distributions.html>`__


.. container::


.. |image0| image:: ../equations/GUID-2D60A1A4-9522-40FC-AEEA-B64EB795144C-low.gif
   :class: .eq

