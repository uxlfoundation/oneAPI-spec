.. _onemkl_vm_sind:

sind
====


.. container::


   Computes the sine of vector elements multiplied by ``π``/180.


   .. container:: section


      .. rubric:: Syntax
         :class: sectiontitle


      Buffer API:


      .. cpp:function:: event oneapi::mkl::vm::sind(queue& exec_queue, int64_t n, buffer<T,1>& a, buffer<T,1>& y, uint64_t mode = oneapi::mkl::vm::mode::not_defined, oneapi::mkl::vm::error_handler<T> errhandler = {} )

      USM API:


      .. cpp:function:: event oneapi::mkl::vm::sind(queue& exec_queue, int64_t n, T* a, T* y, vector_class<event> const & depends = {}, uint64_t mode = oneapi::mkl::vm::mode::not_defined, oneapi::mkl::vm::error_handler<T> errhandler = {} )

      ``sind`` supports the following precisions.


      .. list-table::
         :header-rows: 1

         * - T
         * - ``float``
         * - ``double``




.. container:: section


   .. rubric:: Description
      :class: sectiontitle


   The sind(a) function is a degree argument trigonometric function. It
   computes the sine of vector elements multiplied by ``π``/180. For an
   argument ``a``, the function computes sin(``π``\ \*\ ``a``/180).


   Note that arguments abs(``a``\ :sub:`i`) ≤ 2\ :sup:`24` for single
   precision or abs(``a``\ :sub:`i` ) ≤ 2\ :sup:`52` for double
   precision, they belong to the *fast computational path*:
   trigonometric function arguments for which VM provides the best
   possible performance. Avoid arguments with do not belong to the fast
   computational path in VM High Accuracy (HA) or Low Accuracy (LA)
   functions. For arguments which do not belong to the fast
   computational path you can use VM Enhanced Performance (EP)
   functions, which are fast on the entire function domain. However,
   these functions provide lower accuracy.


   .. container:: tablenoborder


      .. list-table::
         :header-rows: 1

         * - Argument
           - Result
           - Error Code
         * - +0
           - +0
           -  
         * - -0
           - -0
           -  
         * - +∞
           - QNAN
           - ``oneapi::mkl::vm::status::errdom``
         * - -∞
           - QNAN
           - ``oneapi::mkl::vm::status::errdom``
         * - QNAN
           - QNAN
           -  
         * - SNAN
           - QNAN
           -  




.. container:: section


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
      :ref:`onemkl_vm_setmode`
      function for possible values and their description. This is an
      optional parameter. The default value is ``oneapi::mkl::vm::mode::not_defined``.


   errhandler
      Sets local error handling mode for this function call. See the
      :ref:`onemkl_vm_create_error_handler`
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
      the :ref:`onemkl_vm_setmode`
      function for possible values and their description. This is an
      optional parameter. The default value is ``oneapi::mkl::vm::mode::not_defined``.


   errhandler
      Sets local error handling mode for this function call. See the
      :ref:`onemkl_vm_create_error_handler`
      function for arguments and their descriptions. This is an optional
      parameter. The local error handler is disabled by default.


.. container:: section


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


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** :ref:`onemkl_vm_mathematical_functions`


