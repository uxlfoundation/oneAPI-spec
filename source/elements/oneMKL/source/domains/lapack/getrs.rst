.. _onemkl_lapack_getrs:

getrs
=====


.. container::


   Solves a system of linear equations with an LU-factored square
   coefficient matrix, with multiple right-hand sides.


      ``getrs`` supports the following precisions.


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


   The routine solves for ``X`` the following systems of linear
   equations:


   .. list-table:: 
      :header-rows: 1

      * -     \ ``A*X = B``\     
        -     if ``trans``\ =\ ``onemkl::transpose::nontrans``\     
      * -     \ ``AT*X = B``\     
        -     if ``trans``\ =\ ``onemkl::transpose::trans``\     
      * -     \ ``AH*X = B``\     
        -     if ``trans``\ =\ ``onemkl::transpose::conjtrans``\     




   Before calling this routine, you must call
   :ref:`onemkl_lapack_getrf`
   to compute the ``LU`` factorization of ``A``.


getrs (BUFFER Version)
----------------------

.. container::

   .. container:: section


      .. rubric:: Syntax
         :class: sectiontitle


      .. cpp:function::  void onemkl::lapack::getrs(cl::sycl::queue &queue, onemkl::transpose trans,      std::int64_t n, std::int64_t nrhs, cl::sycl::buffer<T,1> &a, std::int64_t      lda, cl::sycl::buffer<std::int64_t,1> &ipiv, cl::sycl::buffer<T,1> &b, std::int64_t      ldb, cl::sycl::buffer<T,1> &scratchpad, std::int64_t      scratchpad_size)

.. container:: section


   .. rubric:: Input Parameters
      :class: sectiontitle


   queue
      The queue where the routine should be executed.


   trans
      Indicates the form of the equations:


      If ``trans=onemkl::transpose::nontrans``, then ``A*X = B`` is solved
      for ``X``.


      If ``trans=onemkl::transpose::trans``, then ``AT*X = B`` is solved
      for ``X``.


      If ``trans=onemkl::transpose::conjtrans``, then ``AH*X = B`` is
      solved for ``X``.


   n
      The order of the matrix ``A`` and the number of rows in matrix
      ``B(0≤n)``.


   nrhs
      The number of right-hand sides (``0≤nrhs``).


   a
      Buffer containing the factorization of the matrix ``A``, as
      returned by :ref:`onemkl_lapack_getrf`. The second dimension of a must be at least
      ``max(1, n)``.


   lda
      The leading dimension of a.


   ipiv
      Array, size at least ``max(1, n)``. The ipiv array, as returned by
      :ref:`onemkl_lapack_getrf`.


   b
      The array b contains the matrix ``B`` whose columns are the
      right-hand sides for the systems of equations. The second
      dimension of b must be at least ``max(1,nrhs)``.


   ldb
      The leading dimension of b.


   scratchpad_size
      Size of scratchpad memory as a number of floating point elements of type T.
      Size should not be less than the value returned by :ref:`onemkl_lapack_getrs_scratchpad_size` function.


.. container:: section


   .. rubric:: Output Parameters
      :class: sectiontitle


   b
      The buffer b is overwritten by the solution matrix ``X``.


   scratchpad
      Buffer holding scratchpad memory to be used by routine for storing intermediate results.


   .. container:: section


      .. rubric:: Throws
         :class: sectiontitle


      onemkl::lapack::exception
         Exception is thrown in case of problems happened during calculations. The ``info`` code of the problem can be obtained by `get_info()` method of exception object:

         If ``info=-i``, the ``i``-th parameter had an illegal value.

         If ``info=i``, the ``i``-th diagonal element of ``U`` is zero,
         and the solve could not be completed.

         If ``info`` equals to value passed as scratchpad size, and ``get_detail()`` returns non zero, then passed scratchpad is of insufficient size, and required size should not be less than value return by ``get_detail()`` method of exception object.


getrs (USM Version)
----------------------

.. container::

   .. container:: section


      .. rubric:: Syntax
         :class: sectiontitle


      .. cpp:function::  cl::sycl::event onemkl::lapack::getrs(cl::sycl::queue &queue, onemkl::transpose trans,      std::int64_t n, std::int64_t nrhs, T *a, std::int64_t      lda, std::int64_t *ipiv, T *b, std::int64_t      ldb, T *scratchpad, std::int64_t      scratchpad_size, const cl::sycl::vector_class<cl::sycl::event> &events = {})

.. container:: section


   .. rubric:: Input Parameters
      :class: sectiontitle


   queue
      The queue where the routine should be executed.


   trans
      Indicates the form of the equations:


      If ``trans=onemkl::transpose::nontrans``, then ``A*X = B`` is solved
      for ``X``.


      If ``trans=onemkl::transpose::trans``, then ``AT*X = B`` is solved
      for ``X``.


      If ``trans=onemkl::transpose::conjtrans``, then ``AH*X = B`` is
      solved for ``X``.


   n
      The order of the matrix ``A`` and the number of rows in matrix
      ``B(0≤n)``.


   nrhs
      The number of right-hand sides (``0≤nrhs``).


   a
      Pointer to array containing the factorization of the matrix ``A``, as
      returned by :ref:`onemkl_lapack_getrf`. The second dimension of a must be at least
      ``max(1, n)``.


   lda
      The leading dimension of a.


   ipiv
      Array, size at least ``max(1, n)``. The ipiv array, as returned by
      :ref:`onemkl_lapack_getrf`.


   b
      The array b contains the matrix ``B`` whose columns are the
      right-hand sides for the systems of equations. The second
      dimension of b must be at least ``max(1,nrhs)``.


   ldb
      The leading dimension of b.


   scratchpad_size
      Size of scratchpad memory as a number of floating point elements of type T.
      Size should not be less than the value returned by :ref:`onemkl_lapack_getrs_scratchpad_size` function.

   events
      List of events to wait for before starting computation. Defaults to empty list.


.. container:: section


   .. rubric:: Output Parameters
      :class: sectiontitle


   b
      The array b is overwritten by the solution matrix ``X``.


   scratchpad
      Pointer to scratchpad memory to be used by routine for storing intermediate results.


   .. container:: section


      .. rubric:: Throws
         :class: sectiontitle


      onemkl::lapack::exception
         Exception is thrown in case of problems happened during calculations. The ``info`` code of the problem can be obtained by `get_info()` method of exception object:

         If ``info=-i``, the ``i``-th parameter had an illegal value.

         If ``info=i``, the ``i``-th diagonal element of ``U`` is zero,
         and the solve could not be completed.

         If ``info`` equals to value passed as scratchpad size, and ``get_detail()`` returns non zero, then passed scratchpad is of insufficient size, and required size should not be less than value return by ``get_detail()`` method of exception object.


   .. container:: section


      .. rubric:: Return Values
         :class: sectiontitle


      Output event to wait on to ensure computation is complete.


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** :ref:`onemkl_lapack-linear-equation-routines` 


