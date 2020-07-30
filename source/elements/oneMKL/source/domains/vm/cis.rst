.. _onemkl_vm_cis:

cis
===


.. container::


   Computes complex exponent of real vector elements (cosine and sine of
   real vector elements combined to complex value).


   .. container:: section


      .. rubric:: Syntax
         :class: sectiontitle


      Buffer API:


      .. cpp:function:: event oneapi::mkl::vm::cis(queue& exec_queue, int64_t n, buffer<T,1>& a, buffer<R,1>& y, uint64_t mode = oneapi::mkl::vm::mode::not_defined, oneapi::mkl::vm::error_handler<T> errhandler = {} )

      USM API:


      .. cpp:function:: event oneapi::mkl::vm::cis(queue& exec_queue, int64_t n, T* a, R* y, vector_class<event> const & depends = {}, uint64_t mode = oneapi::mkl::vm::mode::not_defined, oneapi::mkl::vm::error_handler<T> errhandler = {} )

      ``cis`` supports the following precisions.


      .. list-table::
         :header-rows: 1

         * - T
           - R
         * - ``float``
           - ``std::complex<float>``
         * - ``double``
           - ``std::complex<double>``




.. container:: section


   .. rubric:: Description
      :class: sectiontitle


   The cis(a) function computes complex exponent of real vector elements
   (cosine and sine of real vector elements combined to complex value).


   .. container:: tablenoborder


      .. list-table::
         :header-rows: 1

         * - Argument
           - Result
           - Error Code
         * - + 0
           - +1+i·0
           -  
         * - - 0
           - +1-i·0
           -  
         * - + ∞
           - QNAN+i·QNAN
           - ``oneapi::mkl::vm::status::errdom``
         * - - ∞
           - QNAN+i·QNAN
           - ``oneapi::mkl::vm::status::errdom``
         * - QNAN
           - QNAN+i·QNAN
           -  
         * - SNAN
           - QNAN+i·QNAN
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


