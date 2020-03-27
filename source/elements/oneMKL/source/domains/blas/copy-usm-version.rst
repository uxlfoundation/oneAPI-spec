.. _copy-usm-version:

copy (USM Version)
==================


.. container::


   Copies a vector to another vector.


   .. container:: section
      :name: GUID-D6B6C72E-9516-40C9-B034-9F344C41AAF3


      .. rubric:: Syntax
         :class: sectiontitle


      .. container:: dlsyntaxpara


         .. cpp:function::  event copy(queue &exec_queue, std::int64_t n,         const T \*x, std::int64_t incx, T \*y, std::int64_t incy, const         vector_class<event> &dependencies = {})

         The USM version of ``copy`` supports the following precisions.


         .. list-table:: 
            :header-rows: 1

            * -  T 
            * -  ``float`` 
            * -  ``double`` 
            * -  ``std::complex<float>`` 
            * -  ``std::complex<double>`` 




   .. container:: section
      :name: GUID-5E0A9C5F-BDD5-41E6-97CD-4316FD58C347


      .. rubric:: Description
         :class: sectiontitle


      The copy routines copy one vector to another:


     


         y ←x


      where x and y are vectors of n elements.


   .. container:: section
      :name: GUID-6F86EF6A-8FFE-4C6A-8B71-23B95C1F1365


      .. rubric:: Input Parameters
         :class: sectiontitle


      exec_queue
         The queue where the routine should be executed.


      n
         Number of elements in vector x.


      x
         Pointer to the input vector x. The array holding the vector
         ``x`` must be of size at least ``(1 + (n – 1)*abs(incx))``. See
         `Matrix and Vector
         Storage <../matrix-storage.html>`__ for
         more details.


      incx
         Stride of vector x.


      incy
         Stride of vector y.


      dependencies
         List of events to wait for before starting computation, if any.
         If omitted, defaults to no dependencies.


   .. container:: section
      :name: GUID-4ABB603B-835C-428B-B880-2F088BAB5456


      .. rubric:: Output Parameters
         :class: sectiontitle


      y
         Pointer to the updated vector y.


   .. container:: section
      :name: GUID-FE9BC089-7D9E-470F-B1B6-2679FBFC249F


      .. rubric:: Return Values
         :class: sectiontitle


      Output event to wait on to ensure computation is complete.


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** :ref:`blas-level-1-routines`
      


