.. _pow3o2:

pow3o2
======


.. container::


   Computes the square root of the cube of each vector element.


   .. container:: section
      :name: GUID-AA677C03-EE6E-4062-A2C0-D0B65DEAB664


      .. rubric:: Syntax
         :name: syntax
         :class: sectiontitle


      Buffer API:


      .. cpp:function::  void pow3o2(queue& exec_queue, int64_t n,      buffer<T,1>& a, buffer<T,1>& y, uint64_t mode = mode::not_defined,      error_handler<T> errhandler = {} )

      USM API:


      .. cpp:function::  event pow3o2(queue& exec_queue, int64_t n, T\* a,      T\* y, vector_class<event>\* depends, uint64_t mode =      mode::not_defined, error_handler<T> errhandler = {} )

      ``pow3o2`` supports the following precisions.


      .. list-table:: 
         :header-rows: 1

         * -  T 
         * -  ``float`` 
         * -  ``double`` 




.. container:: section
   :name: GUID-A99862AB-E105-4B47-B077-F619BA14E210


   .. rubric:: Description
      :name: description
      :class: sectiontitle


   The pow3o2(a)function computes the square root of the cube of each
   vector element.


   .. container:: tablenoborder


      .. list-table:: 
         :header-rows: 1

         * -  Data Type 
           -  Threshold Limitations on Input Parameters 
         * -  single precision 
           -  \|\ ``a``\ :sub:`i`\ \| < ``(FLT_MAX)``\ ``2/3`` 
         * -  double precision 
           -  \|\ ``a``\ :sub:`i`\ \| < ``(FLT_MAX)``\ ``2/3`` 




   .. container:: tablenoborder


      .. list-table:: 
         :header-rows: 1

         * -  Argument 
           -  Result 
           -  VM Error Status 
         * -  a < +0 
           -  QNAN 
           -  ``status::errdom`` 
         * -  +0 
           -  +0 
           -    
         * -  -0 
           -  -0 
           -    
         * -  -∞ 
           -  QNAN 
           -  ``status::errdom`` 
         * -  +∞ 
           -  +∞ 
           -    
         * -  QNAN 
           -  QNAN 
           -    
         * -  SNAN 
           -  QNAN 
           -    




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


   An example of how to use pow3o2can be found in the oneMKL
   installation directory, under:


   ::


      examples/sycl/vml/vpow3o2.cpp


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** `Power and Root
      Functions <power-and-root-functions.html>`__


.. container::

