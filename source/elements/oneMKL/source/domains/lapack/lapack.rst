.. _onemkl_lapack:

LAPACK Routines
+++++++++++++++++


.. container::


   oneAPI Math Kernel Library (oneMKL) implements routines from the
   LAPACK package that are used for solving systems of linear equations,
   linear least squares problems, eigenvalue and singular value
   problems, and performing a number of related computational tasks. The
   library includes LAPACK routines for both real and complex data.
   Routines are supported for systems of equations with the following
   types of matrices:


   -  General


   -  Banded


   -  Symmetric or Hermitian positive-definite (full, packed, and
      rectangular full packed (RFP) storage)


   -  Symmetric or Hermitian positive-definite banded


   -  Symmetric or Hermitian indefinite (both full and packed storage)


   -  Symmetric or Hermitian indefinite banded


   -  Triangular (full, packed, and RFP storage)


   -  Triangular banded


   -  Tridiagonal


   -  Diagonally dominant tridiagonal.


   .. container:: Note


      .. rubric:: Note
         :class: NoteTipHead


      Different arrays used as parameters to oneMKL LAPACK routines must
      not overlap.


   .. container:: Note


      .. rubric:: Warning
         :name: warning
         :class: NoteTipHead


      LAPACK routines assume that input matrices do not contain IEEE 754
      special values such as INF or NaN values. Using these special
      values may cause LAPACK to return unexpected results or become
      unstable.


