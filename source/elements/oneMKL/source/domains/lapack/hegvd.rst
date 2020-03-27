
hegvd
=====


.. container::


   Computes all eigenvalues and, optionally, eigenvectors of a real
   generalized symmetric definite eigenproblem using a divide and
   conquer method. This routine belongs to the
   ``onemkl::lapack``\ namespace.


   .. container:: section
      :name: GUID-BF2D51BA-A6DB-484A-ACC7-B37A59DB2BF0


      .. rubric:: Syntax
         :class: sectiontitle


      .. cpp:function::  void hegvd(queue &exec_queue, std::int64_t itype,      job jobz, uplo upper_lower, std::int64_t n, buffer<T,1> &a,      std::int64_t lda, buffer<T,1> &b, std::int64_t ldb,      buffer<realT,1> &w, buffer<T,1> &work, std::int64_t lwork,      buffer<realT,1> &rwork, std::int64_t liwork,      buffer<std::int64_t,1> &iwork, std::int64_t liwork,      buffer<std::int64_t,1> &info)

      ``hegvd`` supports the following precisions.


      .. list-table:: 
         :header-rows: 1

         * -  T 
         * -  ``std::complex<float>`` 
         * -  ``std::complex<double>`` 




.. container:: section
   :name: GUID-DE25DD30-D101-4C07-9195-3C6A1C081339


   .. rubric:: Description
      :class: sectiontitle


   The routine computes all the eigenvalues, and optionally, the
   eigenvectors of a complex generalized Hermitian positive-definite
   eigenproblem, of the form


   ``A*x = λ*B*x, A*B*x = λ*x``, or ``B*A*x = λ*x``.


   Here ``A`` and ``B`` are assumed to be Hermitian and ``B`` is also
   positive definite.


   It uses a divide and conquer algorithm.


.. container:: section
   :name: GUID-F841BA63-D4EE-4C75-9831-BB804CEA8622


   .. rubric:: Input Parameters
      :class: sectiontitle


   exec_queue
      The queue where the routine should be executed.


   itype
      Must be 1 or 2 or 3. Specifies the problem type to be solved:


      if itype\ ``= 1``, the problem type is ``A*x = lambda*B*x;``


      if itype\ ``= 2``, the problem type is ``A*B*x = lambda*x;``


      if itype\ ``= 3``, the problem type is ``B*A*x = lambda*x``.


   jobz
      Must be ``job::novec`` or ``job::vec``.


      If ``jobz = job::novec``, then only eigenvalues are computed.


      If ``jobz = job::vec``, then eigenvalues and eigenvectors are
      computed.


   upper_lower
      Must be ``uplo::upper`` or ``uplo::lower``.


      If ``upper_lower = uplo::upper``, a and b store the upper
      triangular part of ``A`` and ``B``.


      If ``upper_lower = uplo::lower``, a and b stores the lower
      triangular part of ``A`` and ``B``.


   n
      The order of the matrices ``A`` and ``B`` (``0≤n``).


   a
      Buffer, size ``a(lda,*)`` contains the upper or lower triangle of
      the Hermitian matrix ``A``, as specified by upper_lower.


      The second dimension of a must be at least ``max(1, n)``.


   lda
      The leading dimension of a; at least ``max(1,n)``.


   b
      Buffer, size ``b(ldb,*)`` contains the upper or lower triangle of
      the Hermitian matrix ``B``, as specified by upper_lower.


      The second dimension of b must be at least ``max(1, n)``.


   ldb
      The leading dimension of b; at least ``max(1,n)``.


   lwork
      The size of the work buffer. Must be computed by
      `hegvd_get_lwork <hegvd_get_lwork.html>`__.


   lrwork
      The size of the rwork buffer. Must be computed by
      `hegvd_get_lwork <hegvd_get_lwork.html>`__.


   liwork
      The size of the iwork buffer. Must be computed by
      `hegvd_get_lwork <hegvd_get_lwork.html>`__.


.. container:: section
   :name: GUID-F0C3D97D-E883-4070-A1C2-4FE43CC37D12


   .. rubric:: Output Parameters
      :class: sectiontitle


   a
      On exit, if ``jobz = job::vec``, then if ``info = 0``, a contains
      the matrix ``Z`` of eigenvectors. The eigenvectors are normalized
      as follows:


      if itype\ ``= 1`` or ``2``, ``Z``\ :sup:`H`\ ``*B*Z = I``;


      if itype\ ``= 3``, ``Z``\ :sup:`H`\ \*\ ``inv(B)*Z = I``;


      If ``jobz = job::novec``, then on exit the upper triangle (if
      ``upper_lower = uplo::upper``) or the lower triangle (if
      ``upper_lower = uplo::lower``) of ``A``, including the diagonal,
      is destroyed.


   b
      On exit, if ``info≤n``, the part of b containing the matrix is
      overwritten by the triangular factor ``U`` or ``L`` from the
      Cholesky factorization ``B = U``\ :sup:`H`\ ``*U``\ or ``B`` =
      ``L``\ \*\ ``L``\ :sup:`H`.


   w
      Buffer, size at least n. If ``info = 0``, contains the eigenvalues
      of the matrix ``A`` in ascending order. See also info.


   work
      Buffer of workspace.


   rwork
      Buffer of real workspace.


   iwork
      Buffer of integer workspace.


   info
      If ``info = 0``, the execution is successful.


      If ``info = -i``, the ``i``-th argument had an illegal value.


      If ``info = i``, and ``jobz = job::novec``, then the algorithm
      failed to converge; ``i`` off-diagonal elements of an intermediate
      tridiagonal form did not converge to zero;


      if ``info = i``, and ``jobz = job::vec``, then the algorithm
      failed to compute an eigenvalue while working on the submatrix
      lying in rows and columns ``info/(n+1)`` through
      ``mod(info, n+1)``.


      If ``info = n + i``, for ``1≤i≤n``, then the leading minor of
      order ``i`` of ``B`` is not positive-definite. The factorization
      of ``B`` could not be completed and no eigenvalues or eigenvectors
      were computed.


.. container:: section
   :name: GUID-C97BF68F-B566-4164-95E0-A7ADC290DDE2


   .. rubric:: Example
      :class: sectiontitle


   An example of how to use ``hegvd``\ can be found in the oneMKL
   installation directory, under:


   ::


      examples/sycl/lapack/sygvd.cpp


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** `LAPACK
      Routines <lapack.html>`__


