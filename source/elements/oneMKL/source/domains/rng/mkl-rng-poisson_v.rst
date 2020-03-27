.. _mkl-rng-poisson_v:

onemkl::rng::poisson_v
======================


.. container::


   Generates Poisson distributed random values with varying mean.


   .. container:: section
      :name: GUID-BD0D9835-6217-4576-97E5-6448E9426235


      .. rubric:: Syntax
         :name: syntax
         :class: sectiontitle


      .. cpp:function::  template<typename T = std::int32_t, method Method      = gaussian_inverse>

      .. cpp:function::  class poisson_v {

      .. cpp:function::  public:

      .. cpp:function::  poisson_v(std::vector<double> lambda

      .. cpp:function::  poisson_v(const poisson_v<T, Method>& other)

      .. cpp:function::  std::vector<double> lambda() const

      .. cpp:function::  poisson_v<T, Method>& operator=(const      poisson_v<T, Method>& other)

      .. cpp:function::  }

      .. rubric:: Include Files
         :name: include-files
         :class: sectiontitle


      -  mkl_sycl.hpp


      .. rubric:: Description
         :name: description
         :class: sectiontitle


      The onemkl::rng::poisson_v class object is used in the
      onemkl::rng::generate function to provide ``n`` Poisson distributed
      random numbers ``x``\ :sub:`i`\ (``i`` = 1, ..., ``n``) with
      distribution parameter ``λi``, where ``λi∈R``; ``λi > 0``.


      The probability distribution is given by:


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
           -     Generation method. The specific values are as follows:             \ ``onemkl::rng::gaussian_inverse``\       See      brief descriptions of the methods in `Distributions Template      Parameter onemkl::rng::method      Values <distributions-template-parameter-mkl-rng-method-values.html>`__.   
         * -     lambda    
           -     \ ``std::vector<double>``\     
           -     Array of ``n`` distribution parameters λ.    




.. container:: familylinks


   .. container:: parentlink


      **Parent
      topic:** `Distributions <distributions.html>`__


.. container::


.. |image0| image:: ../equations/GUID-19F7C7EA-5657-4016-87A6-4E2721994C56-low.gif
   :class: .eq
.. |image1| image:: ../equations/GUID-BF3DF32F-5256-4DFD-9653-FAD2C740BCA5-low.gif
   :class: .eq

