
div
===


.. container::


   Performs element by element division of vector ``a`` by vector ``b``


   .. container:: section
      :name: GUID-C1A3E7BF-3B61-46CE-9B46-F0F370C0020B


      .. rubric:: Syntax
         :class: sectiontitle


      Buffer API:


      .. cpp:function::  void div(queue& exec_queue, int64_t n,      buffer<T,1>& a, buffer<T,1>& b, buffer<T,1>& y, uint64_t mode =      mode::not_defined, error_handler<T> errhandler = {} )

      USM API:


      .. cpp:function::  event div(queue& exec_queue, int64_t n, T* a,      T* b, T* y, vector_class<event>* depends, uint64_t mode =      mode::not_defined, error_handler<T> errhandler = {} )

      ``div`` supports the following precisions.


      .. list-table:: 
         :header-rows: 1

         * -  T 
         * -  ``float`` 
         * -  ``double`` 
         * -  ``std::complex<float>`` 
         * -  ``std::complex<double>`` 




.. container:: section
   :name: GUID-F80A505B-EB8E-4F49-A7BA-FA962EB04EA3


   .. rubric:: Description
      :class: sectiontitle


   The div(a,b) function performs element by element division of vector
   ``a`` by vector ``b``.


   .. container:: tablenoborder


      .. list-table:: 
         :header-rows: 1

         * -  Argument 1 
           -  Argument 2 
           -  Result 
           -  VM Error Status 
         * -  X > +0 
           -  +0 
           -  +∞ 
           -  ``status::sing`` 
         * -  X > +0 
           -  -0 
           -  -∞ 
           -  ``status::sing`` 
         * -  X < +0 
           -  +0 
           -  -∞ 
           -  ``status::sing`` 
         * -  X < +0 
           -  -0 
           -  +∞ 
           -  ``status::sing`` 
         * -  +0 
           -  +0 
           -  QNAN 
           -  ``status::sing`` 
         * -  -0 
           -  -0 
           -  QNAN 
           -  ``status::sing`` 
         * -  X > +0 
           -  +∞ 
           -  +0 
           -    
         * -  X > +0 
           -  -∞ 
           -  -0 
           -    
         * -  +∞ 
           -  +∞ 
           -  QNAN 
           -    
         * -  -∞ 
           -  -∞ 
           -  QNAN 
           -    
         * -  QNAN 
           -  QNAN 
           -  QNAN 
           -    
         * -  SNAN 
           -  SNAN 
           -  QNAN 
           -    




   Specifications for special values of the complex functions are
   defined according to the following formula


   ``Div(x1+i*y1,x2+i*y2) = (x1+i*y1)*(x2-i*y2)/(x2*x2+y2*y2)``.


   Overflow in a complex function occurs when ``x2+i*y2`` is not zero,
   x1, x2, y1, y2 are finite numbers, but the real or imaginary part of
   the exact result is so large that it does not fit the target
   precision. In that case, the function returns ∞ in that part of the
   result, and sets the VM Error Status to status::overflow.


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


   An example of how to use div can be found in the oneMKL installation
   directory, under:


   ::


      examples/sycl/vml/vdiv.cpp


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** `Power and Root
      Functions <power-and-root-functions.html>`__


