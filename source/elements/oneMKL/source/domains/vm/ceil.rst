
ceil
====


.. container::


   Computes an integer value rounded towards plus infinity for each
   vector element.


   .. container:: section
      :name: GUID-BC6BF105-11C2-491D-BDBF-1574EF510AA6


      .. rubric:: Syntax
         :class: sectiontitle


      Buffer API:


      .. cpp:function::  void ceil(queue& exec_queue, int64_t n,      buffer<T,1>& a, buffer<T,1>& y, uint64_t mode = mode::not_defined      )

      USM API:


      .. cpp:function::  event ceil(queue& exec_queue, int64_t n, T\* a,      T\* y, vector_class<event>\* depends, uint64_t mode =      mode::not_defined )

      ``ceil`` supports the following precisions.


      .. list-table:: 
         :header-rows: 1

         * -  T 
         * -  ``float`` 
         * -  ``double`` 




.. container:: section
   :name: GUID-4F4B28FA-937B-4966-8078-90DE0E5AB226


   .. rubric:: Description
      :class: sectiontitle


   The ceil(a) function computes an integer value rounded towards plus
   infinity for each vector element.


   | 
   | |image0|


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




   The ceil function does not generate any errors.


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


   An example of how to use ceil can be found in the oneMKL installation
   directory, under:


   ::


      examples/sycl/vml/vceil.cpp


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** `Rounding
      Functions <rounding-functions.html>`__



.. |image0| image:: ../equations/GUID-A3089763-5ACF-46DB-AFFF-197043DD5932-low.gif

