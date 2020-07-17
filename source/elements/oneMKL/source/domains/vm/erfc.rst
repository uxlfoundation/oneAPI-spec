.. _onemkl_vm_erfc:

erfc
====


.. container::


   Computes the complementary error function value of vector elements.


   .. container:: section


      .. rubric:: Syntax
         :class: sectiontitle


      Buffer API:


      .. cpp:function:: event oneapi::mkl::vm::erfc(queue& exec_queue, int64_t n, buffer<T,1>& a, buffer<T,1>& y, uint64_t mode = oneapi::mkl::vm::mode::not_defined, oneapi::mkl::vm::error_handler<T> errhandler = {} )

      USM API:


      .. cpp:function:: event oneapi::mkl::vm::erfc(queue& exec_queue, int64_t n, T* a, T* y, vector_class<event> const & depends = {}, uint64_t mode = oneapi::mkl::vm::mode::not_defined, oneapi::mkl::vm::error_handler<T> errhandler = {} )

      ``erfc`` supports the following precisions.


      .. list-table::
         :header-rows: 1

         * - T
         * - ``float``
         * - ``double``




.. container:: section


   .. rubric:: Description
      :class: sectiontitle


   The erfc function computes the complementary error function values
   for elements of the input vector ``a`` and writes them to the output
   vector ``y``.


   The complementary error function is defined as follows:


   |


   .. container:: imagecenter


      |image0|


   Useful relations:


   |image1|


   |image2|


   where


   |image3|


   is the cumulative normal distribution function.


   |image4|


   where ``Φ-1(x)`` and ``erf-1(x)`` are the inverses to ``Φ(x)`` and
   ``erf(x)``, respectively.


   The following figure illustrates the relationships among erf family
   functions (erf, erfc, cdfnorm).


   .. container:: figtop


      erfc Family Functions Relationship
      |


      .. container:: imagecenter


         |image5|


   Useful relations for these functions:


   |image6|


   |


   .. container:: imagecenter


      |image7|


   .. container:: tablenoborder


      .. list-table::
         :header-rows: 1

         * - Argument
           - Result
           - Error Code
         * - a > underflow
           - +0
           - ``oneapi::mkl::vm::status::underflow``
         * - +∞
           - +0
           -  
         * - -∞
           - +2
           -  
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



.. |image0| image:: ../equations/GUID-FB387120-1A86-45B9-BE20-97247EF0ABB5-low.gif
   :class: .eq
.. |image1| image:: ../equations/GUID-51FA6703-70D8-4D01-B7AB-A163F4CDFC94-low.jpg
   :class: .eq
.. |image2| image:: ../equations/GUID-41FCF9BC-28B7-4030-B904-1DBA03DD328C-low.gif
   :class: .eq
.. |image3| image:: ../equations/GUID-9A33FF12-964D-4450-949B-6AB7246435C7-low.gif
   :class: .eq
.. |image4| image:: ../equations/GUID-ABAAF79E-E46B-4053-8A64-9CC8B9C84A3F-low.jpg
   :class: .eq
.. |image5| image:: ../equations/GUID-0B9A59CC-C914-429D-AF87-93B16DABD291-low.jpg
.. |image6| image:: ../equations/GUID-02486559-84D2-4880-8EAB-2085A5BE2D10-low.jpg
   :class: .eq
.. |image7| image:: ../equations/GUID-7CA9B2F2-8D7C-4955-8EA8-D67616FB5B08-low.gif

