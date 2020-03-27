.. _mkl-rng-mt2203:

onemkl::rng::mt2203
===================


.. container::


   Set of 6024 Mersenne Twister pseudorandom number generators MT2203
   [Matsumoto98], [Matsumoto00]. Each of them generates a sequence of
   period length equal to 2\ :sup:`2203`-1. Parameters of the generators
   provide mutual independence of the corresponding sequences..


   .. container:: section
      :name: GUID-753F13BA-A3C7-4F24-90F1-14B6279BD95C


      .. rubric:: Syntax
         :name: syntax
         :class: sectiontitle


      .. container:: dlsyntaxpara


         .. cpp:function::  class mt2203 : internal::engine_base<mt2203>{

         .. cpp:function::  public:

         .. cpp:function::  mt2203 (cl::sycl::queue& queue, std::uint32_t         seed, std::uint32_t engine_idx)

         .. cpp:function::  mt2203 (cl::sycl::queue& queue,         std::initializer_list<std::uint32_t> seed, std::uint32_t         engine_idx)

         .. cpp:function::  mt2203 (const mt2203& other)

         .. cpp:function::  mt2203& operator=(const mt2203& other)

         .. cpp:function::  ~mt2203()

         .. cpp:function::  }

         .. rubric:: Include Files
            :name: include-files
            :class: sectiontitle


         -  mkl_sycl.hpp


         .. rubric:: Description
            :name: description
            :class: sectiontitle


         Set of 6024 Mersenne Twister pseudorandom number generators
         MT2203
         [`Matsumoto98 <bibliography.html>`__],
         [`Matsumoto00 <bibliography.html>`__].
         Each of them generates a sequence of period length equal to
         2\ :sup:`2203`-1. Parameters of the generators provide mutual
         independence of the corresponding sequences..


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
              -     Index of the engine from the set (set contains 6024          basic generators).   




         See `VS
         Notes <bibliography.html>`__ for
         detailed descriptions.


   .. container:: familylinks


      .. container:: parentlink


         **Parent topic:** `Engines (Basic Random Number
         Generators) <engines-basic-random-number-generators.html>`__


   
