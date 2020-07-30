.. _onemkl_vm_atanh:

atanh
=====


.. container::


   Computes inverse hyperbolic tangent of vector elements.


   .. container:: section


      .. rubric:: Syntax
         :class: sectiontitle


      Buffer API:


      .. cpp:function:: event oneapi::mkl::vm::atanh(queue& exec_queue, int64_t n, buffer<T,1>& a, buffer<T,1>& y, uint64_t mode = oneapi::mkl::vm::mode::not_defined, oneapi::mkl::vm::error_handler<T> errhandler = {} )

      USM API:


      .. cpp:function:: event oneapi::mkl::vm::atanh(queue& exec_queue, int64_t n, T* a, T* y, vector_class<event> const & depends = {}, uint64_t mode = oneapi::mkl::vm::mode::not_defined, oneapi::mkl::vm::error_handler<T> errhandler = {} )

      ``atanh`` supports the following precisions.


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


   The atanh(a) function computes inverse hyperbolic tangent of vector
   elements.


   .. container:: tablenoborder


      .. list-table::
         :header-rows: 1

         * - Argument
           - Result
           - Error Code
         * - +1
           - +∞
           - ``oneapi::mkl::vm::status::sing``
         * - -1
           - -∞
           - ``oneapi::mkl::vm::status::sing``
         * - \|a\| > 1
           - QNAN
           - ``oneapi::mkl::vm::status::errdom``
         * - -∞
           - QNAN
           - ``oneapi::mkl::vm::status::errdom``
         * - +∞
           - +∞
           - ``oneapi::mkl::vm::status::errdom``
         * - QNAN
           - QNAN
           -  
         * - SNAN
           - QNAN
           -  




   .. container:: tablenoborder


      .. list-table::
         :header-rows: 1

         * - RE(a) i·IM(a)
           - -∞  
           - -X  
           - -0  
           - +0  
           - +X  
           - +∞  
           - NAN  
         * - +i·∞
           - -0+i·\ ``π``/2
           - -0+i·\ ``π``/2
           - -0+i·\ ``π``/2
           - +0+i·\ ``π``/2
           - +0+i·\ ``π``/2
           - +0+i·\ ``π``/2
           - +0+i·\ ``π``/2
         * - +i·Y
           - -0+i·\ ``π``/2
           -  
           -  
           -  
           -  
           - +0+i·\ ``π``/2
           - QNAN+i·QNAN
         * - +i·0
           - -0+i·\ ``π``/2
           -  
           - -0+i·0
           - +0+i·0
           -  
           - +0+i·\ ``π``/2
           - QNAN+i·QNAN
         * - -i·0
           - -0-i·\ ``π``/2
           -  
           - -0-i·0
           - +0-i·0
           -  
           - +0-i·\ ``π``/2
           - QNAN-i·QNAN
         * - -i·Y
           - -0-i·\ ``π``/2
           -  
           -  
           -  
           -  
           - +0-i·\ ``π``/2
           - QNAN+i·QNAN
         * - -i·∞
           - -0-i·\ ``π``/2
           - -0-i·\ ``π``/2
           - -0-i·\ ``π``/2
           - +0-i·\ ``π``/2
           - +0-i·\ ``π``/2
           - +0-i·\ ``π``/2
           - +0-i·\ ``π``/2
         * - +i·NAN
           - -0+i·QNAN
           - QNAN+i·QNAN
           - -0+i·QNAN
           - +0+i·QNAN
           - QNAN+i·QNAN
           - +0+i·QNAN
           - QNAN+i·QNAN




   Notes:


   - ``atanh(±1±i*0)=±∞±i*0``, and oneapi::mkl::vm::status::sing error is generated


   - ``atanh(CONJ(a))=CONJ(atanh(a))``


   - ``atanh(-a)=-atanh(a)``.


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


