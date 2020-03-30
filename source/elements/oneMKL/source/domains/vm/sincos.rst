
sincos
======


.. container::


   Computes sine and cosine of vector elements.


   .. container:: section
      :name: GUID-BFCA3F3F-F4E7-4E18-9C92-C219C41F5E3A


      .. rubric:: Syntax
         :class: sectiontitle


      Buffer API:


      .. cpp:function::  void sincos(queue& exec_queue, int64_t n,      buffer<T,1>& a, buffer<T,1>& y, buffer<T,1>& z, uint64_t mode =      mode::not_defined, error_handler<T> errhandler = {} )

      USM API:


      .. cpp:function::  event sincos(queue& exec_queue, int64_t n, T\* a,      T\* y, T\* z, vector_class<event>\* depends, uint64_t mode =      mode::not_defined, error_handler<T> errhandler = {} )

      ``sincos`` supports the following precisions.


      .. list-table:: 
         :header-rows: 1

         * -  T 
         * -  ``float`` 
         * -  ``double`` 




.. container:: section
   :name: GUID-B1D1E5EA-C097-4A5B-8671-EE84DB636AD6


   .. rubric:: Description
      :class: sectiontitle


   The sincos(a) function computes sine and cosine of vector elements.


   Note that arguments ``abs(a[i]) ≤ 213``\ and ``abs(a[i]) ≤ 216``\ for
   single and double precisions respectively are called fast
   computational path. These are trigonometric function arguments for
   which VM provides the best possible performance. Avoid arguments that
   do not belong to the fast computational path in the VM High Accuracy
   (HA) and Low Accuracy (LA) functions. Alternatively, you can use VM
   Enhanced Performance (EP) functions that are fast on the entire
   function domain. However, these functions provide less accuracy.


   .. container:: tablenoborder


      .. list-table:: 
         :header-rows: 1

         * -  Argument 
           -  Result 1 
           -  Result 2 
           -  Error Code 
         * -  +0 
           -  +0 
           -  +1 
           -    
         * -  -0 
           -  -0 
           -  +1 
           -    
         * -  +∞ 
           -  QNAN 
           -  QNAN 
           -  ``status::errdom`` 
         * -  -∞ 
           -  QNAN 
           -  QNAN 
           -  ``status::errdom`` 
         * -  QNAN 
           -  QNAN 
           -  QNAN 
           -    
         * -  SNAN 
           -  QNAN 
           -  QNAN 
           -    




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
      The buffer ``y`` containing the output sine vector of size ``n``.


   z
      The buffer ``z`` containing the output cosine vector of size
      ``n``.


   USM API:


   y
      Pointer ``y`` to the output sine vector of size ``n``.


   z
      The buffer ``z`` containing the output cosine vector of size
      ``n``.


   return value (event)
      Function end event.


.. container:: section
   :name: GUID-C97BF68F-B566-4164-95E0-A7ADC290DDE2


   .. rubric:: Example
      :class: sectiontitle


   An example of how to use sincos can be found in the oneMKL
   installation directory, under:


   ::


      examples/sycl/vml/vsincos.cpp


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** `Trigonometric
      Functions <trigonometric-functions.html>`__


