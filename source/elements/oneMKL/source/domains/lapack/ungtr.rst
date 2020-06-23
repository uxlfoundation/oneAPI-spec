.. _onemkl_lapack_ungtr:

ungtr
=====


.. container::


   Generates the complex unitary matrix Q determined by
   :ref:`onemkl_lapack_hetrd`.


      ``ungtr`` supports the following precisions.


      .. list-table:: 
         :header-rows: 1

         * -  T 
         * -  ``std::complex<float>`` 
         * -  ``std::complex<double>`` 




.. container:: section


   .. rubric:: Description
      :class: sectiontitle


   The routine explicitly generates the ``n``-by-``n`` unitary matrix
   ``Q`` formed by
   :ref:`onemkl_lapack_hetrd` when
   reducing a complex Hermitian matrix ``A`` to tridiagonal form:
   ``A = Q*T*QH``. Use this routine after a call to
   :ref:`onemkl_lapack_hetrd`.


ungtr (BUFFER Version)
----------------------

.. container::

   .. container:: section


      .. rubric:: Syntax
         :class: sectiontitle


      .. cpp:function::  void onemkl::lapack::ungtr(cl::sycl::queue &queue, onemkl::uplo upper_lower,      std::int64_t n, cl::sycl::buffer<T,1> &a, std::int64_t lda, cl::sycl::buffer<T,1>      &tau, cl::sycl::buffer<T,1> &scratchpad, std::int64_t scratchpad_size)

.. container:: section


   .. rubric:: Input Parameters
      :class: sectiontitle


   queue
      The queue where the routine should be executed.


   upper_lower
      Must be ``uplo::upper`` or ``uplo::lower``. Uses the same
      ``upper_lower`` as supplied to
      :ref:`onemkl_lapack_hetrd`.


   n
      The order of the matrix ``Q``\ ``(0≤n)``.


   a
      The buffer ``a`` as returned by
      :ref:`onemkl_lapack_hetrd`. The
      second dimension of a must be at least ``max(1, n)``.


   lda
      The leading dimension of a\ ``(n≤lda)``.


   tau
      The buffer ``tau`` as returned by
      :ref:`onemkl_lapack_hetrd`. The
      dimension of tau must be at least ``max(1, n-1)``.


   scratchpad_size
      Size of scratchpad memory as a number of floating point elements of type T.
      Size should not be less than the value returned by :ref:`onemkl_lapack_ungtr_scratchpad_size` function.


.. container:: section


   .. rubric:: Output Parameters
      :class: sectiontitle


   a
      Overwritten by the unitary matrix ``Q``.


   scratchpad
      Buffer holding scratchpad memory to be used by routine for storing intermediate results.


   .. container:: section


      .. rubric:: Throws
         :class: sectiontitle


      onemkl::lapack::exception
         Exception is thrown in case of problems happened during calculations. The ``info`` code of the problem can be obtained by `get_info()` method of exception object:

         If ``info=-i``, the ``i``-th parameter had an illegal value.

         If ``info`` equals to value passed as scratchpad size, and ``get_detail()`` returns non zero, then passed scratchpad is of insufficient size, and required size should not be less than value return by ``get_detail()`` method of exception object.


ungtr (USM Version)
----------------------

.. container::

   .. container:: section


      .. rubric:: Syntax
         :class: sectiontitle


      .. cpp:function::  cl::sycl::event onemkl::lapack::ungtr(cl::sycl::queue &queue, onemkl::uplo upper_lower,      std::int64_t n, T *a, std::int64_t lda, T *tau, T *scratchpad, std::int64_t scratchpad_size, const cl::sycl::vector_class<cl::sycl::event> &events = {})

.. container:: section


   .. rubric:: Input Parameters
      :class: sectiontitle


   queue
      The queue where the routine should be executed.


   upper_lower
      Must be ``uplo::upper`` or ``uplo::lower``. Uses the same
      ``upper_lower`` as supplied to
      :ref:`onemkl_lapack_hetrd`.


   n
      The order of the matrix ``Q``\ ``(0≤n)``.


   a
      The pointer to ``a`` as returned by
      :ref:`onemkl_lapack_hetrd`. The
      second dimension of a must be at least ``max(1, n)``.


   lda
      The leading dimension of a\ ``(n≤lda)``.


   tau
      The pointer to ``tau`` as returned by
      :ref:`onemkl_lapack_hetrd`. The
      dimension of tau must be at least ``max(1, n-1)``.


   scratchpad_size
      Size of scratchpad memory as a number of floating point elements of type T.
      Size should not be less than the value returned by :ref:`onemkl_lapack_ungtr_scratchpad_size` function.

   events
      List of events to wait for before starting computation. Defaults to empty list.


.. container:: section


   .. rubric:: Output Parameters
      :class: sectiontitle


   a
      Overwritten by the unitary matrix ``Q``.


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


