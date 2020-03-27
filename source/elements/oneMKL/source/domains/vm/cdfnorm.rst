.. _cdfnorm:

cdfnorm
=======


.. container::


   Computes the cumulative normal distribution function values of vector
   elements.


   .. container:: section
      :name: GUID-1C0DF8A3-5375-4957-AE9D-0E0CF868EF1A


      .. rubric:: Syntax
         :name: syntax
         :class: sectiontitle


      Buffer API:


      .. cpp:function::  void cdfnorm(queue& exec_queue, int64_t n,      buffer<T,1>& a, buffer<T,1>& y, uint64_t mode = mode::not_defined,      error_handler<T> errhandler = {} )

      USM API:


      .. cpp:function::  event cdfnorm(queue& exec_queue, int64_t n, T\*      a, T\* y, vector_class<event>\* depends, uint64_t mode =      mode::not_defined, error_handler<T> errhandler = {} )

      ``cdfnorm`` supports the following precisions.


      .. list-table:: 
         :header-rows: 1

         * -  T 
         * -  ``float`` 
         * -  ``double`` 




.. container:: section
   :name: GUID-B6D67607-83F0-4A45-8AC3-A577D1240A28


   .. rubric:: Description
      :name: description
      :class: sectiontitle


   The cdfnorm function computes the cumulative normal distribution
   function values for elements of the input vector ``a`` and writes
   them to the output vector ``y``.


   The cumulative normal distribution function is defined as given by:


   | 


   .. container:: imagecenter


      |image0|


   Useful relations:


   | 


   .. container:: imagecenter


      |image1|


   where erfand erfcare the error and complementary error functions.


   The following figure illustrates the relationships among erf family
   functions (erf, erfc, cdfnorm).


   .. container:: figtop
      :name: GUID-C79F54F4-8A82-4E74-9DA6-1D7549A2D879


      cdfnorm Family Functions Relationship
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

         * -  Argument 
           -  Result 
           -  Error Code 
         * -  a < underflow 
           -  +0 
           -  ``status::underflow`` 
         * -  +∞ 
           -  +1 
           -    
         * -  -∞ 
           -  +0 
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


   An example of how to use cdfnorm can be found in the oneMKL
   installation directory, under:


   ::


      examples/sycl/vml/vcdfnorm.cpp


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** `Special
      Functions <special-functions.html>`__



.. |image0| image:: ../equations/GUID-817D9F12-6BD9-4B74-BFA0-39A03D0660C3-low.jpg
   :class: .eq
.. |image1| image:: ../equations/GUID-7CA9B2F2-8D7C-4955-8EA8-D67616FB5B08-low.gif
.. |image2| image:: ../equations/GUID-0B9A59CC-C914-429D-AF87-93B16DABD291-low.jpg
.. |image3| image:: ../equations/GUID-02486559-84D2-4880-8EAB-2085A5BE2D10-low.jpg
   :class: .eq
.. |image4| image:: ../equations/GUID-7CA9B2F2-8D7C-4955-8EA8-D67616FB5B08-low.gif

