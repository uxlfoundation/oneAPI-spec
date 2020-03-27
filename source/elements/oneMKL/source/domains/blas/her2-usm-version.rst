.. _her2-usm-version:

her2 (USM Version)
==================


.. container::


   Computes a rank-2 update of a Hermitian matrix.


   .. container:: section
      :name: GUID-4BED3537-E900-4260-A6EB-2F42CB1D3AFB


      .. rubric:: Syntax
         :name: syntax
         :class: sectiontitle


      .. container:: dlsyntaxpara


         .. cpp:function::  event her2(queue &exec_queue, uplo         upper_lower, std::int64_t n, T alpha, const T \*x, std::int64_t         incx, const T \*y, std::int64_t incy, T \*a, std::int64_t lda,         const vector_class<event> &dependencies = {})

         The USM version of ``her2`` supports the following precisions.


         .. list-table:: 
            :header-rows: 1

            * -  T 
            * -  ``std::complex<float>`` 
            * -  ``std::complex<double>`` 




   .. container:: section
      :name: GUID-2B939041-9BCC-4AE8-A31D-2CFCA67B9B6A


      .. rubric:: Description
         :name: description
         :class: sectiontitle


      The her2 routines compute two scalar-vector-vector products and
      add them to a Hermitian matrix. The operation is defined as


     


         A <- alpha*x*y :sup:`H` + conjg(alpha)*y*x :sup:`H` + A


      where:


      ``alpha`` is a scalar,


      ``A`` is an ``n``-by-``n`` Hermitian matrix.


      ``x`` and ``y`` are vectors or length ``n``.


   .. container:: section
      :name: GUID-E1436726-01FE-4206-871E-B905F59A96B4


      .. rubric:: Input Parameters
         :name: input-parameters
         :class: sectiontitle


      exec_queue
         The queue where the routine should be executed.


      upper_lower
         Specifies whether *A* is upper or lower triangular. See
         :ref:`onemkl_datatypes` for
         more details.


      n
         Number of columns of ``A``. Must be at least zero.


      alpha
         Scaling factor for the matrix-vector product.


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


      a
         Pointer to input matrix ``A``. The array holding input matrix
         ``A`` must have size at least ``lda``\ \*\ ``n``. See `Matrix
         and Vector
         Storage <../matrix-storage.html>`__ for
         more details.


      lda
         Leading dimension of matrix ``A``. Must be at least ``n``, and
         positive.


      dependencies
         List of events to wait for before starting computation, if any.
         If omitted, defaults to no dependencies.


   .. container:: section
      :name: GUID-34B3837B-4980-458B-AC3A-EEE5F635834C


      .. rubric:: Output Parameters
         :name: output-parameters
         :class: sectiontitle


      a
         Pointer to the updated upper triangular part of the Hermitian
         matrix ``A`` if ``upper_lower = upper``, or the updated
         lower triangular part of the Hermitian matrix ``A`` if
         ``upper_lower = lower``.


         The imaginary parts of the diagonal elements are set to zero.


   .. container:: section
      :name: GUID-FE9BC089-7D9E-470F-B1B6-2679FBFC249F


      .. rubric:: Return Values
         :name: return-values
         :class: sectiontitle


      Output event to wait on to ensure computation is complete.


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** :ref:`blas-level-2-routines`
      


