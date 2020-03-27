.. _mkl-rng-uniform-discrete:

onemkl::rng::uniform (Discrete)
===============================


.. container::


   Generates random numbers uniformly distributed over the interval
   ``[a, b)``.


   .. container:: section
      :name: GUID-351E5FB2-A4B6-4198-A538-7FF637E06D51


      .. rubric:: Syntax
         :class: sectiontitle


      .. cpp:function::  template<typename T = float, method Method =      standard>

      .. cpp:function::  class uniform {

      .. cpp:function::  public:

      .. cpp:function::  uniform(): uniform((T)0.0, (T)1.0){}

      .. cpp:function::  uniform(T a, T b)

      .. cpp:function::  uniform(const uniform<T, Method>& other)

      .. cpp:function::  T a() const

      .. cpp:function::  T b() const

      .. cpp:function::  uniform<T, Method>& operator=(const uniform<T,      Method>& other)

      .. cpp:function::  }

      .. rubric:: Include Files
         :class: sectiontitle


      -  ``mkl_sycl.hpp``


      .. rubric:: Description
         :class: sectiontitle


      The onemkl::rng::uniform class object is used in onemkl::rng::generate
      functions to provide random numbers uniformly distributed over the
      interval ``[a, b)``, where ``a, b`` are the left and right bounds
      of the interval respectively, and ``a, b∈Z; a < b``.


      The probability distribution is given by:


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
         * -     a    
           -     \ ``T (std::int32_t)``\     
           -     Left bound ``a``\     
         * -     b    
           -     \ ``T (std::int32_t)``\     
           -     Right bound ``b``\     




.. container:: familylinks


   .. container:: parentlink


      **Parent
      topic:** `Distributions <distributions.html>`__



.. |image0| image:: ../equations/GUID-A5408434-7126-4EEC-8AD1-856204EBF263-low.jpg
   :class: .eq
.. |image1| image:: ../equations/GUID-AAA6EA17-BA1C-4185-A5F4-8997B64E3BDD-low.gif
   :class: .eq

