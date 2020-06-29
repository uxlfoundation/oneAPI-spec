.. _onemkl_lapack_getrf:

getrf
=====


.. container::


   Computes the LU factorization of a general m-by-n matrix.


      ``getrf`` supports the following precisions.


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


   The routine computes the ``LU`` factorization of a general
   ``m``-by-``n`` matrix ``A`` as


   ::


                          A = P*L*U,


   where ``P`` is a permutation matrix, ``L`` is lower triangular with
   unit diagonal elements (lower trapezoidal if ``m > n``) and ``U`` is
   upper triangular (upper trapezoidal if ``m < n``). The routine uses
   partial pivoting, with row interchanges.


getrf (BUFFER Version)
----------------------

.. container::

   .. container:: section


      .. rubric:: Syntax
         :class: sectiontitle


      .. cpp:function::  void onemkl::lapack::getrf(cl::sycl::queue &queue, std::int64_t m,      std::int64_t n, cl::sycl::buffer<T,1> &a, std::int64_t lda,      cl::sycl::buffer<std::int64_t,1> &ipiv, cl::sycl::buffer<T,1> &scratchpad, std::int64_t scratchpad_size)

.. container:: section


   .. rubric:: Input Parameters
      :class: sectiontitle


   queue
      The queue where the routine should be executed.

   m
       The number of rows in the matrix ``A`` (``0≤m``).

   n
       The number of columns in ``A``\ (``0≤n``).

   a
      Buffer holding input matrix ``A``. The buffer a contains    the matrix ``A``. The second dimension of a must be at least   ``max(1, n)``.

   lda
      The leading dimension of a.

   scratchpad_size
      Size of scratchpad memory as a number of floating point elements of type T.
      Size should not be less than the value returned by :ref:`onemkl_lapack_getrf_scratchpad_size` function.






.. container:: section


   .. rubric:: Output Parameters
      :class: sectiontitle


   a
      Overwritten by ``L`` and ``U``. The unit diagonal    elements of ``L`` are not stored.
   ipiv
      Array, size at least ``max(1,min(m, n))``. Contains the    pivot indices; for ``1 ≤i≤min(m, n)``,row ``i`` was interchanged with   row ``ipiv(i)``.


   scratchpad
      Buffer holding scratchpad memory to be used by routine for storing intermediate results.


   .. container:: section


      .. rubric:: Throws
         :class: sectiontitle


      onemkl::lapack::exception
         Exception is thrown in case of problems happened during calculations. The ``info`` code of the problem can be obtained by `get_info()` method of exception object:

         If ``info=-i``, the ``i``-th parameter had an illegal value.

         If ``info=i``, ``uii`` is 0. The factorization has been completed, but   ``U`` is exactly singular. Division by 0 will occur if you use the factor ``U`` for solving a system of linear equations.

         If ``info`` equals to value passed as scratchpad size, and ``get_detail()`` returns non zero, then passed scratchpad is of insufficient size, and required size should not be less than value return by ``get_detail()`` method of exception object.


getrf (USM Version)
----------------------

.. container::

   .. container:: section


      .. rubric:: Syntax
         :class: sectiontitle


      .. cpp:function::  cl::sycl::event onemkl::lapack::getrf(cl::sycl::queue &queue, std::int64_t m,      std::int64_t n, T *a, std::int64_t lda, std::int64_t *ipiv, T *scratchpad, std::int64_t scratchpad_size, const cl::sycl::vector_class<cl::sycl::event> &events = {})

.. container:: section


   .. rubric:: Input Parameters
      :class: sectiontitle


   queue
      The queue where the routine should be executed.

   m
       The number of rows in the matrix ``A`` (``0≤m``).

   n
       The number of columns in ``A``\ (``0≤n``).

   a
      Pointer to array holding input matrix ``A``. The second dimension of ``a`` must be at least   ``max(1, n)``.

   lda
      The leading dimension of a.

   scratchpad_size
      Size of scratchpad memory as a number of floating point elements of type T.
      Size should not be less than the value returned by :ref:`onemkl_lapack_getrf_scratchpad_size` function.

   events
      List of events to wait for before starting computation. Defaults to empty list.


.. container:: section


   .. rubric:: Output Parameters
      :class: sectiontitle


   a
      Overwritten by ``L`` and ``U``. The unit diagonal    elements of ``L`` are not stored.

   ipiv
      Array, size at least ``max(1,min(m, n))``. Contains the    pivot indices; for ``1 ≤i≤min(m, n)``,row ``i`` was interchanged with   row ``ipiv(i)``.


   scratchpad
      Pointer to scratchpad memory to be used by routine for storing intermediate results.


   .. container:: section


      .. rubric:: Throws
         :class: sectiontitle


      onemkl::lapack::exception
         Exception is thrown in case of problems happened during calculations. The ``info`` code of the problem can be obtained by `get_info()` method of exception object:

         If ``info=-i``, the ``i``-th parameter had an illegal value.

         If ``info=i``, ``uii`` is 0. The factorization has been completed, but   ``U`` is exactly singular. Division by 0 will occur if you use the factor ``U`` for solving a system of linear equations.

         If ``info`` equals to value passed as scratchpad size, and ``get_detail()`` returns non zero, then passed scratchpad is of insufficient size, and required size should not be less than value return by ``get_detail()`` method of exception object.


   .. container:: section


      .. rubric:: Return Values
         :class: sectiontitle


      Output event to wait on to ensure computation is complete.


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** :ref:`onemkl_lapack-linear-equation-routines` 