.. container::


   -  `gebrd <gebrd.html>`__
      Reduces a general matrix to bidiagonal form. This routine belongs
      to the ``onemkl::lapack`` namespace.
   -  `gebrd_get_lwork <gebrd_get_lwork.html>`__
      Computes the worksize needed for the function,
      `gebrd <gebrd.html>`__. This
      routine belongs to the ``onemkl::lapack`` namespace.
   -  `geqrf <geqrf.html>`__
      Computes the QR factorization of a general m-by-n matrix. This
      routine belongs to the ``onemkl::lapack`` namespace.
   -  `geqrf_get_lwork <geqrf_get_lwork.html>`__
      Computes the worksize needed for the function geqrf. This routine
      belongs to the ``onemkl::lapack`` namespace.
   -  `geqrf_batch <geqrf_batch.html>`__
      Computes the QR factorizations of a batch of general matrices.
      This routine belongs to the ``onemkl::lapack`` namespace.
   -  `gesvd <gesvd.html>`__
      Computes the singular value decomposition of a general rectangular
      matrix. This routine belongs to the ``onemkl::lapack`` namespace.
   -  `gesvd_get_lwork <gesvd_get_lwork.html>`__
      Computes the worksize needed for the function
      `gesvd <gesvd.html>`__. This
      routine belongs to the ``onemkl::lapack`` namespace.
   -  `getrf <getrf.html>`__
      Computes the LU factorization of a general m-by-n matrix. This
      routine belongs to the ``onemkl::lapack`` namespace.
   -  `getrf_batch <getrf_batch.html>`__
      Computes the LU factorizations of a batch of general matrices.
      This routine belongs to the ``onemkl::lapack`` namespace.
   -  `getri <getri.html>`__
      Computes the inverse of an LU-factored general matrix determined
      by `getrf <getrf.html>`__.This
      routine belongs to the ``onemkl::lapack`` namespace.
   -  `getri_batch <getri_batch.html>`__
      Computes the inverses of a batch of LU-factored matrices
      determined by
      `getrf_batch <getrf_batch.html>`__.
      This routine belongs to the ``onemkl::lapack`` namespace.
   -  `getri_get_lwork <getri_get_lwork.html>`__
      Computes the worksize needed for the function
      `getri <getri.html>`__. This
      routine belongs to the ``onemkl::lapack`` namespace.
   -  `getrs <getrs.html>`__
      Solves a system of linear equations with an LU-factored square
      coefficient matrix, with multiple right-hand sides. This routine
      belongs to the ``onemkl::lapack`` namespace.
   -  `getrs_batch <getrs_batch.html>`__
      Solves a system of linear equations with a batch of LU-factored
      square coefficient matrices, with multiple right-hand sides. This
      routine belongs to the ``onemkl::lapack`` namespace.
   -  `heevd <heevd.html>`__
      Computes all eigenvalues and, optionally, all eigenvectors of a
      complex Hermitian matrix using divide and conquer algorithm. This
      routine belongs to the ``onemkl::lapack`` namespace.
   -  `heevd_get_lwork <heevd_get_lwork.html>`__
      Computes the worksize needed for the function,
      `heevd <heevd.html>`__. This
      routine belongs to the ``onemkl::lapack`` namespace.
   -  `hegvd <hegvd.html>`__
      Computes all eigenvalues and, optionally, eigenvectors of a real
      generalized symmetric definite eigenproblem using a divide and
      conquer method. This routine belongs to the
      ``onemkl::lapack`` namespace.
   -  `hegvd_get_lwork <hegvd_get_lwork.html>`__
      Computes the worksize needed for the function,
      `hegvd <hegvd.html>`__. This
      routine belongs to the ``onemkl::lapack`` namespace.
   -  `hetrd <hetrd.html>`__
      Reduces a complex Hermitian matrix to tridiagonal form. This
      routine belongs to the ``onemkl::lapack`` namespace.
   -  `hetrd_get_lwork <hetrd_get_lwork.html>`__
      Computes the worksize needed for the function,
      `hetrd <hetrd.html>`__. This
      routine belongs to the ``onemkl::lapack`` namespace.
   -  `orgbr <orgbr.html>`__
      Generates the real orthogonal matrix ``Q`` or ``P``\ :sup:`T`
      determined by
      `gebrd <gebrd.html>`__. This
      routine belongs to the ``onemkl::lapack`` namespace.
   -  `orgbr_get_lwork <orgbr_get_lwork.html>`__
      Computes the worksize needed for the function
      `orgbr <orgbr.html>`__. This
      routine belongs to the ``onemkl::lapack`` namespace.
   -  `orgqr <orgqr.html>`__
      Generates the real orthogonal matrix Q of the QR factorization
      formed by geqrf. This routine belongs to the
      ``onemkl::lapack`` namespace.
   -  `orgqr_batch <orgqr_batch.html>`__
      Generates the orthogonal/unitary matrix ``Q``\ :sub:`i` of the QR
      factorizations for a group of general matrices. This routine
      belongs to the ``onemkl::lapack`` namespace.
   -  `orgqr_get_lwork <orgqr_get_lwork.html>`__
      Computes the worksize needed for the function orgqr. This routine
      belongs to the ``onemkl::lapack`` namespace.
   -  `orgtr <orgtr.html>`__
      Generates the real orthogonal matrix Q determined by
      `?sytrd <sytrd.html>`__. This
      routine belongs to the ``onemkl::lapack`` namespace.
   -  `orgtr_get_lwork <orgtr_get_lwork.html>`__
      Computes the worksize needed for the function,
      `orgtr <orgtr.html>`__. This
      routine belongs to the ``onemkl::lapack`` namespace.
   -  `ormqr <ormqr.html>`__
      Multiplies a real matrix by the orthogonal matrix Q of the QR
      factorization formed by geqrf. This routine belongs to the
      ``onemkl::lapack`` namespace.
   -  `ormqr_get_lwork <ormqr_get_lwork.html>`__
      Computes the worksize needed for the function
      `ormqr <ormqr.html>`__. This
      routine belongs to the ``onemkl::lapack`` namespace.
   -  `ormtr <ormtr.html>`__
      Multiplies a real matrix by the real orthogonal matrix ``Q``
      determined by
      `?sytrd <sytrd.html>`__. This
      routine belongs to the ``onemkl::lapack`` namespace.
   -  `ormtr_get_lwork <ormtr_get_lwork.html>`__
      Computes the worksize needed for the function,
      `ormtr <ormtr.html>`__. This
      routine belongs to the ``onemkl::lapack`` namespace.
   -  `potrf <potrf.html>`__
      Computes the Cholesky factorization of a symmetric (Hermitian)
      positive-definite matrix.This routine belongs to the
      ``onemkl::lapack`` namespace.
   -  `potrf (USM
      Version) <potrf-usm-version.html>`__
      Computes the Cholesky factorization of a symmetric (Hermitian)
      positive-definite matrix.This routine belongs to the
      ``onemkl::lapack`` namespace.
   -  `potrf_batch <potrf_batch.html>`__
      Computes the Cholesky factorizations of a batch of symmetric
      (Hermitian) positive-definite matrices. This routine belongs to
      the ``onemkl::lapack`` namespace.
   -  `potri <potri.html>`__
      Computes the inverse of a symmetric (Hermitian) positive-definite
      matrix using the Cholesky factorization. This routine belongs to
      the ``onemkl::lapack`` namespace.
   -  `potrs <potrs.html>`__
      Solves a system of linear equations with a Cholesky-factored
      symmetric (Hermitian) positive-definite coefficient matrix. This
      routine belongs to the ``onemkl::lapack`` namespace.
   -  `potrs (USM
      Version) <potrs-usm-version.html>`__
      Solves a system of linear equations with a Cholesky-factored
      symmetric (Hermitian) positive-definite coefficient matrix. This
      routine belongs to the onemkl::lapack namespace.
   -  `potrs_batch <potrs_batch.html>`__
      Solves a system of linear equations with a batch of
      Cholesky-factored symmetric (Hermitian) positive-definite
      coefficient matrices. This routine belongs to the
      ``onemkl::lapack`` namespace.
   -  `syevd <syevd.html>`__
      Computes all eigenvalues and, optionally, all eigenvectors of a
      real symmetric matrix using divide and conquer algorithm. This
      routine belongs to the ``onemkl::lapack`` namespace.
   -  `syevd_get_lwork <syevd_get_lwork.html>`__
      Computes the worksize needed for the function,
      `syevd <syevd.html>`__. This
      routine belongs to the ``onemkl::lapack`` namespace.
   -  `sygvd <sygvd.html>`__
      Computes all eigenvalues and, optionally, eigenvectors of a real
      generalized symmetric definite eigenproblem using a divide and
      conquer method. This routine belongs to the
      ``onemkl::lapack`` namespace.
   -  `sygvd_get_lwork <sygvd_get_lwork.html>`__
      Computes the worksize needed for the function,
      `sygvd <sygvd.html>`__. This
      routine belongs to the ``onemkl::lapack`` namespace.
   -  `sytrd <sytrd.html>`__
      Reduces a real symmetric matrix to tridiagonal form. This routine
      belongs to the ``onemkl::lapack`` namespace.
   -  `sytrd_get_lwork <sytrd_get_lwork.html>`__
      Computes the worksize needed for the function,
      `sytrd <sytrd.html>`__. This
      routine belongs to the ``onemkl::lapack`` namespace.
   -  `sytrf <sytrf.html>`__
      Computes the Bunch-Kaufman factorization of a symmetric matrix.
      This routine belongs to the ``onemkl::lapack`` namespace.
   -  `sytrf_get_lwork <sytrf_get_lwork.html>`__
      Computes the worksize needed for the function sytrf. This routine
      belongs to the ``onemkl::lapack`` namespace.
   -  `trtrs <trtrs.html>`__
      Solves a system of linear equations with a triangular coefficient
      matrix, with multiple right-hand sides. This routine belongs to
      the ``onemkl::lapack`` namespace.
   -  `ungbr <ungbr.html>`__
      Generates the complex unitary matrix Q or P\ :sup:`t` determined
      by `gebrd <gebrd.html>`__.
      This routine belongs to the ``onemkl::lapack`` namespace.
   -  `ungbr_get_lwork <ungbr_get_lwork.html>`__
      Computes the worksize needed for the function,
      `ungbr <ungbr.html>`__. This
      routine belongs to the ``onemkl::lapack`` namespace.
   -  `ungqr <ungqr.html>`__
      Generates the complex unitary matrix Q of the QR factorization
      formed by geqrf. This routine belongs to the
      ``onemkl::lapack`` namespace.
   -  `ungqr_get_lwork <ungqr_get_lwork.html>`__
      Computes the worksize needed for the function ungqr. This routine
      belongs to the ``onemkl::lapack`` namespace.
   -  `ungtr <ungtr.html>`__
      Generates the complex unitary matrix Q determined by
      `hetrd <hetrd.html>`__. This
      routine belongs to the ``onemkl::lapack`` namespace.
   -  `ungtr_get_lwork <ungtr_get_lwork.html>`__
      Computes the worksize needed for the function,
      `ungtr <ungtr.html>`__. This
      routine belongs to the ``onemkl::lapack`` namespace.
   -  `unmqr <unmqr.html>`__
      Multiplies a complex matrix by the unitary matrix Q of the QR
      factorization formed by unmqr. This routine belongs to the
      ``onemkl::lapack`` namespace.
   -  `unmqr_get_lwork <unmqr_get_lwork.html>`__
      Computes the worksize needed for the function unmqr. This routine
      belongs to the ``onemkl::lapack`` namespace.
   -  `unmtr <unmtr.html>`__
      Multiplies a complex matrix by the complex unitary matrix Q
      determined by
      `hetrd <hetrd.html>`__. This
      routine belongs to the ``onemkl::lapack`` namespace.
   -  `unmtr_get_lwork <unmtr_get_lwork.html>`__
      Computes the worksize needed for the function
      `unmtr <unmtr.html>`__. This
      routine belongs to the ``onemkl::lapack`` namespace.

      **Parent topic:** :ref:`onemkl_dense_linear_algebra`

.. toctree::
    :hidden:
    
    gebrd
    gebrd_get_lwork
    geqrf
    geqrf_get_lwork
    geqrf_batch
    gesvd
    gesvd_get_lwork
    getrf
    getrf_batch
    getri
    getri_batch
    getri_get_lwork
    getrs
    getrs_batch
    heevd
    heevd_get_lwork
    hegvd
    hegvd_get_lwork
    hetrd
    hetrd_get_lwork
    orgbr
    orgbr_get_lwork
    orgqr
    orgqr_batch
    orgqr_get_lwork
    orgtr
    orgtr_get_lwork
    ormqr
    ormqr_get_lwork
    ormtr
    ormtr_get_lwork
    potrf
    potrf-usm-version
    potrf_batch
    potri
    potrs
    potrs-usm-version
    potrs_batch
    syevd
    syevd_get_lwork
    sygvd
    sygvd_get_lwork
    sytrd
    sytrd_get_lwork
    sytrf
    sytrf_get_lwork
    trtrs
    ungbr
    ungbr_get_lwork
    ungqr
    ungqr_get_lwork
    ungtr
    ungtr_get_lwork
    unmqr
    unmqr_get_lwork
    unmtr
    unmtr_get_lwork
