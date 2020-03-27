.. _atanh:

atanh
=====


.. container::


   Computes inverse hyperbolic tangent of vector elements.


   .. container:: section
      :name: GUID-2CCDC84B-41CC-4B77-A2A9-504118A2C011


      .. rubric:: Syntax
         :name: syntax
         :class: sectiontitle


      Buffer API:


      .. cpp:function::  void atanh(queue& exec_queue, int64_t n,      buffer<T,1>& a, buffer<T,1>& y, uint64_t mode = mode::not_defined,      error_handler<T> errhandler = {} )

      USM API:


      .. cpp:function::  event atanh(queue& exec_queue, int64_t n, T\* a,      T\* y, vector_class<event>\* depends, uint64_t mode =      mode::not_defined, error_handler<T> errhandler = {} )

      ``atanh`` supports the following precisions.


      .. list-table:: 
         :header-rows: 1

         * -  T 
         * -  ``float`` 
         * -  ``double`` 
         * -  ``std::complex<float>`` 
         * -  ``std::complex<double>`` 




.. container:: section
   :name: GUID-3A64A0E2-3410-4737-BFF6-1B95BA6927E6


   .. rubric:: Description
      :name: description
      :class: sectiontitle


   The atanh(a) function computes inverse hyperbolic tangent of vector
   elements.


   .. container:: tablenoborder


      .. list-table:: 
         :header-rows: 1

         * -  Argument 
           -  Result 
           -  Error Code 
         * -  +1 
           -  +∞ 
           -  ``status::sing`` 
         * -  -1 
           -  -∞ 
           -  ``status::sing`` 
         * -  \|a\| > 1 
           -  QNAN 
           -  ``status::errdom`` 
         * -  -∞ 
           -  QNAN 
           -  ``status::errdom`` 
         * -  +∞ 
           -  +∞ 
           -  ``status::errdom`` 
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
           -  -0+i·\ ``π``/2 
           -  -0+i·\ ``π``/2 
           -  -0+i·\ ``π``/2 
           -  +0+i·\ ``π``/2 
           -  +0+i·\ ``π``/2 
           -  +0+i·\ ``π``/2 
           -  +0+i·\ ``π``/2 
         * -  +i·Y 
           -  -0+i·\ ``π``/2 
           -    
           -    
           -    
           -    
           -  +0+i·\ ``π``/2 
           -     QNAN+i·QNAN    
         * -  +i·0 
           -  -0+i·\ ``π``/2 
           -    
           -  -0+i·0 
           -  +0+i·0 
           -    
           -  +0+i·\ ``π``/2 
           -     QNAN+i·QNAN    
         * -  -i·0 
           -  -0-i·\ ``π``/2 
           -    
           -  -0-i·0 
           -  +0-i·0 
           -    
           -  +0-i·\ ``π``/2 
           -     QNAN-i·QNAN    
         * -  -i·Y 
           -  -0-i·\ ``π``/2 
           -    
           -    
           -    
           -    
           -  +0-i·\ ``π``/2 
           -     QNAN+i·QNAN    
         * -  -i·∞ 
           -  -0-i·\ ``π``/2 
           -  -0-i·\ ``π``/2 
           -  -0-i·\ ``π``/2 
           -  +0-i·\ ``π``/2 
           -  +0-i·\ ``π``/2 
           -  +0-i·\ ``π``/2 
           -  +0-i·\ ``π``/2 
         * -  +i·NAN 
           -     -0+i·QNAN    
           -     QNAN+i·QNAN    
           -     -0+i·QNAN    
           -     +0+i·QNAN    
           -     QNAN+i·QNAN    
           -     +0+i·QNAN    
           -     QNAN+i·QNAN    




   Notes:


   -  ``atanh(±1±i*0)=±∞±i*0``, and status::sing error is generated


   -  ``atanh(CONJ(a))=CONJ(atanh(a))``


   -  ``atanh(-a)=-atanh(a)``.


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


   An example of how to use atanh can be found in the oneMKL installation
   directory, under:


   ::


      examples/sycl/vml/vatanh.cpp


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** `Hyperbolic
      Functions <hyperbolic-functions.html>`__


.. container::

