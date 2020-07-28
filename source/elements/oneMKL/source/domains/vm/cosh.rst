.. _onemkl_vm_cosh:

cosh
====


.. container::


   Computes hyperbolic cosine of vector elements.


   .. container:: section


      .. rubric:: Syntax
         :class: sectiontitle


      Buffer API:


      .. cpp:function:: event oneapi::mkl::vm::cosh(queue& exec_queue, int64_t n, buffer<T,1>& a, buffer<T,1>& y, uint64_t mode = oneapi::mkl::vm::mode::not_defined, oneapi::mkl::vm::error_handler<T> errhandler = {} )

      USM API:


      .. cpp:function:: event oneapi::mkl::vm::cosh(queue& exec_queue, int64_t n, T* a, T* y, vector_class<event> const & depends = {}, uint64_t mode = oneapi::mkl::vm::mode::not_defined, oneapi::mkl::vm::error_handler<T> errhandler = {} )

      ``cosh`` supports the following precisions.


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


   The cosh(a) function computes hyperbolic cosine of vector elements.


   .. container:: tablenoborder


      .. list-table::
         :header-rows: 1

         * - Data Type
           - Threshold Limitations on Input Parameters
         * - single precision
           - ``-Log(FLT_MAX)-Log2 <a[i] < Log(FLT_MAX)+Log2``
         * - double precision
           - ``-Log(DBL_MAX)-Log2 <a[i] < Log(DBL_MAX)+Log2``




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
         * - X > overflow
           - +∞
           - ``oneapi::mkl::vm::status::overflow``
         * - X < -overflow
           - +∞
           - ``oneapi::mkl::vm::status::overflow``
         * - +∞
           - +∞
           -  
         * - -∞
           - +∞
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
           - +∞+i·QNAN
           - QNAN+i·QNAN
           - QNAN-i·0
           - QNAN+i·0
           - QNAN+i·QNAN
           - +∞+i·QNAN
           - QNAN+i·QNAN
         * - +i·Y
           - +∞·Cos(Y)- i·∞·Sin(Y)
           -  
           -  
           -  
           -  
           - +∞·CIS(Y)
           - QNAN+i·QNAN
         * - +i·0
           - +∞-i·0
           -  
           - +1-i·0
           - +1+i·0
           -  
           - +∞+i·0
           - QNAN+i·0
         * - -i·0
           - +∞+i·0
           -  
           - +1+i·0
           - +1-i·0
           -  
           - +∞-i·0
           - QNAN-i·0
         * - -i·Y
           - +∞·Cos(Y)- i·∞·Sin(Y)
           -  
           -  
           -  
           -  
           - +∞·CIS(Y)
           - QNAN+i·QNAN
         * - -i·∞
           - +∞+i·QNAN
           - QNAN+i·QNAN
           - QNAN+i·0
           - QNAN-i·0
           - QNAN+i·QNAN
           - +∞+i·QNAN
           - QNAN+i·QNAN
         * - +i·NAN
           - +∞+i·QNAN
           - QNAN+i·QNAN
           - QNAN+i·QNAN
           - QNAN-i·QNAN
           - QNAN+i·QNAN
           - +∞+i·QNAN
           - QNAN+i·QNAN




   Notes:


   - The complex cosh(a) function sets the VM Error Status to
      oneapi::mkl::vm::status::overflow in the case of overflow, that is, when RE(a),
      IM(a) are finite non-zero numbers, but the real or imaginary part
      of the exact result is so large that it does not meet the target
      precision.


   - ``cosh(CONJ(a))=CONJ(cosh(a))``


   - ``cosh(-a)=cosh(a)``.


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


