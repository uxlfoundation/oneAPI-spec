.. _onemkl_lapack_potrf:

onemkl::lapack::potrf
=====================


.. container::


   Computes the Cholesky factorization of a symmetric (Hermitian)
   positive-definite matrix.


      ``potrf`` supports the following precisions.


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


   The routine forms the Cholesky factorization of a symmetric
   positive-definite or, for complex data, Hermitian positive-definite
   matrix ``A``:


   .. list-table:: 
      :header-rows: 1

      * -  ``A`` = ``U``\ :sup:`T`\ \*\ ``U`` for real data, ``A`` =    ``U``\ :sup:`H`\ \*\ ``U`` for complex data
        -  if upper_lower=\ ``onemkl::uplo::upper`` 
      * -  ``A`` = ``L``\ \*\ ``L``\ :sup:`T` for real data, ``A`` =    ``L``\ \*\ ``L``\ :sup:`H` for complex data
        -  if upper_lower=\ ``onemkl::uplo::lower`` 




   where ``L`` is a lower triangular matrix and ``U`` is upper
   triangular.


onemkl::lapack::potrf (BUFFER Version)
--------------------------------------

.. container::

   .. container:: section


      .. rubric:: Syntax
         :class: sectiontitle


      .. cpp:function::  void onemkl::lapack::potrf(cl::sycl::queue &queue, onemkl::uplo      upper_lower, std::int64_t n, cl::sycl::buffer<T,1> &a, std::int64_t lda, cl::sycl::buffer<T,1> &scratchpad, std::int64_t      scratchpad_size)

.. container:: section


   .. rubric:: Input Parameters
      :class: sectiontitle


   queue
      The queue where the routine should be executed.


   upper_lower
      Indicates whether the upper or lower triangular part of ``A`` is
      stored and how ``A`` is factored:


      If upper_lower=\ ``onemkl::uplo::upper``, the array ``a`` stores the
      upper triangular part of the matrix ``A``, and the strictly lower
      triangular part of the matrix is not referenced.


      If upper_lower=\ ``onemkl::uplo::lower``, the array ``a`` stores the
      lower triangular part of the matrix ``A``, and the strictly upper
      triangular part of the matrix is not referenced.


   n
      Specifies the order of the matrix ``A`` (``0≤n``).


   a
      Buffer holding input matrix ``A``. The buffer a contains either
      the upper or the lower triangular part of the matrix ``A`` (see
      upper_lower). The second dimension of a must be at least
      ``max(1, n)``.


   lda
      The leading dimension of a.


   scratchpad_size
      Size of scratchpad memory as a number of floating point elements of type T.
      Size should not be less than the value returned by :ref:`onemkl_lapack_potrf_scratchpad_size` function.


.. container:: section


   .. rubric:: Output Parameters
      :class: sectiontitle


   a
      The buffer a is overwritten by the Cholesky factor ``U`` or ``L``,
      as specified by upper_lower.


   scratchpad
      Buffer holding scratchpad memory to be used by routine for storing intermediate results.


   .. container:: section


      .. rubric:: Throws
         :class: sectiontitle


      onemkl::lapack::exception
         Exception is thrown in case of problems happened during calculations. The ``info`` code of the problem can be obtained by `get_info()` method of exception object:

         If ``info=-i``, the ``i``-th parameter had an illegal value.

         If ``info=i``, and ``get_detail()`` returns 0, then the leading minor of order ``i`` (and therefore the
         matrix ``A`` itself) is not positive-definite, and the
         factorization could not be completed. This may indicate an error
         in forming the matrix ``A``.

         If ``info`` equals to value passed as scratchpad size, and ``get_detail()`` returns non zero, then passed scratchpad is of insufficient size, and required size should not be less than value return by ``get_detail()`` method of exception object.


onemkl::lapack::potrf (USM Version)
--------------------------------------

.. container::

   .. container:: section


      .. rubric:: Syntax
         :class: sectiontitle


      .. cpp:function::  cl::sycl::event onemkl::lapack::potrf(cl::sycl::queue &queue, onemkl::uplo      upper_lower, std::int64_t n, T *a, std::int64_t lda, T *scratchpad, std::int64_t      scratchpad_size, const cl::sycl::vector_class<cl::sycl::event> &events = {})

.. container:: section


   .. rubric:: Input Parameters
      :class: sectiontitle


   queue
      The queue where the routine should be executed.


   upper_lower
      Indicates whether the upper or lower triangular part of ``A`` is
      stored and how ``A`` is factored:


      If upper_lower=\ ``onemkl::uplo::upper``, the array ``a`` stores the
      upper triangular part of the matrix ``A``, and the strictly lower
      triangular part of the matrix is not referenced.


      If upper_lower=\ ``onemkl::uplo::lower``, the array ``a`` stores the
      lower triangular part of the matrix ``A``, and the strictly upper
      triangular part of the matrix is not referenced.


   n
      Specifies the order of the matrix ``A`` (``0≤n``).


   a
      Pointer to input matrix ``A``. The array ``a`` contains either
      the upper or the lower triangular part of the matrix ``A`` (see
      upper_lower). The second dimension of a must be at least
      ``max(1, n)``.


   lda
      The leading dimension of a.


   scratchpad_size
      Size of scratchpad memory as a number of floating point elements of type T.
      Size should not be less than the value returned by :ref:`onemkl_lapack_potrf_scratchpad_size` function.

   events
      List of events to wait for before starting computation. Defaults to empty list.


.. container:: section


   .. rubric:: Output Parameters
      :class: sectiontitle


   a
      The memory pointer to by pointer ``a`` is overwritten by the Cholesky factor ``U`` or ``L``,
      as specified by upper_lower.


   scratchpad
      Pointer to scratchpad memory to be used by routine for storing intermediate results.


   .. container:: section


      .. rubric:: Throws
         :class: sectiontitle


      onemkl::lapack::exception
         Exception is thrown in case of problems happened during calculations. The ``info`` code of the problem can be obtained by `get_info()` method of exception object:

         If ``info=-i``, the ``i``-th parameter had an illegal value.

         If ``info=i``, and ``get_detail()`` returns 0, then the leading minor of order ``i`` (and therefore the
         matrix ``A`` itself) is not positive-definite, and the
         factorization could not be completed. This may indicate an error
         in forming the matrix ``A``.

         If ``info`` equals to value passed as scratchpad size, and ``get_detail()`` returns non zero, then passed scratchpad is of insufficient size, and required size should not be less than value return by ``get_detail()`` method of exception object.


   .. container:: section


      .. rubric:: Return Values
         :class: sectiontitle


      Output event to wait on to ensure computation is complete.


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** :ref:`onemkl_lapack-linear-equation-routines` 


