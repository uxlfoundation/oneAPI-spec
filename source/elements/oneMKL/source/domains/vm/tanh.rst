.. _tanh:

tanh
====


.. container::


   Computes hyperbolic tangent of vector elements.


   .. container:: section
      :name: GUID-DAEB1EBF-EC01-4458-AB18-4D7D7B75B89D


      .. rubric:: Syntax
         :name: syntax
         :class: sectiontitle


      Buffer API:


      .. cpp:function::  void tanh(queue& exec_queue, int64_t n,      buffer<T,1>& a, buffer<T,1>& y, uint64_t mode = mode::not_defined      )

      USM API:


      .. cpp:function::  event tanh(queue& exec_queue, int64_t n, T\* a,      T\* y, vector_class<event>\* depends, uint64_t mode =      mode::not_defined )

      ``tanh`` supports the following precisions.


      .. list-table:: 
         :header-rows: 1

         * -  T 
         * -  ``float`` 
         * -  ``double`` 
         * -  ``std::complex<float>`` 
         * -  ``std::complex<double>`` 




.. container:: section
   :name: GUID-5AF8B657-65D9-4839-A32A-6D43FA7EC564


   .. rubric:: Description
      :name: description
      :class: sectiontitle


   The tanh(a) function computes hyperbolic tangent of vector elements.


   .. container:: tablenoborder


      .. list-table:: 
         :header-rows: 1

         * -  Argument 
           -  Result 
           -  Erro Code 
         * -  +0 
           -  +0 
           -    
         * -  -0 
           -  -0 
           -    
         * -  +∞ 
           -  +1 
           -    
         * -  -∞ 
           -  -1 
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

         * -  
           -  
           -  
           -  
           -  
           -  
           -  
           -  
         * -  +i·∞ 
           -     -1+i·0    
           -     QNAN+i·QNAN    
           -     QNAN+i·QNAN    
           -     QNAN+i·QNAN    
           -     QNAN+i·QNAN    
           -     +1+i·0    
           -     QNAN+i·QNAN    
         * -  +i·Y 
           -     -1+i·0·Tan(Y)    
           -    
           -    
           -    
           -    
           -     +1+i·0·Tan(Y)    
           -     QNAN+i·QNAN    
         * -  +i·0 
           -     -1+i·0    
           -    
           -     -0+i·0    
           -     +0+i·0    
           -    
           -     +1+i·0    
           -     QNAN+i·0    
         * -  -i·0 
           -     -1-i·0    
           -    
           -     -0-i·0    
           -     +0-i·0    
           -    
           -     +1-i·0    
           -     QNAN-i·0    
         * -  -i·Y 
           -     -1+i·0·Tan(Y)    
           -    
           -    
           -    
           -    
           -     +1+i·0·Tan(Y)    
           -     QNAN+i·QNAN    
         * -  -i·∞ 
           -     -1-i·0    
           -     QNAN+i·QNAN    
           -     QNAN+i·QNAN    
           -     QNAN+i·QNAN    
           -     QNAN+i·QNAN    
           -     +1-i·0    
           -     QNAN+i·QNAN    
         * -  +i·NAN 
           -     -1+i·0    
           -     QNAN+i·QNAN    
           -     QNAN+i·QNAN    
           -     QNAN+i·QNAN    
           -     QNAN+i·QNAN    
           -     +1+i·0    
           -     QNAN+i·QNAN    




   Notes:


   -  ``tanh(CONJ(a))=CONJ(tanh(a))``


   -  ``tanh(-a)=-tanh(a)``.


   The tanh(a) function does not generate any errors.


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


   An example of how to use tanh can be found in the oneMKL installation
   directory, under:


   ::


      examples/sycl/vml/vtanh.cpp


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** `Hyperbolic
      Functions <hyperbolic-functions.html>`__


.. container::

