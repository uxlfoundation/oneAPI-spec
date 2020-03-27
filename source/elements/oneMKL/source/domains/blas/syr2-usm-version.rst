.. _syr2-usm-version:

syr2 (USM Version)
==================


.. container::


   Computes a rank-2 update of a symmetric matrix.


   .. container:: section
      :name: GUID-580F2222-D47E-43A3-B9A2-037F353825D5


      .. rubric:: Syntax
         :name: syntax
         :class: sectiontitle


      .. container:: dlsyntaxpara


         .. cpp:function::  event syr2(queue &exec_queue, uplo         upper_lower, std::int64_t n, T alpha, const T \*x, std::int64_t         incx, const T \*y, std::int64_t incy, T \*a, std::int64_t lda,         const vector_class<event> &dependencies = {})

         The USM version of ``syr2`` supports the following precisions.


         .. list-table:: 
            :header-rows: 1

            * -  T 
            * -  ``float`` 
            * -  ``double`` 




   .. container:: section
      :name: GUID-CDA05459-F2FE-4933-A552-D6E52EC46D13


      .. rubric:: Description
         :name: description
         :class: sectiontitle


      The syr2 routines compute two scalar-vector-vector product add
      them and add the result to a matrix, with a symmetric matrix. The
      operation is defined as


     


         A <- alpha*x*y :sup:`T` + alpha*y*x :sup:`T` + A


      where:


      ``alpha`` is a scalar,


      ``A`` is an ``n``-by-``n`` symmetric matrix,


      ``x`` and ``y`` are vectors of length ``n``.


   .. container:: section
      :name: GUID-E1436726-01FE-4206-871E-B905F59A96B4


      .. rubric:: Input Parameters
         :name: input-parameters
         :class: sectiontitle


      exec_queue
         The queue where the routine should be executed.


      upper_lower
         Specifies whether ``A`` is upper or lower triangular. See
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
      :name: GUID-6992A39F-8AB7-42D9-B126-4F8ECF9C1ECE


      .. rubric:: Output Parameters
         :name: output-parameters
         :class: sectiontitle


      a
         Pointer to the updated upper triangular part of the symmetric
         matrix ``A`` if ``upper_lower =upper``, or the updated lower
         triangular part of the symmetric matrix ``A`` if
         ``upper_lower =lower``.


   .. container:: section
      :name: GUID-FE9BC089-7D9E-470F-B1B6-2679FBFC249F


      .. rubric:: Return Values
         :name: return-values
         :class: sectiontitle


      Output event to wait on to ensure computation is complete.


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** :ref:`blas-level-2-routines`
      


.. container::

