.. _mkl-rng-sfmt19937:

onemkl::rng::sfmt19937
======================


.. container::


   SIMD-oriented Fast Mersenne Twister pseudorandom number generator
   SFMT19937 [Saito08] with a period length equal to 2\ :sup:`19937`-1
   of the produced sequence.


   .. container:: section
      :name: GUID-753F13BA-A3C7-4F24-90F1-14B6279BD95C


      .. rubric:: Syntax
         :name: syntax
         :class: sectiontitle


      .. container:: dlsyntaxpara


         .. cpp:function::  class sfmt19937 :         internal::engine_base<sfmt19937>{

         .. cpp:function::  public:

         .. cpp:function::  sfmt19937 (cl::sycl::queue& queue,         std::uint32_t seed)

         .. cpp:function::  sfmt19937 (cl::sycl::queue& queue,         std::initializer_list<std::uint32_t> seed)

         .. cpp:function::  sfmt19937 (const sfmt19937& other)

         .. cpp:function::  sfmt19937& operator=(const sfmt19937& other)

         .. cpp:function::  ~sfmt19937()

         .. cpp:function::  }

         .. rubric:: Include Files
            :name: include-files
            :class: sectiontitle


         -  mkl_sycl.hpp


         .. rubric:: Description
            :name: description
            :class: sectiontitle


         SIMD-oriented Fast Mersenne Twister pseudorandom number
         generator SFMT19937
         [`Saito08 <bibliography.html>`__]
         with a period length equal to 2\ :sup:`19937`-1 of the produced
         sequence.


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
              -     Valid sycl queue, calls of onemkl::rng::generate()          routine submit kernels in this queue.   
            * -     seed    
              -     std::uint32_t /          std::initializer_list<std::uint32_t>   
              -     Initial conditions of the engine.    




         See `VS
         Notes <bibliography.html>`__ for
         detailed descriptions.


   .. container:: familylinks


      .. container:: parentlink


         **Parent topic:** `Engines (Basic Random Number
         Generators) <engines-basic-random-number-generators.html>`__


   
