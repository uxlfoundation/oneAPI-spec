.. _onemkl_lapack_potrs:

potrs
=====


.. container::


   Solves a system of linear equations with a Cholesky-factored
   symmetric (Hermitian) positive-definite coefficient matrix.


      potrs supports the following precisions.


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


   The routine solves for ``X`` the system of linear equations
   ``A*X = B`` with a symmetric positive-definite or, for complex data,
   Hermitian positive-definite matrix ``A``, given the Cholesky
   factorization of ``A``:


   .. list-table:: 
      :header-rows: 1

      * -  ``A = UT*U`` for real data, ``A = UH*U`` for complex data
        -  if ``upper_lower=onemkl::uplo::upper``
      * -  ``A = L*LT`` for real data, ``A = L*LH`` for complex data
        -  if ``upper_lower=onemkl::uplo::lower``




   where ``L`` is a lower triangular matrix and ``U`` is upper
   triangular. The system is solved with multiple right-hand sides
   stored in the columns of the matrix ``B``.


   Before calling this routine, you must call
   :ref:`onemkl_lapack_potrf` to compute
   the Cholesky factorization of ``A``.


potrs (BUFFER Version)
----------------------

.. container::

   .. container:: section


      .. rubric:: Syntax
         :class: sectiontitle


      .. cpp:function::  void onemkl::lapack::potrs(cl::sycl::queue &queue, onemkl::uplo upper_lower,      std::int64_t n, std::int64_t nrhs, cl::sycl::buffer<T,1> &a, std::int64_t      lda, cl::sycl::buffer<T,1> &b, std::int64_t ldb, cl::sycl::buffer<T,1> &scratchpad, std::int64_t      scratchpad_size)

.. container:: section


   .. rubric:: Input Parameters
      :class: sectiontitle


   queue
      The queue where the routine should be executed.

   upper_lower
      Indicates how the input matrix has been factored:

      If ``upper_lower = onemkl::uplo::upper``, the upper triangle   ``U`` of ``A`` is stored, where ``A`` = ``U``\ :sup:`T`\ \*\ ``U``   for real data, ``A`` = ``U``\ :sup:`H`\ \*\ ``U`` for complex data.

      If ``upper_lower = onemkl::uplo::lower``, the lower triangle   ``L`` of ``A`` is stored, where ``A`` = ``L``\ \*\ ``L``\ :sup:`T`   for real data, ``A`` = ``L``\ \*\ ``L``\ :sup:`H` for complex   data.

   n
      The order of matrix ``A`` (``0≤n``).\

   nrhs
      The number of right-hand sides (``0≤nrhs``).

   a
      Buffer containing the factorization of the matrix A, as    returned by   :ref:`onemkl_lapack_potrf`.   The second dimension of ``a`` must be at least ``max(1, n)``.

   lda
      The leading dimension of ``a``.

   b
      The array ``b`` contains the matrix ``B`` whose columns    are the right-hand sides for the systems of equations. The second   dimension of ``b`` must be at least ``max(1,nrhs)``.

   ldb
      The leading dimension of ``b``.

   scratchpad_size
      Size of scratchpad memory as a number of floating point elements of type T.
      Size should not be less than the value returned by :ref:`onemkl_lapack_potrs_scratchpad_size` function.


.. container:: section


   .. rubric:: Output Parameters
      :class: sectiontitle


   b
      Overwritten by the solution matrix ``X``.

   scratchpad
      Buffer holding scratchpad memory to be used by routine for storing intermediate results.


   .. container:: section


      .. rubric:: Throws
         :class: sectiontitle


      onemkl::lapack::exception
         Exception is thrown in case of problems happened during calculations. The ``info`` code of the problem can be obtained by `get_info()` method of exception object:

         If ``info=-i``, the ``i``-th parameter had an illegal value.

         If ``info=i``, the ``i``-th diagonal element of the Cholesky factor is zero, and the solve could not be completed.

         If ``info`` equals to value passed as scratchpad size, and ``get_detail()`` returns non zero, then passed scratchpad is of insufficient size, and required size should not be less than value return by ``get_detail()`` method of exception object.


potrs (USM Version)
----------------------

.. container::

   .. container:: section


      .. rubric:: Syntax
         :class: sectiontitle


      .. cpp:function::  cl::sycl::event onemkl::lapack::potrs(cl::sycl::queue &queue, onemkl::uplo upper_lower,      std::int64_t n, std::int64_t nrhs, T *a, std::int64_t      lda, T *b, std::int64_t ldb, T *scratchpad, std::int64_t      scratchpad_size, const cl::sycl::vector_class<cl::sycl::event> &events = {})

.. container:: section


   .. rubric:: Input Parameters
      :class: sectiontitle


   queue
      The queue where the routine should be executed.

   upper_lower
      Indicates how the input matrix has been factored:

      If ``upper_lower = onemkl::uplo::upper``, the upper triangle   ``U`` of ``A`` is stored, where ``A`` = ``U``\ :sup:`T`\ \*\ ``U``   for real data, ``A`` = ``U``\ :sup:`H`\ \*\ ``U`` for complex data.

      If ``upper_lower = onemkl::uplo::lower``, the lower triangle   ``L`` of ``A`` is stored, where ``A`` = ``L``\ \*\ ``L``\ :sup:`T`   for real data, ``A`` = ``L``\ \*\ ``L``\ :sup:`H` for complex   data.

   n
      The order of matrix ``A`` (``0≤n``).\

   nrhs
      The number of right-hand sides (``0≤nrhs``).

   a
      Pointer to array containing the factorization of the matrix ``A``, as    returned by   :ref:`onemkl_lapack_potrf`.   The second dimension of ``a`` must be at least ``max(1, n)``.

   lda
      The leading dimension of ``a``.

   b
      The array ``b`` contains the matrix ``B`` whose columns    are the right-hand sides for the systems of equations. The second   dimension of ``b`` must be at least ``max(1,nrhs)``.

   ldb
      The leading dimension of ``b``.

   scratchpad_size
      Size of scratchpad memory as a number of floating point elements of type T.
      Size should not be less than the value returned by :ref:`onemkl_lapack_potrs_scratchpad_size` function.

   events
      List of events to wait for before starting computation. Defaults to empty list.


.. container:: section


   .. rubric:: Output Parameters
      :class: sectiontitle


   b
      Overwritten by the solution matrix ``X``.

   scratchpad
      Pointer to scratchpad memory to be used by routine for storing intermediate results.


   .. container:: section


      .. rubric:: Throws
         :class: sectiontitle


      onemkl::lapack::exception
         Exception is thrown in case of problems happened during calculations. The ``info`` code of the problem can be obtained by `get_info()` method of exception object:

         If ``info=-i``, the ``i``-th parameter had an illegal value.

         If ``info=i``, the ``i``-th diagonal element of the Cholesky factor is zero, and the solve could not be completed.

         If ``info`` equals to value passed as scratchpad size, and ``get_detail()`` returns non zero, then passed scratchpad is of insufficient size, and required size should not be less than value return by ``get_detail()`` method of exception object.


   .. container:: section


      .. rubric:: Return Values
         :class: sectiontitle


      Output event to wait on to ensure computation is complete.


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** :ref:`onemkl_lapack-linear-equation-routines` 


