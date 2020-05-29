.. _onemkl_lapack_gesvd:

onemkl::lapack::gesvd
=====================


.. container::


   Computes the singular value decomposition of a general rectangular
   matrix.


      ``gesvd`` supports the following precisions.


      .. list-table::
         :header-rows: 1

         * -  T
         * -  ``float``
         * -  ``double``
         * -  ``std::complex<float>``
         * -  ``std::complex<double>``



onemkl::lapack::gesvd (BUFFER Version)
--------------------------------------

.. container::

   .. container:: section


      .. rubric:: Syntax
         :class: sectiontitle


      .. cpp:function::  void onemkl::lapack::gesvd(cl::sycl::queue &queue, onemkl::job jobu, onemkl::job      jobvt, std::int64_t m, std::int64_t n, cl::sycl::buffer<T,1> &a,      std::int64_t lda, cl::sycl::buffer<realT,1> &s, cl::sycl::buffer<T,1> &u, std::int64_t      ldu, cl::sycl::buffer<T,1> &vt, std::int64_t ldvt, cl::sycl::buffer<T,1> &scratchpad,      std::int64_t scratchpad_size)


.. container:: section


   .. rubric:: Description
      :class: sectiontitle


   The routine computes the singular value decomposition (SVD) of a
   real/complex ``m``-by-``n`` matrix ``A``, optionally computing the
   left and/or right singular vectors. The SVD is written as


   ``A = U*Σ*VT`` for real routines


   ``A = U*Σ*VH`` for complex routines


   where Σ is an ``m``-by-``n`` diagonal matrix, ``U`` is an
   ``m``-by-``m`` orthogonal/unitary matrix, and ``V`` is an
   ``n``-by-``n`` orthogonal/unitary matrix. The diagonal elements of Σ
   are the singular values of ``A``; they are real and non-negative, and
   are returned in descending order. The first ``min(m, n)`` columns of
   ``U`` and ``V`` are the left and right singular vectors of ``A``.


.. container:: section


   .. rubric:: Input Parameters
      :class: sectiontitle


   queue
      The queue where the routine should be executed.


   jobu
      Must be ``job::allvec``, ``job::somevec``, ``job::overwritevec``,
      or ``job::novec``. Specifies options for computing all or part of
      the matrix ``U``.


      If ``jobu = job::allvec``, all ``m`` columns of ``U`` are returned
      in the buffer u;


      if ``jobu = job::somevec``, the first ``min(m, n)`` columns of
      ``U`` (the left singular vectors) are returned in the buffer u;


      if ``jobu = job::overwritevec``, the first ``min(m, n)`` columns
      of ``U`` (the left singular vectors) are overwritten on the buffer
      a;


      if ``jobu = job::novec``, no columns of ``U`` (no left singular
      vectors) are computed.


   jobvt
      Must be ``job::allvec, job::somevec``, ``job::overwritevec``, or
      ``job::novec``. Specifies options for computing all or part of the
      matrix *V\ T/V\ H*.


      If ``jobvt = job::allvec``, all n columns of *V\ T/V\ H* are
      returned in the buffer vt;


      if ``jobvt = job::somevec``, the first ``min(m, n)`` columns of
      *V\ T/V\ H* (the left singular vectors) are returned in the buffer
      vt;


      if ``jobvt = job::overwritevec``, the first ``min(m, n)`` columns
      of *V\ T/V\ H* (the left singular vectors) are overwritten on the
      buffer a;


      if ``jobvt = job::novec``, no columns of *V\ T/V\ H* (no left
      singular vectors) are computed.


      jobvt and jobu cannot both be ``job::overwritevec``.


   m
      The number of rows in the matrix ``A`` (``0≤m``).


   a
      The buffer a, size ``(lda,*)``. The buffer ``a`` contains the
      matrix ``A``. The second dimension of a must be at least
      ``max(1, m)``.


   lda
      The leading dimension of a.


   ldu
      The leading dimension of u.


   ldvt
      The leading dimension of vt.


   scratchpad_size
      Size of scratchpad memory as a number of floating point elements of type T.
      Size should not be less than the value returned by :ref:`onemkl_lapack_gesvd_scratchpad_size` function.


