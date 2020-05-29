.. _mkl-rng-niederreiter:

onemkl::rng::niederreiter
=========================


.. container::


   Niederreiter quasi-random number generator [Bratley92], which works
   in arbitrary dimension.


   .. container:: section
      :name: GUID-753F13BA-A3C7-4F24-90F1-14B6279BD95C


      .. rubric:: Syntax
         :class: sectiontitle


      .. container:: dlsyntaxpara


         ::
	    
           class niederreiter :         internal::engine_base<niederreiter>{
           public:
             niederreiter (cl::sycl::queue& queue,         std::uint32_t dimensions)
             niederreiter (cl::sycl::queue& queue,         std::vector<std::uint32_t> irred_polynomials)
             niederreiter (const niederreiter& other)
             niederreiter& operator=(const niederreiter&         other)
             ~niederreiter()
           }

         .. rubric:: Include Files
            :class: sectiontitle


         -  mkl_sycl.hpp


         .. rubric:: Description
            :class: sectiontitle


         Niederreiter quasi-random number generator
         [`Bratley92 <bibliography.html>`__],
         which works in arbitrary dimension.


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
            * -     dimensions    
              -     std::uint32_t     
              -     Number of dimensions.    
            * -     irred_polynomials    
              -     std::vector<std::uint32_t>     
              -     User-defined direction numbers.    




         See `VS
         Notes <bibliography.html>`__ for
         detailed descriptions.


   .. container:: familylinks


      .. container:: parentlink


         **Parent topic:** `Engines (Basic Random Number
         Generators) <engines-basic-random-number-generators.html>`__


   
