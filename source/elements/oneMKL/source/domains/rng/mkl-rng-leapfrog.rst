.. _mkl-rng-leapfrog:

onemkl::rng::leapfrog
=====================


.. container::


   Proceed state of engine using the leapfrog method.


   .. container:: section
      :name: GUID-7E060642-8D85-47BF-841A-A3132DF6D15E


      .. rubric:: Syntax
         :class: sectiontitle


      .. cpp:function::  template<typename EngineType>

      .. cpp:function::  void leapfrog (EngineType& engine, std::uint64_t      idx, std::uint64_t stride)

      .. rubric:: Include Files
         :class: sectiontitle


      -  ``mkl_sycl.hpp``


      .. rubric:: Input Parameters
         :class: sectiontitle


      .. list-table:: 
         :header-rows: 1

         * -     Name    
           -     Type    
           -     Description    
         * -     engine    
           -     \ ``EngineType``\     
           -      Object of engine class, which supports       leapfrog.   
         * -     idx    
           -     \ ``std::uint64_t``\     
           -     Index of the computational node.     
         * -     stride    
           -     \ ``std::uint64_t``\     
           -     Largest number of computational nodes, or stride.          




   .. container:: section
      :name: GUID-F50F8E51-3E2B-4A06-800B-BF54619FDBC6


      .. rubric:: Description
         :class: sectiontitle


      The onemkl::rng::leapfrog function generates random numbers in an
      engine with non-unit stride. This feature is particularly useful
      in distributing random numbers from the original stream across the
      stride buffers without generating the original random sequence
      with subsequent manual distribution.


      One of the important applications of the leapfrog method is
      splitting the original sequence into non-overlapping subsequences
      across stride computational nodes. The function initializes the
      original random stream (see `Figure "Leapfrog
      Method" <#SF_FIG10-1>`__) to generate random numbers for the
      computational node ``idx, 0 ≤idx < stride``, where ``stride`` is
      the largest number of computational nodes used.


      .. container:: figtop
         :name: SF_FIG10-1


         Leapfrog Method\ |image0|


      The leapfrog method is supported only for those basic generators
      that allow splitting elements by the leapfrog method, which is
      more efficient than simply generating them by a generator with
      subsequent manual distribution across computational nodes. See `VS
      Notes <bibliography.html>`__
      for details.


      The following code illustrates the initialization of three
      independent streams using the leapfrog method:


      .. container:: tbstyle(tblExampleStandard)


         .. rubric:: Code for Leapfrog Method
            :name: code-for-leapfrog-method
            :class: sectiontitle


         ::


            ...
            // Creating 3 identical engines
            onemkl::rng::mcg31m1 engine_1(queue, seed);


            onemkl::rng::mcg31m1 engine_2(queue, engine_1);
            onemkl::rng::mcg31m1 engine_3(queue, engine_1);




            // Leapfrogging the states of engines
            onemkl::rng::leapfrog(engine_1, 0 , 3);
            onemkl::rng::leapfrog(engine_2, 1 , 3);
            onemkl::rng::leapfrog(engine_3, 2 , 3);
            // Generating random numbers
            ...


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** `Service
      Routines <service-routines.html>`__



.. |image0| image:: ../equations/GUID-D90F2CB0-58B4-42F5-A1F9-FD1EA859DD44-low.png

