
powr
====


.. container::


   Computes ``a`` to the power ``b`` for elements of two vectors, where
   the elements of vector argument ``a`` are all non-negative.


   .. container:: section
      :name: SYNTAX_0ACC976C27864E859D5C4385DE3EBC25


      .. rubric:: Syntax
         :class: sectiontitle


      Buffer API:


      .. cpp:function::  void powr(queue& exec_queue, int64_t n,      buffer<T,1>& a, buffer<T,1>& b, buffer<T,1>& y, uint64_t mode =      mode::not_defined, error_handler<T> errhandler = {} )

      USM API:


      .. cpp:function::  event powr(queue& exec_queue, int64_t n, T* a,      T* b, T* y, vector_class<event>* depends, uint64_t mode =      mode::not_defined, error_handler<T> errhandler = {} )

      ``powr`` supports the following precisions.


      .. list-table:: 
         :header-rows: 1

         * -  T 
         * -  ``float`` 
         * -  ``double`` 




.. container:: section
   :name: GUID-4F551F28-28FE-4426-B33E-DFF1778B1FDC


   .. rubric:: Description
      :class: sectiontitle


   The powr(a,b) function raises each element of vector ``a`` by the
   corresponding element of vector ``b``. The elements of ``a`` are all
   nonnegative (``a``\ :sub:`i`\ ≥ 0).


   .. container:: tablenoborder


      .. list-table:: 
         :header-rows: 1

         * -  Data Type 
           -  Threshold Limitations on Input Parameters 
         * -  single precision 
           -  ``a``\ :sub:`i` < (FLT_MAX)\ :sup:`1/``b``\ i` 
         * -  double precision 
           -  ``a``\ :sub:`i` < (DBL_MAX)\ :sup:`1/``b``\ i` 




   Special values and VM Error Status treatment for v?Powr function are
   the same as for pow, unless otherwise indicated in this table:


   .. container:: tablenoborder


      .. list-table:: 
         :header-rows: 1

         * -  Argument 1 
           -  Argument 2 
           -  Result 
           -  Error Code 
         * -  ``a`` < 0 
           -  any value ``b`` 
           -  NAN 
           -  ``status::errdom`` 
         * -  0 < ``a`` < ∞ 
           -  ±0 
           -  1 
           -    
         * -  ±0 
           -  -∞ < ``b`` < 0 
           -  +∞ 
           -    
         * -  ±0 
           -  -∞ 
           -  +∞ 
           -    
         * -  ±0 
           -  ``b`` > 0 
           -  +0 
           -    
         * -  1 
           -  -∞ < ``b`` < ∞ 
           -  1 
           -    
         * -  ±0 
           -  ±0 
           -  NAN 
           -    
         * -  +∞ 
           -  ±0 
           -  NAN 
           -    
         * -  1 
           -  +∞ 
           -  NAN 
           -    
         * -  ``a``\ ≥ 0 
           -  NAN 
           -  NAN 
           -    
         * -  NAN 
           -  any value ``b`` 
           -  NAN 
           -    
         * -  0 < ``a`` <1 
           -  -∞ 
           -  +∞ 
           -    
         * -  ``a`` > 1 
           -  -∞ 
           -  +0 
           -    
         * -  0 ≤\ ``a`` < 1 
           -  +∞ 
           -  +0 
           -    
         * -  ``a`` > 1 
           -  +∞ 
           -  +∞ 
           -    
         * -  +∞ 
           -  ``b`` < +0 
           -  +0 
           -    
         * -  +∞ 
           -  ``b`` > +0 
           -  +∞ 
           -    
         * -  QNAN 
           -  QNAN 
           -  QNAN 
           -  ``status::errdom`` 
         * -  QNAN 
           -  SNAN 
           -  QNAN 
           -  ``status::errdom`` 
         * -  SNAN 
           -  QNAN 
           -  QNAN 
           -  ``status::errdom`` 
         * -  SNAN 
           -  SNAN 
           -  QNAN 
           -  ``status::errdom`` 




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
      The buffer ``a`` containing 1st input vector of size ``n``.


   b
      The buffer ``b`` containing 2nd input vector of size ``n``.


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


   An example of how to use powr can be found in the oneMKL installation
   directory, under:


   ::


      examples/sycl/vml/vpowr.cpp


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** `Power and Root
      Functions <power-and-root-functions.html>`__


