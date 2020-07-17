.. _onemkl_vm_cdfnorminv:

cdfnorminv
==========


.. container::


   Computes the inverse cumulative normal distribution function values
   of vector elements.


   .. container:: section


      .. rubric:: Syntax
         :class: sectiontitle


      Buffer API:


      .. cpp:function:: event oneapi::mkl::vm::cdfnorminv(queue& exec_queue, int64_t n, buffer<T,1>& a, buffer<T,1>& y, uint64_t mode = oneapi::mkl::vm::mode::not_defined, oneapi::mkl::vm::error_handler<T> errhandler = {} )

      USM API:


      .. cpp:function:: event oneapi::mkl::vm::cdfnorminv(queue& exec_queue, int64_t n, T* a, T* y, vector_class<event> const & depends = {}, uint64_t mode = oneapi::mkl::vm::mode::not_defined, oneapi::mkl::vm::error_handler<T> errhandler = {} )

      ``cdfnorminv`` supports the following precisions.


      .. list-table::
         :header-rows: 1

         * - T
         * - ``float``
         * - ``double``




.. container:: section


   .. rubric:: Description
      :class: sectiontitle


   The cdfnorminv(a) function computes the inverse cumulative normal
   distribution function values for elements of the input vector ``a``
   and writes them to the output vector ``y``.


   The inverse cumulative normal distribution function is defined as
   given by:


   |


   .. container:: imagecenter


      |image0|


   where cdfnorm(x) denotes the cumulative normal distribution function.


   Useful relations:


   |


   .. container:: imagecenter


      |image1|


   where erfinv(x)denotes the inverse error function and
   erfcinv(x)denotes the inverse complementary error functions.


   The following figure illustrates the relationships among erfinv
   family functions (erfinv, erfcinv, cdfnorminv).


   .. container:: figtop


      cdfnorminv Family Functions Relationship
      |


      .. container:: imagecenter


         |image2|


   Useful relations for these functions:


   |image3|


   |


   .. container:: imagecenter


      |image4|


   .. container:: tablenoborder


      .. list-table::
         :header-rows: 1

         * - Argument
           - Result
           - Error Code
         * - +0.5
           - +0
           -  
         * - +1
           - +∞
           - ``oneapi::mkl::vm::status::sing``
         * - -0
           - -∞
           - ``oneapi::mkl::vm::status::sing``
         * - +0
           - -∞
           - ``oneapi::mkl::vm::status::sing``
         * - a < -0
           - QNAN
           - ``oneapi::mkl::vm::status::errdom``
         * - a > +1
           - QNAN
           - ``oneapi::mkl::vm::status::errdom``
         * - +∞
           - QNAN
           - ``oneapi::mkl::vm::status::errdom``
         * - -∞
           - QNAN
           - ``oneapi::mkl::vm::status::errdom``
         * - QNAN
           - QNAN
           -  
         * - SNAN
           - QNAN
           -  




.. container:: section


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
      :ref:`onemkl_vm_setmode`
      function for possible values and their description. This is an
      optional parameter. The default value is ``oneapi::mkl::vm::mode::not_defined``.


   errhandler
      Sets local error handling mode for this function call. See the
      :ref:`onemkl_vm_create_error_handler`
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
      the :ref:`onemkl_vm_setmode`
      function for possible values and their description. This is an
      optional parameter. The default value is ``oneapi::mkl::vm::mode::not_defined``.


   errhandler
      Sets local error handling mode for this function call. See the
      :ref:`onemkl_vm_create_error_handler`
      function for arguments and their descriptions. This is an optional
      parameter. The local error handler is disabled by default.


.. container:: section


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


.. container:: familylinks


   .. container:: parentlink

      **Parent topic:** :ref:`onemkl_vm_mathematical_functions`



.. |image0| image:: ../equations/GUID-A3054E0D-CFC1-44E8-89F7-B5A232903EE9-low.jpg
   :class: .eq
.. |image1| image:: ../equations/GUID-CF961E8B-3127-4493-839A-C045E325BC42-low.jpg
.. |image2| image:: ../equations/GUID-8C1F2803-8F8F-4795-BF16-41856C6442CF-low.jpg
.. |image3| image:: ../equations/GUID-D4002137-8BA4-4D20-871B-550F2C6F9CE8-low.gif
   :class: .eq
.. |image4| image:: ../equations/GUID-CF961E8B-3127-4493-839A-C045E325BC42-low.jpg

