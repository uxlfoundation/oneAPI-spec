.. _hetrd:

hetrd
=====


.. container::


   Reduces a complex Hermitian matrix to tridiagonal form. This routine
   belongs to the ``onemkl::lapack``\ namespace.


   .. container:: section
      :name: GUID-45C31AF5-960E-44EA-95AE-8F09E043F00A


      .. rubric:: Syntax
         :class: sectiontitle


      .. cpp:function::  void hetrd(queue &exec_queue, uplo upper_lower,      std::int64_t n, buffer<T,1> &a, std::int64_t lda, buffer<realT,1>      &d, buffer<realT,1> &e, buffer<T,1> &tau, buffer<T,1> &work,      std::int64_t lwork, buffer<std::int64_t,1> &info)

      ``hetrd`` supports the following precisions.


      .. list-table:: 
         :header-rows: 1

         * -  Routine name 
           -  T 
         * -  ``chetrd`` 
           -  ``std::complex<float>`` 
         * -  ``zhetrd`` 
           -  ``std::complex<double>`` 




.. container:: section
   :name: GUID-D81658C9-221D-4347-AD47-193372E5E2DB


   .. rubric:: Description
      :class: sectiontitle


   The routine reduces a complex Hermitian matrix ``A`` to symmetric
   tridiagonal form ``T`` by a unitary similarity transformation:
   ``A = Q*T*QH``. The unitary matrix ``Q`` is not formed explicitly but
   is represented as a product of ``n``-1 elementary reflectors.
   Routines are provided to work with ``Q`` in this representation.


.. container:: section
   :name: GUID-26A5866D-0DF8-4835-8776-E5E73F0C657A


   .. rubric:: Input Parameters
      :class: sectiontitle


   exec_queue
      The queue where the routine should be executed.


   upper_lower
      Must be ``uplo::upper`` or ``uplo::lower``.


      If ``upper_lower = uplo::upper``, a stores the upper triangular
      part of ``A``.


      If ``upper_lower = uplo::lower``, a stores the lower triangular
      part of ``A``.


   n
      The order of the matrices ``A``\ ``(0≤n)``.


   a
      Buffer, size ``(lda,*)``. The buffer a contains either the upper
      or lower triangle of the Hermitian matrix ``A``, as specified by
      upper_lower.


      The second dimension of a must be at least ``max(1, n)``.


   lda
      The leading dimension of a; at least ``max(1, n)``


   lwork
      The side of the work buffer. Should be computed by
      `hetrd_get_lwork <hetrd_get_lwork.html>`__


.. container:: section
   :name: GUID-F0C3D97D-E883-4070-A1C2-4FE43CC37D12


   .. rubric:: Output Parameters
      :class: sectiontitle


   a
      On exit,


      if ``upper_lower = uplo::upper``, the diagonal and first
      superdiagonal of ``A`` are overwritten by the corresponding
      elements of the tridiagonal matrix ``T``, and the elements above
      the first superdiagonal, with the buffer tau, represent the
      orthogonal matrix ``Q`` as a product of elementary reflectors;


      if ``upper_lower = uplo::lower``, the diagonal and first
      subdiagonal of ``A`` are overwritten by the corresponding elements
      of the tridiagonal matrix ``T``, and the elements below the first
      subdiagonal, with the buffer tau, represent the orthogonal matrix
      ``Q`` as a product of elementary reflectors.


   d
      Buffer containing the diagonal elements of the matrix ``T``. The
      dimension of d must be at least ``max(1, n)``.


   e
      Buffer containing the off diagonal elements of the matrix ``T``.
      The dimension of e must be at least ``max(1, n-1)``.


   tau
      Buffer, size at least ``max(1, n-1)``. Stores ``(n-1)`` scalars
      that define elementary reflectors in decomposition of the unitary
      matrix ``Q`` in a product of ``n-1`` elementary reflectors.


   work
      Buffer of workspace.


   info
      If info\ ``=0``, the execution is successful.


      If info\ ``=-i``, the ``i``-th parameter had an illegal value.


.. container:: section
   :name: GUID-C97BF68F-B566-4164-95E0-A7ADC290DDE2


   .. rubric:: Example
      :class: sectiontitle


   An example of how to use ``hetrd``\ can be found in the oneMKL
   installation directory, under:


   ::


      examples/sycl/lapack/sytrd.cpp


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** `LAPACK
      Routines <lapack.html>`__


