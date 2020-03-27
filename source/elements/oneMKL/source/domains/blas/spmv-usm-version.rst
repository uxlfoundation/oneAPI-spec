.. _spmv-usm-version:

spmv (USM Version)
==================


.. container::


   Computes a matrix-vector product with a symmetric packed matrix.


   .. container:: section
      :name: GUID-BCC82B03-92EB-4D73-B69C-8AE8646FBEAC


      .. rubric:: Syntax
         :class: sectiontitle


      .. container:: dlsyntaxpara


         .. cpp:function::  event spmv(queue &exec_queue, uplo         upper_lower, std::int64_t n, T alpha, const T \*a, const T \*x,         std::int64_t incx, T beta, T \*y, std::int64_t incy, const         vector_class<event> &dependencies = {})

         The USM version of ``spmv`` supports the following precisions.


         .. list-table:: 
            :header-rows: 1

            * -  T 
            * -  ``float`` 
            * -  ``double`` 




   .. container:: section
      :name: GUID-D27BBFFF-79F4-4236-96A6-B305FA1858B0


      .. rubric:: Description
         :class: sectiontitle


      The spmv routines compute a scalar-matrix-vector product and add
      the result to a scalar-vector product, with a symmetric packed
      matrix. The operation is defined as


     


         y <- alpha*A*x + beta*y


      where:


      ``alpha`` and ``beta`` are scalars,


      ``A`` is an ``n``-by-``n`` symmetric matrix, supplied in packed
      form.


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
         ``A`` must have size at least (``n``\ \*(``n``\ +1))/2. See
         `Matrix and Vector
         Storage <../matrix-storage.html>`__ for
         more details.


      x
         Pointer to input vector ``x``. The array holding input vector
         ``x`` must be of size at least (1 + (``n`` - 1)*abs(``incx``)).
         See `Matrix and Vector
         Storage <../matrix-storage.html>`__ for
         more details.


      incx
         Stride of vector ``x``.


      beta
         Scaling factor for vector ``y``.


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
      :name: GUID-23FF1F5C-5560-40B6-807D-B6352FA320D6


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
      


