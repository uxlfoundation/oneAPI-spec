.. _mkl-rng-poisson:

onemkl::rng::poisson
====================


.. container::


   Generates Poisson distributed random values.


   .. container:: section
      :name: GUID-06F1B760-4D88-4DB3-9F11-9087594F9EF2


      .. rubric:: Syntax
         :name: syntax
         :class: sectiontitle


      .. cpp:function::  template<typename T = std::int32_t, method Method      = ptpe>

      .. cpp:function::  class poisson {

      .. cpp:function::  public:

      .. cpp:function::  poisson(): poisson(0.5){}

      .. cpp:function::  poisson(double lambda)

      .. cpp:function::  poisson(const poisson<T, Method>& other)

      .. cpp:function::  double lambda() const

      .. cpp:function::  poisson<T, Method>& operator=(const poisson<T,      Method>& other)

      .. cpp:function::  }

      .. rubric:: Include Files
         :name: include-files
         :class: sectiontitle


      -  mkl_sycl.hpp


      .. rubric:: Description
         :name: description
         :class: sectiontitle


      The onemkl::rng::poisson class object is used in the
      onemkl::rng::generate function to provide Poisson distributed random
      numbers with distribution parameter λ, where ``λ∈R; λ > 0``.


      The probability distribution is given by:


      | 
      | |image0|
      | ``k``\ ∈ {0, 1, 2, ...}.


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
           -     Generation method. The specific values are as follows:             \ ``onemkl::rng::ptpe``\       \ ``onemkl::rng::gaussian_inverse``\       See      brief descriptions of the methods in `Distributions Template      Parameter onemkl::rng::method      Values <distributions-template-parameter-mkl-rng-method-values.html>`__.   
         * -     lambda    
           -     \ ``double``\     
           -     Distribution parameter λ.    




.. container:: familylinks


   .. container:: parentlink


      **Parent
      topic:** `Distributions <distributions.html>`__



.. |image0| image:: ../equations/GUID-96C9ACB0-9A38-4682-85C6-4E71711C32C0-low.gif
   :class: .eq
.. |image1| image:: ../equations/GUID-E48BA1ED-9ABF-487F-80F3-1FA1E0F6EABC-low.jpg
   :class: .eq

