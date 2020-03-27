.. _pow:

pow
===


.. container::


   Computes ``a`` to the power ``b`` for elements of two vectors.


   .. container:: section
      :name: GUID-7DE07F1A-1D16-4E23-B1AB-9B798F71FD3B


      .. rubric:: Syntax
         :class: sectiontitle


      Buffer API:


      .. cpp:function::  void pow(queue& exec_queue, int64_t n,      buffer<T,1>& a, buffer<T,1>& b, buffer<T,1>& y, uint64_t mode =      mode::not_defined, error_handler<T> errhandler = {} )

      USM API:


      .. cpp:function::  event pow(queue& exec_queue, int64_t n, T\* a,      T\* b, T\* y, vector_class<event>\* depends, uint64_t mode =      mode::not_defined, error_handler<T> errhandler = {} )

      ``pow`` supports the following precisions.


      .. list-table:: 
         :header-rows: 1

         * -  T 
         * -  ``float`` 
         * -  ``double`` 
         * -  ``std::complex<float>`` 
         * -  ``std::complex<double>`` 




.. container:: section
   :name: GUID-C055D80E-FB98-4BCC-800D-FA894D3210A1


   .. rubric:: Description
      :class: sectiontitle


   The pow(a,b) function computes ``a`` to the power ``b`` for elements
   of two vectors.


   The real function pow has certain limitations on the input range of
   ``a`` and ``b`` parameters. Specifically, if ``a``\ [i] is positive,
   then ``b``\ [i] may be arbitrary. For negative ``a``\ [i], the value
   of ``b``\ [i] must be an integer (either positive or negative).


   The complex function pow has no input range limitations.


   .. container:: tablenoborder


      .. list-table:: 
         :header-rows: 1

         * -     Argument 1    
           -     Argument 2    
           -     Result    
           -     Error Code    
         * -  +0 
           -  neg. odd integer 
           -  +∞ 
           -  ``status::errdom`` 
         * -  -0 
           -  neg. odd integer 
           -  -∞ 
           -  ``status::errdom`` 
         * -  +0 
           -  neg. even integer 
           -  +∞ 
           -  ``status::errdom`` 
         * -  -0 
           -  neg. even integer 
           -  +∞ 
           -  ``status::errdom`` 
         * -  +0 
           -  neg. non-integer 
           -  +∞ 
           -  ``status::errdom`` 
         * -  -0 
           -  neg. non-integer 
           -  +∞ 
           -  ``status::errdom`` 
         * -  -0 
           -  pos. odd integer 
           -  +0 
           -    
         * -  -0 
           -  pos. odd integer 
           -  -0 
           -    
         * -  +0 
           -  pos. even integer 
           -  +0 
           -    
         * -  -0 
           -  pos. even integer 
           -  +0 
           -    
         * -  +0 
           -  pos. non-integer 
           -  +0 
           -    
         * -  -0 
           -  pos. non-integer 
           -  +0 
           -    
         * -  -1 
           -  +∞ 
           -  +1 
           -    
         * -  -1 
           -  -∞ 
           -  +1 
           -    
         * -  +1 
           -  any value 
           -  +1 
           -    
         * -  +1 
           -  +0 
           -  +1 
           -    
         * -  +1 
           -  -0 
           -  +1 
           -    
         * -  +1 
           -  +∞ 
           -  +1 
           -    
         * -  +1 
           -  -∞ 
           -  +1 
           -    
         * -  +1 
           -  QNAN 
           -  +1 
           -    
         * -  any value 
           -  +0 
           -  +1 
           -    
         * -  +0 
           -  +0 
           -  +1 
           -    
         * -  -0 
           -  +0 
           -  +1 
           -    
         * -  +∞ 
           -  +0 
           -  +1 
           -    
         * -  -∞ 
           -  +0 
           -  +1 
           -    
         * -  QNAN 
           -  +0 
           -  +1 
           -    
         * -  any value 
           -  -0 
           -  +1 
           -    
         * -  +0 
           -  -0 
           -  +1 
           -    
         * -  -0 
           -  -0 
           -  +1 
           -    
         * -  +∞ 
           -  -0 
           -  +1 
           -    
         * -  -∞ 
           -  -0 
           -  +1 
           -    
         * -  QNAN 
           -  -0 
           -  +1 
           -    
         * -  a < +0 
           -  non-integer 
           -  QNAN 
           -  ``status::errdom`` 
         * -  \|a\| < 1 
           -  -∞ 
           -  +∞ 
           -    
         * -  +0 
           -  -∞ 
           -  +∞ 
           -  ``status::errdom`` 
         * -  -0 
           -  -∞ 
           -  +∞ 
           -  ``status::errdom`` 
         * -  \|a\| > 1 
           -  -∞ 
           -  +0 
           -    
         * -  +∞ 
           -  -∞ 
           -  +0 
           -    
         * -  -∞ 
           -  -∞ 
           -  +0 
           -    
         * -  \|a\| < 1 
           -  +∞ 
           -  +0 
           -    
         * -  +0 
           -  +∞ 
           -  +0 
           -    
         * -  -0 
           -  +∞ 
           -  +0 
           -    
         * -  \|a\| > 1 
           -  +∞ 
           -  +∞ 
           -    
         * -  +∞ 
           -  +∞ 
           -  +∞ 
           -    
         * -  -∞ 
           -  +∞ 
           -  +∞ 
           -    
         * -  -∞ 
           -  neg. odd integer 
           -  -0 
           -    
         * -  -∞ 
           -  neg. even integer 
           -  +0 
           -    
         * -  -∞ 
           -  neg. non-integer 
           -  +0 
           -    
         * -  -∞ 
           -  pos. odd integer 
           -  -∞ 
           -    
         * -  -∞ 
           -  pos. even integer 
           -  +∞ 
           -    
         * -  -∞ 
           -  pos. non-integer 
           -  +∞ 
           -    
         * -  +∞ 
           -  b < +0 
           -  +0 
           -    
         * -  +∞ 
           -  b > +0 
           -  +∞ 
           -    
         * -  Big finite value\* 
           -  Big finite value\* 
           -  +/-∞ 
           -  ``status::overflow`` 
         * -  QNAN 
           -  QNAN 
           -  QNAN 
           -    
         * -  QNAN 
           -  SNAN 
           -  QNAN 
           -    
         * -  SNAN 
           -  QNAN 
           -  QNAN 
           -    
         * -  SNAN 
           -  SNAN 
           -  QNAN 
           -    




   \* Overflow in a real function is supported only in the HA/LA accuracy
   modes. The overflow occurs when x and y are finite numbers, but the
   result is too large to fit the target precision. In this case, the
   function:


   #. Returns ∞ in the result.


   #. Sets the VM Error Status to status::overflow.


   Overflow in a complex function occurs (supported in the HA/LA
   accuracy modes only) when all RE(x), RE(y), IM(x), IM(y) arguments
   are finite numbers, but the real or imaginary part of the computed
   result is so large that it does not fit the target precision. In this
   case, the function returns ∞ in that part of the result, and sets the
   VM Error Status to ``status::overflow`` (overriding any possible
   ``status::accuracy_warning`` status).


   The complex double precision versions of this function are
   implemented in the EP accuracy mode only. If used in HA or LA mode,
   the functions set the VM Error Status to
   ``status::accuracy_warning``.


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
      The buffer ``a`` containing 1st input vector of size ``n``.


   b
      The buffer ``b`` containing 2nd input vector of size ``n``.


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
      Pointer ``a`` to the 1st input vector of size ``n``.


   b
      Pointer ``b`` to the 2nd input vector of size ``n``.


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


   An example of how to use pow can be found in the oneMKL installation
   directory, under:


   ::


      examples/sycl/vml/vpow.cpp


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** `Power and Root
      Functions <power-and-root-functions.html>`__


