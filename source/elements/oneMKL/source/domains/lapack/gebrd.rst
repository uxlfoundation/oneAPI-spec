
gebrd
=====


.. container::


   Reduces a general matrix to bidiagonal form. This routine belongs to
   the ``onemkl::lapack``\ namespace.


   .. container:: section
      :name: GUID-8DFD8E6D-C63C-4D34-9784-4DEDFF7C1965


      .. rubric:: Syntax
         :class: sectiontitle


      For real precisions:


      .. cpp:function::  void gebrd(queue &exec_queue, std::int64_t m,      std::int64_t n, buffer<T,1> &a, std::int64_t lda, buffer<T,1> &d,      buffer<T,1> &e, buffer<T,1> &tauq, buffer<T,1> &taup, buffer<T,1>      &work, std::int64_t lwork, buffer<std::int64_t,1> &info)

      For complex precisions:


      .. cpp:function::  void gebrd(queue &exec_queue, std::int64_t m,      std::int64_t n, buffer<T,1> &a, std::int64_t lda, buffer<realT,1>      &d, buffer<realT,1> &e, buffer<T,1> &tauq, buffer<T,1> &taup,      buffer<T,1> &work, std::int64_t lwork, buffer<std::int64_t,1>      &info)

      ``gebrd`` supports the following precisions.


      .. list-table:: 
         :header-rows: 1

         * -  T 
         * -  ``float`` 
         * -  ``double`` 
         * -  ``std::complex<float>`` 
         * -  ``std::complex<double>`` 




.. container:: section
   :name: GUID-B6C26CE6-BBEA-493E-922B-C81BEB0C48CC


   .. rubric:: Description
      :class: sectiontitle


   The routine reduces a general ``m``-by-``n`` matrix ``A`` to a
   bidiagonal matrix ``B`` by an orthogonal (unitary) transformation.


   If ``m≥n``, the reduction is given by |image0|


   where ``B``\ :sub:`1` is an ``n``-by-``n`` upper diagonal matrix,
   ``Q`` and ``P`` are orthogonal or, for a complex ``A``, unitary
   matrices; ``Q``\ :sub:`1` consists of the first ``n`` columns of
   ``Q``.


   If ``m < n``, the reduction is given by


   ``A = Q*B*PH = Q*(B10)*PH = Q1*B1*P1H``,


   where ``B``\ :sub:`1` is an ``m``-by-``m`` lower diagonal matrix,
   ``Q`` and ``P`` are orthogonal or, for a complex ``A``, unitary
   matrices; ``P``\ :sub:`1` consists of the first ``m`` columns of
   ``P``.


   The routine does not form the matrices ``Q`` and ``P`` explicitly,
   but represents them as products of elementary reflectors. Routines
   are provided to work with the matrices ``Q`` and ``P`` in this
   representation:


   If the matrix ``A`` is real,


   -  to compute ``Q`` and ``P`` explicitly, call
      `orgbr <orgbr.html>`__.


   If the matrix ``A`` is complex,


   -  to compute ``Q`` and ``P`` explicitly, call
      `ungbr <ungbr.html>`__.


.. container:: section
   :name: GUID-F841BA63-D4EE-4C75-9831-BB804CEA8622


   .. rubric:: Input Parameters
      :class: sectiontitle


   exec_queue
      The queue where the routine should be executed.


   m
      The number of rows in the matrix ``A`` (``0≤m``).


   n
      The number of columns in the matrix ``A`` (``0≤n``).


   a
      The buffer ``a``, size (``lda,*``). The buffer ``a`` contains the
      matrix ``A``. The second dimension of ``a`` must be at least
      ``max(1, m)``.


   lda
      The leading dimension of ``a``.


   lwork
      The size of the work buffer. Must be computed by
      `gebrd_get_lwork <gebrd_get_lwork.html>`__.


.. container:: section
   :name: GUID-F0C3D97D-E883-4070-A1C2-4FE43CC37D12


   .. rubric:: Output Parameters
      :class: sectiontitle


   a
      If ``m≥n``, the diagonal and first super-diagonal of a are
      overwritten by the upper bidiagonal matrix ``B``. The elements
      below the diagonal, with the buffer tauq, represent the orthogonal
      matrix ``Q`` as a product of elementary reflectors, and the
      elements above the first superdiagonal, with the buffer taup,
      represent the orthogonal matrix ``P`` as a product of elementary
      reflectors.


      If ``m<n``, the diagonal and first sub-diagonal of a are
      overwritten by the lower bidiagonal matrix ``B``. The elements
      below the first subdiagonal, with the buffer tauq, represent the
      orthogonal matrix ``Q`` as a product of elementary reflectors, and
      the elements above the diagonal, with the buffer taup, represent
      the orthogonal matrix ``P`` as a product of elementary reflectors.


   d
      Buffer, size at least ``max(1, min(m,n))``. Contains the diagonal
      elements of ``B``.


   e
      Buffer, size at least ``max(1, min(m,n) - 1)``. Contains the
      off-diagonal elements of ``B``.


   tauq
      Buffer, size at least ``max(1, min(m, n))``. The scalar factors of
      the elementary reflectors which represent the orthogonal or
      unitary matrix ``Q``.


   taup
      Buffer, size at least ``max(1, min(m, n))``. The scalar factors of
      the elementary reflectors which represent the orthogonal or
      unitary matrix ``P``.


   work
      Buffer of workspace.


   info
      Buffer containing error information.


      If ``info=0``, the execution is successful.


      If ``info=-i``, the ``i``-th parameter had an illegal value.


.. container:: section
   :name: GUID-C97BF68F-B566-4164-95E0-A7ADC290DDE2


   .. rubric:: Example
      :class: sectiontitle


   An example of how to use ``gebrd``\ can be found in the oneMKL
   installation directory, under:


   ::


      examples/sycl/lapack/gebrd.cpp


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** `LAPACK
      Routines <lapack.html>`__



.. |image0| image:: ../equations/GUID-03C78F41-D16C-4BFE-B087-BE4F5A6A0ee1.png
   :class: img-middle

