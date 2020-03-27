.. _swap-usm-version:

swap (USM Version)
==================


.. container::


   Swaps a vector with another vector.


   .. container:: section
      :name: GUID-F0DF0055-DF25-4EC7-8FF2-48D4FA91E42E


      .. rubric:: Syntax
         :name: syntax
         :class: sectiontitle


      .. container:: dlsyntaxpara


         .. cpp:function::  event swap(queue &exec_queue, std::int64_t n,         T \*x, std::int64_t incx, T \*y, std::int64_t incy, const         vector_class<event> &dependencies = {})

         The USM version of swap supports the following precisions.


         .. list-table:: 
            :header-rows: 1

            * -  T 
            * -  ``float`` 
            * -  ``double`` 
            * -  ``std::complex<float>`` 
            * -  ``std::complex<double>`` 




   .. container:: section
      :name: GUID-FE88C4B7-4C74-41F8-94DE-E62888DD3BA4


      .. rubric:: Description
         :name: description
         :class: sectiontitle


      Given two vectors of ``n`` elements, ``x`` and ``y``, the swap
      routines return vectors ``y`` and ``x`` swapped, each replacing
      the other.


     


         y <- x, x <- y


   .. container:: section
      :name: GUID-A615800D-734E-4997-BB91-1C76AEEE9EC2


      .. rubric:: Input Parameters
         :name: input-parameters
         :class: sectiontitle


      exec_queue
         The queue where the routine should be executed.


      n
         Number of elements in vector ``x``.


      x
         Pointer to the input vector ``x``. The array must be of size at
         least (1 + (``n`` - 1)*abs(``incx``)). See `Matrix and Vector
         Storage <../matrix-storage.html>`__ for
         more details.


      incx
         Stride of vector x.


      y
         Pointer to the input vector ``y``. The array must be of size at
         least (1 + (``n`` - 1)*abs(``incy``)). See `Matrix and Vector
         Storage <../matrix-storage.html>`__ for
         more details.


      incy
         Stride of vector y.


      dependencies
         List of events to wait for before starting computation, if any.
         If omitted, defaults to no dependencies.


   .. container:: section
      :name: GUID-106AC665-DCBA-40ED-8779-0D9017064855


      .. rubric:: Output Parameters
         :name: output-parameters
         :class: sectiontitle


      x
         Pointer to the updated array ``x``, that is, the input vector
         ``y``.


      y
         Pointer to the updated array ``y``, that is, the input vector
         ``x``.


   .. container:: section
      :name: GUID-FE9BC089-7D9E-470F-B1B6-2679FBFC249F


      .. rubric:: Return Values
         :name: return-values
         :class: sectiontitle


      Output event to wait on to ensure computation is complete.


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** :ref:`blas-level-1-routines`
      


