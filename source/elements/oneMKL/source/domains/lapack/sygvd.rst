
sygvd
=====


.. container::


   Computes all eigenvalues and, optionally, eigenvectors of a real
   generalized symmetric definite eigenproblem using a divide and
   conquer method. This routine belongs to the
   ``onemkl::lapack``\ namespace.


   .. container:: section
      :name: GUID-29D24E37-E230-495D-9821-2BEA82B7E5CA


      .. rubric:: Syntax
         :class: sectiontitle


      .. cpp:function::  void sygvd(queue &exec_queue, std::int64_t itype,      job jobz, uplo upper_lower, std::int64_t n, buffer<T,1> &a,      std::int64_t lda, buffer<T,1> &b, std::int64_t ldb, buffer<T,1>      &w, buffer<T,1> &work, std::int64_t &lwork, buffer<std::int64_t,1>      &iwork, std::int64_t liwork, buffer<std::int64_t,1> &info)

      ``sygvd`` supports the following precisions.


      .. list-table:: 
         :header-rows: 1

         * -  T 
         * -  ``float`` 
         * -  ``double`` 




.. container:: section
   :name: GUID-1D5CC125-1BEF-4FA3-B688-A64D5C4E75AB


   .. rubric:: Description
      :class: sectiontitle


   The routine computes all the eigenvalues, and optionally, the
   eigenvectors of a real generalized symmetric-definite eigenproblem,
   of the form


   ``A*x = λ*B*x``, ``A*B*x = λ*x``, or ``B*A*x = λ*x`` .


   Here ``A`` and ``B`` are assumed to be symmetric and ``B`` is also
   positive definite.


   It uses a divide and conquer algorithm.


.. container:: section
   :name: GUID-26A5866D-0DF8-4835-8776-E5E73F0C657A


   .. rubric:: Input Parameters
      :class: sectiontitle


   exec_queue
      The queue where the routine should be executed.


   itype
      Must be 1 or 2 or 3. Specifies the problem type to be solved:


      if itype\ ``= 1``, the problem type is ``A*x = lambda*B*x``;


      if itype\ ``= 2``, the problem type is ``A*B*x = lambda*x``;


      if itype\ ``= 3``, the problem type is ``B*A*x = lambda*x``.


   jobz
      Must be ``job::novec`` or ``job::vec``.


      If ``jobz = job::novec``, then only eigenvalues are computed.


      If ``jobz = job::vec``, then eigenvalues and eigenvectors are
      computed.


   upper_lower
      Must be ``uplo::upper`` or ``uplo::lower``.


      If ``upper_lower = job::upper``, a and b store the upper
      triangular part of ``A`` and ``B``.


      If ``upper_lower = job::lower``, a and b stores the lower
      triangular part of ``A`` and ``B``.


   n
      The order of the matrices ``A`` and ``B``\ ``(0≤n)``.


   a
      Buffer, size a\ ``(lda,*)`` contains the upper or lower triangle
      of the symmetric matrix ``A``, as specified by upper_lower. The
      second dimension of a must be at least ``max(1, n)``.


   lda
      The leading dimension of a; at least ``max(1, n)``.


   b
      Buffer, size b\ ``(ldb,*)`` contains the upper or lower triangle
      of the symmetric matrix ``B``, as specified by upper_lower. The
      second dimension of b must be at least ``max(1, n)``.


   ldb
      The leading dimension of b; at least ``max(1, n)``.


   lwork
      The size of the work buffer. Should be computed by
      `sygvd_get_lwork <sygvd_get_lwork.html>`__.


   liwork
      The size of the iwork buffer. Should be computed by
      `sygvd_get_lwork <sygvd_get_lwork.html>`__.


.. container:: section
   :name: GUID-F0C3D97D-E883-4070-A1C2-4FE43CC37D12


   .. rubric:: Output Parameters
      :class: sectiontitle


   a
      On exit, if ``jobz = job::vec``, then if ``info = 0``, ``a``
      contains the matrix ``Z`` of eigenvectors. The eigenvectors are
      normalized as follows:


      if itype\ ``= 1``\ or ``2`` , ``Z``\ :sup:`T`\ ``*B*Z = I``;


      if itype\ ``= 3`` , ``Z``\ :sup:`T`\ ``*inv(B)*Z = I``;


      If ``jobz = job::novec``, then on exit the upper triangle (if
      ``upper_lower = uplo::upper``) or the lower triangle (if
      ``upper_lower = uplo::lower``) of ``A``, including the diagonal,
      is destroyed.


   b
      On exit, if ``info≤n``, the part of b containing the matrix is
      overwritten by the triangular factor ``U`` or ``L`` from the
      Cholesky factorization ``B`` = ``U``\ :sup:`T`\ ``*U`` or
      ``B = L*L``\ :sup:`T`.


   w
      Buffer, size at least ``n``. If ``info = 0``, contains the
      eigenvalues of the matrix ``A`` in ascending order. See also
      ``info``.


   work
      Buffer of workspace.


   iwork
      Buffer of integer workspace.


   info
      Buffer containing error information.


      If info\ ``= 0``, the execution is successful.


      If info\ ``> 0``, an error code is returned as specified below.


      For info\ ``≤ n``:


      -  If ``info = i``, and ``jobz = job::novec``, then the algorithm
         failed to converge; ``i`` indicates the number of off-diagonal
         elements of an intermediate tridiagonal form which did not
         converge to zero.


      -  If ``info = i``, and ``jobz = job:vec``, then the algorithm
         failed to compute an eigenvalue while working on the submatrix
         lying in rows and columns ``info/(n+1)`` through
         ``mod(info,n+1)``.


      For info\ ``> n``:


      -  If info\ ``= n + i``, for ``1 ≤i≤n``, then the leading minor of
         order ``i`` of ``B`` is not positive-definite. The
         factorization of ``B`` could not be completed and no
         eigenvalues or eigenvectors were computed.


      -  If info\ ``= -i``, the ``i``-th parameter had an illegal value.


.. container:: section
   :name: GUID-C97BF68F-B566-4164-95E0-A7ADC290DDE2


   .. rubric:: Example
      :class: sectiontitle


   An example of how to use ``sygvd``\ can be found in the oneMKL
   installation directory, under:


   ::


      examples/sycl/lapack/sygvd.cpp


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** `LAPACK
      Routines <lapack.html>`__


