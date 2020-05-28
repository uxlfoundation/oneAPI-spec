.. _onemkl_lapack_syevd:

onemkl::lapack::syevd
=====================


.. container::


   Computes all eigenvalues and, optionally, all eigenvectors of a real
   symmetric matrix using divide and conquer algorithm.


      ``syevd`` supports the following precisions.


      .. list-table:: 
         :header-rows: 1

         * -  T 
         * -  ``float`` 
         * -  ``double`` 




.. container:: section


   .. rubric:: Description
      :class: sectiontitle


   The routine computes all the eigenvalues, and optionally all the
   eigenvectors, of a real symmetric matrix ``A``. In other words, it
   can compute the spectral factorization of ``A`` as: ``A = Z*λ*ZT``.


   Here Λ is a diagonal matrix whose diagonal elements are the
   eigenvalues λ\ :sub:`i`, and ``Z`` is the orthogonal matrix whose
   columns are the eigenvectors ``z``\ :sub:`i`. Thus,


   ``A*zi = λi*zi`` for ``i = 1, 2, ..., n``.


   If the eigenvectors are requested, then this routine uses a divide
   and conquer algorithm to compute eigenvalues and eigenvectors.
   However, if only eigenvalues are required, then it uses the
   Pal-Walker-Kahan variant of the ``QL`` or ``QR`` algorithm.


onemkl::lapack::syevd (BUFFER Version)
--------------------------------------

.. container::

   .. container:: section


      .. rubric:: Syntax
         :class: sectiontitle


      .. cpp:function::  void onemkl::lapack::syevd(cl::sycl::queue &queue, jobz jobz, onemkl::uplo      upper_lower, std::int64_t n, cl::sycl::buffer<T,1> &a, std::int64_t lda,      cl::sycl::buffer<T,1> &w, cl::sycl::buffer<T,1> &scratchpad, std::int64_t scratchpad_size)

.. container:: section


   .. rubric:: Input Parameters
      :class: sectiontitle


   queue
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
      The leading dimension of ``a``. Must be at least ``max(1,n)``.


   scratchpad_size
      Size of scratchpad memory as a number of floating point elements of type T.
      Size should not be less than the value returned by :ref:`onemkl_lapack_syevd_scratchpad_size` function.


.. container:: section


   .. rubric:: Output Parameters
      :class: sectiontitle


   a
      If ``jobz = job::vec``, then on exit this buffer is overwritten by
      the orthogonal matrix ``Z`` which contains the eigenvectors of
      ``A``.


   w
      Buffer, size at least n. Contains the eigenvalues
      of the matrix ``A`` in ascending order.


   scratchpad
      Buffer holding scratchpad memory to be used by routine for storing intermediate results.


   .. container:: section


      .. rubric:: Throws
         :class: sectiontitle


      onemkl::lapack::exception
         Exception is thrown in case of problems happened during calculations. The ``info`` code of the problem can be obtained by `get_info()` method of exception object:

         If ``info=-i``, the ``i``-th parameter had an illegal value.

         If ``info=i``, and ``jobz = onemkl::job::novec``, then the algorithm
         failed to converge; ``i`` indicates the number of off-diagonal
         elements of an intermediate tridiagonal form which did not
         converge to zero.

         If ``info=i``, and ``jobz = onemkl::job::vec``, then the algorithm failed
         to compute an eigenvalue while working on the submatrix lying in
         rows and columns ``info/(n+1)`` through ``mod(info,n+1)``.

         If ``info`` equals to value passed as scratchpad size, and ``get_detail()`` returns non zero, then passed scratchpad is of insufficient size, and required size should not be less than value return by ``get_detail()`` method of exception object.


onemkl::lapack::syevd (USM Version)
--------------------------------------

.. container::

   .. container:: section


      .. rubric:: Syntax
         :class: sectiontitle


      .. cpp:function::  cl::sycl::event onemkl::lapack::syevd(cl::sycl::queue &queue, jobz jobz, onemkl::uplo      upper_lower, std::int64_t n, T *a, std::int64_t lda, T *w, T *scratchpad, std::int64_t scratchpad_size, const cl::sycl::vector_class<cl::sycl::event> &events = {})

.. container:: section


   .. rubric:: Input Parameters
      :class: sectiontitle


   queue
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
      Pointer to array containing ``A``, size (``lda,*``).
      The second dimension of ``a`` must be at least ``max(1, n)``.


   lda
      The leading dimension of ``a``. Must be at least ``max(1,n)``.


   scratchpad_size
      Size of scratchpad memory as a number of floating point elements of type T.
      Size should not be less than the value returned by :ref:`onemkl_lapack_syevd_scratchpad_size` function.

   events
      List of events to wait for before starting computation. Defaults to empty list.


.. container:: section


   .. rubric:: Output Parameters
      :class: sectiontitle


   a
      If ``jobz = job::vec``, then on exit this array is overwritten by
      the orthogonal matrix ``Z`` which contains the eigenvectors of
      ``A``.


   w
      Pointer to array of size at least n. Contains the eigenvalues
      of the matrix ``A`` in ascending order.


   scratchpad
      Pointer to scratchpad memory to be used by routine for storing intermediate results.


   .. container:: section


      .. rubric:: Throws
         :class: sectiontitle


      onemkl::lapack::exception
         Exception is thrown in case of problems happened during calculations. The ``info`` code of the problem can be obtained by `get_info()` method of exception object:

         If ``info=-i``, the ``i``-th parameter had an illegal value.

         If ``info=i``, and ``jobz = onemkl::job::novec``, then the algorithm
         failed to converge; ``i`` indicates the number of off-diagonal
         elements of an intermediate tridiagonal form which did not
         converge to zero.

         If ``info=i``, and ``jobz = onemkl::job::vec``, then the algorithm failed
         to compute an eigenvalue while working on the submatrix lying in
         rows and columns ``info/(n+1)`` through ``mod(info,n+1)``.

         If ``info`` equals to value passed as scratchpad size, and ``get_detail()`` returns non zero, then passed scratchpad is of insufficient size, and required size should not be less than value return by ``get_detail()`` method of exception object.


   .. container:: section


      .. rubric:: Return Values
         :class: sectiontitle


      Output event to wait on to ensure computation is complete.


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** :ref:`onemkl_lapack-singular-value-eigenvalue-routines` 


