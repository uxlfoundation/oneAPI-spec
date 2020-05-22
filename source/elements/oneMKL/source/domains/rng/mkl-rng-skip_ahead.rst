.. _mkl-rng-skip_ahead:

onemkl::rng::skip_ahead
=======================


.. container::


   Proceed state of engine by the skip-ahead method.


   .. container:: section
      :name: GUID-9E40F47F-122A-4194-A64E-786CD0A54B27


      .. rubric:: Syntax
         :class: sectiontitle


      The onemkl::rng::skip_ahead function supports the following
      interfaces to apply the skip-ahead method:


      -  Common interface


      -  Interface with a partitioned number of skipped elements


      **Common Interface**


      .. cpp:function::  template<typename EngineType> void skip_ahead (EngineType& engine,      std::uint64_t num_to_skip)

      **Interface with Partitioned Number of Skipped Elements**


      .. cpp:function::  template<typename EngineType> void skip_ahead (EngineType& engine,      std::initializer_list<std::uint64_t> num_to_skip)

      .. rubric:: Include Files
         :class: sectiontitle


      -  ``mkl_sycl.hpp``


      .. rubric:: Input Parameters
         :class: sectiontitle


      **Common Interface**


      .. list-table:: 
         :header-rows: 1

         * -     Name    
           -     Type    
           -     Description    
         * -     engine    
           -     \ ``EngineType``\     
           -      Object of engine class, which supports the       block-splitting method.   
         * -     num_to_skip    
           -     \ ``std::uint64_t``\     
           -     Number of skipped elements.     




      **Interface with Partitioned Number of Skipped Elements**


      .. list-table:: 
         :header-rows: 1

         * -     Name    
           -     Type    
           -     Description    
         * -     engine    
           -     \ ``EngineType``\     
           -      Object of engine class, which supports the       block-splitting method.   
         * -     num_to_skip    
           -     \ ``std::initializer_list<std::uint64_t``\     
           -     Partitioned number of skipped elements.     




   .. container:: section
      :name: GUID-425A6B4F-F9FE-4699-A3B2-16EDDF19B988


      .. rubric:: Description
         :class: sectiontitle


      The onemkl::rng::skip_ahead function skips a given number of elements
      in a random sequence provided by engine. This feature is
      particularly useful in distributing random numbers from original
      engine across different computational nodes. If the largest number
      of random numbers used by a computational node is num_to_skip,
      then the original random sequence may be split by
      onemkl::rng::skip_ahead into non-overlapping blocks of num_to_skip
      size so that each block corresponds to the respective
      computational node. The number of computational nodes is
      unlimited. This method is known as the block-splitting method or
      as the skip-ahead method. (see `Figure "Block-Splitting
      Method" <#SF_FIG10-2>`__).


      .. container:: figtop
         :name: SF_FIG10-2


         Block-Splitting Method\ |image0|


      The skip-ahead method is supported only for those basic generators
      that allow skipping elements by the skip-ahead method, which is
      more efficient than simply generating them by generator with
      subsequent manual skipping. See `VS
      Notes <bibliography.html>`__
      for details.


      Please note that for quasi-random basic generators the skip-ahead
      method works with components of quasi-random vectors rather than
      with whole quasi-random vectors. Therefore, to skip NS
      quasi-random vectors, set the num_to_skip parameter equal to the
      num_to_skip \*dim, where dim is the dimension of the quasi-random
      vector.


      When the number of skipped elements is greater than 2\ :sup:`63`
      the interface with the partitioned number of skipped elements is
      used. Prior calls to the function represent the number of skipped
      elements with the list of size ``n`` as shown below:


      ``num_to_skip``\ [0]+ ``num_to_skip``\ [1]*2\ :sup:`64`\ +
      ``num_to_skip``\ [2]\* 2\ :sup:`128`\ + …
      +\ ``num_to_skip``\ [n-1]*2\ :sup:`64*(n-1)` ;


      When the number of skipped elements is less than 2\ :sup:`63` both
      interfaces can be used.


      The following code illustrates how to initialize three independent
      streams using the onemkl::rng::skip_ahead function:


      .. container:: tbstyle(tblExampleStandard)


         .. rubric:: Code for Block-Splitting Method
            :name: code-for-block-splitting-method
            :class: sectiontitle


         ::


            ...
            // Creating 3 identical engines
            onemkl::rng::mcg31m1 engine_1(queue, seed);
            onemkl::rng::mcg31m1 engine_2(queue, engine_1);
            onemkl::rng::mcg31m1 engine_3(queue, engine_2);


            // Skipping ahead by 7 elements the 2nd engine
            onemkl::rng::skip_ahead(engine_2, 7);


            // Skipping ahead by 14 elements the 3nd engine
            onemkl::rng::skip_ahead(engine_3, 14);
            ...


      .. container:: tbstyle(tblExampleStandard)


         .. rubric:: Code for Block-Splitting Method with Partitioned
            Number of Elements
            :name: code-for-block-splitting-method-with-partitioned-number-of-elements
            :class: sectiontitle


         ::


            // Creating first engine 
            onemkl::rng::mrg32k3a engine_1(queue, seed);


            // To skip 2^64 elements in the random stream number of skipped elements should be
            /represented as num_to_skip = 2^64 = 0 + 1 * 2^64
            std::initializer_list<std::uint64_t> num_to_skip = {0, 1};




            // Creating the 2nd engine based on 1st. Skipping by 2^64
            onemkl::rng::mrg32k3a engine_2(queue, engine_1);
            onemkl::rng::skip_ahead(engine_2, num_to_skip);


            // Creating the 3rd engine based on 2nd. Skipping by 2^64
            onemkl::rng::mrg32k3a engine_3(queue, engine_2);
            onemkl::rng::skip_ahead(engine_3, num_to_skip);
            ...


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** `Service
      Routines <service-routines.html>`__



.. |image0| image:: ../equations/GUID-061AF9F8-B166-4154-9BF1-4E2C99F1CE1F-low.png

