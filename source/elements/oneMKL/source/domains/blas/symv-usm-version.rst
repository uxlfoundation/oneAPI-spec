.. _symv-usm-version:

symv (USM Version)
==================


.. container::


   Computes a matrix-vector product for a symmetric matrix.


   .. container:: section
      :name: GUID-1E9C9EA9-0366-420E-A704-AB605C8ED92A


      .. rubric:: Syntax
         :class: sectiontitle


      .. container:: dlsyntaxpara


         .. cpp:function::  event symv(queue &exec_queue, uplo         upper_lower, std::int64_t n, T alpha, const T \*a, std::int64_t         lda, const T \*x, std::int64_t incx, T beta, T \*y,         std::int64_t incy, const vector_class<event> &dependencies =         {})

         The USM version of ``symv`` supports the following precisions.


         .. list-table:: 
            :header-rows: 1

            * -  T 
            * -  ``float`` 
            * -  ``double`` 




   .. container:: section
      :name: GUID-DE8D8321-D53D-4226-A940-CDE0E720EC95


      .. rubric:: Description
         :class: sectiontitle


      The symv routines routines compute a scalar-matrix-vector product
      and add the result to a scalar-vector product, with a symmetric
      matrix. The operation is defined as


     


         y <- alpha*A*x + beta*y


      where:


      ``alpha`` and ``beta`` are scalars,


      ``A`` is an ``n``-by-``n`` symmetric matrix,


      ``x`` and ``y`` are vectors of length ``n``.


   .. container:: section
      :name: GUID-E1436726-01FE-4206-871E-B905F59A96B4


      .. rubric:: Input Parameters
         :class: sectiontitle


      exec_queue
         The queue where the routine should be executed.


      upper_lower
         Specifies whether ``A`` is upper or lower triangular. See
         :ref:`onemkl_datatypes` for
         more details.


      n
         Number of rows and columns of ``A``. Must be at least zero.


      alpha
         Scaling factor for the matrix-vector product.


      a
         Pointer to input matrix ``A``. The array holding input matrix
         ``A`` must have size at least ``lda``\ \*\ ``n``. See `Matrix
         and Vector
         Storage <../matrix-storage.html>`__ for
         more details.


      lda
         Leading dimension of matrix ``A``. Must be at least ``m``, and
         positive.


      x
         Pointer to input vector ``x``. The array holding input vector
         ``x`` must be of size at least (1 + (``n`` - 1)*abs(``incx``)).
         See `Matrix and Vector
         Storage <../matrix-storage.html>`__ for
         more details.


      incx
         Stride of vector ``x``.


      y
         Pointer to input/output vector ``y``. The array holding
         input/output vector ``y`` must be of size at least (1 + (``n``
         - 1)*abs(``incy``)). See `Matrix and Vector
         Storage <../matrix-storage.html>`__ for
         more details.


      incy
         Stride of vector ``y``.


      dependencies
         List of events to wait for before starting computation, if any.
         If omitted, defaults to no dependencies.


   .. container:: section
      :name: GUID-E16C8443-A2A4-483C-9D46-FF428E80FEB0


      .. rubric:: Output Parameters
         :class: sectiontitle


      y
         Pointer to the updated vector ``y``.


   .. container:: section
      :name: GUID-FE9BC089-7D9E-470F-B1B6-2679FBFC249F


      .. rubric:: Return Values
         :name: return-values
         :class: sectiontitle


      Output event to wait on to ensure computation is complete.


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** :ref:`blas-level-2-routines`
      


