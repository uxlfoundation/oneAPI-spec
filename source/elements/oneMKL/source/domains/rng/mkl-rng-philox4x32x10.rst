.. _mkl-rng-philox4x32x10:

onemkl::rng::philox4x32x10
==========================


.. container::


   A Philox4x32-10 counter-based pseudorandom number generator.
   [Salmon11].


   .. container:: section
      :name: GUID-753F13BA-A3C7-4F24-90F1-14B6279BD95C


      .. rubric:: Syntax
         :class: sectiontitle


      .. container:: dlsyntaxpara


         .. cpp:function::  class philox4x32x10 :         internal::engine_base<philox4x32x10>{

         .. cpp:function::  public:

         .. cpp:function::  philox4x32x10 (cl::sycl::queue& queue,         std::uint64_t seed)

         .. cpp:function::  philox4x32x10 (cl::sycl::queue& queue,         std::initializer_list<std::uint64_t> seed)

         .. cpp:function::  philox4x32x10 (const philox4x32x10& other)

         .. cpp:function::  philox4x32x10& operator=(const philox4x32x10&         other)

         .. cpp:function::  ~philox4x32x10()

         .. cpp:function::  }

         .. rubric:: Include Files
            :class: sectiontitle


         -  mkl_sycl.hpp


         .. rubric:: Description
            :class: sectiontitle


         A Philox4x32-10 counter-based pseudorandom number generator.
         [`Salmon11 <bibliography.html>`__].


         .. rubric:: Input Parameters
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
              -     std::uint64_t /          std::initializer_list<std::uint64_t>   
              -     Initial conditions of the generator state or engine          state.   




         See `VS
         Notes <bibliography.html>`__ for
         detailed descriptions.


   .. container:: familylinks


      .. container:: parentlink


         **Parent topic:** `Engines (Basic Random Number
         Generators) <engines-basic-random-number-generators.html>`__


   