.. container:: section


   .. rubric:: Output Parameters
      :class: sectiontitle


   a
      On exit,


      If ``jobu = job::overwritevec``, a is overwritten with the first
      ``min(m,n)`` columns of ``U`` (the left singular vectors stored
      columnwise);


      If ``jobvt = job::overwritevec``, a is overwritten with the first
      ``min(m, n)`` rows of ``V``\ :sup:`T`/``V``\ :sup:`H` (the right
      singular vectors stored rowwise);


      If ``jobu ≠ job::overwritevec`` and ``jobvt ≠ job::overwritevec``,
      the contents of a are destroyed.


   s
      Buffer containing the singular values, size at least
      ``max(1, min(m,n))``. Contains the singular values of ``A`` sorted
      so that ``s(i) ≥ s(i+1)``.


   u
      Buffer containing ``U``; the second dimension of u must be at
      least ``max(1, m)`` if ``jobu = job::allvec``, and at least
      ``max(1, min(m, n))`` if ``jobu = job::somevec``.


      If ``jobu = job::allvec``, ``u`` contains the m-by-m
      orthogonal/unitary matrix ``U``.


      If ``jobu = job::somevec``, u contains the first ``min(m, n)``
      columns of ``U`` (the left singular vectors stored column-wise).


      If ``jobu = job::novec`` or ``job::overwritevec``, u is not
      referenced.


   vt
      Buffer containing ``V``\ :sup:`T`; the second dimension of vt must
      be at least ``max(1, n)``.


      If ``jobvt = job::allvec``, vt contains the n-by-n
      orthogonal/unitary matrix ``V``\ :sup:`T`/``V``\ :sup:`H`.


      If ``jobvt = job::somevec``, vt contains the first ``min(m, n)``
      rows of ``V``\ :sup:`T`/``V``\ :sup:`H` (the right singular
      vectors stored row-wise).


      If ``jobvt = job::novec`` or ``job::overwritevec``, vt is not
      referenced.


   scratchpad
      Buffer holding scratchpad memory to be used by routine for storing intermediate results.


   .. container:: section


      .. rubric:: Throws
         :class: sectiontitle


      onemkl::lapack::exception
         Exception is thrown in case of problems happened during calculations. The ``info`` code of the problem can be obtained by `get_info()` method of exception object:

         If ``info=-i``, the ``i``-th parameter had an illegal value.

         If ``info=i``, then if ``bdsqr`` did not converge, ``i`` specifies
         how many superdiagonals of the intermediate bidiagonal form ``B``
         did not converge to zero, and ``scratchpad(2:min(m,n))`` contains the unconverged
         superdiagonal elements of an upper bidiagonal matrix ``B`` whose
         diagonal is in ``s`` (not necessarily sorted). ``B`` satisfies
         ``A = U*B*V``\ :sup:`T`, so it has the same singular values as
         ``A``, and singular vectors related by ``U`` and ``V``\ :sup:`T`.

         If ``info`` equals to value passed as scratchpad size, and ``get_detail()`` returns non zero, then passed scratchpad is of insufficient size, and required size should not be less than value return by ``get_detail()`` method of exception object.


onemkl::lapack::gesvd (USM Version)
--------------------------------------

.. container::

   .. container:: section


      .. rubric:: Syntax
         :class: sectiontitle


      .. cpp:function::  cl::sycl::event onemkl::lapack::gesvd(cl::sycl::queue &queue, onemkl::job jobu, onemkl::job      jobvt, std::int64_t m, std::int64_t n, T *a,      std::int64_t lda, RealT *s, T *u, std::int64_t      ldu, T *vt, std::int64_t ldvt, T *scratchpad,      std::int64_t scratchpad_size, const cl::sycl::vector_class<cl::sycl::event> &events = {})


.. container:: section


   .. rubric:: Description
      :class: sectiontitle


   The routine computes the singular value decomposition (SVD) of a
   real/complex ``m``-by-``n`` matrix ``A``, optionally computing the
   left and/or right singular vectors. The SVD is written as


   ``A = U*Σ*VT`` for real routines


   ``A = U*Σ*VH`` for complex routines


   where Σ is an ``m``-by-``n`` diagonal matrix, ``U`` is an
   ``m``-by-``m`` orthogonal/unitary matrix, and ``V`` is an
   ``n``-by-``n`` orthogonal/unitary matrix. The diagonal elements of Σ
   are the singular values of ``A``; they are real and non-negative, and
   are returned in descending order. The first ``min(m, n)`` columns of
   ``U`` and ``V`` are the left and right singular vectors of ``A``.


