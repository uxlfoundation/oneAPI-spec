.. _nrm2-usm-version:

nrm2 (USM Version)
==================


.. container::


   Computes the Euclidean norm of a vector.


   .. container:: section
      :name: GUID-F55A15D5-CCDA-4C44-B86F-C9A5FB36725E


      .. rubric:: Syntax
         :class: sectiontitle


      .. container:: dlsyntaxpara


         .. cpp:function::  event nrm2(queue &exec_queue, std::int64_t n,         const T \*x, std::int64_t incx, T_res \*result, const         vector_class<event> &dependencies = {})

         The USM version of ``nrm2`` supports the following precisions.


         .. list-table:: 
            :header-rows: 1

            * -  T 
              -  T_res 
            * -  ``float`` 
              -  ``float`` 
            * -  ``double`` 
              -  ``double`` 
            * -  ``std::complex<float>`` 
              -  ``float`` 
            * -  ``std::complex<double>`` 
              -  ``double`` 




   .. container:: section
      :name: GUID-2BF2C965-5A8C-47F1-9C73-FB0E485CE32A


      .. rubric:: Description
         :class: sectiontitle


      The nrm2 routines computes Euclidean norm of a vector


     


         result = ||x||,


      where:


      ``x`` is a vector of ``n`` elements.


   .. container:: section
      :name: GUID-A615800D-734E-4997-BB91-1C76AEEE9EC2


      .. rubric:: Input Parameters
         :class: sectiontitle


      exec_queue
         The queue where the routine should be executed.


      n
         Number of elements in vector ``x``.


      x
         Pointer to input vector ``x``. The array holding input vector
         ``x`` must be of size at least (1 + (``n`` - 1)*abs(``incx``)).
         See `Matrix and Vector
         Storage <../matrix-storage.html>`__ for
         more details.


      incx
         Stride of vector x.


      dependencies
         List of events to wait for before starting computation, if any.
         If omitted, defaults to no dependencies.


   .. container:: section
      :name: GUID-2B160DEB-ADBB-4044-8078-4B613A0DA4E1


      .. rubric:: Output Parameters
         :class: sectiontitle


      result
         Pointer to where the Euclidean norm of the vector ``x`` will be
         stored.


   .. container:: section
      :name: GUID-FE9BC089-7D9E-470F-B1B6-2679FBFC249F


      .. rubric:: Return Values
         :class: sectiontitle


      Output event to wait on to ensure computation is complete.


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** :ref:`blas-level-1-routines`
      


