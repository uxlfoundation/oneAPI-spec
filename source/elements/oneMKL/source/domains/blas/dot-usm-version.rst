.. _dot-usm-version:

dot (USM Version)
=================


.. container::


   Computes the dot product of two real vectors.


   .. container:: section
      :name: GUID-13355B56-0278-45E5-B310-3B0AC541C675


      .. rubric:: Syntax
         :name: syntax
         :class: sectiontitle


      .. container:: dlsyntaxpara


         .. cpp:function::  event dot(queue &exec_queue, std::int64_t n,         const T \*x, std::int64_t incx, const T \*y, std::int64_t incy,         T_res \*result, const vector_class<event> &dependencies = {})

         The USM version of ``dot`` supports the following precisions.


         .. list-table:: 
            :header-rows: 1

            * -  T 
              -  T_res 
            * -  ``float`` 
              -  ``float`` 
            * -  ``double`` 
              -  ``double`` 
            * -  ``float`` 
              -  ``double`` 




   .. container:: section
      :name: GUID-4BC6BF9A-BAB9-4078-A6B5-9C7ECB9D4821


      .. rubric:: Description
         :name: description
         :class: sectiontitle


      The dot routines perform a dot product between two vectors:


      |image0|


      .. container:: Note


         .. rubric:: Note
            :name: note
            :class: NoteTipHead


         For the mixed precision version (inputs are float while result
         is double), the dot product is computed with double precision.


   .. container:: section
      :name: GUID-6F86EF6A-8FFE-4C6A-8B71-23B95C1F1365


      .. rubric:: Input Parameters
         :name: input-parameters
         :class: sectiontitle


      exec_queue
         The queue where the routine should be executed.


      n
         Number of elements in vectors x and y.


      x
         Pointer to the input vector x. The array holding the vector x
         must be of size at least ``(1 + (n – 1)*abs(incx))``. See
         `Matrix and Vector
         Storage <../matrix-storage.html>`__ for
         more details.


      incx
         Stride of vector x.


      y
         Pointer to the input vector y. The array holding the vector y
         must be of size at least ``(1 + (n – 1)*abs(incy))``. See
         `Matrix and Vector
         Storage <../matrix-storage.html>`__ for
         more details.


      incy
         Stride of vector y.


      dependencies
         List of events to wait for before starting computation, if any.
         If omitted, defaults to no dependencies.


   .. container:: section
      :name: GUID-CAAFE234-AF82-4B61-8406-D57EC527BED5


      .. rubric:: Output Parameters
         :name: output-parameters
         :class: sectiontitle


      result
         Pointer to where the result (a scalar) will be stored.


   .. container:: section
      :name: GUID-FE9BC089-7D9E-470F-B1B6-2679FBFC249F


      .. rubric:: Return Values
         :name: return-values
         :class: sectiontitle


      Output event to wait on to ensure computation is complete.


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** :ref:`blas-level-1-routines`
      



.. |image0| image:: ../equations/GUID-75532DED-BE44-4D85-B9C0-99C825778ee1.png
   :class: img-middle

