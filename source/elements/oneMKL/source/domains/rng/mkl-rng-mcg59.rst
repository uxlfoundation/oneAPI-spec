.. _mkl-rng-mcg59:

onemkl::rng::mcg59
===============


.. container::


   The 59-bit multiplicative congruential pseudorandom number generator
   MCG(1313, 259) from NAG Numerical Libraries [NAG].


   .. container:: section
      :name: GUID-753F13BA-A3C7-4F24-90F1-14B6279BD95C


      .. rubric:: Syntax
         :name: syntax
         :class: sectiontitle


      .. container:: dlsyntaxpara


         .. cpp:function::  class mcg59 : internal::engine_base<mcg59>{

         .. cpp:function::  public:

         .. cpp:function::  mcg59 (cl::sycl::queue& queue, std::uint64_t         seed)

         .. cpp:function::  mcg59 (const mcg59&other)

         .. cpp:function::  mcg59& operator=(const mcg59& other)

         .. cpp:function::  ~mcg59()

         .. cpp:function::  }

         .. rubric:: Include Files
            :name: include-files
            :class: sectiontitle


         -  mkl_sycl.hpp


         .. rubric:: Description
            :name: description
            :class: sectiontitle


         The 59-bit multiplicative congruential pseudorandom number
         generator MCG(1313, 259) from NAG Numerical Libraries
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
              -     std::uint64_t     
              -     Initial conditions of the engine.    




         See `VS
         Notes <bibliography.html>`__ for
         detailed descriptions.


   .. container:: familylinks


      .. container:: parentlink


         **Parent topic:** `Engines (Basic Random Number
         Generators) <engines-basic-random-number-generators.html>`__


   .. container::

