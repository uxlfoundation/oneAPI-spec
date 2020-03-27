
sinpi
=====


.. container::


   Computes the sine of vector elements multiplied by ``π``.


   .. container:: section
      :name: SYNTAX_86CD5B48F7F8421581B2186506AA2C36


      .. rubric:: Syntax
         :class: sectiontitle


      Buffer API:


      .. cpp:function::  void sinpi(queue& exec_queue, int64_t n,      buffer<T,1>& a, buffer<T,1>& y, uint64_t mode = mode::not_defined,      error_handler<T> errhandler = {} )

      USM API:


      .. cpp:function::  event sinpi(queue& exec_queue, int64_t n, T\* a,      T\* y, vector_class<event>\* depends, uint64_t mode =      mode::not_defined, error_handler<T> errhandler = {} )

      ``sinpi`` supports the following precisions.


      .. list-table:: 
         :header-rows: 1

         * -  T 
         * -  ``float`` 
         * -  ``double`` 




.. container:: section
   :name: GUID-E91E43A7-AC3D-4B7B-B62F-DEEC45C2D291


   .. rubric:: Description
      :class: sectiontitle


   The sinpi(a) function computes the sine of vector elements multiplied
   by ``π``. For an argument ``a``, the function computes
   sin(``π``\ \*\ ``a``).


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
         * -  +\ ``n``, positive integer 
           -  +0 
           -    
         * -  -``n``, negative integer 
           -  -0 
           -    
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




   If arguments abs(``a``\ :sub:`i`) ≤ 2\ :sup:`22` for single precision
   or abs(``a``\ :sub:`i` ) ≤ 2\ :sup:`51` for double precision, they
   belong to the *fast computational path*: arguments for which VM
   provides the best possible performance. Avoid arguments which do not
   belong to the fast computational path in VM High Accuracy (HA) or Low
   Accuracy (LA) functions. For arguments which do not belong to the
   fast computational path you can use VM Enhanced Performance (EP)
   functions, which are fast on the entire function domain. However,
   these functions provide lower accuracy.


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


   An example of how to use sinpi can be found in the oneMKL installation
   directory, under:


   ::


      examples/sycl/vml/vsinpi.cpp


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** `Trigonometric
      Functions <trigonometric-functions.html>`__


