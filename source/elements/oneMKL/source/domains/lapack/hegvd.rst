.. _onemkl_lapack_hegvd:

onemkl::lapack::hegvd
=====================


.. container::


   Computes all eigenvalues and, optionally, eigenvectors of a real
   generalized symmetric definite eigenproblem using a divide and
   conquer method.


      ``hegvd`` supports the following precisions.


      .. list-table:: 
         :header-rows: 1

         * -  T 
         * -  ``std::complex<float>`` 
         * -  ``std::complex<double>`` 




.. container:: section


   .. rubric:: Description
      :class: sectiontitle


   The routine computes all the eigenvalues, and optionally, the
   eigenvectors of a complex generalized Hermitian positive-definite
   eigenproblem, of the form


   ``A*x = λ*B*x, A*B*x = λ*x``, or ``B*A*x = λ*x``.


   Here ``A`` and ``B`` are assumed to be Hermitian and ``B`` is also
   positive definite.


   It uses a divide and conquer algorithm.


onemkl::lapack::hegvd (BUFFER Version)
--------------------------------------

.. container::

   .. container:: section


      .. rubric:: Syntax
         :class: sectiontitle


      .. cpp:function::  void onemkl::lapack::hegvd(cl::sycl::queue &queue, std::int64_t itype,      onemkl::job jobz, onemkl::uplo upper_lower, std::int64_t n, cl::sycl::buffer<T,1> &a,      std::int64_t lda, cl::sycl::buffer<T,1> &b, std::int64_t ldb,      cl::sycl::buffer<realT,1> &w, cl::sycl::buffer<T,1> &scratchpad, std::int64_t scratchpad_size)

.. container:: section


   .. rubric:: Input Parameters
      :class: sectiontitle


   queue
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


   scratchpad_size
      Size of scratchpad memory as a number of floating point elements of type T.
      Size should not be less than the value returned by :ref:`onemkl_lapack_hegvd_scratchpad_size` function.


.. container:: section


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
      of the matrix ``A`` in ascending order.


   scratchpad
      Buffer holding scratchpad memory to be used by routine for storing intermediate results.


   .. container:: section


      .. rubric:: Throws
         :class: sectiontitle


      onemkl::lapack::exception
         Exception is thrown in case of problems happened during calculations. The ``info`` code of the problem can be obtained by `get_info()` method of exception object:

         If ``info=-i``, the ``i``-th parameter had an illegal value.

         For ``info≤n``:

            If ``info=i``, and ``jobz = onemkl::job::novec``, then the algorithm
            failed to converge; ``i`` indicates the number of off-diagonal elements
            of an intermediate tridiagonal form which did not converge to zero;

            If ``info=i``, and ``jobz = onemkl::job::vec``, then the algorithm
            failed to compute an eigenvalue while working on the submatrix
            lying in rows and columns ``info/(n+1)`` through
            ``mod(info, n+1)``.

         For ``info>n``:

            If ``info=n+i``, for ``1≤i≤n``, then the leading minor of
            order ``i`` of ``B`` is not positive-definite. The factorization
            of ``B`` could not be completed and no eigenvalues or eigenvectors
            were computed.

         If ``info`` equals to value passed as scratchpad size, and ``get_detail()`` returns non zero, then passed scratchpad is of insufficient size, and required size should not be less than value return by ``get_detail()`` method of exception object.


onemkl::lapack::hegvd (USM Version)
--------------------------------------

.. container::

   .. container:: section


      .. rubric:: Syntax
         :class: sectiontitle


      .. cpp:function::  cl::sycl::event onemkl::lapack::hegvd(cl::sycl::queue &queue, std::int64_t itype,      onemkl::job jobz, onemkl::uplo upper_lower, std::int64_t n, T *a,      std::int64_t lda, T *b, std::int64_t ldb,      RealT *w, T *scratchpad, std::int64_t scratchpad_size, const cl::sycl::vector_class<cl::sycl::event> &events = {})

.. container:: section


   .. rubric:: Input Parameters
      :class: sectiontitle


   queue
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
      Pointer to array of size ``a(lda,*)`` containing the upper or lower triangle of
      the Hermitian matrix ``A``, as specified by upper_lower.
      The second dimension of ``a`` must be at least ``max(1, n)``.


   lda
      The leading dimension of a; at least ``max(1,n)``.


   b
      Pointer to array of size ``b(ldb,*)`` containing the upper or lower triangle of
      the Hermitian matrix ``B``, as specified by upper_lower.
      The second dimension of b must be at least ``max(1, n)``.


   ldb
      The leading dimension of b; at least ``max(1,n)``.


   scratchpad_size
      Size of scratchpad memory as a number of floating point elements of type T.
      Size should not be less than the value returned by :ref:`onemkl_lapack_hegvd_scratchpad_size` function.

   events
      List of events to wait for before starting computation. Defaults to empty list.


.. container:: section


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
      Pointer to array of size at least n. If ``info = 0``, contains the eigenvalues
      of the matrix ``A`` in ascending order.


   scratchpad
      Pointer to scratchpad memory to be used by routine for storing intermediate results.


   .. container:: section


      .. rubric:: Throws
         :class: sectiontitle


      onemkl::lapack::exception
         Exception is thrown in case of problems happened during calculations. The ``info`` code of the problem can be obtained by `get_info()` method of exception object:

         If ``info=-i``, the ``i``-th parameter had an illegal value.

         For ``info≤n``:

            If ``info=i``, and ``jobz = onemkl::job::novec``, then the algorithm
            failed to converge; ``i`` indicates the number of off-diagonal elements
            of an intermediate tridiagonal form which did not converge to zero;

            If ``info=i``, and ``jobz = onemkl::job::vec``, then the algorithm
            failed to compute an eigenvalue while working on the submatrix
            lying in rows and columns ``info/(n+1)`` through
            ``mod(info, n+1)``.

         For ``info>n``:

            If ``info=n+i``, for ``1≤i≤n``, then the leading minor of
            order ``i`` of ``B`` is not positive-definite. The factorization
            of ``B`` could not be completed and no eigenvalues or eigenvectors
            were computed.

         If ``info`` equals to value passed as scratchpad size, and ``get_detail()`` returns non zero, then passed scratchpad is of insufficient size, and required size should not be less than value return by ``get_detail()`` method of exception object.


   .. container:: section


      .. rubric:: Return Values
         :class: sectiontitle


      Output event to wait on to ensure computation is complete.


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** :ref:`onemkl_lapack-singular-value-eigenvalue-routines` 


