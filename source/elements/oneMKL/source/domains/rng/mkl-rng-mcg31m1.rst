.. _mkl-rng-mcg31m1:

onemkl::rng::mcg31m1
====================


.. container::


   The 31-bit multiplicative congruential pseudorandom number generator
   MCG(1132489760, 231 -1) [L'Ecuyer99]


   .. container:: section
      :name: GUID-753F13BA-A3C7-4F24-90F1-14B6279BD95C


      .. rubric:: Syntax
         :class: sectiontitle


      .. container:: dlsyntaxpara


         ::
	    
           class mcg31m1 :         internal::engine_base<mcg31m1>{
           public:
             mcg31m1 (cl::sycl::queue& queue, std::uint32_t         seed)
             mcg31m1 (const mcg31m1& other)
             mcg31m1& operator=(const mcg31m1& other)
             ~mcg31m1()
           }

         .. rubric:: Include Files
            :class: sectiontitle


         -  mkl_sycl.hpp


         .. rubric:: Description
            :class: sectiontitle


         The 31-bit multiplicative congruential pseudorandom number
         generator MCG(1132489760, 231 -1)
         [`[L'Ecuyer99] <bibliography.html>`__].


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
              -     std::uint32_t     
              -     Initial conditions of the engine.    




         See `VS
         Notes <bibliography.html>`__ for
         detailed descriptions.


   .. container:: familylinks


      .. container:: parentlink


         **Parent topic:** `Engines (Basic Random Number
         Generators) <engines-basic-random-number-generators.html>`__


   
