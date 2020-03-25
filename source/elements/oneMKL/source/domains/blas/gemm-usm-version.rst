.. _gemm-usm-version:

gemm (USM Version)
==================


.. container::


   Computes a matrix-matrix product with general matrices.


   .. container:: section
      :name: GUID-7885D940-FAC1-4F37-9E1C-A022DED99EBD


      .. rubric:: Syntax
         :name: syntax
         :class: sectiontitle


      .. container:: dlsyntaxpara


         .. cpp:function::  event gemm(queue &exec_queue, transpose         transa, transpose transb, std::int64_t m, std::int64_t n,         std::int64_t k, T alpha, const T \*a, std::int64_t lda, const T         \*b, std::int64_t ldb, T beta, T \*c, std::int64_t ldc, const         vector_class<event> &dependencies = {})

         The USM version of ``gemm`` supports the following precisions.


         .. list-table:: 
            :header-rows: 1

            * -  T 
            * -  ``float`` 
            * -  ``double`` 
            * -  ``std::complex<float>`` 
            * -  ``std::complex<double>`` 




   .. container:: section
      :name: GUID-14237C95-6322-47A4-BC11-D3CDD2118C42


      .. rubric:: Description
         :name: description
         :class: sectiontitle


      The gemm routine computes a scalar-matrix-matrix product and adds
      the result to a scalar-matrix product, with general matrix inputs.
      The operation is defined as


     


         C <- alpha*op(A)*op(B) + beta*C


      where:


      ``op(X)`` is one of ``op(X) = X``, or ``op(X) = XT``, or
      ``op(X) = XH``,


      ``alpha`` and ``beta`` are scalars,


      ``A``, ``B`` and ``C`` are matrices:


      ``op(A)`` is an ``m``-by-``k`` matrix,


      ``op(B)`` is a ``k``-by-``n`` matrix,


      ``C`` is an ``m``-by-``n`` matrix.


   .. container:: section
      :name: GUID-D89C4959-F0C2-4E91-8853-9225F0772DF0


      .. rubric:: Input Parameters
         :name: input-parameters
         :class: sectiontitle


      exec_queue
         The queue where the routine should be executed.


      transa
         Specifies the form of ``op(A)``, the transposition operation
         applied to ``A``. See
         :ref:`onemkl_datatypes`
         for more details.


      transb
         Specifies the form of ``op(B)``, the transposition operation
         applied to ``B``. See
         :ref:`onemkl_datatypes`
         for more details.


      m
         Specifies the number of rows of the matrix ``op(A)`` and of the
         matrix ``C``. The value of m must be at least zero.


      n
         Specifies the number of columns of the matrix ``op(B)`` and the
         number of columns of the matrix ``C``. The value of n must be
         at least zero.


      k
         Specifies the number of columns of the matrix ``op(A)`` and the
         number of rows of the matrix ``op(B)``. The value of k must be
         at least zero.


      alpha
         Scaling factor for the matrix-matrix product.


      a
         Pointer to input matrix ``A``. If ``A`` is not transposed,
         ``A`` is an ``m``-by-``k`` matrix so the array ``a`` must have
         size at least ``lda``\ \*\ ``k``. If ``A`` is transposed, ``A``
         is an ``k``-by-``m`` matrix so the array ``a`` must have size
         at least ``lda``\ \*\ ``m``. See `Matrix and Vector
         Storage <../matrix-storage.html>`__ for
         more details.


      lda
         The leading dimension of ``A``. Must be at least m if ``A`` is
         not transposed, and at least k if ``A`` is transposed. It must
         be positive.


      b
         Pointer to input matrix ``B``. If ``B`` is not transposed,
         ``B`` is an ``k``-by-``n`` matrix so the array ``b`` must have
         size at least ``ldb``\ \*\ ``n``. If ``B`` is transposed, ``B``
         is an ``n``-by-``k`` matrix so the array ``b`` must have size
         at least ``ldb``\ \*\ ``k``. See `Matrix and Vector
         Storage <../matrix-storage.html>`__ for
         more details.


      ldb
         The leading dimension of ``B``. Must be at least k if ``B`` is
         not transposed, and at least n if ``B`` is transposed. It must
         be positive.


      beta
         Scaling factor for matrix ``C``.


      c
         The pointer to input/output matrix ``C``. It must have a size
         of at least ldc\*n. See `Matrix and Vector
         Storage <../matrix-storage.html>`__ for
         more details.


      ldc
         The leading dimension of ``C``. It must be positive and at
         least the size of m.


      dependencies
         List of events to wait for before starting computation, if any.
         If omitted, defaults to no dependencies.


   .. container:: section
      :name: GUID-EEF5C7D0-D206-4961-809F-55DCA3E93F68


      .. rubric:: Output Parameters
         :name: output-parameters
         :class: sectiontitle


      c
         Pointer to the output matrix, overwritten by
         ``alpha*op(A)*op(B) + beta*C``.


   .. container:: section
      :name: GUID-AC72653A-4AC8-4B9D-B7A9-13A725AA19BF


      .. rubric:: Notes
         :name: notes
         :class: sectiontitle


      If ``beta`` = 0, matrix ``C`` does not need to be initialized
      before calling ``gemm``.


   .. container:: section
      :name: GUID-FE9BC089-7D9E-470F-B1B6-2679FBFC249F


      .. rubric:: Return Values
         :name: return-values
         :class: sectiontitle


      Output event to wait on to ensure computation is complete.


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** :ref:`blas-level-3-routines`
      


.. container::

