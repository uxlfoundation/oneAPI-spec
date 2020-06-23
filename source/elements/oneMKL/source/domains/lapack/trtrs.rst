.. _onemkl_lapack_trtrs:

trtrs
=====


.. container::


   Solves a system of linear equations with a triangular coefficient
   matrix, with multiple right-hand sides.


      ``trtrs`` supports the following precisions.


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
   equations with a triangular matrix ``A``, with multiple right-hand
   sides stored in ``B``:


   .. list-table:: 
      :header-rows: 1

      * -     A*X = B    
        -  
        -     if ``transa`` =\ ``transpose::nontrans``,    
      * -     \ ``AT*X = B``\     
        -  
        -     if ``transa`` =\ ``transpose::trans``,    
      * -     A\ :sup:`H`\ ``*X`` = B    
        -  
        -     if ``transa`` =\ ``transpose::conjtrans`` (for complex    matrices only).   




trtrs (BUFFER Version)
----------------------

.. container::

   .. container:: section


      .. rubric:: Syntax
         :class: sectiontitle


      .. cpp:function::  void onemkl::lapack::trtrs(cl::sycl::queue &queue, onemkl::uplo upper_lower, onemkl::transpose transa, onemkl::diag unit_diag, std::int64_t n, std::int64_t nrhs,      cl::sycl::buffer<T,1> &a, std::int64_t lda, cl::sycl::buffer<T,1> &b, std::int64_t      ldb, cl::sycl::buffer<T,1> &scratchpad, std::int64_t      scratchpad_size)

.. container:: section


   .. rubric:: Input Parameters
      :class: sectiontitle


   queue
      The queue where the routine should be executed.

   upper_lower
      Indicates whether ``A`` is upper or lower    triangular:

         If upper_lower = ``uplo::upper``, then   ``A`` is upper triangular.

         If upper_lower =   ``uplo::lower``, then ``A`` is lower triangular.

   transa
      If transa = ``transpose::nontrans``, then    ``A``\ \*\ ``X`` = ``B`` is solved for ``X``.

      If   transa = ``transpose::trans``, then ``A``\ :sup:`T`\ \*\ ``X`` =   ``B`` is solved for ``X``.

      If transa =   ``transpose::conjtrans``, then ``A``\ :sup:`H`\ \*\ ``X`` = ``B`` is   solved for ``X``.

   unit_diag
      If unit_diag = ``diag::nonunit``, then ``A`` is not a    unit triangular matrix.

      If unit_diag = ``diag::unit``,   then ``A`` is unit triangular: diagonal elements of ``A`` are assumed   to be 1 and not referenced in the array a.

   n
      The order of ``A``; the number of rows in ``B``;    n\ ``≥ 0``.

   nrhs
      The number of right-hand sides; nrhs\ ``≥ 0``.

   a
      Buffer containing the matrix ``A``.      The    second dimension of a must be at least ``max(1,n)``.

   lda
      The leading dimension of ``a``;    lda\ ``≥ max(1, n)``.

   b
      Buffer containing the matrix ``B`` whose columns are the    right-hand sides for the systems of equations.      The   second dimension of b at least ``max(1,nrhs)``.

   ldb
      The leading dimension of b; ldb\ ``≥ max(1, n)``.

   scratchpad_size
      Size of scratchpad memory as a number of floating point elements of type T.
      Size should not be less than the value returned by :ref:`onemkl_lapack_trtrs_scratchpad_size` function.


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

         If ``info`` equals to value passed as scratchpad size, and ``get_detail()`` returns non zero, then passed scratchpad is of insufficient size, and required size should not be less than value return by ``get_detail()`` method of exception object.


trtrs (USM Version)
----------------------

.. container::

   .. container:: section


      .. rubric:: Syntax
         :class: sectiontitle


      .. cpp:function::  cl::sycl::event onemkl::lapack::trtrs(cl::sycl::queue &queue, onemkl::uplo upper_lower, onemkl::transpose transa, onemkl::diag unit_diag, std::int64_t n, std::int64_t nrhs, T *a, std::int64_t lda, T *b, std::int64_t ldb, T *scratchpad, std::int64_t      scratchpad_size, const cl::sycl::vector_class<cl::sycl::event> &events = {})

.. container:: section


   .. rubric:: Input Parameters
      :class: sectiontitle


   queue
      The queue where the routine should be executed.

   upper_lower
      Indicates whether ``A`` is upper or lower    triangular:

         If upper_lower = ``uplo::upper``, then   ``A`` is upper triangular.

         If upper_lower =   ``uplo::lower``, then ``A`` is lower triangular.

   transa
      If transa = ``transpose::nontrans``, then    ``A``\ \*\ ``X`` = ``B`` is solved for ``X``.

      If   transa = ``transpose::trans``, then ``A``\ :sup:`T`\ \*\ ``X`` =   ``B`` is solved for ``X``.

      If transa =   ``transpose::conjtrans``, then ``A``\ :sup:`H`\ \*\ ``X`` = ``B`` is   solved for ``X``.

   unit_diag
      If unit_diag = ``diag::nonunit``, then ``A`` is not a    unit triangular matrix.

      If unit_diag = ``diag::unit``,   then ``A`` is unit triangular: diagonal elements of ``A`` are assumed   to be 1 and not referenced in the array a.

   n
      The order of ``A``; the number of rows in ``B``;    n\ ``≥ 0``.

   nrhs
      The number of right-hand sides; nrhs\ ``≥ 0``.

   a
      Array containing the matrix ``A``.      The    second dimension of a must be at least ``max(1,n)``.

   lda
      The leading dimension of ``a``;    lda\ ``≥ max(1, n)``.

   b
      Array containing the matrix ``B`` whose columns are the    right-hand sides for the systems of equations.      The   second dimension of b at least ``max(1,nrhs)``.

   ldb
      The leading dimension of b; ldb\ ``≥ max(1, n)``.

   scratchpad_size
      Size of scratchpad memory as a number of floating point elements of type T.
      Size should not be less than the value returned by :ref:`onemkl_lapack_trtrs_scratchpad_size` function.

   events
      List of events to wait for before starting computation. Defaults to empty list.


.. container:: section


   .. rubric:: Output Parameters
      :class: sectiontitle


   b
      Overwritten by the solution matrix ``X``.

   scratchpad
      Pointer toscratchpad memory to be used by routine for storing intermediate results.


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


      **Parent topic:** :ref:`onemkl_lapack-linear-equation-routines` 


