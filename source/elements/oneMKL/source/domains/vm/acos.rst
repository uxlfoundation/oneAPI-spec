
acos
====


.. container::


   Computes inverse cosine of vector elements.


   .. container:: section
      :name: GUID-F58A2419-0EA1-4E8E-9091-72FEA17B49FD


      .. rubric:: Syntax
         :class: sectiontitle


      Buffer API:


      .. cpp:function::  void acos(queue& exec_queue, int64_t n,      buffer<T,1>& a, buffer<T,1>& y, uint64_t mode = mode::not_defined,      error_handler<T> errhandler = {} )

      USM API:


      .. cpp:function::  event acos(queue& exec_queue, int64_t n, T\* a,      T\* y, vector_class<event>\* depends, uint64_t mode =      mode::not_defined, error_handler<T> errhandler = {} )

      ``acos`` supports the following precisions.


      .. list-table:: 
         :header-rows: 1

         * -  T 
         * -  ``float`` 
         * -  ``double`` 
         * -  ``std::complex<float>`` 
         * -  ``std::complex<double>`` 




.. container:: section
   :name: GUID-3F56F0D4-A10A-4FFA-B030-F9DF49326E62


   .. rubric:: Description
      :class: sectiontitle


   The acos(a) function computes inverse cosine of vector elements.


   .. container:: tablenoborder


      .. list-table:: 
         :header-rows: 1

         * -  Argument 
           -  Result 
           -  Error Code 
         * -  +0 
           -  +\ ``π``/2 
           -    
         * -  -0 
           -  +\ ``π``/2 
           -    
         * -  +1 
           -  +0 
           -    
         * -  -1 
           -  +\ ``π`` 
           -    
         * -  \|a\| > 1 
           -  QNAN 
           -  ``status::errdom`` 
         * -  +∞ 
           -  QNAN 
           -  ``status::errdom`` 
         * -  -∞ 
           -  QNAN 
           -  ``status::errdom`` 
         * -  QNAN 
           -  QNAN 
           -    
         * -  SNAN 
           -  QNAN 
           -    




   .. container:: tablenoborder


      .. list-table:: 
         :header-rows: 1

         * -     RE(a)      i·IM(a)    
           -     -∞           
           -     -X           
           -     -0           
           -     +0           
           -     +X           
           -     +∞           
           -     NAN           
         * -  +i·∞ 
           -  +3·\ ``π``/4-i·∞ 
           -  +\ ``π``/2-i·∞ 
           -  +\ ``π``/2-i·∞ 
           -  +\ ``π``/2-i·∞ 
           -  +\ ``π``/2-i·∞ 
           -  +\ ``π``/4-i·∞ 
           -  QNAN-i·∞ 
         * -  +i·Y 
           -  +\ ``π``-i·∞ 
           -    
           -    
           -    
           -    
           -  +0-i·∞ 
           -  QNAN+i·QNAN 
         * -  +i·0 
           -  +\ ``π``-i·∞ 
           -    
           -  +\ ``π``/2-i·0 
           -  +\ ``π``/2-i·0 
           -    
           -  +0-i·∞ 
           -  QNAN+i·QNAN 
         * -  -i·0 
           -  +\ ``π``\ +i·∞ 
           -    
           -  +\ ``π``/2+i·0 
           -  +\ ``π``/2+i·0 
           -    
           -  +0+i·∞ 
           -  QNAN+i·QNAN 
         * -  -i·Y 
           -  +\ ``π``\ +i·∞ 
           -    
           -    
           -    
           -    
           -  +0+i·∞ 
           -  QNAN+i·QNAN 
         * -  -i·∞ 
           -  +3\ ``π``/4+i·∞ 
           -  +\ ``π``/2+i·∞ 
           -  +\ ``π``/2+i·∞ 
           -  +\ ``π``/2+i·∞ 
           -  +\ ``π``/2+i·∞ 
           -  +\ ``π``/4+i·∞ 
           -  QNAN+i·∞ 
         * -  +i·NAN 
           -  QNAN+i·∞ 
           -  QNAN+i·QNAN 
           -  +\ ``π``/2+i·QNAN 
           -  +\ ``π``/2+i·QNAN 
           -  QNAN+i·QNAN 
           -  QNAN+i·∞ 
           -  QNAN+i·QNAN 




   Notes:


   -  ``acos(CONJ(a))=CONJ(acos(a))``.


.. container:: section
   :name: GUID-8D31EE70-939F-4573-948A-01F1C3018531


   .. rubric:: Input Parameters
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
      Pointer ``a`` to the input vector of size ``n``.


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
      :class: sectiontitle


   An example of how to use acos can be found in the oneMKL installation
   directory, under:


   ::


      examples/sycl/vml/vacos.cpp


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** `Trigonometric
      Functions <trigonometric-functions.html>`__


