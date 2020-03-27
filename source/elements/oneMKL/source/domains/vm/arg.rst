.. _arg:

arg
===


.. container::


   Computes argument of vector elements.


   .. container:: section
      :name: GUID-B43F4847-BE63-4396-A993-2F6FC5201525


      .. rubric:: Syntax
         :name: syntax
         :class: sectiontitle


      Buffer API:


      .. cpp:function::  void arg(queue& exec_queue, int64_t n,      buffer<A,1>& a, buffer<R,1>& y, uint64_t mode = mode::not_defined      )

      USM API:


      .. cpp:function::  event arg(queue& exec_queue, int64_t n, A\* a,      R\* y, vector_class<event>\* depends, uint64_t mode =      mode::not_defined )

      ``arg`` supports the following precisions.


      .. list-table:: 
         :header-rows: 1

         * -  T 
         * -  ``std::complex<float>`` 
         * -  ``std::complex<double>`` 




.. container:: section
   :name: GUID-75EB29ED-7EBD-463F-A86A-F95625E7703B


   .. rubric:: Description
      :name: description
      :class: sectiontitle


   The arg(a) function computes argument of vector elements.


   See `Special Value
   Notations <special-value-notations.html>`__
   for the conventions used in the table below.


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
           -  +3·π/4 
           -  +π/2 
           -  +π/2 
           -  +π/2 
           -  +π/2 
           -  +π/4 
           -  NAN 
         * -  +i·Y 
           -  +π 
           -    
           -  +π/2 
           -  +π/2 
           -    
           -  +0 
           -  NAN 
         * -  +i·0 
           -  +π 
           -  +π 
           -  +π 
           -  +0 
           -  +0 
           -  +0 
           -  NAN 
         * -  -i·0 
           -  -π 
           -  -π 
           -  -π 
           -  -0 
           -  -0 
           -  -0 
           -  NAN 
         * -  -i·Y 
           -  -π 
           -    
           -  -π/2 
           -  -π/2 
           -    
           -  -0 
           -  NAN 
         * -  -i·∞ 
           -  -3·π/4 
           -  -π/2 
           -  -π/2 
           -  -π/2 
           -  -π/2 
           -  -π/4 
           -  NAN 
         * -  +i·NAN 
           -  NAN 
           -  NAN 
           -  NAN 
           -  NAN 
           -  NAN 
           -  NAN 
           -  NAN 




   .. container:: Note


      .. rubric:: Note
         :name: note
         :class: NoteTipHead


      ``arg(a)=atan2(IM(a),RE(a))``


   The arg function does not generate any errors.


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


   An example of how to use arg can be found in the oneMKL installation
   directory, under:


   ::


      examples/sycl/vml/varg.cpp


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** `Arithmetic
      Functions <arithmetic-functions.html>`__


.. container::

