.. _hpr2-usm-version:

hpr2 (USM Version)
==================


.. container::


   Performs a rank-2 update of a Hermitian packed matrix.


   .. container:: section
      :name: GUID-9F8EB534-6520-4470-85AC-6AD8F2467AD4


      .. rubric:: Syntax
         :class: sectiontitle


      .. container:: dlsyntaxpara


         .. cpp:function::  event hpr2(queue &exec_queue, uplo         upper_lower, std::int64_t n, T alpha, const T \*x, std::int64_t         incx, const T \*y, std::int64_t incy, T \*a, const         vector_class<event> &dependencies = {})

         The USM version of ``hpr2`` supports the following precisions.


         .. list-table:: 
            :header-rows: 1

            * -  T 
            * -  ``std::complex<float>`` 
            * -  ``std::complex<double>`` 




   .. container:: section
      :name: GUID-16FE1EDC-1A72-4BAB-8AFF-C316C4CE5838


      .. rubric:: Description
         :class: sectiontitle


      The hpr2 routines compute two scalar-vector-vector products and
      add them to a Hermitian packed matrix. The operation is defined as


     


         A <- alpha*x*y :sup:`H` + conjg(alpha)*y*x :sup:`H` + A


      where:


      ``alpha`` is a scalar,


      ``A`` is an ``n``-by-``n`` Hermitian matrix, supplied in packed
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
         ``A`` must have size at least (``n``\ \*(``n``-1))/2. See
         `Matrix and Vector
         Storage <../matrix-storage.html>`__ for
         more details.


         The imaginary parts of the diagonal elements need not be set
         and are assumed to be zero.


      dependencies
         List of events to wait for before starting computation, if any.
         If omitted, defaults to no dependencies.


   .. container:: section
      :name: GUID-9A77A2E0-F610-44EE-A3EE-81327B90A3FD


      .. rubric:: Output Parameters
         :class: sectiontitle


      a
         Pointer to the updated upper triangular part of the Hermitian
         matrix ``A`` if ``upper_lower =upper``, or the updated lower
         triangular part of the Hermitian matrix ``A`` if
         ``upper_lower =lower``.


         The imaginary parts of the diagonal elements are set to zero.


   .. container:: section
      :name: GUID-FE9BC089-7D9E-470F-B1B6-2679FBFC249F


      .. rubric:: Return Values
         :class: sectiontitle


      Output event to wait on to ensure computation is complete.


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** :ref:`blas-level-2-routines`
      


