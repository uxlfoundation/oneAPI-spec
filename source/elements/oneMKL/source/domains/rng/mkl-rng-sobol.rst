.. _mkl-rng-sobol:

onemkl::rng::sobol
==================


.. container::


   Sobol quasi-random number generator [Sobol76], [Bratley88], which
   works in arbitrary dimension.


   .. container:: section
      :name: GUID-753F13BA-A3C7-4F24-90F1-14B6279BD95C


      .. rubric:: Syntax
         :name: syntax
         :class: sectiontitle


      .. container:: dlsyntaxpara


         .. cpp:function::  class sobol : internal::engine_base<sobol>{

         .. cpp:function::  public:

         .. cpp:function::  sobol (cl::sycl::queue& queue, std::uint32_t         dimensions)

         .. cpp:function::  sobol (cl::sycl::queue& queue,         std::vector<std::uint32_t> direction_numbers)

         .. cpp:function::  sobol (const sobol& other)

         .. cpp:function::  sobol& operator=(const sobol& other)

         .. cpp:function::  ~sobol()

         .. cpp:function::  }

         .. rubric:: Include Files
            :name: include-files
            :class: sectiontitle


         -  mkl_sycl.hpp


         .. rubric:: Description
            :name: description
            :class: sectiontitle


         Sobol quasi-random number generator
         [`Sobol76 <bibliography.html>`__],
         [`Bratley88 <bibliography.html>`__],
         which works in arbitrary dimension.


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
            * -     dimensions    
              -     std::uint32_t     
              -     Number of dimensions.    
            * -     direction_numbers    
              -     std::vector<std::uint32_t>     
              -     User-defined direction numbers.    




         See `VS
         Notes <bibliography.html>`__ for
         detailed descriptions.


   .. container:: familylinks


      .. container:: parentlink


         **Parent topic:** `Engines (Basic Random Number
         Generators) <engines-basic-random-number-generators.html>`__


   .. container::

