
exp
===


.. container::


   Computes an exponential of vector elements.


   .. container:: section
      :name: GUID-00F57D01-9DEC-4760-9E15-3F34947E08FC


      .. rubric:: Syntax
         :class: sectiontitle


      Buffer API:


      .. cpp:function::  void exp(queue& exec_queue, int64_t n,      buffer<T,1>& a, buffer<T,1>& y, uint64_t mode = mode::not_defined,      error_handler<T> errhandler = {} )

      USM API:


      .. cpp:function::  event exp(queue& exec_queue, int64_t n, T* a,      T* y, vector_class<event>* depends, uint64_t mode =      mode::not_defined, error_handler<T> errhandler = {} )

      ``exp`` supports the following precisions.


      .. list-table:: 
         :header-rows: 1

         * -  T 
         * -  ``float`` 
         * -  ``double`` 
         * -  ``std::complex<float>`` 
         * -  ``std::complex<double>`` 




.. container:: section
   :name: GUID-B0C816A4-40E7-4221-B809-E4C3030A2073


   .. rubric:: Description
      :class: sectiontitle


   The exp(a) function computes an exponential of vector elements.


   .. container:: tablenoborder


      .. list-table:: 
         :header-rows: 1

         * -  Data Type 
           -  Threshold Limitations on Input Parameters 
         * -  single precision 
           -  ``a[i] < Log( FLT_MAX )`` 
         * -  double precision 
           -  ``a[i] < Log( DBL_MAX )`` 




   .. container:: tablenoborder


      .. list-table:: 
         :header-rows: 1

         * -  Argument 
           -  Result 
           -  Error Code 
         * -  +0 
           -  +1 
           -    
         * -  -0 
           -  +1 
           -    
         * -  a > overflow 
           -  +∞ 
           -  ``status::overflow`` 
         * -  a < underflow 
           -  +0 
           -  ``status::overflow`` 
         * -  +∞ 
           -  +∞ 
           -    
         * -  -∞ 
           -  +0 
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
           -  
           -  
           -  
           -  
           -  
           -  
           -  
         * -  +i·Y 
           -  
           -    
           -    
           -    
           -    
           -  
           -  
         * -  +i·0 
           -  
           -    
           -  
           -  
           -    
           -  
           -  
         * -  -i·0 
           -  
           -    
           -  
           -  
           -    
           -  
           -  
         * -  -i·Y 
           -  
           -    
           -    
           -    
           -    
           -  
           -  
         * -  -i·∞ 
           -  
           -  
           -  
           -  
           -  
           -  
           -  
         * -  +i·NAN 
           -  
           -  
           -  
           -  
           -  
           -  
           -  




   Notes:


   -  The complex exp(z) function sets the VM Error Status to
      status::overflow in the case of overflow, that is, when both RE(z)
      and IM(z) are finite non-zero numbers, but the real or imaginary
      part of the exact result is so large that it does not meet the
      target precision.


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


   An example of how to use exp can be found in the oneMKL installation
   directory, under:


   ::


      examples/sycl/vml/vexp.cpp


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** `Exponential and Logarithmic
      Functions <exponential-and-logarithmic-functions.html>`__


