.. _sinh:

sinh
====


.. container::


   Computes hyperbolic sine of vector elements.


   .. container:: section
      :name: GUID-BDC2B01B-DF48-43AB-BD52-25BEDE8290D3


      .. rubric:: Syntax
         :name: syntax
         :class: sectiontitle


      Buffer API:


      .. cpp:function::  void sinh(queue& exec_queue, int64_t n,      buffer<T,1>& a, buffer<T,1>& y, uint64_t mode = mode::not_defined,      error_handler<T> errhandler = {} )

      USM API:


      .. cpp:function::  event sinh(queue& exec_queue, int64_t n, T\* a,      T\* y, vector_class<event>\* depends, uint64_t mode =      mode::not_defined, error_handler<T> errhandler = {} )

      ``sinh`` supports the following precisions.


      .. list-table:: 
         :header-rows: 1

         * -  T 
         * -  ``float`` 
         * -  ``double`` 
         * -  ``std::complex<float>`` 
         * -  ``std::complex<double>`` 




.. container:: section
   :name: GUID-9CA1335D-E846-4750-8710-177B8B025DD6


   .. rubric:: Description
      :name: description
      :class: sectiontitle


   The sinh(a) function computes hyperbolic sine of vector elements.


   .. container:: tablenoborder


      .. list-table:: 
         :header-rows: 1

         * -  Data Type 
           -  Threshold Limitations on Input Parameters 
         * -  single precision 
           -  ``-Log(FLT_MAX)-Log(2) <a[i] < Log(FLT_MAX)+Log(2)`` 
         * -  double precision 
           -  ``-Log(DBL_MAX)-Log(2) <a[i] < Log(DBL_MAX)+Log(2)`` 




   .. container:: tablenoborder


      .. list-table:: 
         :header-rows: 1

         * -  Argument 
           -  Result 
           -  Error Code 
         * -  +0 
           -  +0 
           -    
         * -  -0 
           -  -0 
           -    
         * -  a > overflow 
           -  +∞ 
           -  ``status::overflow`` 
         * -  a < -overflow 
           -  -∞ 
           -  ``status::overflow`` 
         * -  +∞ 
           -  +∞ 
           -    
         * -  -∞ 
           -  -∞ 
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
           -     -∞+i·QNAN    
           -     QNAN+i·QNAN    
           -     -0+i·QNAN    
           -     +0+i·QNAN    
           -     QNAN+i·QNAN    
           -     +∞+i·QNAN    
           -     QNAN+i·QNAN    
         * -  +i·Y 
           -     -∞·Cos(Y)+ i·∞·Sin(Y)    
           -    
           -    
           -    
           -    
           -     +∞·CIS(Y)    
           -     QNAN+i·QNAN    
         * -  +i·0 
           -     -∞+i·0    
           -    
           -  -0+i·0 
           -  +0+i·0 
           -    
           -     +∞+i·0    
           -     QNAN+i·0    
         * -  -i·0 
           -     -∞-i·0    
           -    
           -  -0-i·0 
           -  +0-i·0 
           -    
           -     +∞-i·0    
           -     QNAN-i·0    
         * -  -i·Y 
           -     -∞·Cos(Y)+ i·∞·Sin(Y)    
           -    
           -    
           -    
           -    
           -     +∞·CIS(Y)    
           -     QNAN+i·QNAN    
         * -  -i·∞ 
           -     -∞+i·QNAN    
           -     QNAN+i·QNAN    
           -     -0+i·QNAN    
           -     +0+i·QNAN    
           -     QNAN+i·QNAN    
           -     +∞+i·QNAN    
           -     QNAN+i·QNAN    
         * -  +i·NAN 
           -     -∞+i·QNAN    
           -     QNAN+i·QNAN    
           -     -0+i·QNAN    
           -     +0+i·QNAN    
           -     QNAN+i·QNAN    
           -     +∞+i·QNAN    
           -     QNAN+i·QNAN    




   Notes:


   -  The complex sinh(a) function sets the VM Error Status to
      status::overflow in the case of overflow, that is, when RE(a),
      IM(a) are finite non-zero numbers, but the real or imaginary part
      of the exact result is so large that it does not meet the target
      precision.


   -  ``sinh(CONJ(a))=CONJ(sinh(a))``


   -  ``sinh(-a)=-sinh(a)``.


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


   An example of how to use sinh can be found in the oneMKL installation
   directory, under:


   ::


      examples/sycl/vml/vsinh.cpp


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** `Hyperbolic
      Functions <hyperbolic-functions.html>`__


