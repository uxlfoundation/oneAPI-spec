.. _powx:

powx
====


.. container::


   Computes vector ``a`` to the scalar power ``b``.


   .. container:: section
      :name: GUID-71AC966A-838E-47D1-9CA9-C0EDC80463D5


      .. rubric:: Syntax
         :class: sectiontitle


      Buffer API:


      .. cpp:function::  void powx(queue& exec_queue, int64_t n,      buffer<T,1>& a, T b, buffer<T,1>& y, uint64_t mode =      mode::not_defined, error_handler<T> errhandler = {} )

      USM API:


      .. cpp:function::  event powx(queue& exec_queue, int64_t n, T\* a, T      b, T\* y, vector_class<event>\* depends, uint64_t mode =      mode::not_defined, error_handler<T> errhandler = {} )

      ``powx`` supports the following precisions.


      .. list-table:: 
         :header-rows: 1

         * -  T 
         * -  ``float`` 
         * -  ``double`` 
         * -  ``std::complex<float>`` 
         * -  ``std::complex<double>`` 




.. container:: section
   :name: GUID-F3B0C52A-D11B-4954-AE5F-202C1B689A37


   .. rubric:: Description
      :class: sectiontitle


   The powx function computes ``a`` to the power ``b`` for a vector
   ``a`` and a scalar ``b``.


   The real function powx has certain limitations on the input range of
   ``a`` and ``b`` parameters. Specifically, if ``a``\ [i] is positive,
   then ``b`` may be arbitrary. For negative ``a``\ [i], the value of
   ``b`` must be an integer (either positive or negative).


   The complex function powx has no input range limitations.


   Special values and VM Error Status treatment are the same as for the
   pow function.


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
      Fixed value of power ``b``.


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
      Fixed value of power ``b``.


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


   An example of how to use powx can be found in the oneMKL installation
   directory, under:


   ::


      examples/sycl/vml/vpowx.cpp


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** `Power and Root
      Functions <power-and-root-functions.html>`__


