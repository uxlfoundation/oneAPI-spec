.. _log10:

log10
=====


.. container::


   Computes the base 10 logarithm of vector elements.


   .. container:: section
      :name: GUID-29020D28-42E7-4969-A410-740513FC3F76


      .. rubric:: Syntax
         :name: syntax
         :class: sectiontitle


      Buffer API:


      .. cpp:function::  void log10(queue& exec_queue, int64_t n,      buffer<T,1>& a, buffer<T,1>& y, uint64_t mode = mode::not_defined,      error_handler<T> errhandler = {} )

      USM API:


      .. cpp:function::  event log10(queue& exec_queue, int64_t n, T\* a,      T\* y, vector_class<event>\* depends, uint64_t mode =      mode::not_defined, error_handler<T> errhandler = {} )

      ``log10`` supports the following precisions.


      .. list-table:: 
         :header-rows: 1

         * -  T 
         * -  ``float`` 
         * -  ``double`` 
         * -  ``std::complex<float>`` 
         * -  ``std::complex<double>`` 




.. container:: section
   :name: GUID-62B1C679-FF49-45DA-9778-7199B9DE27A3


   .. rubric:: Description
      :name: description
      :class: sectiontitle


   The log10(a) function computes the base 10 logarithm of vector
   elements.


   .. container:: tablenoborder


      .. list-table:: 
         :header-rows: 1

         * -  Argument 
           -  Result 
           -  Error Code 
         * -  +1 
           -  +0 
           -    
         * -  a <+0 
           -  QNAN 
           -  ``status::errdom`` 
         * -  +0 
           -  -∞ 
           -  ``status::sing`` 
         * -  -0 
           -  -∞ 
           -  ``status::sing`` 
         * -  -∞ 
           -  QNAN 
           -  ``status::errdom`` 
         * -  +∞ 
           -  +∞ 
           -    
         * -  QNAN 
           -  QNAN 
           -    
         * -  SNAN 
           -  QNAN 
           -    




   .. container:: tablenoborder


      .. list-table:: 
         :header-rows: 1

         * -     RE(a)      i·IM(a)    
           -     -∞    
           -     -X           
           -     -0    
           -     +0    
           -     +X           
           -     +∞           
           -     NAN           
         * -  +i·∞ 
           -  |image0| 
           -  |image1| 
           -  |image2| 
           -  |image3| 
           -  |image4| 
           -  |image5| 
           -     +∞+i·QNAN    
         * -  +i·Y 
           -  |image6| 
           -    
           -    
           -    
           -    
           -  +∞+i·0 
           -     QNAN+i·QNAN    
         * -  +i·0 
           -  |image7| 
           -    
           -  |image8| 
           -  -∞+i·0 
           -    
           -  +∞+i·0 
           -     QNAN+i·QNAN    
         * -  -i·0 
           -  |image9| 
           -    
           -  |image10| 
           -  -∞-i·0 
           -    
           -  +∞-i·0 
           -     QNAN-i·QNAN    
         * -  -i·Y 
           -  |image11| 
           -    
           -    
           -    
           -    
           -  +∞-i·0 
           -     QNAN+i·QNAN    
         * -  -i·∞ 
           -  |image12| 
           -  |image13| 
           -  |image14| 
           -  |image15| 
           -  |image16| 
           -  |image17| 
           -     +∞+i·QNAN    
         * -  +i·NAN 
           -     +∞+i·QNAN    
           -     QNAN+i·QNAN    
           -     QNAN+i·QNAN    
           -     QNAN+i·QNAN    
           -     QNAN+i·QNAN    
           -     +∞+i·QNAN    
           -     QNAN+i·QNAN    




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


   An example of how to use log10can be found in the oneMKL installation
   directory, under:


   ::


      examples/sycl/vml/vlog10.cpp


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** `Exponential and Logarithmic
      Functions <exponential-and-logarithmic-functions.html>`__


.. container::


.. |image0| image:: ../equations/GUID-2293B947-42D6-4E5F-BBB3-9DC135AA724A-low.gif
.. |image1| image:: ../equations/GUID-7AE86F5B-8BE2-42D5-B6C7-AF9FF41CCE11-low.jpg
.. |image2| image:: ../equations/GUID-7AE86F5B-8BE2-42D5-B6C7-AF9FF41CCE11-low.jpg
.. |image3| image:: ../equations/GUID-7AE86F5B-8BE2-42D5-B6C7-AF9FF41CCE11-low.jpg
.. |image4| image:: ../equations/GUID-7AE86F5B-8BE2-42D5-B6C7-AF9FF41CCE11-low.jpg
.. |image5| image:: ../equations/GUID-98EC239E-D5C9-4960-834B-827656CF3052-low.gif
.. |image6| image:: ../equations/GUID-32A750B8-7BCC-409B-BD48-E88FBEF86D32-low.jpg
.. |image7| image:: ../equations/GUID-32A750B8-7BCC-409B-BD48-E88FBEF86D32-low.jpg
.. |image8| image:: ../equations/GUID-F01C1454-13EC-4D30-8E73-8E41755B8AF2-low.gif
.. |image9| image:: ../equations/GUID-8F8B1A27-FCBD-4E61-ACC0-459C9EBAE376-low.gif
.. |image10| image:: ../equations/GUID-DF275A8A-05D4-49D9-9031-E4A9382C284C-low.gif
.. |image11| image:: ../equations/GUID-8F8B1A27-FCBD-4E61-ACC0-459C9EBAE376-low.gif
.. |image12| image:: ../equations/GUID-2293B947-42D6-4E5F-BBB3-9DC135AA724A-low.gif
.. |image13| image:: ../equations/GUID-9AB7A841-1EEC-49D6-BBF8-5B346FB32C1A-low.jpg
.. |image14| image:: ../equations/GUID-9AB7A841-1EEC-49D6-BBF8-5B346FB32C1A-low.jpg
.. |image15| image:: ../equations/GUID-9AB7A841-1EEC-49D6-BBF8-5B346FB32C1A-low.jpg
.. |image16| image:: ../equations/GUID-9AB7A841-1EEC-49D6-BBF8-5B346FB32C1A-low.jpg
.. |image17| image:: ../equations/GUID-9114D36E-F829-485D-BF04-8747E20120BD-low.gif

