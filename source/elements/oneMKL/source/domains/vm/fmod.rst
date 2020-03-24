.. _fmod:

fmod
====


.. container::


   The fmod function performs element by element computation of the
   modulus function of vector ``a`` with respect to vector ``b``.


   .. container:: section
      :name: SYNTAX_64545149F3C747DD84C9C42A7CA69BFC


      .. rubric:: Syntax
         :name: syntax
         :class: sectiontitle


      Buffer API:


      .. cpp:function::  void fmod(queue& exec_queue, int64_t n,      buffer<T,1>& a, buffer<T,1>& b, buffer<T,1>& y, uint64_t mode =      mode::not_defined, error_handler<T> errhandler = {} )

      USM API:


      .. cpp:function::  event fmod( queue& exec_queue, int64_t n, T\* a,      T\* b, T\* y, uint64_t mode = mode::not_defined, error_handler<T>      errhandler = {} )

      ``fmod`` supports the following precisions.


      .. list-table:: 
         :header-rows: 1

         * -  T 
         * -  ``float`` 
         * -  ``double`` 




.. container:: section
   :name: GUID-A9A5BC7E-6DDF-47C7-8839-9623C6DA8469


   .. rubric:: Description
      :name: description
      :class: sectiontitle


   The fmod (a,b) function computes the modulus function of each element
   of vector ``a``, with respect to the corresponding elements of vector
   ``b``:


   ``ai - bi*trunc(ai/bi)``


   In general, the modulus function ``fmod (ai, bi)`` returns the value
   ``ai - n*bi`` for some integer ``n`` such that if ``b``\ :sub:`i` is
   nonzero, the result has the same sign as ``a``\ :sub:`i` and a
   magnitude less than the magnitude of ``b``\ :sub:`i`.


   .. container:: tablenoborder


      .. list-table:: 
         :header-rows: 1

         * -  Argument 1 
           -  Argument 2 
           -  Result 
           -  Error Code 
         * -  ``a`` not NAN 
           -  ±0 
           -  NAN 
           -  ``status::sing`` 
         * -  ±∞ 
           -  ``b`` not NAN 
           -  NAN 
           -  ``status::sing`` 
         * -  ±0 
           -  ``b``\ ≠ 0, not NAN 
           -  ±0 
           -    
         * -  ``a`` finite 
           -  ±∞ 
           -  ``a`` 
           -    
         * -  NAN 
           -  ``b`` 
           -    
           -    
         * -  ``a`` 
           -  NAN 
           -  NAN 
           -    




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


   An example of how to use fmodcan be found in the oneMKL installation
   directory, under:


   ::


      examples/sycl/vml/vfmod.cpp


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** `Arithmetic
      Functions <arithmetic-functions.html>`__


.. container::

