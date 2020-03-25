.. _dotc-usm-version:

dotc (USM Version)
==================


.. container::


   Computes the dot product of two complex vectors, conjugating the
   first vector.


   .. container:: section
      :name: GUID-9D36611B-564D-475B-8D98-5F53A4F698F5


      .. rubric:: Syntax
         :name: syntax
         :class: sectiontitle


      .. container:: dlsyntaxpara


         .. cpp:function::  void dotc(queue &exec_queue, std::int64_t n,         const T \*x, std::int64_t incx, const T \*y, std::int64_t incy,         T \*result, const vector_class<event> &dependencies = {})

         The USM version of ``dotc`` supports the following precisions.


         .. list-table:: 
            :header-rows: 1

            * -  T 
            * -  ``std::complex<float>`` 
            * -  ``std::complex<double>`` 




   .. container:: section
      :name: GUID-3E4588D2-5FDE-43F1-955E-85173AE62252


      .. rubric:: Description
         :name: description
         :class: sectiontitle


      The ``dotc`` routines perform a dot product between two complex
      vectors, conjugating the first of them:


      |image0|


   .. container:: section
      :name: GUID-38675523-DEDD-4314-8486-7C66614ED2C7


      .. rubric:: Input Parameters
         :name: input-parameters
         :class: sectiontitle


      exec_queue
         The queue where the routine should be executed.


      n
         The number of elements in vectors ``x`` and ``y``.


      x
         Pointer to input vector ``x``. The array holding the input
         vector ``x`` must be of size at least (1 + (``n`` -
         1)*abs(``incx``)). See `Matrix and Vector
         Storage <../matrix-storage.html>`__ for
         more details.


      incx
         The stride of vector ``x``.


      y
         Pointer to input vector ``y``. The array holding the input
         vector ``y`` must be of size at least (1 + (``n`` -
         1)*abs(``incy``)). See `Matrix and Vector
         Storage <../matrix-storage.html>`__ for
         more details..


      incy
         The stride of vector ``y``.


      dependencies
         List of events to wait for before starting computation, if any.
         If omitted, defaults to no dependencies.


   .. container:: section
      :name: GUID-B84A5D05-6B61-4D13-8185-2A349C41CE46


      .. rubric:: Output Parameters
         :name: output-parameters
         :class: sectiontitle


      result
         The pointer to where the result (a scalar) is stored.


   .. container:: section
      :name: GUID-FE9BC089-7D9E-470F-B1B6-2679FBFC249F


      .. rubric:: Return Values
         :name: return-values
         :class: sectiontitle


      Output event to wait on to ensure computation is complete.


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** :ref:`blas-level-1-routines`
      


.. container::


.. |image0| image:: ../equations/GUID-B2211D34-A472-4FB8-9CFB-1E11AF4F0ee1.png
   :class: img-middle

