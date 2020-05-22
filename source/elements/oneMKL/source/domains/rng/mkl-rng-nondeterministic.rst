.. _mkl-rng-nondeterministic:

onemkl::rng::nondeterministic
=============================


.. container::


   Non-deterministic random number generator (RDRAND-based)
   [AVX][IntelSWMan].


   .. container:: section
      :name: GUID-753F13BA-A3C7-4F24-90F1-14B6279BD95C


      .. rubric:: Syntax
         :class: sectiontitle


      .. container:: dlsyntaxpara


         ::
	    
           class nondeterministic :         internal::engine_base<nondeterministic>{
           public:
             nondeterministic (cl::sycl::queue& queue)
             nondeterministic (const nondeterministic&         other)
             nondeterministic& operator=(const         nondeterministic& other)
             ~nondeterministic()
           }

         .. rubric:: Include Files
            :class: sectiontitle


         -  mkl_sycl.hpp


         .. rubric:: Description
            :class: sectiontitle


         Non-deterministic random number generator (RDRAND-based)
         [`AVX <bibliography.html>`__][`IntelSWMan <bibliography.html>`__].


         .. rubric:: Input Parameters
            :class: sectiontitle


         .. list-table:: 
            :header-rows: 1

            * -     Name    
              -     Type    
              -     Description    
            * -     queue    
              -     cl::sycl::queue    
              -     Valid cl::sycl::queue, calls of          onemkl::rng::generate() routine submits kernels in this         queue.   




         See `VS
         Notes <bibliography.html>`__ for
         detailed descriptions.


   .. container:: familylinks


      .. container:: parentlink


         **Parent topic:** `Engines (Basic Random Number
         Generators) <engines-basic-random-number-generators.html>`__


   
