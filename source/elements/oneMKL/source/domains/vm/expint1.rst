.. _expint1:

expint1
=======


.. container::


   Computes the exponential integral of vector elements.


   .. container:: section
      :name: GUID-00E0B6DA-99CA-40FC-AD84-C9F08D78CD7B


      .. rubric:: Syntax
         :name: syntax
         :class: sectiontitle


      Buffer API:


      .. cpp:function::  void expint1(queue& exec_queue, int64_t n,      buffer<T,1>& a, buffer<T,1>& y, uint64_t mode = mode::not_defined,      error_handler<T> errhandler = {} )

      USM API:


      .. cpp:function::  event expint1(queue& exec_queue, int64_t n, T\*      a, T\* y, vector_class<event>\* depends, uint64_t mode =      mode::not_defined, error_handler<T> errhandler = {} )

      ``expint1`` supports the following precisions.


      .. list-table:: 
         :header-rows: 1

         * -  T 
         * -  ``float`` 
         * -  ``double`` 




.. container:: section
   :name: GUID-131CC04C-F0F5-48FB-83B3-EF2194D745C4


   .. rubric:: Description
      :name: description
      :class: sectiontitle


   The expint1(a) function computes the exponential integral of vector
   elements of the input vector ``a`` and writes them to the output
   vector ``y``.


   For positive real values ``x``, this can be written as:


   |image0|.


   For negative real values ``x``, the result is defined as NAN.


   .. container:: tablenoborder


      .. list-table:: 
         :header-rows: 1

         * -  Argument 
           -  Result 
           -  Error Code 
         * -  ``x`` < +0 
           -  QNAN 
           -  ``status::errdom`` 
         * -  +0 
           -  +∞ 
           -  ``status::sing`` 
         * -  -0 
           -  +∞ 
           -  ``status::sing`` 
         * -  +∞ 
           -  +0 
           -    
         * -  -∞ 
           -  QNAN 
           -  ``status::errdom`` 
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


   An example of how to use expint1can be found in the oneMKL
   installation directory, under:


   ::


      examples/sycl/vml/vexpint1.cpp


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** `Special
      Functions <special-functions.html>`__


.. container::


.. |image0| image:: ../equations/GUID-B229F6A5-0619-4F06-994B-8A734C356ee1.png
   :class: img-middle

