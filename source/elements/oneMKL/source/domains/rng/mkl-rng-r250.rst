.. _mkl-rng-r250:

onemkl::rng::r250
=================


.. container::


   The 32-bit generalized feedback shift register pseudorandom number
   generator GFSR(250,103)[Kirkpatrick81].


   .. container:: section
      :name: GUID-753F13BA-A3C7-4F24-90F1-14B6279BD95C


      .. rubric:: Syntax
         :class: sectiontitle


      .. container:: dlsyntaxpara


         ::
	    
           class r250 : internal::engine_base<r250>{
           public:
             r250 (cl::sycl::queue& queue, std::uint32_t         seed)
             r250 (cl::sycl::queue& queue,         std::initializer_list<std::uint32_t> seed)
             r250 (const r250& other)
             r250& operator=(const r250& other)
             ~r250()
           }

         .. rubric:: Include Files
            :class: sectiontitle


         -  mkl_sycl.hpp


         .. rubric:: Description
            :class: sectiontitle


         The 32-bit generalized feedback shift register pseudorandom
         number generator GFSR(250,103)
         [`Kirkpatrick81 <bibliography.html>`__].


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


   