.. container:: section


   .. rubric:: Input Parameters
      :class: sectiontitle


   queue
      The queue where the routine should be executed.


   jobu
      Must be ``job::allvec``, ``job::somevec``, ``job::overwritevec``,
      or ``job::novec``. Specifies options for computing all or part of
      the matrix ``U``.


      If ``jobu = job::allvec``, all ``m`` columns of ``U`` are returned
      in the array u;


      if ``jobu = job::somevec``, the first ``min(m, n)`` columns of
      ``U`` (the left singular vectors) are returned in the array u;


      if ``jobu = job::overwritevec``, the first ``min(m, n)`` columns
      of ``U`` (the left singular vectors) are overwritten on the array
      a;


      if ``jobu = job::novec``, no columns of ``U`` (no left singular
      vectors) are computed.


   jobvt
      Must be ``job::allvec, job::somevec``, ``job::overwritevec``, or
      ``job::novec``. Specifies options for computing all or part of the
      matrix *V\ T/V\ H*.


      If ``jobvt = job::allvec``, all n columns of *V\ T/V\ H* are
      returned in the array vt;


      if ``jobvt = job::somevec``, the first ``min(m, n)`` columns of
      *V\ T/V\ H* (the left singular vectors) are returned in the array
      vt;


      if ``jobvt = job::overwritevec``, the first ``min(m, n)`` columns
      of *V\ T/V\ H* (the left singular vectors) are overwritten on the
      array a;


      if ``jobvt = job::novec``, no columns of *V\ T/V\ H* (no left
      singular vectors) are computed.


      jobvt and jobu cannot both be ``job::overwritevec``.


   m
      The number of rows in the matrix ``A`` (``0≤m``).


   a
      Pointer to array ``a``, size ``(lda,*)``, containing the
      matrix ``A``. The second dimension of ``a`` must be at least
      ``max(1, m)``.


   lda
      The leading dimension of a.


   ldu
      The leading dimension of u.


   ldvt
      The leading dimension of vt.


   scratchpad_size
      Size of scratchpad memory as a number of floating point elements of type T.
      Size should not be less than the value returned by :ref:`onemkl_lapack_gesvd_scratchpad_size` function.

   events
      List of events to wait for before starting computation. Defaults to empty list.


.. container:: section


   .. rubric:: Output Parameters
      :class: sectiontitle


   a
      On exit,


      If ``jobu = job::overwritevec``, a is overwritten with the first
      ``min(m,n)`` columns of ``U`` (the left singular vectors stored
      columnwise);


      If ``jobvt = job::overwritevec``, a is overwritten with the first
      ``min(m, n)`` rows of ``V``\ :sup:`T`/``V``\ :sup:`H` (the right
      singular vectors stored rowwise);


      If ``jobu ≠ job::overwritevec`` and ``jobvt ≠ job::overwritevec``,
      the contents of a are destroyed.


   s
      Array containing the singular values, size at least
      ``max(1, min(m,n))``. Contains the singular values of ``A`` sorted
      so that ``s(i) ≥ s(i+1)``.


   u
      Array containing ``U``; the second dimension of u must be at
      least ``max(1, m)`` if ``jobu = job::allvec``, and at least
      ``max(1, min(m, n))`` if ``jobu = job::somevec``.


      If ``jobu = job::allvec``, ``u`` contains the m-by-m
      orthogonal/unitary matrix ``U``.


      If ``jobu = job::somevec``, u contains the first ``min(m, n)``
      columns of ``U`` (the left singular vectors stored column-wise).


      If ``jobu = job::novec`` or ``job::overwritevec``, u is not
      referenced.


   vt
      Array containing ``V``\ :sup:`T`; the second dimension of vt must
      be at least ``max(1, n)``.


      If ``jobvt = job::allvec``, vt contains the n-by-n
      orthogonal/unitary matrix ``V``\ :sup:`T`/``V``\ :sup:`H`.


      If ``jobvt = job::somevec``, vt contains the first ``min(m, n)``
      rows of ``V``\ :sup:`T`/``V``\ :sup:`H` (the right singular
      vectors stored row-wise).


      If ``jobvt = job::novec`` or ``job::overwritevec``, vt is not
      referenced.


   scratchpad
      Pointer to scratchpad memory to be used by routine for storing intermediate results.


   .. container:: section


      .. rubric:: Throws
         :class: sectiontitle


      onemkl::lapack::exception
         Exception is thrown in case of problems happened during calculations. The ``info`` code of the problem can be obtained by `get_info()` method of exception object:

         If ``info=-i``, the ``i``-th parameter had an illegal value.

         If ``info=i``, then if ``bdsqr`` did not converge, ``i`` specifies
         how many superdiagonals of the intermediate bidiagonal form ``B``
         did not converge to zero, and ``scratchpad(2:min(m,n))`` contains the unconverged
         superdiagonal elements of an upper bidiagonal matrix ``B`` whose
         diagonal is in ``s`` (not necessarily sorted). ``B`` satisfies
         ``A = U*B*V``\ :sup:`T`, so it has the same singular values as
         ``A``, and singular vectors related by ``U`` and ``V``\ :sup:`T`.

         If ``info`` equals to value passed as scratchpad size, and ``get_detail()`` returns non zero, then passed scratchpad is of insufficient size, and required size should not be less than value return by ``get_detail()`` method of exception object.


   .. container:: section


      .. rubric:: Return Values
         :class: sectiontitle


      Output event to wait on to ensure computation is complete.


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** :ref:`onemkl_lapack-singular-value-eigenvalue-routines` 


