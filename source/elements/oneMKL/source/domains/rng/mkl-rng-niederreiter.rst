.. _mkl-rng-niederreiter:

onemkl::rng::niederreiter
======================


.. container::


   Niederreiter quasi-random number generator [Bratley92], which works
   in arbitrary dimension.


   .. container:: section
      :name: GUID-753F13BA-A3C7-4F24-90F1-14B6279BD95C


      .. rubric:: Syntax
         :name: syntax
         :class: sectiontitle


      .. container:: dlsyntaxpara


         .. cpp:function::  class niederreiter :         internal::engine_base<niederreiter>{

         .. cpp:function::  public:

         .. cpp:function::  niederreiter (cl::sycl::queue& queue,         std::uint32_t dimensions)

         .. cpp:function::  niederreiter (cl::sycl::queue& queue,         std::vector<std::uint32_t> irred_polynomials)

         .. cpp:function::  niederreiter (const niederreiter& other)

         .. cpp:function::  niederreiter& operator=(const niederreiter&         other)

         .. cpp:function::  ~niederreiter()

         .. cpp:function::  }

         .. rubric:: Include Files
            :name: include-files
            :class: sectiontitle


         -  mkl_sycl.hpp


         .. rubric:: Description
            :name: description
            :class: sectiontitle


         Niederreiter quasi-random number generator
         [`Bratley92 <bibliography.html>`__],
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


   .. container::

