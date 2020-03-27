.. _heevd:

heevd
=====


.. container::


   Computes all eigenvalues and, optionally, all eigenvectors of a
   complex Hermitian matrix using divide and conquer algorithm. This
   routine belongs to the ``onemkl::lapack``\ namespace.


   .. container:: section
      :name: GUID-27408EB8-B8F0-4D65-93CB-8AD0E3E34EC9


      .. rubric:: Syntax
         :class: sectiontitle


      .. cpp:function::  void heevd(queue &exec_queue, job jobz, uplo      upper_lower, std::int64_t n, butter<T,1> &a, std::int64_t lda,      buffer<realT,1> &w, buffer<T,1> &work, std::int64_t lwork,      buffer<realT, 1> &rwork, std::int64_t lrwork, buffer<T,1> &iwork,      std::int64_t liwork, buffer<std::int64_t,1> &info)

      ``heevd`` supports the following precisions.


      .. list-table:: 
         :header-rows: 1

         * -  T 
         * -  ``std::complex<float>`` 
         * -  ``std::complex<double>`` 




.. container:: section
   :name: GUID-D9C0329E-BFA0-4C7A-B67E-2765FE54F2EC


   .. rubric:: Description
      :class: sectiontitle


   The routine computes all the eigenvalues, and optionally all the
   eigenvectors, of a complex Hermitian matrix ``A``. In other words, it
   can compute the spectral factorization of ``A`` as: ``A = Z*Λ*ZH``.


   Here Λ is a real diagonal matrix whose diagonal elements are the
   eigenvalues λ\ :sub:`i`, and ``Z`` is the (complex) unitary matrix
   whose columns are the eigenvectors ``z``\ :sub:`i`. Thus,


   ``A*zi = λi*zi`` for ``i = 1, 2, ..., n``.


   If the eigenvectors are requested, then this routine uses a divide
   and conquer algorithm to compute eigenvalues and eigenvectors.
   However, if only eigenvalues are required, then it uses the
   Pal-Walker-Kahan variant of the ``QL`` or ``QR`` algorithm.


.. container:: section
   :name: GUID-F841BA63-D4EE-4C75-9831-BB804CEA8622


   .. rubric:: Input Parameters
      :class: sectiontitle


   exec_queue
      The queue where the routine should be executed.


   jobz
      Must be ``job::novec`` or ``job::vec``.


      If ``jobz = job::novec``, then only eigenvalues are computed.


      If ``jobz = job::vec``, then eigenvalues and eigenvectors are
      computed.


   upper_lower
      Must be ``uplo::upper`` or ``uplo::lower``.


      If ``upper_lower = job::upper``, a stores the upper triangular
      part of ``A``.


      If ``upper_lower = job::lower``, a stores the lower triangular
      part of ``A``.


   n
      The order of the matrix ``A`` (``0≤n``).


   a
      The buffer a, size (``lda,*``). The buffer a contains the matrix
      ``A``. The second dimension of a must be at least ``max(1, n)``.


   lda
      The leading dimension of a. Must be at least ``max(1,n)``.


   lwork
      The size of the work buffer. Must be computed by
      `heevd_get_lwork <heevd_get_lwork.html>`__.


   lrwork
      The size of the rwork buffer. Must be computed by
      `heevd_get_lwork <heevd_get_lwork.html>`__.


   liwork
      The size of the iwork buffer. Must be computed by
      `heevd_get_lwork <heevd_get_lwork.html>`__.


.. container:: section
   :name: GUID-F0C3D97D-E883-4070-A1C2-4FE43CC37D12


   .. rubric:: Output Parameters
      :class: sectiontitle


   a
      If ``jobz = job::vec``, then on exit this buffer is overwritten by
      the unitary matrix ``Z`` which contains the eigenvectors of ``A``.


   w
      Buffer, size at least n. If ``info = 0``, contains the eigenvalues
      of the matrix ``A`` in ascending order. See also info.


   work
      Buffer of workspace.


   rwork
      Buffer of real precision workspace


   iwork
      Buffer of integer workspace.


   info
      Buffer containing error information.


      If ``info = 0``, the execution is successful.


      If ``info = i``, and ``jobz = job::novec``, then the algorithm
      failed to converge; ``i`` indicates the number of off-diagonal
      elements of an intermediate tridiagonal form which did not
      converge to zero.


      If ``info = i``, and ``jobz = job:vec``, then the algorithm failed
      to compute an eigenvalue while working on the submatrix lying in
      rows and columns ``info/(n+1)`` through ``mod(info,n+1)``.


      If ``info = -i``, the ``i``-th parameter had an illegal value.


.. container:: section
   :name: GUID-C97BF68F-B566-4164-95E0-A7ADC290DDE2


   .. rubric:: Example
      :class: sectiontitle


   An example of how to use ``heevd``\ can be found in the oneMKL
   installation directory, under:


   ::


      examples/sycl/lapack/heevd.cpp


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** `LAPACK
      Routines <lapack.html>`__


