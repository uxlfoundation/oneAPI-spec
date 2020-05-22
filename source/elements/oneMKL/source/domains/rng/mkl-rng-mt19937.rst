.. _mkl-rng-mt19937:

onemkl::rng::mt19937
====================


.. container::


   Mersenne Twister pseudorandom number generator MT19937 [Matsumoto98]
   with period length 2\ :sup:`19937`-1 of the produced sequence.


   .. container:: section
      :name: GUID-753F13BA-A3C7-4F24-90F1-14B6279BD95C


      .. rubric:: Syntax
         :class: sectiontitle


      .. container:: dlsyntaxpara


         ::
	    
           class mt19937 :         internal::engine_base<mt19937>{
           public:
            mt19937 (cl::sycl::queue& queue, std::uint32_t         seed)
            mt19937 (cl::sycl::queue& queue,         std::initializer_list<std::uint32_t> seed)
            mt19937 (const mt19937& other)
            mt19937& operator=(const mt19937& other)
            ~mt19937()
          }

         .. rubric:: Include Files
            :class: sectiontitle


         -  mkl_sycl.hpp


         .. rubric:: Description
            :class: sectiontitle


         Mersenne Twister pseudorandom number generator MT19937
         [`Matsumoto98 <bibliography.html>`__]
         with period length 2\ :sup:`19937`-1 of the produced sequence.


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
              -     std::uint32_t /          std::initializer_list<std::uint32_t>   
              -     Initial conditions of the engine.    




         See `VS
         Notes <bibliography.html>`__ for
         detailed descriptions.


   .. container:: familylinks


      .. container:: parentlink


         **Parent topic:** `Engines (Basic Random Number
         Generators) <engines-basic-random-number-generators.html>`__


   
