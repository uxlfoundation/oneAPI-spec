.. _her2k-usm-version:

her2k (USM Version)
===================


.. container::


   Performs a Hermitian rank-2k update.


   .. container:: section
      :name: GUID-1839F1B0-EFE0-40A4-901E-53E7F9B395C2


      .. rubric:: Syntax
         :name: syntax
         :class: sectiontitle


      .. container:: dlsyntaxpara


         .. cpp:function::  event her2k(queue &exec_queue, uplo         upper_lower, transpose trans, std::int64_t n, std::int64_t k, T         alpha, const T\* a, std::int64_t lda, const T\* b, std::int64_t         ldb, T_real beta, T\* c, std::int64_t ldc, const         vector_class<event> &dependencies = {})

         The USM version of her2k supports the following precisions:


         .. list-table:: 
            :header-rows: 1

            * -  T 
              -  T_real 
            * -  ``std::complex<float>`` 
              -  ``float`` 
            * -  ``std::complex<double>`` 
              -  ``double`` 




   .. container:: section
      :name: GUID-6DDD93FE-028E-400C-BBD0-CA13132FAC35


      .. rubric:: Description
         :name: description
         :class: sectiontitle


      The her2k routines perform a rank-2k update of an ``n`` x ``n``
      Hermitian matrix ``C`` by general matrices ``A`` and ``B``. If
      ``trans`` = ``transpose::nontrans``. The operation is defined as


     


         C <- alpha*A*B :sup:`H` + conjg(alpha)*B*A :sup:`H` + beta*C


      where ``A`` is ``n`` x ``k`` and ``B`` is ``k`` x ``n``.


      If ``trans`` = ``transpose::conjtrans``, the operation is defined
      as:


     


         C <- alpha*B*A :sup:`H` + conjg(alpha)*A*B :sup:`H` + beta*C


      where ``A`` is ``k`` x ``n`` and ``B`` is ``n`` x ``k``.


      In both cases:


      ``alpha`` is a complex scalar and ``beta`` is a real scalar.


      ``C`` is a Hermitian matrix and ``A, B`` are general matrices.


      The inner dimension of both matrix multiplications is ``k``.


   .. container:: section
      :name: GUID-54538396-B04D-4A2A-8A7D-E503A6F815AD


      .. rubric:: Input Parameters
         :name: input-parameters
         :class: sectiontitle


      exec_queue
         The queue where the routine should be executed.


      upper_lower
         Specifies whether ``A``'s data is stored in its upper or lower
         triangle. See
         :ref:`onemkl_datatypes` for
         more details.


      trans
         Specifies the operation to apply, as described above. Supported
         operations are ``transpose::nontrans`` and
         ``transpose::conjtrans``.


      n
         The number of rows and columns in ``C``. The value of ``n``
         must be at least zero.


      k
         The inner dimension of matrix multiplications. The value of
         ``k`` must be at least equal to zero.


      alpha
         Complex scaling factor for the rank-2\ ``k`` update.


      a
         Pointer to input matrix ``A``. If ``trans`` =
         ``transpose::nontrans``, ``A`` is an ``n``-by-``k`` matrix so
         the array ``a`` must have size at least ``lda``\ \*\ ``k``.
         Otherwise, ``A`` is an ``k``-by-``n`` matrix so the array ``a``
         must have size at least ``lda``\ \*\ ``n``. See `Matrix and
         Vector
         Storage <../matrix-storage.html>`__ for
         more details.


      lda
         Leading dimension of ``A``. Must be at least ``n`` if ``trans``
         = ``transpose::nontrans``, and at least ``k`` otherwise. Must
         be positive.


      beta
         Real scaling factor for matrix ``C``.


      b
         Pointer to input matrix ``B``. If ``trans`` =
         ``transpose::nontrans``, ``B`` is an ``k``-by-``n`` matrix so
         the array ``b`` must have size at least ``ldb``\ \*\ ``n``.
         Otherwise, ``B`` is an ``n``-by-``k`` matrix so the array ``b``
         must have size at least ``ldb``\ \*\ ``k``. See `Matrix and
         Vector
         Storage <../matrix-storage.html>`__ for
         more details.


      ldb
         Leading dimension of ``B``. Must be at least ``k`` if ``trans``
         = ``transpose::nontrans``, and at least ``n`` otherwise. Must
         be positive.


      c
         Pointer to input/output matrix ``C``. Must have size at least
         ``ldc``\ \*\ ``n``. See `Matrix and Vector
         Storage <../matrix-storage.html>`__ for
         more details.


      ldc
         Leading dimension of ``C``. Must be positive and at least
         ``n``.


      dependencies
         List of events to wait for before starting computation, if any.
         If omitted, defaults to no dependencies.


   .. container:: section
      :name: GUID-48D39D42-B29F-4428-A588-9058570B5D5E


      .. rubric:: Output Parameters
         :name: output-parameters
         :class: sectiontitle


      c
         Pointer to the output matrix, overwritten by the updated ``C``
         matrix.


   .. container:: section
      :name: GUID-4A36C03B-4011-4B48-A192-E3873031C1CC


      .. rubric:: Return Values
         :name: return-values
         :class: sectiontitle


      Output event to wait on to ensure computation is complete.


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** :ref:`blas-level-3-routines`
      


.. container::

