.. _mkl-rng-wichmann_hill:

onemkl::rng::wichmann_hill
=======================


.. container::


   Wichmann-Hill pseudorandom number generator (a set of 273 basic
   generators) from NAG Numerical Libraries [NAG].


   .. container:: section
      :name: GUID-753F13BA-A3C7-4F24-90F1-14B6279BD95C


      .. rubric:: Syntax
         :name: syntax
         :class: sectiontitle


      .. container:: dlsyntaxpara


         .. cpp:function::  class wichmann_hill :         internal::engine_base<wichmann_hill>{

         .. cpp:function::  public:

         .. cpp:function::  wichmann_hill (cl::sycl::queue& queue,         std::uint32_t seed, std::uint32_t engine_idx)

         .. cpp:function::  wichmann_hill (cl::sycl::queue& queue,         std::initializer_list<std::uint32_t> seed, std::uint32_t         engine_idx)

         .. cpp:function::  wichmann_hill (const wichmann_hill& other)

         .. cpp:function::  wichmann_hill& operator=(const wichmann_hill&         other)

         .. cpp:function::  ~wichmann_hill()

         .. cpp:function::  }

         .. rubric:: Include Files
            :name: include-files
            :class: sectiontitle


         -  mkl_sycl.hpp


         .. rubric:: Description
            :name: description
            :class: sectiontitle


         Wichmann-Hill pseudorandom number generator (a set of 273 basic
         generators) from NAG Numerical Libraries
         [`NAG <bibliography.html>`__].


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
              -     Valid cl::sycl::queue, calls of          onemkl::rng::generate() routine submit kernels in this         queue.   
            * -     seed    
              -     std::uint32_t /          std::initializer_list<std::uint32_t>   
              -     Initial conditions of the engine.    
            * -     engine_idx    
              -     std::uint32_t     
              -     Index of the engine from the set (set contains 273          basic generators)   




         See `VS
         Notes <bibliography.html>`__ for
         detailed descriptions.


   .. container:: familylinks


      .. container:: parentlink


         **Parent topic:** `Engines (Basic Random Number
         Generators) <engines-basic-random-number-generators.html>`__


   .. container::

