.. _tanpi:

tanpi
=====


.. container::


   Computes the tangent of vector elements multiplied by ``π``.


   .. container:: section
      :name: SYNTAX_86CD5B48F7F8421581B2186506AA2C36


      .. rubric:: Syntax
         :name: syntax
         :class: sectiontitle


      Buffer API:


      .. cpp:function::  void tanpi(queue& exec_queue, int64_t n,      buffer<T,1>& a, buffer<T,1>& y, uint64_t mode = mode::not_defined,      error_handler<T> errhandler = {} )

      USM API:


      .. cpp:function::  event tanpi(queue& exec_queue, int64_t n, T\* a,      T\* y, vector_class<event>\* depends, uint64_t mode =      mode::not_defined, error_handler<T> errhandler = {} )

      ``tanpi`` supports the following precisions.


      .. list-table:: 
         :header-rows: 1

         * -  T 
         * -  ``float`` 
         * -  ``double`` 




.. container:: section
   :name: GUID-DF8B717D-CDFE-441D-8B48-643A7DA97E03


   .. rubric:: Description
      :name: description
      :class: sectiontitle


   The tanpi(a) function computes the tangent of vector elements
   multiplied by ``π``. For an argument ``a``, the function computes
   tan(``π``\ \*\ ``a``).


   .. container:: tablenoborder


      .. list-table:: 
         :header-rows: 1

         * -  Argument 
           -  Result 
           -  Error Code 
         * -  +0 
           -  +0 
           -    
         * -  -0 
           -  +0 
           -    
         * -  ``n``, even integer 
           -  \*copysign(0.0, ``n``) 
           -    
         * -  ``n``, odd integer 
           -  \*copysign(0.0, -``n``) 
           -    
         * -  ``n`` + 0.5, for ``n`` even integer and ``n`` + 0.5       representable
           -  +∞ 
           -    
         * -  ``n`` + 0.5, for ``n`` odd integer and ``n`` + 0.5       representable
           -  -∞ 
           -    
         * -  +∞ 
           -  QNAN 
           -  ``status::errdom`` 
         * -  -∞ 
           -  QNAN 
           -  ``status::errdom`` 
         * -  QNAN 
           -  QNAN 
           -    
         * -  SNAN 
           -  QNAN 
           -    




   The copysign(``x``, ``y``) function returns the first vector argument
   ``x`` with the sign changed to match that of the second argument
   ``y``.


   If arguments abs(``a``\ :sub:`i`) ≤ 2 :sup:`13` for single precision
   or abs(``a``\ :sub:`i` ) ≤ 2 :sup:`67` for double precision, they
   belong to the *fast computational path*: arguments for which VM
   provides the best possible performance. Avoid arguments with do not
   belong to the fast computational path in VM High Accuracy (HA) or Low
   Accuracy (LA) functions. For arguments which do not belong to the
   fast computational path you can use VM Enhanced Performance (EP)
   functions, which are fast on the entire function domain. However,
   these functions provide lower accuracy.


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
      The buffer ``a`` containing input vector of size ``n``.


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
      Pointer ``a`` to the input vector of size ``n``.


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


   An example of how to use tanpi can be found in the oneMKL installation
   directory, under:


   ::


      examples/sycl/vml/vtanpi.cpp


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** `Trigonometric
      Functions <trigonometric-functions.html>`__


.. container::

