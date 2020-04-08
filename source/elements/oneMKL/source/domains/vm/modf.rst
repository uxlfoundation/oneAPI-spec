
modf
====


.. container::


   Computes a truncated integer value and the remaining fraction part
   for each vector element.


   .. container:: section
      :name: GUID-F66BB36F-D7BF-4EEC-A9E7-A4666E85A1FA


      .. rubric:: Syntax
         :class: sectiontitle


      Buffer API:


      .. cpp:function::  void modf(queue& exec_queue, int64_t n,      buffer<T,1>& a, buffer<T,1>& y, buffer<T,1>& z, uint64_t mode =      mode::not_defined )

      USM API:


      .. cpp:function::  event modf(queue& exec_queue, int64_t n, T* a,      T* y, T* z, vector_class<event>* depends, uint64_t mode =      mode::not_defined )

      ``modf`` supports the following precisions.


      .. list-table:: 
         :header-rows: 1

         * -  T 
         * -  ``float`` 
         * -  ``double`` 




.. container:: section
   :name: GUID-F4792591-FD2F-45ED-AF28-7C03E3030B81


   .. rubric:: Description
      :class: sectiontitle


   The modf(a) function computes a truncated integer value and the
   remaining fraction part for each vector element.


   | 
   | |image0|


   .. container:: tablenoborder


      .. list-table:: 
         :header-rows: 1

         * -  Argument 
           -  Result 1 
           -  Result 2 
           -  Error Code 
         * -  +0 
           -  +0 
           -  +0 
           -    
         * -  -0 
           -  -0 
           -  -0 
           -    
         * -  +∞ 
           -  +∞ 
           -  +0 
           -    
         * -  -∞ 
           -  -∞ 
           -  -0 
           -    
         * -  SNAN 
           -  QNAN 
           -  QNAN 
           -    
         * -  QNAN 
           -  QNAN 
           -  QNAN 
           -    




   The modf function does not generate any errors.


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
      :class: sectiontitle


   Buffer API:


   y
      The buffer ``y`` containing the output vector of size ``n`` for
      truncated integer values.


   z
      The buffer ``z`` containing the output vector of size ``n`` for
      remaining fraction parts.


   USM API:


   y
      Pointer ``y`` to the output vector of size ``n`` for truncated
      integer values.


   z
      Pointer ``z`` to the output vector of size ``n`` for remaining
      fraction parts.


   return value (event)
      Function end event.


.. container:: section
   :name: GUID-C97BF68F-B566-4164-95E0-A7ADC290DDE2


   .. rubric:: Example
      :class: sectiontitle


   An example of how to use modf can be found in the oneMKL installation
   directory, under:


   ::


      examples/sycl/vml/vmodf.cpp


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** `Rounding
      Functions <rounding-functions.html>`__



.. |image0| image:: ../equations/GUID-38C12345-5E6E-4D94-8072-460502CB52EC-low.gif

