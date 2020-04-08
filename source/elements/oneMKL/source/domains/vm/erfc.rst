
erfc
====


.. container::


   Computes the complementary error function value of vector elements.


   .. container:: section
      :name: GUID-0CFCF122-275C-4778-A86A-4F9E6DD81EBC


      .. rubric:: Syntax
         :class: sectiontitle


      Buffer API:


      .. cpp:function::  void erfc(queue& exec_queue, int64_t n,      buffer<T,1>& a, buffer<T,1>& y, uint64_t mode = mode::not_defined,      error_handler<T> errhandler = {} )

      USM API:


      .. cpp:function::  event erfc(queue& exec_queue, int64_t n, T* a,      T* y, vector_class<event>* depends, uint64_t mode =      mode::not_defined, error_handler<T> errhandler = {} )

      ``erfc`` supports the following precisions.


      .. list-table:: 
         :header-rows: 1

         * -  T 
         * -  ``float`` 
         * -  ``double`` 




.. container:: section
   :name: GUID-453802E1-D316-46A3-B888-4605174DA49A


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
      :name: GUID-C79F54F4-8A82-4E74-9DA6-1D7549A2D879


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

         * -  Argument 
           -  Result 
           -  Error Code 
         * -  a > underflow 
           -  +0 
           -  ``status::underflow`` 
         * -  +∞ 
           -  +0 
           -    
         * -  -∞ 
           -  +2 
           -    
         * -  QNAN 
           -  QNAN 
           -    
         * -  SNAN 
           -  QNAN 
           -    




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
      Pointer ``a`` to the input vector of size ``n``.


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


   An example of how to use erfc can be found in the oneMKL installation
   directory, under:


   ::


      examples/sycl/vml/verfc.cpp


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** `Special
      Functions <special-functions.html>`__



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

