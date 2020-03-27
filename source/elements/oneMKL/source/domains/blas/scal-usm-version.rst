.. _scal-usm-version:

scal (USM Version)
==================


.. container::


   Computes the product of a vector by a scalar.


   .. container:: section
      :name: GUID-178A4C6A-3BA5-40F7-A3D6-4B6590B75EB4


      .. rubric:: Syntax
         :class: sectiontitle


      .. container:: dlsyntaxpara


         .. cpp:function::  event scal(queue &exec_queue, std::int64_t n,         T_scalar alpha, T \*x, std::int64_t incx, const         vector_class<event> &dependencies = {})

         The USM version of ``scal`` supports the following precisions.


         .. list-table:: 
            :header-rows: 1

            * -  T 
              -  T_scalar 
            * -  ``float`` 
              -  ``float`` 
            * -  ``double`` 
              -  ``double`` 
            * -  ``std::complex<float>`` 
              -  ``std::complex<float>`` 
            * -  ``std::complex<double>`` 
              -  ``std::complex<double>`` 
            * -  ``std::complex<float>`` 
              -  ``float`` 
            * -  ``std::complex<double>`` 
              -  ``double`` 




   .. container:: section
      :name: GUID-8DDCA613-2750-43D0-A89B-13866F2DDE8C


      .. rubric:: Description
         :class: sectiontitle


      The scal routines computes a scalar-vector product:


     


         x <- alpha*x


      where:


      ``x`` is a vector of ``n`` elements,


      ``alpha`` is a scalar.


   .. container:: section
      :name: GUID-A615800D-734E-4997-BB91-1C76AEEE9EC2


      .. rubric:: Input Parameters
         :class: sectiontitle


      exec_queue
         The queue where the routine should be executed.


      n
         Number of elements in vector ``x``.


      alpha
         Specifies the scalar ``alpha``.


      x
         Pointer to the input vector ``x``. The array must be of size at
         least (1 + (``n`` - 1)*abs(``incx``)). See `Matrix and Vector
         Storage <../matrix-storage.html>`__ for
         more details.


      incx
         Stride of vector x.


   .. container:: section
      :name: GUID-B36EBB3E-C79B-49F8-9F47-7B19BD6BE105


      .. rubric:: Output Parameters
         :class: sectiontitle


      x
         Pointer to the updated array ``x``.


   .. container:: section
      :name: GUID-FE9BC089-7D9E-470F-B1B6-2679FBFC249F


      .. rubric:: Return Values
         :name: return-values
         :class: sectiontitle


      Output event to wait on to ensure computation is complete.


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** :ref:`blas-level-1-routines`
      


