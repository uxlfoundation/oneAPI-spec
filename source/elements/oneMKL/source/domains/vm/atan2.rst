.. _atan2:

atan2
=====


.. container::


   Computes four-quadrant inverse tangent of elements of two vectors.


   .. container:: section
      :name: GUID-4EBD17B8-6907-4FBE-BDF9-51E9E13C57CE


      .. rubric:: Syntax
         :name: syntax
         :class: sectiontitle


      Buffer API:


      .. cpp:function::  void atan2(queue& exec_queue, int64_t n,      buffer<T,1>& a, buffer<T,1>& b, buffer<T,1>& y, uint64_t mode =      mode::not_defined )

      USM API:


      .. cpp:function::  event atan2(queue& exec_queue, int64_t n, T\* a,      T\* b, T\* y, vector_class<event>\* depends, uint64_t mode =      mode::not_defined )

      ``ad2d`` supports the following precisions.


      .. list-table:: 
         :header-rows: 1

         * -  T 
         * -  ``float`` 
         * -  ``double`` 




.. container:: section
   :name: GUID-D62F5991-3666-491A-A47D-8EFBD489F435


   .. rubric:: Description
      :name: description
      :class: sectiontitle


   The atan2(a,b) function computes four-quadrant inverse tangent of
   elements of two vectors.


   The elements of the output vector are computed as the four-quadrant
   arctangent of ``a[i] / b[i]``.


   .. container:: tablenoborder


      .. list-table:: 
         :header-rows: 1

         * -  Argument 1 
           -  Argument 2 
           -  Result 
           -  Error Code 
         * -  -∞ 
           -  -∞ 
           -  -3\*\ ``π``/4 
           -    
         * -  -∞ 
           -  b < +0 
           -  -``π``/2 
           -    
         * -  -∞ 
           -  -0 
           -  -``π``/2 
           -    
         * -  -∞ 
           -  +0 
           -  -``π``/2 
           -    
         * -  -∞ 
           -  b > +0 
           -  -``π``/2 
           -    
         * -  -∞ 
           -  +∞ 
           -  -``π``/4 
           -    
         * -  a < +0 
           -  -∞ 
           -  -``π`` 
           -    
         * -  a < +0 
           -  -0 
           -  -``π``/2 
           -    
         * -  a < +0 
           -  +0 
           -  -``π``/2 
           -    
         * -  a < +0 
           -  +∞ 
           -  -0 
           -    
         * -  -0 
           -  -∞ 
           -  -``π`` 
           -    
         * -  -0 
           -  b < +0 
           -  -``π`` 
           -    
         * -  -0 
           -  -0 
           -  -``π`` 
           -    
         * -  -0 
           -  +0 
           -  -0 
           -    
         * -  -0 
           -  b > +0 
           -  -0 
           -    
         * -  -0 
           -  +∞ 
           -  -0 
           -    
         * -  +0 
           -  -∞ 
           -  +\ ``π`` 
           -    
         * -  +0 
           -  b < +0 
           -  +\ ``π`` 
           -    
         * -  +0 
           -  -0 
           -  +\ ``π`` 
           -    
         * -  +0 
           -  +0 
           -  +0 
           -    
         * -  +0 
           -  b > +0 
           -  +0 
           -    
         * -  +0 
           -  +∞ 
           -  +0 
           -    
         * -  a > +0 
           -  -∞ 
           -  +\ ``π`` 
           -    
         * -  a > +0 
           -  -0 
           -  +\ ``π``/2 
           -    
         * -  a > +0 
           -  +0 
           -  +\ ``π``/2 
           -    
         * -  a > +0 
           -  +∞ 
           -  +0 
           -    
         * -  +∞ 
           -  -∞ 
           -  +3\*\ ``π``/4 
           -    
         * -  +∞ 
           -  b < +0 
           -  +\ ``π``/2 
           -    
         * -  +∞ 
           -  -0 
           -  +\ ``π``/2 
           -    
         * -  +∞ 
           -  +0 
           -  +\ ``π``/2 
           -    
         * -  +∞ 
           -  b > +0 
           -  +\ ``π``/2 
           -    
         * -  +∞ 
           -  +∞ 
           -  +\ ``π``/4 
           -    
         * -  a > +0 
           -  QNAN 
           -  QNAN 
           -    
         * -  a > +0 
           -  SNAN 
           -  QNAN 
           -    
         * -  QNAN 
           -  b > +0 
           -  QNAN 
           -    
         * -  SNAN 
           -  b > +0 
           -  QNAN 
           -    
         * -  QNAN 
           -  QNAN 
           -  QNAN 
           -    
         * -  QNAN 
           -  SNAN 
           -  QNAN 
           -    
         * -  SNAN 
           -  QNAN 
           -  QNAN 
           -    
         * -  SNAN 
           -  SNAN 
           -  QNAN 
           -    




   The atan2(a,b) function does not generate any errors.


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
      The buffer ``a`` containing 1st input vector of size ``n``.


   b
      The buffer ``b`` containing 2nd input vector of size ``n``.


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
      Pointer ``a`` to the 1st input vector of size ``n``.


   b
      Pointer ``b`` to the 2nd input vector of size ``n``.


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


   An example of how to use atan2can be found in the oneMKL installation
   directory, under:


   ::


      examples/sycl/vml/vatan2.cpp


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** `Trigonometric
      Functions <trigonometric-functions.html>`__


