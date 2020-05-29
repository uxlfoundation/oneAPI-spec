.. _mkl-rng-ars5:

onemkl::rng::ars5
=================


.. container::


   ARS-5 counter-based pseudorandom number generator with a period of
   2\ :sup:`128`, which uses instructions from the AES-NI set
   ARS5[Salmon11].


   .. container:: section
      :name: GUID-753F13BA-A3C7-4F24-90F1-14B6279BD95C


      .. rubric:: Syntax
         :class: sectiontitle


      .. container:: dlsyntaxpara


		  
         ::
	    
             class ars5 : internal::engine_base<ars5>{
             public:
               ars5 (cl::sycl::queue& queue, std::uint64_t seed)
               ars5 (cl::sycl::queue& queue, std::initializer_list<std::uint64_t> seed)
               ars5 (const ars5& other)
               ars5& operator=(const ars5& other)
               ~ars5()
             }

         .. rubric:: Include Files
            :class: sectiontitle


         -  mkl_sycl.hpp


         .. rubric:: Description
            :class: sectiontitle


         ARS-5 counter-based pseudorandom number generator with a period
         of 2\ :sup:`128`, which uses instructions from the AES-NI set
         ARS5[`Salmon11 <bibliography.html>`__].


         .. rubric:: Input Parameters
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
              -     std::uint64_t /          std::initializer_list<std::uint64_t>   
              -     Initial conditions of the engine.    




         See `VS
         Notes <bibliography.html>`__ for
         detailed descriptions.


   .. container:: familylinks


      .. container:: parentlink


         **Parent topic:** `Engines (Basic Random Number
         Generators) <engines-basic-random-number-generators.html>`__


   
