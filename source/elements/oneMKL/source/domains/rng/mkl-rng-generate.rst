.. _mkl-rng-generate:

onemkl::rng::generate
==================


.. container::


   Entry point to obtain random numbers from a given engine with proper
   statistics of a given distribution.


   .. container:: section
      :name: GUID-753F13BA-A3C7-4F24-90F1-14B6279BD95C


      .. rubric:: Syntax
         :name: syntax
         :class: sectiontitle


      Buffer API


      .. container:: dlsyntaxpara


         .. cpp:function::  template<typename T, method Method,         template<typename, method>class Distr, typename EngineType>

         .. cpp:function::  void generate (const Distr<T, Method>& distr,         EngineType& engine, const std::int64_t n, cl::sycl::buffer<T,         1>& r)

         USM API


         .. cpp:function::  template<typename T, method Method,         template<typename, method>class Distr, typename EngineType>

         .. cpp:function::  cl::sycl::event generate (const Distr<T,         Method>& distr, EngineType& engine, const std::int64_t n, T \*         r , const cl::sycl::vector_class<cl::sycl::event> &         dependencies)

         .. rubric:: Include Files
            :name: include-files
            :class: sectiontitle


         -  mkl_sycl.hpp


         .. rubric:: Input Parameters
            :name: input-parameters
            :class: sectiontitle


         .. list-table:: 
            :header-rows: 1

            * -     Name    
              -     Type    
              -     Description    
            * -     distr    
              -     const Distr<T, Method>    
              -     Distribution object. See          `Distributions <distributions.html>`__         for details.   
            * -     engine    
              -     EngineType    
              -     Engine object. See          `Engines <engines-basic-random-number-generators.html>`__         for details.   
            * -     n    
              -     const std::int64_t    
              -     Number of random values to be generated.    




      .. container:: section
         :name: GUID-AD3394E9-6864-4509-A178-6BA8CFB88A2C


         .. rubric:: Output Parameters
            :name: output-parameters
            :class: sectiontitle


         Buffer API


         .. list-table:: 
            :header-rows: 1

            * -     Name    
              -     Type    
              -     Description    
            * -     r    
              -     cl::sycl::buffer<T, 1>    
              -     cl::sycl::buffer\ ``r`` to the output          vector.   




         USM API


         .. list-table:: 
            :header-rows: 1

            * -     Name    
              -     Type    
              -     Description    
            * -     r    
              -     T\*    
              -     Pointer ``r`` to the output vector.    
            * -     event    
              -     cl::sycl::event    
              -     Function return event after submitting task in          cl::sycl::queue from the engine.   




         onemkl::rng::generate submits a kernel into a queue that is held
         by the engine and fills cl::sycl::buffer/T\* vector with n
         random numbers.


   .. container:: familylinks


      .. container:: parentlink


         **Parent topic:** `Generate
         Routine <generate-routine.html>`__


   .. container::

