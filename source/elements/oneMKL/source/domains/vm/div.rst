.. _onemkl_vm_div:

div
===


.. container::


   Performs element by element division of vector ``a`` by vector ``b``


   .. container:: section


      .. rubric:: Syntax
         :class: sectiontitle


      Buffer API:


      .. cpp:function:: event oneapi::mkl::vm::div(queue& exec_queue, int64_t n, buffer<T,1>& a, buffer<T,1>& b, buffer<T,1>& y, uint64_t mode = oneapi::mkl::vm::mode::not_defined, oneapi::mkl::vm::error_handler<T> errhandler = {} )

      USM API:


      .. cpp:function:: event oneapi::mkl::vm::div(queue& exec_queue, int64_t n, T* a, T* b, T* y, vector_class<event> const & depends = {}, uint64_t mode = oneapi::mkl::vm::mode::not_defined, oneapi::mkl::vm::error_handler<T> errhandler = {} )

      ``div`` supports the following precisions.


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


   The div(a, b) function performs element by element division of vector
   ``a`` by vector ``b``.


   .. container:: tablenoborder


      .. list-table::
         :header-rows: 1

         * - Argument 1
           - Argument 2
           - Result
           - VM Error Status
         * - X > +0
           - +0
           - +∞
           - ``oneapi::mkl::vm::status::sing``
         * - X > +0
           - -0
           - -∞
           - ``oneapi::mkl::vm::status::sing``
         * - X < +0
           - +0
           - -∞
           - ``oneapi::mkl::vm::status::sing``
         * - X < +0
           - -0
           - +∞
           - ``oneapi::mkl::vm::status::sing``
         * - +0
           - +0
           - QNAN
           - ``oneapi::mkl::vm::status::sing``
         * - -0
           - -0
           - QNAN
           - ``oneapi::mkl::vm::status::sing``
         * - X > +0
           - +∞
           - +0
           -  
         * - X > +0
           - -∞
           - -0
           -  
         * - +∞
           - +∞
           - QNAN
           -  
         * - -∞
           - -∞
           - QNAN
           -  
         * - QNAN
           - QNAN
           - QNAN
           -  
         * - SNAN
           - SNAN
           - QNAN
           -  




   Specifications for special values of the complex functions are
   defined according to the following formula


   ``Div(x1+i*y1, x2+i*y2) = (x1+i*y1)*(x2-i*y2)/(x2*x2+y2*y2)``.


   Overflow in a complex function occurs when ``x2+i*y2`` is not zero,
   x1, x2, y1, y2 are finite numbers, but the real or imaginary part of
   the exact result is so large that it does not fit the target
   precision. In that case, the function returns ∞ in that part of the
   result, and sets the VM Error Status to oneapi::mkl::vm::status::overflow.


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


