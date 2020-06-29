.. _onemkl_lapack_gebrd:

gebrd
=====


.. container::


   Reduces a general matrix to bidiagonal form.


      ``gebrd`` supports the following precisions.


      .. list-table:: 
         :header-rows: 1

         * -  T 
         * -  ``float`` 
         * -  ``double`` 
         * -  ``std::complex<float>`` 
         * -  ``std::complex<double>`` 




.. container:: section


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
      :ref:`onemkl_lapack_orgbr`.


   If the matrix ``A`` is complex,


   -  to compute ``Q`` and ``P`` explicitly, call
      :ref:`onemkl_lapack_ungbr`


gebrd (BUFFER Version)
----------------------

.. container::

   .. container:: section


      .. rubric:: Syntax
         :class: sectiontitle


      .. cpp:function::  void onemkl::lapack::gebrd(cl::sycl::queue &queue, std::int64_t m,      std::int64_t n, cl::sycl::buffer<T,1> &a, std::int64_t lda, cl::sycl::buffer<realT,1>      &d, cl::sycl::buffer<realT,1> &e, cl::sycl::buffer<T,1> &tauq, cl::sycl::buffer<T,1> &taup,      cl::sycl::buffer<T,1> &scratchpad, std::int64_t scratchpad_size)


.. container:: section


   .. rubric:: Input Parameters
      :class: sectiontitle


   queue
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


   scratchpad_size
      Size of scratchpad memory as a number of floating point elements of type T.
      Size should not be less than the value returned by :ref:`onemkl_lapack_gebrd_scratchpad_size` function.


.. container:: section


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


   scratchpad
      Buffer holding scratchpad memory to be used by routine for storing intermediate results.


   .. container:: section


      .. rubric:: Throws
         :class: sectiontitle


      onemkl::lapack::exception
         Exception is thrown in case of problems happened during calculations. The ``info`` code of the problem can be obtained by `get_info()` method of exception object:

         If ``info=-i``, the ``i``-th parameter had an illegal value.

         If ``info`` equals to value passed as scratchpad size, and ``get_detail()`` returns non zero, then passed scratchpad is of insufficient size, and required size should not be less than value return by ``get_detail()`` method of exception object.


gebrd (USM Version)
----------------------

.. container::

   .. container:: section


      .. rubric:: Syntax
         :class: sectiontitle


      .. cpp:function::  cl::sycl::event onemkl::lapack::gebrd(cl::sycl::queue &queue, std::int64_t m, std::int64_t n, T *a, std::int64_t lda, RealT *d, RealT *e, T *tauq, T *taup, T *scratchpad, std::int64_t scratchpad_size, const cl::sycl::vector_class<cl::sycl::event> &events = {})


.. container:: section


   .. rubric:: Input Parameters
      :class: sectiontitle


   queue
      The queue where the routine should be executed.


   m
      The number of rows in the matrix ``A`` (``0≤m``).


   n
      The number of columns in the matrix ``A`` (``0≤n``).


   a
      Pointer to matrix ``A``. The second dimension of ``a`` must be at least
      ``max(1, m)``.


   lda
      The leading dimension of ``a``.


   scratchpad_size
      Size of scratchpad memory as a number of floating point elements of type T.
      Size should not be less than the value returned by :ref:`onemkl_lapack_gebrd_scratchpad_size` function.

   events
      List of events to wait for before starting computation. Defaults to empty list.


.. container:: section


   .. rubric:: Output Parameters
      :class: sectiontitle


   a
      If ``m≥n``, the diagonal and first super-diagonal of a are
      overwritten by the upper bidiagonal matrix ``B``. The elements
      below the diagonal, with the array tauq, represent the orthogonal
      matrix ``Q`` as a product of elementary reflectors, and the
      elements above the first superdiagonal, with the array taup,
      represent the orthogonal matrix ``P`` as a product of elementary
      reflectors.


      If ``m<n``, the diagonal and first sub-diagonal of a are
      overwritten by the lower bidiagonal matrix ``B``. The elements
      below the first subdiagonal, with the array tauq, represent the
      orthogonal matrix ``Q`` as a product of elementary reflectors, and
      the elements above the diagonal, with the array taup, represent
      the orthogonal matrix ``P`` as a product of elementary reflectors.


   d
      Pointer to memory of size at least ``max(1, min(m,n))``. Contains the diagonal
      elements of ``B``.


   e
      Pointer to memory of size at least ``max(1, min(m,n) - 1)``. Contains the
      off-diagonal elements of ``B``.


   tauq
      Pointer to memory of size at least ``max(1, min(m, n))``. The scalar factors of
      the elementary reflectors which represent the orthogonal or
      unitary matrix ``Q``.


   taup
      Pointer to memory of size at least ``max(1, min(m, n))``. The scalar factors of
      the elementary reflectors which represent the orthogonal or
      unitary matrix ``P``.


   scratchpad
      Pointer to scratchpad memory to be used by routine for storing intermediate results.


   .. container:: section


      .. rubric:: Throws
         :class: sectiontitle


      onemkl::lapack::exception
         Exception is thrown in case of problems happened during calculations. The ``info`` code of the problem can be obtained by `get_info()` method of exception object:

         If ``info=-i``, the ``i``-th parameter had an illegal value.

         If ``info`` equals to value passed as scratchpad size, and ``get_detail()`` returns non zero, then passed scratchpad is of insufficient size, and required size should not be less than value return by ``get_detail()`` method of exception object.


   .. container:: section


      .. rubric:: Return Values
         :class: sectiontitle


      Output event to wait on to ensure computation is complete.


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** :ref:`onemkl_lapack-singular-value-eigenvalue-routines`



.. |image0| image:: ../equations/GUID-03C78F41-D16C-4BFE-B087-BE4F5A6A0ee1.png
   :class: img-middle

