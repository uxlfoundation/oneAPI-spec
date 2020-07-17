.. _onemkl_vm_arg:

arg
===


.. container::


   Computes argument of vector elements.


   .. container:: section


      .. rubric:: Syntax
         :class: sectiontitle


      Buffer API:


      .. cpp:function:: event oneapi::mkl::vm::arg(queue& exec_queue, int64_t n, buffer<T,1>& a, buffer<R,1>& y, uint64_t mode = oneapi::mkl::vm::mode::not_defined )

      USM API:


      .. cpp:function:: event oneapi::mkl::vm::arg(queue& exec_queue, int64_t n, T* a, R* y, vector_class<event> const & depends = {}, uint64_t mode = oneapi::mkl::vm::mode::not_defined )

      ``arg`` supports the following precisions.


      .. list-table::
         :header-rows: 1

         * - T
           - R
         * - ``std::complex<float>``
           - ``float``
         * - ``std::complex<double>``
           - ``double``


.. container:: section


   .. rubric:: Description
      :class: sectiontitle


   The arg(a) function computes argument of vector elements.


   See :ref:`onemkl_vm_special_value_notations` for the conventions used in the
   table below.


   .. container:: tablenoborder


      .. list-table::
         :header-rows: 1

         * - RE(a) i·IM(a)
           - -∞  
           - -X  
           - -0  
           - +0  
           - +X  
           - +∞  
           - NAN  
         * - +i·∞
           - +3·π/4
           - +π/2
           - +π/2
           - +π/2
           - +π/2
           - +π/4
           - NAN
         * - +i·Y
           - +π
           -  
           - +π/2
           - +π/2
           -  
           - +0
           - NAN
         * - +i·0
           - +π
           - +π
           - +π
           - +0
           - +0
           - +0
           - NAN
         * - -i·0
           - -π
           - -π
           - -π
           - -0
           - -0
           - -0
           - NAN
         * - -i·Y
           - -π
           -  
           - -π/2
           - -π/2
           -  
           - -0
           - NAN
         * - -i·∞
           - -3·π/4
           - -π/2
           - -π/2
           - -π/2
           - -π/2
           - -π/4
           - NAN
         * - +i·NAN
           - NAN
           - NAN
           - NAN
           - NAN
           - NAN
           - NAN
           - NAN




   .. container:: Note


      .. rubric:: Note
         :class: NoteTipHead


      ``arg(a)=atan2(IM(a), RE(a))``


   The arg function does not generate any errors.


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
      The buffer ``y`` containing the output vector of size ``n``.


   USM API:


   y
      Pointer ``y`` to the output vector of size ``n``.


   return value (event)
      Function end event.


.. container:: familylinks


   .. container:: parentlink

      **Parent topic:** :ref:`onemkl_vm_mathematical_functions`


