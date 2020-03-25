.. _atanpi:

atanpi
======


.. container::


   Computes the inverse tangent of vector elements divided by ``π``.


   .. container:: section
      :name: SYNTAX_86CD5B48F7F8421581B2186506AA2C36


      .. rubric:: Syntax
         :name: syntax
         :class: sectiontitle


      Buffer API:


      .. cpp:function::  void atanpi(queue& exec_queue, int64_t n,      buffer<T,1>& a, buffer<T,1>& y, uint64_t mode = mode::not_defined      )

      USM API:


      .. cpp:function::  event atanpi(queue& exec_queue, int64_t n, T\* a,      T\* y, vector_class<event>\* depends, uint64_t mode =      mode::not_defined )

      ``atanpi`` supports the following precisions.


      .. list-table:: 
         :header-rows: 1

         * -  T 
         * -  ``float`` 
         * -  ``double`` 




.. container:: section
   :name: GUID-B54BFE44-523C-4869-9704-09BF8F77D46E


   .. rubric:: Description
      :name: description
      :class: sectiontitle


   The atanpi(a) function computes the inverse tangent of vector
   elements divided by ``π``. For an argument ``a``, the function
   computes atan(``a``)/``π``.


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
           -  +1/2 
           -    
         * -  -∞ 
           -  -1/2 
           -    
         * -  QNAN 
           -  QNAN 
           -    
         * -  SNAN 
           -  QNAN 
           -    




   The atanpi function does not generate any errors.


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


   An example of how to use atanpican be found in the oneMKL
   installation directory, under:


   ::


      examples/sycl/vml/vatanpi.cpp


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** `Trigonometric
      Functions <trigonometric-functions.html>`__


.. container::

