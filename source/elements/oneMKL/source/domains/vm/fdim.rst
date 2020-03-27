
fdim
====


.. container::


   Returns vector containing the differences of the corresponding
   elements of the vector arguments if the first is larger and +0
   otherwise.


   .. container:: section
      :name: SYNTAX_86CD5B48F7F8421581B2186506AA2C36


      .. rubric:: Syntax
         :class: sectiontitle


      Buffer API:


      .. cpp:function::  void fdim(queue& exec_queue, int64_t n,      buffer<T,1>& a, buffer<T,1>& b, buffer<T,1>& y, uint64_t mode =      mode::not_defined )

      USM API:


      .. cpp:function::  event fdim(queue& exec_queue, int64_t n, T\* a,      T\* b, T\* y, vector_class<event>\* depends, uint64_t mode =      mode::not_defined )

      ``fdim`` supports the following precisions.


      .. list-table:: 
         :header-rows: 1

         * -  T 
         * -  ``float`` 
         * -  ``double`` 




.. container:: section
   :name: GUID-A095107B-945F-461D-8A26-1433A0F708FB


   .. rubric:: Description
      :class: sectiontitle


   The fdim(a,b) function returns a vector containing the differences of
   the corresponding elements of the first and second vector arguments
   if the first element is larger, and +0 otherwise.


   .. container:: tablenoborder


      .. list-table:: 
         :header-rows: 1

         * -  Argument 1 
           -  Argument 2 
           -  Result 
           -  Error Code 
         * -  any 
           -  QNAN 
           -  QNAN 
           -    
         * -  any 
           -  SNAN 
           -  QNAN 
           -    
         * -  QNAN 
           -  any 
           -  QNAN 
           -    
         * -  SNAN 
           -  any 
           -  QNAN 
           -    




   The fdim(a,b) function does not generate any errors.


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


   An example of how to use fdim can be found in the oneMKL installation
   directory, under:


   ::


      examples/sycl/vml/vfdim.cpp


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** `Miscellaneous VM
      Functions <miscellaneous-vm-functions.html>`__


