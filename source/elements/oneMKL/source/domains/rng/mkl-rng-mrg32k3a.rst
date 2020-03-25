.. _mkl-rng-mrg32k3a:

onemkl::rng::mrg32k3a
==================


.. container::


   The combined multiple recursive pseudorandom number generator
   MRG32k3a [ L'Ecuyer99a]


   .. container:: section
      :name: GUID-753F13BA-A3C7-4F24-90F1-14B6279BD95C


      .. rubric:: Syntax
         :name: syntax
         :class: sectiontitle


      .. container:: dlsyntaxpara


         .. cpp:function::  class mrg32k3a:         internal::engine_base<mrg32k3a>{

         .. cpp:function::  public:

         .. cpp:function::  mrg32k3a (cl::sycl::queue& queue,         std::initializer_list<std::uint32_t> seed)

         .. cpp:function::  mrg32k3a (const mrg32k3a& other)

         .. cpp:function::  mrg32k3a& operator=(const mrg32k3a& other)

         .. cpp:function::  mrg32k3a()

         .. cpp:function::  }

         .. rubric:: Include Files
            :name: include-files
            :class: sectiontitle


         -  ``mkl_sycl.hpp``


         .. rubric:: Description
            :name: description
            :class: sectiontitle


         The combined multiple recursive pseudorandom number generator
         MRG32k3a
         `[L'Ecuyer99a] <bibliography.html>`__.


         .. rubric:: Input Parameters
            :name: input-parameters
            :class: sectiontitle


         .. list-table:: 
            :header-rows: 1

            * -     Name    
              -     Type    
              -     Description    
            * -     queue    
              -     cl::sycl::queue    
              -     Valid cl::sycl::queue, calls of the          onemkl::rng::generate() routine submits kernels in this         queue.   
            * -     seed    
              -     std::uint32_t /          std::initializer_list<std::uint32_t>   
              -     Initial conditions of the generator state or engine          state.   




         See `VS
         Notes <bibliography.html>`__ for
         detailed descriptions.


   .. container:: familylinks


      .. container:: parentlink


         **Parent topic:** `Engines (Basic Random Number
         Generators) <engines-basic-random-number-generators.html>`__


   .. container::

