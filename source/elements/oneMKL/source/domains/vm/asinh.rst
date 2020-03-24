.. _asinh:

asinh
=====


.. container::


   Computes inverse hyperbolic sine of vector elements.


   .. container:: section
      :name: GUID-67342CEA-AD7E-48E2-B261-6D04E8B92313


      .. rubric:: Syntax
         :name: syntax
         :class: sectiontitle


      Buffer API:


      .. cpp:function::  void asinh(queue& exec_queue, int64_t n,      buffer<T,1>& a, buffer<T,1>& y, uint64_t mode = mode::not_defined      )

      USM API:


      .. cpp:function::  event asinh(queue& exec_queue, int64_t n, T\* a,      T\* y, vector_class<event>\* depends, uint64_t mode =      mode::not_defined )

      ``asinh`` supports the following precisions.


      .. list-table:: 
         :header-rows: 1

         * -  T 
         * -  ``float`` 
         * -  ``double`` 
         * -  ``std::complex<float>`` 
         * -  ``std::complex<double>`` 




.. container:: section
   :name: GUID-34F09044-BED2-4706-9B6A-3CE175D4C363


   .. rubric:: Description
      :name: description
      :class: sectiontitle


   The asinh(a) function computes inverse hyperbolic sine of vector
   elements.


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
           -  -0 
           -    
         * -  +∞ 
           -  +∞ 
           -    
         * -  -∞ 
           -  -∞ 
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
           -  -∞+i·\ ``π``/4 
           -  -∞+i·\ ``π``/2 
           -  +∞+i·\ ``π``/2 
           -  +∞+i·\ ``π``/2 
           -  +∞+i·\ ``π``/2 
           -  +∞+i·\ ``π``/4 
           -  +∞+i·QNAN 
         * -  +i·Y 
           -  -∞+i·0 
           -    
           -    
           -    
           -    
           -  +∞+i·0 
           -     QNAN+i·QNAN    
         * -  +i·0 
           -  +∞+i·0 
           -    
           -  +0+i·0 
           -  +0+i·0 
           -    
           -  +∞+i·0 
           -     QNAN+i·QNAN    
         * -  -i·0 
           -  -∞-i·0 
           -    
           -  -0-i·0 
           -  +0-i·0 
           -    
           -  +∞-i·0 
           -     QNAN-i·QNAN    
         * -  -i·Y 
           -  -∞-i·0 
           -    
           -    
           -    
           -    
           -  +∞-i·0 
           -     QNAN+i·QNAN    
         * -  -i·∞ 
           -  -∞-i·\ ``π``/4 
           -  -∞-i·\ ``π``/2 
           -  -∞-i·\ ``π``/2 
           -  +∞-i·\ ``π``/2 
           -  +∞-i·\ ``π``/2 
           -  +∞-i·\ ``π``/4 
           -  +∞+i·QNAN 
         * -  +i·NAN 
           -  -∞+i·QNAN 
           -     QNAN+i·QNAN    
           -     QNAN+i·QNAN    
           -     QNAN+i·QNAN    
           -     QNAN+i·QNAN    
           -  +∞+i·QNAN 
           -     QNAN+i·QNAN    




   The asinh(a) function does not generate any errors.


   Notes:


   -  ``asinh(CONJ(a))=CONJ(asinh(a))``


   -  ``asinh(-a)=-asinh(a)``.


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


   An example of how to use asinhcan be found in the oneMKL installation
   directory, under:


   ::


      examples/sycl/vml/vasinh.cpp


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** `Hyperbolic
      Functions <hyperbolic-functions.html>`__


.. container::

