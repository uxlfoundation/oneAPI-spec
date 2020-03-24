.. _syr-usm-version:

syr (USM Version)
=================


.. container::


   Computes a rank-1 update of a symmetric matrix.


   .. container:: section
      :name: GUID-E620D36F-6B4E-40A6-8BDA-3D625DEF55A8


      .. rubric:: Syntax
         :name: syntax
         :class: sectiontitle


      .. container:: dlsyntaxpara


         .. cpp:function::  event syr(queue &exec_queue, uplo upper_lower,         std::int64_t n, T alpha, const T \*x, std::int64_t incx, T \*a,         std::int64_t lda, const vector_class<event> &dependencies =         {})

         The USM version of ``syr`` supports the following precisions.


         .. list-table:: 
            :header-rows: 1

            * -  T 
            * -  ``float`` 
            * -  ``double`` 




   .. container:: section
      :name: GUID-E154DE4B-4559-4471-B92B-46AF8777AC97


      .. rubric:: Description
         :name: description
         :class: sectiontitle


      The syr routines compute a scalar-vector-vector product add them
      and add the result to a matrix, with a symmetric matrix. The
      operation is defined as


     


         A  <- alpha*x*x :sup:`T` + A


      where:


      ``alpha`` is scalar,


      ``A`` is an ``n``-by-``n`` symmetric matrix,


      ``x`` is a vector of length ``n``.


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
      :name: GUID-C03D1215-FD77-4AD8-8FA2-C48A5D8B938C


      .. rubric:: Output Parameters
         :name: output-parameters
         :class: sectiontitle


      a
         Pointer to the updated upper triangularpart of the symmetric
         matrix ``A`` if ``upper_lower =upper`` or the updated lower
         triangular part of thesymmetric matrix ``A`` if
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

