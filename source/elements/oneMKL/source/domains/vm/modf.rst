.. _onemkl_vm_modf:

modf
====


.. container::


   Computes a truncated integer value and the remaining fraction part
   for each vector element.


   .. container:: section


      .. rubric:: Syntax
         :class: sectiontitle


      Buffer API:


      .. cpp:function:: event oneapi::mkl::vm::modf(queue& exec_queue, int64_t n, buffer<T,1>& a, buffer<T,1>& y, buffer<T,1>& z, uint64_t mode = oneapi::mkl::vm::mode::not_defined )

      USM API:


      .. cpp:function:: event oneapi::mkl::vm::modf(queue& exec_queue, int64_t n, T* a, T* y, T* z, vector_class<event> const & depends = {}, uint64_t mode = oneapi::mkl::vm::mode::not_defined )

      ``modf`` supports the following precisions.


      .. list-table::
         :header-rows: 1

         * - T
         * - ``float``
         * - ``double``




.. container:: section


   .. rubric:: Description
      :class: sectiontitle


   The modf(a) function computes a truncated integer value and the
   remaining fraction part for each vector element.


   |
   | |image0|


   .. container:: tablenoborder


      .. list-table::
         :header-rows: 1

         * - Argument
           - Result 1
           - Result 2
           - Error Code
         * - +0
           - +0
           - +0
           -  
         * - -0
           - -0
           - -0
           -  
         * - +∞
           - +∞
           - +0
           -  
         * - -∞
           - -∞
           - -0
           -  
         * - SNAN
           - QNAN
           - QNAN
           -  
         * - QNAN
           - QNAN
           - QNAN
           -  




   The modf function does not generate any errors.


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


.. container:: section


   .. rubric:: Output Parameters
      :class: sectiontitle


   Buffer API:


   y
      The buffer ``y`` containing the output vector of size ``n`` for
      truncated integer values.


   z
      The buffer ``z`` containing the output vector of size ``n`` for
      remaining fraction parts.


   USM API:


   y
      Pointer ``y`` to the output vector of size ``n`` for truncated
      integer values.


   z
      Pointer ``z`` to the output vector of size ``n`` for remaining
      fraction parts.


   return value (event)
      Function end event.


.. container:: familylinks


   .. container:: parentlink

      **Parent topic:** :ref:`onemkl_vm_mathematical_functions`



.. |image0| image:: ../equations/GUID-38C12345-5E6E-4D94-8072-460502CB52EC-low.gif

