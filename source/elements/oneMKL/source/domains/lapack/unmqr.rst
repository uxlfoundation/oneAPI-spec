.. _onemkl_lapack_unmqr:

unmqr
=====


.. container::


   Multiplies a complex matrix by the unitary matrix Q of the QR
   factorization formed by unmqr.


      ``unmqr`` supports the following precisions.


      .. list-table:: 
         :header-rows: 1

         * -  T 
         * -  ``std::complex<float>`` 
         * -  ``std::complex<double>`` 




.. container:: section


   .. rubric:: Description
      :class: sectiontitle


   The routine multiplies a rectangular complex matrix ``C`` by ``Q`` or
   ``Q``\ :sup:`H`, where ``Q`` is the unitary matrix ``Q`` of the
   ``QR`` factorization formed by the routines
   :ref:`onemkl_lapack_geqrf`.


   Depending on the parameters ``left_right`` and ``trans``, the routine
   can form one of the matrix products ``Q*C``, ``Q``\ :sup:`H`\ ``*C``,
   ``C*Q``, or ``C*Q``\ :sup:`H` (overwriting the result on ``C``).


unmqr (BUFFER Version)
----------------------

.. container::

   .. container:: section


      .. rubric:: Syntax
         :class: sectiontitle


      .. cpp:function::  void onemkl::lapack::unmqr(cl::sycl::queue &queue, onemkl::side      left_right, onemkl::transpose trans, std::int64_t m, std::int64_t n,      std::int64_t k, cl::sycl::buffer<T,1> &a, std::int64_t lda, cl::sycl::buffer<T,1>      &tau, cl::sycl::buffer<T,1> &c, std::int64_t ldc, cl::sycl::buffer<T,1> &scratchpad,      std::int64_t scratchpad_size)

.. container:: section


   .. rubric:: Input Parameters
      :class: sectiontitle


   queue
      The queue where the routine should be executed.


   left_right
      If ``left_right=onemkl::side::left``, ``Q`` or ``Q``\ :sup:`H` is
      applied to ``C`` from the left.


      If ``left_right=onemkl::side::right``, ``Q`` or ``Q``\ :sup:`H` is
      applied to ``C`` from the right.


   trans
      If ``trans=onemkl::transpose::trans``, the routine multiplies ``C``
      by ``Q``.


      If ``trans=onemkl::transpose::nontrans``, the routine multiplies
      ``C`` by ``Q``\ :sup:`H`.


   m
      The number of rows in the matrix ``A`` (``m≤0``).


   n
      The number of columns in the matrix ``A`` (``0≤n≤m``).


   k
      The number of elementary reflectors whose product defines the
      matrix ``Q`` (``0≤k≤n``).


   a
      The buffer ``a`` as returned by
      :ref:`onemkl_lapack_geqrf`.
      The second dimension of ``a`` must be at least ``max(1,k)``.


   lda
      The leading dimension of ``a``.


   tau
      The buffer ``tau`` as returned by
      :ref:`onemkl_lapack_geqrf`.
      The second dimension of a must be at least ``max(1,k)``.


   c
      The buffer ``c`` contains the matrix ``C``. The second dimension
      of c must be at least ``max(1,n)``.


   ldc
      The leading dimension of c.


   scratchpad_size
      Size of scratchpad memory as a number of floating point elements of type T.
      Size should not be less than the value returned by :ref:`onemkl_lapack_unmqr_scratchpad_size` function.


.. container:: section


   .. rubric:: Output Parameters
      :class: sectiontitle


   c
      Overwritten by the product ``Q``\ \*\ ``C``,
      ``Q``\ :sup:`H`\ \*\ ``C``, ``C``\ \*\ ``Q``, or
      ``C``\ \*\ ``Q``\ :sup:`H` (as specified by ``left_right`` and
      ``trans``).


   scratchpad
      Buffer holding scratchpad memory to be used by routine for storing intermediate results.


   .. container:: section


      .. rubric:: Throws
         :class: sectiontitle


      onemkl::lapack::exception
         Exception is thrown in case of problems happened during calculations. The ``info`` code of the problem can be obtained by `get_info()` method of exception object:

         If ``info=-i``, the ``i``-th parameter had an illegal value.

         If ``info`` equals to value passed as scratchpad size, and ``get_detail()`` returns non zero, then passed scratchpad is of insufficient size, and required size should not be less than value return by ``get_detail()`` method of exception object.


unmqr (USM Version)
----------------------

.. container::

   .. container:: section


      .. rubric:: Syntax
         :class: sectiontitle


      .. cpp:function::  cl::sycl::event onemkl::lapack::unmqr(cl::sycl::queue &queue, onemkl::side      left_right, onemkl::transpose trans, std::int64_t m, std::int64_t n,      std::int64_t k, T *a, std::int64_t lda, T *tau, T *c, std::int64_t ldc, T *scratchpad, std::int64_t scratchpad_size, const cl::sycl::vector_class<cl::sycl::event> &events = {})

.. container:: section


   .. rubric:: Input Parameters
      :class: sectiontitle


   queue
      The queue where the routine should be executed.


   left_right
      If ``left_right=onemkl::side::left``, ``Q`` or ``Q``\ :sup:`H` is
      applied to ``C`` from the left.


      If ``left_right=onemkl::side::right``, ``Q`` or ``Q``\ :sup:`H` is
      applied to ``C`` from the right.


   trans
      If ``trans=onemkl::transpose::trans``, the routine multiplies ``C``
      by ``Q``.


      If ``trans=onemkl::transpose::nontrans``, the routine multiplies
      ``C`` by ``Q``\ :sup:`H`.


   m
      The number of rows in the matrix ``A`` (``m≤0``).


   n
      The number of columns in the matrix ``A`` (``0≤n≤m``).


   k
      The number of elementary reflectors whose product defines the
      matrix ``Q`` (``0≤k≤n``).


   a
      The pointer to ``a`` as returned by
      :ref:`onemkl_lapack_geqrf`.
      The second dimension of ``a`` must be at least ``max(1,k)``.


   lda
      The leading dimension of ``a``.


   tau
      The pointer to ``tau`` as returned by
      :ref:`onemkl_lapack_geqrf`.
      The second dimension of a must be at least ``max(1,k)``.


   c
      The array ``c`` contains the matrix ``C``. The second dimension
      of c must be at least ``max(1,n)``.


   ldc
      The leading dimension of c.


   scratchpad_size
      Size of scratchpad memory as a number of floating point elements of type T.
      Size should not be less than the value returned by :ref:`onemkl_lapack_unmqr_scratchpad_size` function.

   events
      List of events to wait for before starting computation. Defaults to empty list.


.. container:: section


   .. rubric:: Output Parameters
      :class: sectiontitle


   c
      Overwritten by the product ``Q``\ \*\ ``C``,
      ``Q``\ :sup:`H`\ \*\ ``C``, ``C``\ \*\ ``Q``, or
      ``C``\ \*\ ``Q``\ :sup:`H` (as specified by ``left_right`` and
      ``trans``).


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


      **Parent topic:** :ref:`onemkl_lapack-linear-equation-routines` 


