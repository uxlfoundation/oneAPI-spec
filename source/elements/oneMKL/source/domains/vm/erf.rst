.. _erf:

erf
===


.. container::


   Computes the error function value of vector elements.


   .. container:: section
      :name: GUID-3B72BA93-E9E8-4CC9-AB9D-8680D2B5D272


      .. rubric:: Syntax
         :name: syntax
         :class: sectiontitle


      Buffer API:


      .. cpp:function::  void erf(queue& exec_queue, int64_t n,      buffer<T,1>& a, buffer<T,1>& y, uint64_t mode = mode::not_defined      )

      USM API:


      .. cpp:function::  event erf(queue& exec_queue, int64_t n, T\* a,      T\* y, vector_class<event>\* depends, uint64_t mode =      mode::not_defined )

      ``erf`` supports the following precisions.


      .. list-table:: 
         :header-rows: 1

         * -  T 
         * -  ``float`` 
         * -  ``double`` 




.. container:: section
   :name: GUID-79EB3648-1E04-434D-9F1C-ADD94918B7F5


   .. rubric:: Description
      :name: description
      :class: sectiontitle


   The erf function computes the error function values for elements of
   the input vector ``a`` and writes them to the output vector ``y``.


   The error function is defined as given by:


   .. container:: imagecenter


      |image0|


   Useful relations:


   |image1|


   where erfc is the complementary error function.


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


      erf Family Functions Relationship
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
         * -  +∞ 
           -  +1 
           -    
         * -  -∞ 
           -  -1 
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


   An example of how to use erfcan be found in the oneMKL installation
   directory, under:


   ::


      examples/sycl/vml/verf.cpp


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** `Special
      Functions <special-functions.html>`__


.. container::


.. |image0| image:: ../equations/GUID-8742E2B1-94AF-4622-B964-181611E3D1F2-low.jpg
   :class: .eq
.. |image1| image:: ../equations/GUID-6ABD7CD8-8E05-409D-B84F-9B88E4CDE9DB-low.gif
   :class: .eq
.. |image2| image:: ../equations/GUID-41FCF9BC-28B7-4030-B904-1DBA03DD328C-low.gif
   :class: .eq
.. |image3| image:: ../equations/GUID-EA77C856-3F93-40ED-AB2A-0F1BD8C4CE7A-low.jpg
   :class: .eq
.. |image4| image:: ../equations/GUID-895E6B37-AC54-40D4-B134-E2816B7F30D3-low.gif
   :class: .eq
.. |image5| image:: ../equations/GUID-0B9A59CC-C914-429D-AF87-93B16DABD291-low.jpg
.. |image6| image:: ../equations/GUID-02486559-84D2-4880-8EAB-2085A5BE2D10-low.jpg
   :class: .eq
.. |image7| image:: ../equations/GUID-7CA9B2F2-8D7C-4955-8EA8-D67616FB5B08-low.gif

