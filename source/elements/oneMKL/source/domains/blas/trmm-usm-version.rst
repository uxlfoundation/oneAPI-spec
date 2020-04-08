.. _trmm-usm-version:

trmm (USM Version)
==================


.. container::


   Computes a matrix-matrix product where one input matrix is triangular
   and one input matrix is general.


   .. container:: section
      :name: GUID-15B16EFC-8B31-4459-88DC-A8C5EF6C9932


      .. rubric:: Syntax
         :class: sectiontitle


      .. container:: dlsyntaxpara


         .. cpp:function::  event trmm(queue &exec_queue, uplo         upper_lower, transpose transa, diag unit_diag, std::int64_t m,         std::int64_t n, T alpha, const T* a, std::int64_t lda, T* b,         std::int64_t ldb, const vector_class<event> &dependencies =         {})

         trmm supports the following precisions.


         .. list-table:: 
            :header-rows: 1

            * -  T 
            * -  ``float`` 
            * -  ``double`` 
            * -  ``std::complex<float>`` 
            * -  ``std::complex<double>`` 




   .. container:: section
      :name: GUID-E1AAECF3-E29D-411F-B052-2F2E8080F3A1


      .. rubric:: Description
         :class: sectiontitle


      The trmm routines compute a scalar-matrix-matrix product where one
      of the matrices in the multiplication is triangular. The argument
      ``left_right`` determines if the triangular matrix, ``A``, is on
      the left of the multiplication (``left_right`` = ``side::left``)
      or on the right (``left_right`` = ``side::right``). Depending on
      ``left_right``. The operation is defined as


     


         B <- alpha*op(A)*B


      or


     


         B <- alpha*B*op(A)


      where:


      op(``A``) is one of op(``A``) = *A*, or op(``A``) =
      ``A``\ :sup:`T`, or op(``A``) = ``A``\ :sup:`H`,


      ``alpha`` is a scalar,


      ``A`` is a triangular matrix, and ``B`` is a general matrix.


      Here ``B`` is ``m`` x ``n`` and ``A`` is either ``m`` x ``m`` or
      ``n`` x ``n``, depending on ``left_right``.


   .. container:: section
      :name: GUID-DE8B0FD7-11E3-42BC-99ED-3A07040FA6CB


      .. rubric:: Input Parameters
         :class: sectiontitle


      exec_queue
         The queue where the routine should be executed.


      left_right
         Specifies whether ``A`` is on the left side of the
         multiplication (``side::left``) or on the right side
         (``side::right``). See
         :ref:`onemkl_datatypes` for
         more details.


      uplo
         Specifies whether the matrix ``A`` is upper or lower
         triangular. See
         :ref:`onemkl_datatypes` for
         more details.


      trans
         Specifies op(``A``), the transposition operation applied to
         ``A``. See
         :ref:`onemkl_datatypes` for
         more details.


      unit_diag
         Specifies whether ``A`` is assumed to be unit triangular (all
         diagonal elements are 1). See
         :ref:`onemkl_datatypes` for
         more details.


      m
         Specifies the number of rows of ``B``. The value of ``m`` must
         be at least zero.


      n
         Specifies the number of columns of ``B``. The value of ``n``
         must be at least zero.


      alpha
         Scaling factor for the matrix-matrix product.


      a
         Pointer to input matrix ``A``. Must have size at least
         ``lda``\ \*\ ``m`` if ``left_right`` = ``side::left``, or
         ``lda``\ \*\ ``n`` if ``left_right`` = ``side::right``. See
         `Matrix and Vector
         Storage <../matrix-storage.html>`__ for
         more details.


      lda
         Leading dimension of ``A``. Must be at least ``m`` if
         ``left_right`` = ``side::left``, and at least ``n`` if
         ``left_right`` = ``side::right``. Must be positive.


      b
         Pointer to input/output matrix ``B``. Must have size at least
         ``ldb``\ \*\ ``n``. See `Matrix and Vector
         Storage <../matrix-storage.html>`__ for
         more details.


      ldb
         Leading dimension of ``B``. Must be at least ``m`` and
         positive.


      dependencies
         List of events to wait for before starting computation, if any.
         If omitted, defaults to no dependencies.


   .. container:: section
      :name: GUID-1F1FF9D8-3833-4C9E-9CAC-53BA1791DCF1


      .. rubric:: Output Parameters
         :class: sectiontitle


      b
         Pointer to the output matrix, overwritten by
         ``alpha``\ \*op(``A``)\*\ ``B`` or
         ``alpha``\ \*\ ``B``\ \*op(``A``).


   .. container:: section
      :name: EXAMPLE_5EF48B8A07D849EA84A74FE22F0D5B24


      .. rubric:: Notes
         :class: sectiontitle


      If ``alpha`` = 0, matrix ``B`` is set to zero, and ``A`` and ``B``
      do not need to be initialized at entry.


   .. container:: section
      :name: GUID-FE9BC089-7D9E-470F-B1B6-2679FBFC249F


      .. rubric:: Return Values
         :class: sectiontitle


      Output event to wait on to ensure computation is complete.


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** :ref:`blas-level-3-routines`
      


