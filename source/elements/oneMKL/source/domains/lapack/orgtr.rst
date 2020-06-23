.. _onemkl_lapack_orgtr:

orgtr
=====


.. container::


   Generates the real orthogonal matrix Q determined by
   :ref:`onemkl_lapack_sytrd`.


      ``orgtr`` supports the following precisions.


      .. list-table:: 
         :header-rows: 1

         * -  T 
         * -  ``float`` 
         * -  ``double`` 




.. container:: section


   .. rubric:: Description
      :class: sectiontitle


   The routine explicitly generates the ``n``-by-``n`` orthogonal matrix
   ``Q`` formed by
   :ref:`onemkl_lapack_sytrd` when
   reducing a real symmetric matrix ``A`` to tridiagonal form:
   ``A = Q*T*QT``. Use this routine after a call to
   :ref:`onemkl_lapack_sytrd`.


orgtr (BUFFER Version)
----------------------

.. container::

   .. container:: section


      .. rubric:: Syntax
         :class: sectiontitle


      .. cpp:function::  void onemkl::lapack::orgtr(cl::sycl::queue &queue, onemkl::uplo upper_lower,      std::int64_t n, cl::sycl::buffer<T,1> &a, std::int64_t lda, cl::sycl::buffer<T,1>      &tau, cl::sycl::buffer<T,1> &scratchpad, std::int64_t scratchpad_size)

.. container:: section


   .. rubric:: Input Parameters
      :class: sectiontitle


   queue
      The queue where the routine should be executed.


   upper_lower
      Must be ``uplo::upper`` or ``uplo::lower``. Uses the same
      ``upper_lower`` as supplied
      to :ref:`onemkl_lapack_sytrd`.


   n
      The order of the matrix ``Q``\ ``(0≤n)``.


   a
      The buffer ``a`` as returned by
      :ref:`onemkl_lapack_sytrd`. The
      second dimension of a must be at least ``max(1,n)``.


   lda
      The leading dimension of a\ ``(n≤lda)``.


   tau
      The buffer ``tau`` as returned by
      :ref:`onemkl_lapack_sytrd`. The
      dimension of tau must be at least ``max(1, n-1)``.


   scratchpad_size
      Size of scratchpad memory as a number of floating point elements of type T.
      Size should not be less than the value returned by :ref:`onemkl_lapack_orgtr_scratchpad_size` function.


.. container:: section


   .. rubric:: Output Parameters
      :class: sectiontitle


   a
      Overwritten by the orthogonal matrix ``Q``.


   scratchpad
      Buffer holding scratchpad memory to be used by routine for storing intermediate results.


   .. container:: section


      .. rubric:: Throws
         :class: sectiontitle


      onemkl::lapack::exception
         Exception is thrown in case of problems happened during calculations. The ``info`` code of the problem can be obtained by `get_info()` method of exception object:

         If ``info=-i``, the ``i``-th parameter had an illegal value.

         If ``info`` equals to value passed as scratchpad size, and ``get_detail()`` returns non zero, then passed scratchpad is of insufficient size, and required size should not be less than value return by ``get_detail()`` method of exception object.


orgtr (USM Version)
----------------------

.. container::

   .. container:: section


      .. rubric:: Syntax
         :class: sectiontitle


      .. cpp:function::  cl::sycl::event onemkl::lapack::orgtr(cl::sycl::queue &queue, onemkl::uplo upper_lower,      std::int64_t n, T *a, std::int64_t lda, T *tau, T *scratchpad, std::int64_t scratchpad_size, const cl::sycl::vector_class<cl::sycl::event> &events = {})

.. container:: section


   .. rubric:: Input Parameters
      :class: sectiontitle


   queue
      The queue where the routine should be executed.


   upper_lower
      Must be ``uplo::upper`` or ``uplo::lower``. Uses the same
      ``upper_lower`` as supplied
      to :ref:`onemkl_lapack_sytrd`.


   n
      The order of the matrix ``Q``\ ``(0≤n)``.


   a
      The pointer to ``a`` as returned by
      :ref:`onemkl_lapack_sytrd`. The
      second dimension of a must be at least ``max(1,n)``.


   lda
      The leading dimension of a\ ``(n≤lda)``.


   tau
      The pointer to ``tau`` as returned by
      :ref:`onemkl_lapack_sytrd`. The
      dimension of tau must be at least ``max(1, n-1)``.


   scratchpad_size
      Size of scratchpad memory as a number of floating point elements of type T.
      Size should not be less than the value returned by :ref:`onemkl_lapack_orgtr_scratchpad_size` function.

   events
      List of events to wait for before starting computation. Defaults to empty list.


.. container:: section


   .. rubric:: Output Parameters
      :class: sectiontitle


   a
      Overwritten by the orthogonal matrix ``Q``.


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


