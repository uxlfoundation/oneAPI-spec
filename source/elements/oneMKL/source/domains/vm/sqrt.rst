.. _sqrt:

sqrt
====


.. container::


   Computes a square root of vector elements.


   .. container:: section
      :name: GUID-EFEC353B-3FDA-45D7-BD63-76814D931C73


      .. rubric:: Syntax
         :name: syntax
         :class: sectiontitle


      Buffer API:


      .. cpp:function::  void sqrt(queue& exec_queue, int64_t n,      buffer<T,1>& a, buffer<T,1>& y, uint64_t mode = mode::not_defined,      error_handler<T> errhandler = {} )

      USM API:


      .. cpp:function::  event sqrt(queue& exec_queue, int64_t n, T\* a,      T\* y, vector_class<event>\* depends, uint64_t mode =      mode::not_defined, error_handler<T> errhandler = {} )

      ``sqrt`` supports the following precisions.


      .. list-table:: 
         :header-rows: 1

         * -  T 
         * -  ``float`` 
         * -  ``double`` 
         * -  ``std::complex<float>`` 
         * -  ``std::complex<double>`` 




.. container:: section
   :name: GUID-51B494BC-9297-4A34-86C2-349D9F30E076


   .. rubric:: Description
      :name: description
      :class: sectiontitle


   The sqrt function computes a square root of vector elements.


   .. container:: tablenoborder


      .. list-table:: 
         :header-rows: 1

         * -  Argument 
           -  Result 
           -  VM Error Status 
         * -  a< +0 
           -  QNAN 
           -  ``status::errdom`` 
         * -  +0 
           -  +0 
           -    
         * -  -0 
           -  -0 
           -    
         * -  -∞ 
           -  QNAN 
           -  ``status::errdom`` 
         * -  +∞ 
           -  +∞ 
           -    
         * -  QNAN 
           -  QNAN 
           -    
         * -  SNAN 
           -  QNAN 
           -    




   .. container:: tablenoborder


      .. list-table:: 
         :header-rows: 1

         * -  
           -  
           -  
           -  
           -  
           -  
           -  
           -  
         * -  +i·∞ 
           -  +∞+i·∞ 
           -  +∞+i·∞ 
           -  +∞+i·∞ 
           -  +∞+i·∞ 
           -  +∞+i·∞ 
           -  +∞+i·∞ 
           -  +∞+i·∞ 
         * -  +i·Y 
           -  +0+i·∞ 
           -    
           -    
           -    
           -    
           -  +∞+i·0 
           -  
         * -  +i·0 
           -  +0+i·∞ 
           -    
           -  +0+i·0 
           -  +0+i·0 
           -    
           -  +∞+i·0 
           -  
         * -  -i·0 
           -  +0-i·∞ 
           -    
           -  +0-i·0 
           -  +0-i·0 
           -    
           -  +∞-i·0 
           -  
         * -  -i·Y 
           -  +0-i·∞ 
           -    
           -    
           -    
           -    
           -  +∞-i·0 
           -  
         * -  -i·∞ 
           -  +∞-i·∞ 
           -  +∞-i·∞ 
           -  +∞-i·∞ 
           -  +∞-i·∞ 
           -  +∞-i·∞ 
           -  +∞-i·∞ 
           -  +∞-i·∞ 
         * -  +i·NAN 
           -  
           -  
           -  
           -  
           -  
           -  
           -  




   Notes:


   -  ``Sqrt(CONJ(z))=CONJ(Sqrt(z))``.


.. container:: section
   :name: GUID-8D31EE70-939F-4573-948A-01F1C3018531


   .. rubric:: Input Parameters
      :name: input-parameters
      :class: sectiontitle


   Buffer API:


   exec_queue
      The queue where the routine should be executed.


   n
      Specifies the number of elements to be calculated.


   a
      The buffer ``a`` containing input vector of size ``n``.


   mode
      Overrides the global VM mode setting for this function call. See
      `set_mode <setmode.html>`__
      function for possible values and their description. This is an
      optional parameter. The default value is ``mode::not_defined``.


   errhandler
      Sets local error handling mode for this function call. See the
      `create_error_handler <create_error_handler.html>`__
      function for arguments and their descriptions. This is an optional
      parameter. The local error handler is disabled by default.


   USM API:


   exec_queue
      The queue where the routine should be executed.


   n
      Specifies the number of elements to be calculated.


   a
      Pointer ``a`` to the 1st input vector of size ``n``.


   depends
      Vector of dependent events (to wait for input data to be ready).


   mode
      Overrides the global VM mode setting for this function call. See
      the `set_mode <setmode.html>`__
      function for possible values and their description. This is an
      optional parameter. The default value is ``mode::not_defined``.


   errhandler
      Sets local error handling mode for this function call. See the
      `create_error_handler <create_error_handler.html>`__
      function for arguments and their descriptions. This is an optional
      parameter. The local error handler is disabled by default.


.. container:: section
   :name: GUID-08546E2A-7637-44E3-91A3-814E524F5FB7


   .. rubric:: Output Parameters
      :name: output-parameters
      :class: sectiontitle


   Buffer API:


   y
      The buffer ``y`` containing the output vector of size ``n``.


   USM API:


   y
      Pointer ``y`` to the output vector of size ``n``.


   return value (event)
      Function end event.


.. container:: section
   :name: GUID-C97BF68F-B566-4164-95E0-A7ADC290DDE2


   .. rubric:: Example
      :name: example
      :class: sectiontitle


   An example of how to use sqrt can be found in the oneMKL installation
   directory, under:


   ::


      examples/sycl/vml/vsqrt.cpp


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** `Power and Root
      Functions <power-and-root-functions.html>`__


.. container::

