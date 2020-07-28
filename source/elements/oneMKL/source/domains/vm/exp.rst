.. _onemkl_vm_exp:

exp
===


.. container::


   Computes an exponential of vector elements.


   .. container:: section


      .. rubric:: Syntax
         :class: sectiontitle


      Buffer API:


      .. cpp:function:: event oneapi::mkl::vm::exp(queue& exec_queue, int64_t n, buffer<T,1>& a, buffer<T,1>& y, uint64_t mode = oneapi::mkl::vm::mode::not_defined, oneapi::mkl::vm::error_handler<T> errhandler = {} )

      USM API:


      .. cpp:function:: event oneapi::mkl::vm::exp(queue& exec_queue, int64_t n, T* a, T* y, vector_class<event> const & depends = {}, uint64_t mode = oneapi::mkl::vm::mode::not_defined, oneapi::mkl::vm::error_handler<T> errhandler = {} )

      ``exp`` supports the following precisions.


      .. list-table::
         :header-rows: 1

         * - T
         * - ``float``
         * - ``double``
         * - ``std::complex<float>``
         * - ``std::complex<double>``




.. container:: section


   .. rubric:: Description
      :class: sectiontitle


   The exp(a) function computes an exponential of vector elements.


   .. container:: tablenoborder


      .. list-table::
         :header-rows: 1

         * - Data Type
           - Threshold Limitations on Input Parameters
         * - single precision
           - ``a[i] < Log( FLT_MAX )``
         * - double precision
           - ``a[i] < Log( DBL_MAX )``




   .. container:: tablenoborder


      .. list-table::
         :header-rows: 1

         * - Argument
           - Result
           - Error Code
         * - +0
           - +1
           -  
         * - -0
           - +1
           -  
         * - a > overflow
           - +∞
           - ``oneapi::mkl::vm::status::overflow``
         * - a < underflow
           - +0
           - ``oneapi::mkl::vm::status::overflow``
         * - +∞
           - +∞
           -  
         * - -∞
           - +0
           -  
         * - QNAN
           - QNAN
           -  
         * - SNAN
           - QNAN
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
         * - +i·∞
           -
           -
           -
           -
           -
           -
           -
         * - +i·Y
           -
           -  
           -  
           -  
           -  
           -
           -
         * - +i·0
           -
           -  
           -
           -
           -  
           -
           -
         * - -i·0
           -
           -  
           -
           -
           -  
           -
           -
         * - -i·Y
           -
           -  
           -  
           -  
           -  
           -
           -
         * - -i·∞
           -
           -
           -
           -
           -
           -
           -
         * - +i·NAN
           -
           -
           -
           -
           -
           -
           -




   Notes:


   - The complex exp(z) function sets the VM Error Status to
      oneapi::mkl::vm::status::overflow in the case of overflow, that is, when both RE(z)
      and IM(z) are finite non-zero numbers, but the real or imaginary
      part of the exact result is so large that it does not meet the
      target precision.


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


