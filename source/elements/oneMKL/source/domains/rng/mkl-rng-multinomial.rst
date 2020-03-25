.. _mkl-rng-multinomial:

onemkl::rng::multinomial
=====================


.. container::


   Generates multinomially distributed random numbers.


   .. container:: section
      :name: GUID-6E025ECB-EC40-43D4-91E6-D30F7FA11F54


      .. rubric:: Syntax
         :name: syntax
         :class: sectiontitle


      .. cpp:function::  template<typename T = std::int32_t, method Method      = poisson_inverse>

      .. cpp:function::  class multinomial {

      .. cpp:function::  public:

      .. cpp:function::  multinomial(double ntrial, std::vector<double>      p)

      .. cpp:function::  multinomial(const multinomial<T, Method>& other)

      .. cpp:function::  std::int32_t ntrial() const

      .. cpp:function::  std::vector<double> p() const

      .. cpp:function::  multinomial<T, Method>& operator=(const      multinomial<T, Method>& other)

      .. cpp:function::  }

      .. rubric:: Include Files
         :name: include-files
         :class: sectiontitle


      -  mkl_sycl.hpp


      .. rubric:: Description
         :name: description
         :class: sectiontitle


      The onemkl::rng::multinomial class object is used in the
      onemkl::rng::generate function to provide multinomially distributed
      random numbers with ``ntrial`` independent trials and ``k``
      possible mutually exclusive outcomes, with corresponding
      probabilities ``pi``, where ``pi∈R; 0 ≤pi≤ 1, m∈N, k∈N``.


      The probability distribution is given by:


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
           -     Generation method. The specific values are as follows:             \ ``onemkl::rng::poisson_inverse``\       See      brief descriptions of the methods in `Distributions Template      Parameter onemkl::rng::method      Values <distributions-template-parameter-mkl-rng-method-values.html>`__.   
         * -     ntrial    
           -     \ ``std::int32_t``\     
           -     Number of independent trials ``m``.    
         * -     p    
           -     \ ``std::vector<double>``\     
           -     Probability vector of possible outcomes (``k``       length).   




.. container:: familylinks


   .. container:: parentlink


      **Parent
      topic:** `Distributions <distributions.html>`__


.. container::


.. |image0| image:: ../equations/GUID-749B9421-ABAF-41EA-B8B9-3C9941EF5B72-low.png
   :class: .eq

