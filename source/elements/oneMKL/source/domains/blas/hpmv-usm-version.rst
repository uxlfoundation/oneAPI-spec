.. _hpmv-usm-version:

hpmv (USM Version)
==================


.. container::


   Computes a matrix-vector product using a Hermitian packed matrix.


   .. container:: section
      :name: GUID-C6E4A4A7-5CBE-46ED-A021-8FEAABAA2E93


      .. rubric:: Syntax
         :class: sectiontitle


      .. container:: dlsyntaxpara


         .. cpp:function::  event hpmv(queue &exec_queue, uplo         upper_lower, std::int64_t n, T alpha, const T \*a, const T \*x,         std::int64_t incx, T beta, T \*y, std::int64_t incy, const         vector_class<event> &dependencies = {})

         The USM version of ``hpmv`` supports the following precisions.


         .. list-table:: 
            :header-rows: 1

            * -  T 
            * -  ``std::complex<float>`` 
            * -  ``std::complex<double>`` 




   .. container:: section
      :name: GUID-A95C32C5-0371-429B-847C-4EE29FD9C480


      .. rubric:: Description
         :class: sectiontitle


      The hpmv routines compute a scalar-matrix-vector product and add
      the result to a scalar-vector product, with a Hermitian packed
      matrix. The operation is defined as


     


         y <- alpha*A*x + beta*y


      where:


      ``alpha`` and ``beta`` are scalars,


      ``A`` is an ``n``-by-``n`` Hermitian matrix supplied in packed
      form,


      ``x`` and ``y`` are vectors of length ``n``.


   .. container:: section
      :name: GUID-E1436726-01FE-4206-871E-B905F59A96B4


      .. rubric:: Input Parameters
         :class: sectiontitle


      exec_queue
         The queue where the routine should be executed.


      upper_lower
         Specifies whether *A* is upper or lower triangular. See
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


         The imaginary parts of the diagonal elements need not be set
         and are assumed to be zero.


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
      :name: GUID-416B82CD-C5B8-472A-8347-04997EA6D6E6


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
      


