.. _asum-usm-version:

asum (USM Version)
==================


.. container::


   Computes the sum of magnitudes of the vector elements.


   .. container:: section
      :name: GUID-C135E117-8018-473E-BE83-8833C95BB3B5


      .. rubric:: Syntax
         :name: syntax
         :class: sectiontitle


      .. container:: dlsyntaxpara


         .. cpp:function::  event asum(queue &exec_queue, std::int64_t n,         const T \*x, std::int64_t incx, T_res \*result, const         vector_class<event> &dependencies = {})

         The USM version of ``asum`` supports the following precisions.


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
      :name: GUID-6AFCECB5-6614-46AC-B921-AB5DED0D22B2


      .. rubric:: Description
         :name: description
         :class: sectiontitle


      The asum routine computes the sum of the magnitudes of elements of
      a real vector, or the sum of magnitudes of the real and imaginary
      parts of elements of a complex vector:


      |image0|


      where ``x`` is a vector with ``n`` elements.


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
         Pointer to input vector ``x``. The array holding the vector
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
         :name: output-parameters
         :class: sectiontitle


      result
         Pointer to the output matrix where the scalar result is stored
         (the sum of magnitudes of the real and imaginary parts of all
         elements of the vector).


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


.. |image0| image:: ../equations/GUID-4F76F5A1-251F-4AC0-A2E0-A3B4B6F39ee1.png
   :class: img-middle

