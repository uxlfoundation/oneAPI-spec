.. _nextafter:

nextafter
=========


.. container::


   Returns vector of elements containing the next representable
   floating-point values following the values from the elements of one
   vector in the direction of the corresponding elements of another
   vector.


   .. container:: section
      :name: SYNTAX_86CD5B48F7F8421581B2186506AA2C36


      .. rubric:: Syntax
         :name: syntax
         :class: sectiontitle


      Buffer API:


      .. cpp:function::  void nextafter( queue& exec_queue, int64_t n,      buffer<T,1>& a, buffer<T,1>& b, buffer<T,1>& y, uint64_t mode =      mode::not_defined, error_handler<T> errhandler = {} )

      USM API:


      .. cpp:function::  event nextafter( queue& exec_queue, int64_t n,      T\* a, T\* b, T\* y, vector_class<event>\* depends, uint64_t mode      = mode::not_defined, error_handler<T> errhandler = {} )

      ``nextafter`` supports the following precisions.


      .. list-table:: 
         :header-rows: 1

         * -  T 
         * -  ``float`` 
         * -  ``double`` 




.. container:: section
   :name: GUID-7C6C326E-17CF-4C11-8D82-C05385748AD3


   .. rubric:: Description
      :name: description
      :class: sectiontitle


   The nextafter(a,b) function returns a vector containing the next
   representable floating-point values following the first vector
   argument elements in the direction of the second vector argument's
   corresponding elements.


   .. container:: tablenoborder


      .. list-table:: 
         :header-rows: 1

         * -  Arguments/Results 
           -  Error Code 
         * -  Input vector argument element is ﬁnite and the corresponding       result vector element value is inﬁnite
           -  ``status::overflow`` 
         * -  Result vector element value is subnormal or zero, and       different from the corresponding input vector argument element
           -  ``status::underflow`` 




   Even though underﬂow or overﬂow canoccur, the returned value is
   independent of the current roundingdirection mode.


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


   An example of how to use nextaftercan be found in the oneMKL
   installation directory, under:


   ::


      examples/sycl/vml/vnextafter.cpp


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** `Miscellaneous VM
      Functions <miscellaneous-vm-functions.html>`__


.. container::

