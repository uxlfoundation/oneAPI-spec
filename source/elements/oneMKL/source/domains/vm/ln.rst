.. _ln:

ln
==


.. container::


   Computes natural logarithm of vector elements.


   .. container:: section
      :name: GUID-8AB5FE38-A52D-44DE-BB89-865CC91BCEAF


      .. rubric:: Syntax
         :name: syntax
         :class: sectiontitle


      Buffer API:


      .. cpp:function::  void ln(queue& exec_queue, int64_t n,      buffer<T,1>& a, buffer<T,1>& y, uint64_t mode = mode::not_defined,      error_handler<T> errhandler = {} )

      USM API:


      .. cpp:function::  event ln(queue& exec_queue, int64_t n, T\* a, T\*      y, vector_class<event>\* depends, uint64_t mode =      mode::not_defined, error_handler<T> errhandler = {} )

      ``ln`` supports the following precisions.


      .. list-table:: 
         :header-rows: 1

         * -  T 
         * -  ``float`` 
         * -  ``double`` 
         * -  ``std::complex<float>`` 
         * -  ``std::complex<double>`` 




.. container:: section
   :name: GUID-CD893B76-7F70-46D2-BB55-631EA43FADDD


   .. rubric:: Description
      :name: description
      :class: sectiontitle


   The ln(a)function computes natural logarithm of vector elements.


   .. container:: tablenoborder


      .. list-table:: 
         :header-rows: 1

         * -  Argument 
           -  Result 
           -  Error Code 
         * -  +1 
           -  +0 
           -    
         * -  a <+0 
           -  QNAN 
           -  ``status::errdom`` 
         * -  +0 
           -  -∞ 
           -  ``status::sing`` 
         * -  -0 
           -  -∞ 
           -  ``status::sing`` 
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




   .. container:: tablenoborder


      .. list-table:: 
         :header-rows: 1

         * -     RE(a)      i·IM(a)    
           -     -∞           
           -     -X           
           -     -0           
           -     +0           
           -     +X           
           -     +∞           
           -     NAN           
         * -  +i·∞ 
           -  |image0| 
           -  +∞+i·\ ``π``/2 
           -  +∞+i·\ ``π``/2 
           -  +∞+i·\ ``π``/2 
           -  +∞+i·\ ``π``/2 
           -  +∞+i·\ ``π``/4 
           -     +∞+i·QNAN    
         * -  +i·Y 
           -  +∞-i·\ ``π`` 
           -    
           -    
           -    
           -    
           -  +∞+i·0 
           -     QNAN+i·QNAN    
         * -  +i·0 
           -  +∞-i·\ ``π`` 
           -    
           -  -∞+i·\ ``π`` 
           -  -∞-i·0 
           -    
           -  +∞+i·0 
           -     QNAN+i·QNAN    
         * -  -i·0 
           -  +∞-i·\ ``π`` 
           -    
           -  -∞+i·\ ``π`` 
           -  -∞-i·0 
           -    
           -  +∞-i·0 
           -     QNAN+i·QNAN    
         * -  -i·Y 
           -  +∞-i·\ ``π`` 
           -    
           -    
           -    
           -    
           -  +∞-i·0 
           -     QNAN+i·QNAN    
         * -  -i·∞ 
           -  |image1| 
           -  +∞-i·\ ``π``/2 
           -  +∞-i·\ ``π``/2 
           -  +∞-i·\ ``π``/2 
           -  +∞-i·\ ``π``/2 
           -  +∞-i·\ ``π``/4 
           -  +∞+i·QNAN 
         * -  +i·NAN 
           -     +∞+i·QNAN    
           -     QNAN+i·QNAN    
           -     QNAN+i·QNAN    
           -     QNAN+i·QNAN    
           -     QNAN+i·QNAN    
           -     +∞+i·QNAN    
           -     QNAN+i·QNAN    




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


   An example of how to use lncan be found in the oneMKL installation
   directory, under:


   ::


      examples/sycl/vml/vln.cpp


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** `Exponential and Logarithmic
      Functions <exponential-and-logarithmic-functions.html>`__


.. container::


.. |image0| image:: ../equations/GUID-6FB20CE7-1E2A-4340-995F-0E621DEF0E2D-low.jpg
.. |image1| image:: ../equations/GUID-0C4BC54F-4C29-4577-80AA-BCBCD291582A-low.jpg

