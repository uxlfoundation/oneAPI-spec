.. _gesvd:

gesvd
=====


.. container::


   Computes the singular value decomposition of a general rectangular
   matrix. This routine belongs to the ``onemkl::lapack``\ namespace.


   .. container:: section
      :name: GUID-A44AA615-E4A1-48E4-967E-95164FA96BB5


      .. rubric:: Syntax
         :name: syntax
         :class: sectiontitle


      For real precisions:


      .. cpp:function::  void gesvd(queue &exec_queue, job jobu, job      jobvt, std::int64_t m, std::int64_t n, buffer<T,1> &a,      std::int64_t lda, buffer<T,1> &s, buffer<T,1> &u, std::int64_t      ldu, buffer<T,1> &vt, std::int64_t ldvt, buffer<T,1> &work,      std::int64_t lwork, buffer<std::int64_t,1> &info)

      For complex precisions:


      .. cpp:function::  void gesvd(queue &exec_queue, job jobu, job      jobvt, std::int64_t m, std::int64_t n, buffer<T,1> &a,      std::int64_t lda, buffer<realT,1> &s, buffer<T,1> &u, std::int64_t      ldu, buffer<T,1> &vt, std::int64_t ldvt, buffer<T,1> &work,      std::int64_t lwork, buffer<realT,1> &rwork, buffer<std::int64_t,1>      &info)

      ``gesvd`` supports the following precisions.


      .. list-table:: 
         :header-rows: 1

         * -  T 
         * -  ``float`` 
         * -  ``double`` 
         * -  ``std::complex<float>`` 
         * -  ``std::complex<double>`` 




.. container:: section
   :name: GUID-2D82CB14-C82B-4083-943F-F322E6287F94


   .. rubric:: Description
      :name: description
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
   :name: GUID-F841BA63-D4EE-4C75-9831-BB804CEA8622


   .. rubric:: Input Parameters
      :name: input-parameters
      :class: sectiontitle


   exec_queue
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


   lwork
      The size of the work buffer. Should be computed by
      `gesvd_get_lwork <gesvd_get_lwork.html>`__.


.. container:: section
   :name: GUID-F0C3D97D-E883-4070-A1C2-4FE43CC37D12


   .. rubric:: Output Parameters
      :name: output-parameters
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


   work
      Buffer of workspace. For real flavors:


      If ``info > 0, work(2:min(m,n))`` contains the unconverged
      superdiagonal elements of an upper bidiagonal matrix ``B`` whose
      diagonal is in ``s`` (not necessarily sorted). ``B`` satisfies
      ``A = U*B*V``\ :sup:`T`, so it has the same singular values as
      ``A``, and singular vectors related by ``U`` and ``V``\ :sup:`T`.


   rwork
      (Only for complex flavors) Buffer of real workspace, dimension at
      least ``5*min(m,n)``.


      On exit:


      If ``info > 0, rwork(1:min(m,n)-1)`` contains the unconverged
      superdiagonal elements of an upper bidiagonal matrix ``B`` whose
      diagonal is in ``s`` (not necessarily sorted). ``B`` satisfies
      ``A = U*B*V``\ :sup:`T`, so it has the same singular values as
      ``A``, and singular vectors related by ``U`` and ``V``\ :sup:`T`.


   info
      Buffer containing error information.


      If ``info = 0``, the execution is successful.


      If ``info = -i``, the ``i-th`` parameter had an illegal value.


      If ``info = i``, then if ``?bdsqr`` did not converge, i specifies
      how many superdiagonals of the intermediate bidiagonal form ``B``
      did not converge to zero (see the description of the work and
      rwork parameters for details).


.. container:: section
   :name: GUID-C97BF68F-B566-4164-95E0-A7ADC290DDE2


   .. rubric:: Example
      :name: example
      :class: sectiontitle


   An example of how to use ``gesvd``\ can be found in the oneMKL
   installation directory, under:


   ::


      examples/sycl/lapack/gesvd.cpp


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** `LAPACK
      Routines <lapack.html>`__


