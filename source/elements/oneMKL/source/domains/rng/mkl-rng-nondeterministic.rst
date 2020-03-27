.. _mkl-rng-nondeterministic:

onemkl::rng::nondeterministic
=============================


.. container::


   Non-deterministic random number generator (RDRAND-based)
   [AVX][IntelSWMan].


   .. container:: section
      :name: GUID-753F13BA-A3C7-4F24-90F1-14B6279BD95C


      .. rubric:: Syntax
         :name: syntax
         :class: sectiontitle


      .. container:: dlsyntaxpara


         .. cpp:function::  class nondeterministic :         internal::engine_base<nondeterministic>{

         .. cpp:function::  public:

         .. cpp:function::  nondeterministic (cl::sycl::queue& queue)

         .. cpp:function::  nondeterministic (const nondeterministic&         other)

         .. cpp:function::  nondeterministic& operator=(const         nondeterministic& other)

         .. cpp:function::  ~nondeterministic()

         .. cpp:function::  }

         .. rubric:: Include Files
            :name: include-files
            :class: sectiontitle


         -  mkl_sycl.hpp


         .. rubric:: Description
            :name: description
            :class: sectiontitle


         Non-deterministic random number generator (RDRAND-based)
         [`AVX <bibliography.html>`__][`IntelSWMan <bibliography.html>`__].


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
              -     Valid cl::sycl::queue, calls of          onemkl::rng::generate() routine submits kernels in this         queue.   




         See `VS
         Notes <bibliography.html>`__ for
         detailed descriptions.


   .. container:: familylinks


      .. container:: parentlink


         **Parent topic:** `Engines (Basic Random Number
         Generators) <engines-basic-random-number-generators.html>`__


   .. container::

