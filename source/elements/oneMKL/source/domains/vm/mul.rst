.. _mul:

mul
===


.. container::


   Performs element by element multiplication of vector ``a`` and vector
   ``b``.


   .. container:: section
      :name: GUID-D4DC8FD8-7FF6-4A4B-A62B-BC72EFB22136


      .. rubric:: Syntax
         :name: syntax
         :class: sectiontitle


      Buffer API:


      .. cpp:function::  void mul(queue& exec_queue, int64_t n,      buffer<T,1>& a, buffer<T,1>& b, buffer<T,1>& y, uint64_t mode =      mode::not_defined, error_handler<T> errhandler = {} )

      USM API:


      .. cpp:function::  event mul(queue& exec_queue, int64_t n, T\* a,      T\* b, T\* y, vector_class<event>\* depends, uint64_t mode =      mode::not_defined, error_handler<T> errhandler = {} )

      ``mul`` supports the following precisions.


      .. list-table:: 
         :header-rows: 1

         * -  T 
         * -  ``float`` 
         * -  ``double`` 
         * -  ``std::complex<float>`` 
         * -  ``std::complex<double>`` 




.. container:: section
   :name: GUID-CCDDF7AC-0DF5-48D3-B7BF-290C6A40D84F


   .. rubric:: Description
      :name: description
      :class: sectiontitle


   The mul(a, b) function performs element by element multiplication of
   vector ``a`` and vector ``b``.


   .. container:: tablenoborder


      .. list-table:: 
         :header-rows: 1

         * -  Argument 1 
           -  Argument 2 
           -  Result 
           -  Error Code 
         * -  +0 
           -  +0 
           -  +0 
           -    
         * -  +0 
           -  -0 
           -  -0 
           -    
         * -  -0 
           -  +0 
           -  -0 
           -    
         * -  -0 
           -  -0 
           -  +0 
           -    
         * -  +0 
           -  +∞ 
           -  QNAN 
           -    
         * -  +0 
           -  -∞ 
           -  QNAN 
           -    
         * -  -0 
           -  +∞ 
           -  QNAN 
           -    
         * -  -0 
           -  -∞ 
           -  QNAN 
           -    
         * -  +∞ 
           -  +0 
           -  QNAN 
           -    
         * -  +∞ 
           -  -0 
           -  QNAN 
           -    
         * -  -∞ 
           -  +0 
           -  QNAN 
           -    
         * -  -∞ 
           -  -0 
           -  QNAN 
           -    
         * -  +∞ 
           -  +∞ 
           -  +∞ 
           -    
         * -  +∞ 
           -  -∞ 
           -  -∞ 
           -    
         * -  -∞ 
           -  +∞ 
           -  -∞ 
           -    
         * -  -∞ 
           -  -∞ 
           -  +∞ 
           -    
         * -  SNAN 
           -  any value 
           -  QNAN 
           -    
         * -  any value 
           -  SNAN 
           -  QNAN 
           -    
         * -  QNAN 
           -  non-SNAN 
           -  QNAN 
           -    
         * -  non-SNAN 
           -  QNAN 
           -  QNAN 
           -    




   Specifications for special values of the complex functions are
   defined according to the following formula


   ``mul(x1+i*y1,x2+i*y2) = (x1*x2-y1*y2) + i*(x1*y2+y1*x2)``


   Overflow in a complex function occurs (supported in the HA/LA
   accuracy modes only) when all RE(x), RE(y), IM(x), IM(y) arguments
   are finite numbers, but the real or imaginary part of the computed
   result is so large that it does not fit the target precision. In this
   case, the function returns ∞ in that part of the result, and sets the
   VM Error Status to ``status::overflow`` (overriding any possible
   ``status::accuracy_warning`` status).


.. container:: section
   :name: GUID-8D31EE70-939F-4573-948A-01F1C3018531


   .. rubric:: Input Parameters
      :name: input-parameters
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
      :name: output-parameters
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
      :name: example
      :class: sectiontitle


   An example of how to use mulcan be found in the oneMKL installation
   directory, under:


   ::


      examples/sycl/vml/vmul.cpp


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** `Arithmetic
      Functions <arithmetic-functions.html>`__


.. container::

