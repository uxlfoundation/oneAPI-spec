.. _dotu-usm-version:

dotu (USM Version)
==================


.. container::


   Computes the dot product of two complex vectors.


   .. container:: section
      :name: GUID-27A695AE-7ED5-4CFF-9783-0E50D111BED2


      .. rubric:: Syntax
         :name: syntax
         :class: sectiontitle


      .. container:: dlsyntaxpara


         .. cpp:function::  event dotu(queue &exec_queue, std::int64_t n,         const T \*x, std::int64_t incx, const T \*y, std::int64_t incy,         T \*result, const vector_class<event> &dependencies = {})

         The USM version of ``dotu`` supports the following precisions.


         .. list-table:: 
            :header-rows: 1

            * -  T 
            * -  ``std::complex<float>`` 
            * -  ``std::complex<double>`` 




   .. container:: section
      :name: GUID-7E67CFC6-917F-41A3-A664-F99EE4E04E43


      .. rubric:: Description
         :name: description
         :class: sectiontitle


      The dotu routines perform a dot product between two complex
      vectors:


      |image0|


   .. container:: section
      :name: GUID-A615800D-734E-4997-BB91-1C76AEEE9EC2


      .. rubric:: Input Parameters
         :name: input-parameters
         :class: sectiontitle


      exec_queue
         The queue where the routine should be executed.


      n
         Number of elements in vectors ``x`` and ``y``.


      x
         Pointer to the input vector ``x``. The array holding input
         vector ``x`` must be of size at least (1 + (``n`` -
         1)*abs(``incx``)). See `Matrix and Vector
         Storage <../matrix-storage.html>`__ for
         more details.


      incx
         Stride of vector x.


      y
         Pointer to input vector ``y``. The array holding input vector
         ``y`` must be of size at least (1 + (``n`` - 1)*abs(``incy``)).
         See `Matrix and Vector
         Storage <../matrix-storage.html>`__ for
         more details.


      incy
         Stride of vector y.


      dependencies
         List of events to wait for before starting computation, if any.
         If omitted, defaults to no dependencies.


   .. container:: section
      :name: GUID-2B160DEB-ADBB-4044-8078-4B613A0DA4E1


      .. rubric:: Output Parameters
         :name: output-parameters
         :class: sectiontitle


      result
         Pointer to where the result (a scalar) is stored.


   .. container:: section
      :name: GUID-FE9BC089-7D9E-470F-B1B6-2679FBFC249F


      .. rubric:: Return Values
         :name: return-values
         :class: sectiontitle


      Output event to wait on to ensure computation is complete.


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** :ref:`blas-level-1-routines`
      



.. |image0| image:: ../equations/GUID-42AF2BFE-F8F1-4F96-A4E0-05D4FB5A7ee1.png
   :class: img-middle

