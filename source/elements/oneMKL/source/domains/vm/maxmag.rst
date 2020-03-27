.. _maxmag:

maxmag
======


.. container::


   Returns the element with the larger magnitude between each pair of
   elements of the two vector arguments.


   .. container:: section
      :name: SYNTAX_86CD5B48F7F8421581B2186506AA2C36


      .. rubric:: Syntax
         :name: syntax
         :class: sectiontitle


      Buffer API:


      .. cpp:function::  void maxmag(queue& exec_queue, int64_t n,      buffer<T,1>& a, buffer<T,1>& b, buffer<T,1>& y, uint64_t mode =      mode::not_defined )

      USM API:


      .. cpp:function::  event maxmag(queue& exec_queue, int64_t n, T\* a,      T\* b, T\* y, vector_class<event>\* depends, uint64_t mode =      mode::not_defined )

      ``maxmag`` supports the following precisions.


      .. list-table:: 
         :header-rows: 1

         * -  T 
         * -  ``float`` 
         * -  ``double`` 




.. container:: section
   :name: GUID-ECB5A7FD-CBFB-4FDC-BFEE-B3A6307CEB3C


   .. rubric:: Description
      :name: description
      :class: sectiontitle


   The maxmag(a,b) function returns a vector with element values equal
   to the element with the larger magnitude from each pair of
   corresponding elements of the two vectors ``a`` and ``b``:


   -  If \|\ ``a``\ \| > \|\ ``b``\ \| maxmag(a,b) returns ``a``,
      otherwise maxmag(a,b) returns ``b``.


   -  If \|\ ``b``\ \| > \|\ ``a``\ \| maxmag(a,b) returns ``b``,
      otherwise maxmag(a,b) returns ``a``.


   -  Otherwise maxmag(a,b) behaves like fmax.


   .. container:: tablenoborder


      .. list-table:: 
         :header-rows: 1

         * -  Argument 1 
           -  Argument 2 
           -  Result 
           -  Error Code 
         * -  ``a`` not NAN 
           -  NAN 
           -  ``a`` 
           -    
         * -  NAN 
           -  ``b`` not NAN 
           -  ``b`` 
           -    
         * -  NAN 
           -  NAN 
           -  NAN 
           -    




   The maxmag(a,b) function does not generate any errors.


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


   An example of how to use maxmag can be found in the oneMKL
   installation directory, under:


   ::


      examples/sycl/vml/vmaxmag.cpp


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** `Miscellaneous VM
      Functions <miscellaneous-vm-functions.html>`__


.. container::

