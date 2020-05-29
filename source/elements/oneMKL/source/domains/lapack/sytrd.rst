.. _onemkl_lapack_sytrd:

onemkl::lapack::sytrd
=====================


.. container::


   Reduces a real symmetric matrix to tridiagonal form.


      ``sytrd`` supports the following precisions.


      .. list-table:: 
         :header-rows: 1

         * -  T 
         * -  ``float`` 
         * -  ``double`` 




.. container:: section


   .. rubric:: Description
      :class: sectiontitle


   The routine reduces a real symmetric matrix ``A`` to symmetric
   tridiagonal form ``T`` by an orthogonal similarity transformation:
   ``A = Q*T*QT``. The orthogonal matrix ``Q`` is not formed explicitly
   but is represented as a product of ``n``-1 elementary reflectors.
   Routines are provided for working with ``Q`` in this representation .


onemkl::lapack::sytrd (BUFFER Version)
--------------------------------------

.. container::

   .. container:: section


      .. rubric:: Syntax
         :class: sectiontitle


      .. cpp:function::  void onemkl::lapack::sytrd(cl::sycl::queue &queue, onemkl::uplo upper_lower,      std::int64_t n, cl::sycl::buffer<T,1> &a, std::int64_t lda, cl::sycl::buffer<T,1> &d,      cl::sycl::buffer<T,1> &e, cl::sycl::buffer<T,1> &tau, cl::sycl::buffer<T,1> &scratchpad, std::int64_t      scratchpad_size)

.. container:: section


   .. rubric:: Input Parameters
      :class: sectiontitle


   queue
      The queue where the routine should be executed.


   upper_lower
      Must be ``uplo::upper`` or ``uplo::lower``.


      If ``upper_lower = uplo::upper``, ``a`` stores the upper
      triangular part of ``A``.


      If ``upper_lower = uplo::lower``, ``a`` stores the lower
      triangular part of ``A``.


   n
      The order of the matrices ``A``\ ``(0≤n)``.


   a
      The buffer a, size ``(lda,*)``. Contains the upper or lower
      triangle of the symmetric matrix ``A``, as specified by
      ``upper_lower``.


      The second dimension of a must be at least ``max(1,n)``.


   lda
      The leading dimension of a; at least ``max(1,n)``.


   scratchpad_size
      Size of scratchpad memory as a number of floating point elements of type T.
      Size should not be less than the value returned by :ref:`onemkl_lapack_sytrd_scratchpad_size` function.


.. container:: section


   .. rubric:: Output Parameters
      :class: sectiontitle


   a
      On exit,


      if ``upper_lower = uplo::upper``, the diagonal and first
      superdiagonal of ``A`` are overwritten by the corresponding
      elements of the tridiagonal matrix ``T``, and the elements above
      the first superdiagonal, with the buffer tau, represent the
      orthogonal matrix ``Q`` as a product of elementary reflectors;


      if ``upper_lower = uplo::lower``, the diagonal and first
      subdiagonal of ``A`` are overwritten by the corresponding elements
      of the tridiagonal matrix ``T``, and the elements below the first
      subdiagonal, with the buffer tau, represent the orthogonal matrix
      ``Q`` as a product of elementary reflectors.


   d
      Buffer containing the diagonal elements of the matrix ``T``. The
      dimension of d must be at least ``max(1, n)``.


   e
      Buffer containing the off diagonal elements of the matrix ``T``.
      The dimension of e must be at least ``max(1, n-1)``.


   tau
      Buffer, size at least ``max(1, n)``. Stores ``(n-1)`` scalars that
      define elementary reflectors in decomposition of the unitary
      matrix ``Q`` in a product of ``n-1`` elementary reflectors.
      tau\ ``(n)`` is used as workspace.


   scratchpad
      Buffer holding scratchpad memory to be used by routine for storing intermediate results.


   .. container:: section


      .. rubric:: Throws
         :class: sectiontitle


      onemkl::lapack::exception
         Exception is thrown in case of problems happened during calculations. The ``info`` code of the problem can be obtained by `get_info()` method of exception object:

         If ``info=-i``, the ``i``-th parameter had an illegal value.

         If ``info`` equals to value passed as scratchpad size, and ``get_detail()`` returns non zero, then passed scratchpad is of insufficient size, and required size should not be less than value return by ``get_detail()`` method of exception object.


onemkl::lapack::sytrd (USM Version)
--------------------------------------

.. container::

   .. container:: section


      .. rubric:: Syntax
         :class: sectiontitle


      .. cpp:function::  cl::sycl::event onemkl::lapack::sytrd(cl::sycl::queue &queue, onemkl::uplo upper_lower,      std::int64_t n, T *a, std::int64_t lda, T *d, T *e, T *tau, T *scratchpad, std::int64_t scratchpad_size, const cl::sycl::vector_class<cl::sycl::event> &events = {})

.. container:: section


   .. rubric:: Input Parameters
      :class: sectiontitle


   queue
      The queue where the routine should be executed.


   upper_lower
      Must be ``uplo::upper`` or ``uplo::lower``.


      If ``upper_lower = uplo::upper``, ``a`` stores the upper
      triangular part of ``A``.


      If ``upper_lower = uplo::lower``, ``a`` stores the lower
      triangular part of ``A``.


   n
      The order of the matrices ``A``\ ``(0≤n)``.


   a
      The pointer to matrix ``A``, size ``(lda,*)``. Contains the upper or lower
      triangle of the symmetric matrix ``A``, as specified by
      ``upper_lower``.
      The second dimension of a must be at least ``max(1,n)``.


   lda
      The leading dimension of a; at least ``max(1,n)``.


   scratchpad_size
      Size of scratchpad memory as a number of floating point elements of type T.
      Size should not be less than the value returned by :ref:`onemkl_lapack_sytrd_scratchpad_size` function.

   events
      List of events to wait for before starting computation. Defaults to empty list.


.. container:: section


   .. rubric:: Output Parameters
      :class: sectiontitle


   a
      On exit,


      if ``upper_lower = uplo::upper``, the diagonal and first
      superdiagonal of ``A`` are overwritten by the corresponding
      elements of the tridiagonal matrix ``T``, and the elements above
      the first superdiagonal, with the array tau, represent the
      orthogonal matrix ``Q`` as a product of elementary reflectors;


      if ``upper_lower = uplo::lower``, the diagonal and first
      subdiagonal of ``A`` are overwritten by the corresponding elements
      of the tridiagonal matrix ``T``, and the elements below the first
      subdiagonal, with the array tau, represent the orthogonal matrix
      ``Q`` as a product of elementary reflectors.


   d
      Pointer to diagonal elements of the matrix ``T``. The
      dimension of d must be at least ``max(1, n)``.


   e
      Ponter to off diagonal elements of the matrix ``T``.
      The dimension of e must be at least ``max(1, n-1)``.


   tau
      Pointer to array of size at least ``max(1, n)``. Stores ``(n-1)`` scalars that
      define elementary reflectors in decomposition of the unitary
      matrix ``Q`` in a product of ``n-1`` elementary reflectors.
      tau\ ``(n)`` is used as workspace.


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


