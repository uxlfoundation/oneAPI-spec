
cis
===


.. container::


   Computes complex exponent of real vector elements (cosine and sine of
   real vector elements combined to complex value).


   .. container:: section
      :name: GUID-17081E6F-15C0-4E14-8B93-C1113AEC0663


      .. rubric:: Syntax
         :class: sectiontitle


      Buffer API:


      .. cpp:function::  void cis(queue& exec_queue, int64_t n,      buffer<T,1>& a, buffer<T,1>& y, uint64_t mode = mode::not_defined,      error_handler<T> errhandler = {} )

      USM API:


      .. cpp:function::  event cis(queue& exec_queue, int64_t n, A\* a,      R\* y, vector_class<event>\* depends, uint64_t mode =      mode::not_defined, error_handler<T> errhandler = {} )

      ``cis`` supports the following precisions.


      .. list-table:: 
         :header-rows: 1

         * -  T 
           -  R 
         * -  ``float`` 
           -  ``std::complex<float>`` 
         * -  ``double`` 
           -  ``std::complex<double>`` 




.. container:: section
   :name: GUID-7D4F56C4-F5E9-4AA9-8D7B-04CE2ED6584A


   .. rubric:: Description
      :class: sectiontitle


   The cis(a) function computes complex exponent of real vector elements
   (cosine and sine of real vector elements combined to complex value).


   .. container:: tablenoborder


      .. list-table:: 
         :header-rows: 1

         * -     Argument    
           -     Result    
           -     Error Code    
         * -     + 0    
           -     +1+i·0    
           -    
         * -     - 0    
           -     +1-i·0    
           -    
         * -     + ∞    
           -     QNAN+i·QNAN    
           -  ``status::errdom`` 
         * -     - ∞    
           -     QNAN+i·QNAN    
           -  ``status::errdom`` 
         * -     QNAN    
           -     QNAN+i·QNAN    
           -    
         * -     SNAN    
           -     QNAN+i·QNAN    
           -    




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


   An example of how to use cis can be found in the oneMKL installation
   directory, under:


   ::


      examples/sycl/vml/vcis.cpp


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** `Trigonometric
      Functions <trigonometric-functions.html>`__


