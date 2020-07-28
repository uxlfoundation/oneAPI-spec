.. _onemkl_vm_fmod:

fmod
====


.. container::


   The fmod function performs element by element computation of the
   modulus function of vector ``a`` with respect to vector ``b``.


   .. container:: section


      .. rubric:: Syntax
         :class: sectiontitle


      Buffer API:


      .. cpp:function:: event oneapi::mkl::vm::fmod(queue& exec_queue, int64_t n, buffer<T,1>& a, buffer<T,1>& b, buffer<T,1>& y, uint64_t mode = oneapi::mkl::vm::mode::not_defined, oneapi::mkl::vm::error_handler<T> errhandler = {} )

      USM API:


      .. cpp:function:: event oneapi::mkl::vm::fmod( queue& exec_queue, int64_t n, T* a, T* b, T* y, vector_class<event> const & depends = {}, uint64_t mode = oneapi::mkl::vm::mode::not_defined, oneapi::mkl::vm::error_handler<T> errhandler = {} )

      ``fmod`` supports the following precisions.


      .. list-table::
         :header-rows: 1

         * - T
         * - ``float``
         * - ``double``




.. container:: section


   .. rubric:: Description
      :class: sectiontitle


   The fmod (a, b) function computes the modulus function of each element
   of vector ``a``, with respect to the corresponding elements of vector
   ``b``:


   ``ai - bi*trunc(ai/bi)``


   In general, the modulus function ``fmod (ai, bi)`` returns the value
   ``ai - n*bi`` for some integer ``n`` such that if ``b``\ :sub:`i` is
   nonzero, the result has the same sign as ``a``\ :sub:`i` and a
   magnitude less than the magnitude of ``b``\ :sub:`i`.


   .. container:: tablenoborder


      .. list-table::
         :header-rows: 1

         * - Argument 1
           - Argument 2
           - Result
           - Error Code
         * - ``a`` not NAN
           - ±0
           - NAN
           - ``oneapi::mkl::vm::status::sing``
         * - ±∞
           - ``b`` not NAN
           - NAN
           - ``oneapi::mkl::vm::status::sing``
         * - ±0
           - ``b``\ ≠ 0, not NAN
           - ±0
           -  
         * - ``a`` finite
           - ±∞
           - ``a``
           -  
         * - NAN
           - ``b``
           -  
           -  
         * - ``a``
           - NAN
           - NAN
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
      The buffer ``a`` containing 1st input vector of size ``n``.


   b
      The buffer ``b`` containing 2nd input vector of size ``n``.


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
      Pointer ``a`` to the 1st input vector of size ``n``.


   b
      Pointer ``b`` to the 2nd input vector of size ``n``.


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


