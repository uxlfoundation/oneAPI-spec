.. _onemkl_lapack_potri:

potri
=====


.. container::


   Computes the inverse of a symmetric (Hermitian) positive-definite
   matrix using the Cholesky factorization.


      potri supports the following precisions.


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


   The routine computes the inverse ``inv(A)`` of a symmetric positive
   definite or, for complex flavors, Hermitian positive-definite matrix
   ``A``. Before calling this routine, call
   :ref:`onemkl_lapack_potrf`
   to factorize ``A``.


potri (BUFFER Version)
----------------------

.. container::

   .. container:: section


      .. rubric:: Syntax
         :class: sectiontitle


      .. cpp:function::  void onemkl::lapack::potri(cl::sycl::queue &queue, onemkl::uplo upper_lower,      std::int64_t n, cl::sycl::buffer<T,1> &a, std::int64_t lda, cl::sycl::buffer<T,1> &scratchpad, std::int64_t      scratchpad_size)

.. container:: section


   .. rubric:: Input Parameters
      :class: sectiontitle


   queue
      The queue where the routine should be executed.

   upper_lower
      Indicates how the input matrix ``A`` has been    factored:

      If ``upper_lower = onemkl::uplo::upper``, the upper   triangle of ``A`` is stored.

      If   ``upper_lower = onemkl::uplo::lower``, the lower triangle of ``A`` is   stored.

   n
      Specifies the order of the matrix    ``A``\ (``0≤n``).

   a
      Contains the factorization of the matrix ``A``, as    returned by   :ref:`onemkl_lapack_potrf`.   The second dimension of ``a`` must be at least ``max(1, n)``.

   lda
      The leading dimension of ``a``.

   scratchpad_size
      Size of scratchpad memory as a number of floating point elements of type T.
      Size should not be less than the value returned by :ref:`onemkl_lapack_potri_scratchpad_size` function.


.. container:: section


   .. rubric:: Output Parameters
      :class: sectiontitle


   a
      Overwritten by the upper or lower triangle of the inverse    of ``A``. Specified by ``upper_lower``.

   scratchpad
      Buffer holding scratchpad memory to be used by routine for storing intermediate results.


   .. container:: section


      .. rubric:: Throws
         :class: sectiontitle


      onemkl::lapack::exception
         Exception is thrown in case of problems happened during calculations. The ``info`` code of the problem can be obtained by `get_info()` method of exception object:

         If ``info=-i``, the ``i``-th parameter had an illegal value.

         If ``info=i``, the ``i``-th diagonal element of the Cholesky factor
         (and therefore the factor itself) is zero, and the inversion could not be completed.

         If ``info`` equals to value passed as scratchpad size, and ``get_detail()`` returns non zero, then passed scratchpad is of insufficient size, and required size should not be less than value return by ``get_detail()`` method of exception object.


potri (USM Version)
----------------------

.. container::

   .. container:: section


      .. rubric:: Syntax
         :class: sectiontitle


      .. cpp:function::  cl::sycl::event onemkl::lapack::potri(cl::sycl::queue &queue, onemkl::uplo upper_lower,      std::int64_t n, T *a, std::int64_t lda, T *scratchpad, std::int64_t      scratchpad_size, const cl::sycl::vector_class<cl::sycl::event> &events = {})

.. container:: section


   .. rubric:: Input Parameters
      :class: sectiontitle


   queue
      The queue where the routine should be executed.

   upper_lower
      Indicates how the input matrix ``A`` has been    factored:

      If ``upper_lower = onemkl::uplo::upper``, the upper   triangle of ``A`` is stored.

      If   ``upper_lower = onemkl::uplo::lower``, the lower triangle of ``A`` is   stored.

   n
      Specifies the order of the matrix    ``A``\ (``0≤n``).

   a
      Contains the factorization of the matrix ``A``, as    returned by   :ref:`onemkl_lapack_potrf`.   The second dimension of ``a`` must be at least ``max(1, n)``.

   lda
      The leading dimension of ``a``.

   scratchpad_size
      Size of scratchpad memory as a number of floating point elements of type T.
      Size should not be less than the value returned by :ref:`onemkl_lapack_potri_scratchpad_size` function.

   events
      List of events to wait for before starting computation. Defaults to empty list.


.. container:: section


   .. rubric:: Output Parameters
      :class: sectiontitle


   a
      Overwritten by the upper or lower triangle of the inverse    of ``A``. Specified by ``upper_lower``.

   scratchpad
      Pointer to scratchpad memory to be used by routine for storing intermediate results.


   .. container:: section


      .. rubric:: Throws
         :class: sectiontitle


      onemkl::lapack::exception
         Exception is thrown in case of problems happened during calculations. The ``info`` code of the problem can be obtained by `get_info()` method of exception object:

         If ``info=-i``, the ``i``-th parameter had an illegal value.

         If ``info=i``, the ``i``-th diagonal element of the Cholesky factor
         (and therefore the factor itself) is zero, and the inversion could not be completed.

         If ``info`` equals to value passed as scratchpad size, and ``get_detail()`` returns non zero, then passed scratchpad is of insufficient size, and required size should not be less than value return by ``get_detail()`` method of exception object.


   .. container:: section


      .. rubric:: Return Values
         :class: sectiontitle


      Output event to wait on to ensure computation is complete.


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** :ref:`onemkl_lapack-linear-equation-routines` 


