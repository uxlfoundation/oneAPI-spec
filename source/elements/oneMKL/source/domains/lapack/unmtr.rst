.. _onemkl_lapack_unmtr:

onemkl::lapack::unmtr
=====================


.. container::


   Multiplies a complex matrix by the complex unitary matrix Q
   determined by
   :ref:`onemkl_lapack_hetrd`.


      ``unmtr`` supports the following precisions.


      .. list-table:: 
         :header-rows: 1

         * -  T 
         * -  ``std::complex<float>`` 
         * -  ``std::complex<double>`` 




.. container:: section


   .. rubric:: Description
      :class: sectiontitle


   The routine multiplies a complex matrix ``C`` by ``Q`` or
   ``Q``\ :sup:`H`, where ``Q`` is the unitary matrix ``Q`` formed by
   :ref:`onemkl_lapack_hetrd`
   when reducing a complex Hermitian matrix ``A`` to tridiagonal form:
   ``A = Q*T*QH``. Use this routine after a call to
   :ref:`onemkl_lapack_hetrd`.


   Depending on the parameters left_right and trans, the routine can
   form one of the matrix products ``Q*C``, ``Q``\ :sup:`H`\ ``*C``,
   ``C*Q``, or ``C*Q``\ :sup:`H` (overwriting the result on ``C``).


onemkl::lapack::unmtr (BUFFER Version)
--------------------------------------

.. container::

   .. container:: section


      .. rubric:: Syntax
         :class: sectiontitle


      .. cpp:function::  void onemkl::lapack::unmtr(cl::sycl::queue &queue, onemkl::side left_right,      onemkl::uplo upper_lower, onemkl::transpose trans, std::int64_t m, std::int64_t n,      cl::sycl::buffer<T,1> &a, std::int64_t lda, cl::sycl::buffer<T,1> &tau, cl::sycl::buffer<T,1>      &c, std::int64_t ldc, cl::sycl::buffer<T,1> &scratchpad, std::int64_t scratchpad_size)

.. container:: section


   .. rubric:: Input Parameters
      :class: sectiontitle


   In the descriptions below, ``r`` denotes the order of ``Q``:


   .. container:: tablenoborder


      .. list-table:: 
         :header-rows: 1

         * -  ``r``\ =\ ``m`` 
           -  if ``left_right = side::left`` 
         * -  ``r``\ =\ ``n`` 
           -  if ``left_right = side::right`` 




   queue
      The queue where the routine should be executed.


   left_right
      Must be either ``side::left`` or ``side::right``.


      If ``left_right=side::left``, ``Q`` or ``Q``\ :sup:`H` is applied
      to ``C`` from the left.


      If ``left_right=side::right``, ``Q`` or ``Q``\ :sup:`H` is applied
      to ``C`` from the right.


   upper_lower
      Must be either ``uplo::upper`` or ``uplo::lower``. Uses the same
      ``upper_lower`` as supplied to
      :ref:`onemkl_lapack_hetrd`.


   trans
      Must be either ``transpose::nontrans`` or
      ``transpose::conjtrans``.


      If ``trans=transpose::nontrans``, the routine multiplies ``C`` by
      ``Q``.


      If ``trans=transpose::conjtrans``, the routine multiplies ``C`` by
      ``Q``\ :sup:`H`.


   m
      The number of rows in the matrix ``C`` (``m≥0``).


   n
      The number of columns the matrix ``C`` (``n≥0``).


   k
      The number of elementary reflectors whose product defines the
      matrix ``Q`` (``0≤k≤n``).


   a
      The buffer ``a`` as returned by
      :ref:`onemkl_lapack_hetrd`.


   lda
      The leading dimension of a\ ``(max(1,r)≤lda)``.


   tau
      The buffer ``tau`` as returned by
      :ref:`onemkl_lapack_hetrd`. The
      dimension of tau must be at least ``max(1,r-1)``.


   c
      The buffer c contains the matrix ``C``. The second dimension of c
      must be at least ``max(1,n)``.


   ldc
      The leading dimension of c\ ``(max(1,n)≤ldc)``.


   scratchpad_size
      Size of scratchpad memory as a number of floating point elements of type T.
      Size should not be less than the value returned by :ref:`onemkl_lapack_unmtr_scratchpad_size` function.


.. container:: section


   .. rubric:: Output Parameters
      :class: sectiontitle


   c
      Overwritten by the product ``Q*C``, ``Q``\ :sup:`H`\ ``*C``,
      ``C*Q``, or ``C*Q``\ :sup:`H` (as specified by left_right and
      trans).


   scratchpad
      Buffer holding scratchpad memory to be used by routine for storing intermediate results.


   .. container:: section


      .. rubric:: Throws
         :class: sectiontitle


      onemkl::lapack::exception
         Exception is thrown in case of problems happened during calculations. The ``info`` code of the problem can be obtained by `get_info()` method of exception object:

         If ``info=-i``, the ``i``-th parameter had an illegal value.

         If ``info`` equals to value passed as scratchpad size, and ``get_detail()`` returns non zero, then passed scratchpad is of insufficient size, and required size should not be less than value return by ``get_detail()`` method of exception object.


onemkl::lapack::unmtr (USM Version)
--------------------------------------

.. container::

   .. container:: section


      .. rubric:: Syntax
         :class: sectiontitle


      .. cpp:function::  cl::sycl::event onemkl::lapack::unmtr(cl::sycl::queue &queue, onemkl::side left_right,      onemkl::uplo upper_lower, onemkl::transpose trans, std::int64_t m, std::int64_t n, T *a, std::int64_t lda, T *tau, T *c, std::int64_t ldc, T *scratchpad, std::int64_t scratchpad_size, const cl::sycl::vector_class<cl::sycl::event> &events = {})

.. container:: section


   .. rubric:: Input Parameters
      :class: sectiontitle


   In the descriptions below, ``r`` denotes the order of ``Q``:


   .. container:: tablenoborder


      .. list-table:: 
         :header-rows: 1

         * -  ``r``\ =\ ``m`` 
           -  if ``left_right = side::left`` 
         * -  ``r``\ =\ ``n`` 
           -  if ``left_right = side::right`` 




   queue
      The queue where the routine should be executed.


   left_right
      Must be either ``side::left`` or ``side::right``.


      If ``left_right=side::left``, ``Q`` or ``Q``\ :sup:`H` is applied
      to ``C`` from the left.


      If ``left_right=side::right``, ``Q`` or ``Q``\ :sup:`H` is applied
      to ``C`` from the right.


   upper_lower
      Must be either ``uplo::upper`` or ``uplo::lower``. Uses the same
      ``upper_lower`` as supplied to
      :ref:`onemkl_lapack_hetrd`.


   trans
      Must be either ``transpose::nontrans`` or
      ``transpose::conjtrans``.


      If ``trans=transpose::nontrans``, the routine multiplies ``C`` by
      ``Q``.


      If ``trans=transpose::conjtrans``, the routine multiplies ``C`` by
      ``Q``\ :sup:`H`.


   m
      The number of rows in the matrix ``C`` (``m≥0``).


   n
      The number of columns the matrix ``C`` (``n≥0``).


   k
      The number of elementary reflectors whose product defines the
      matrix ``Q`` (``0≤k≤n``).


   a
      The pointer to ``a`` as returned by
      :ref:`onemkl_lapack_hetrd`.


   lda
      The leading dimension of a\ ``(max(1,r)≤lda)``.


   tau
      The pointer to ``tau`` as returned by
      :ref:`onemkl_lapack_hetrd`. The
      dimension of tau must be at least ``max(1,r-1)``.


   c
      The array ``c`` contains the matrix ``C``. The second dimension of c
      must be at least ``max(1,n)``.


   ldc
      The leading dimension of c\ ``(max(1,n)≤ldc)``.


   scratchpad_size
      Size of scratchpad memory as a number of floating point elements of type T.
      Size should not be less than the value returned by :ref:`onemkl_lapack_unmtr_scratchpad_size` function.

   events
      List of events to wait for before starting computation. Defaults to empty list.


.. container:: section


   .. rubric:: Output Parameters
      :class: sectiontitle


   c
      Overwritten by the product ``Q*C``, ``Q``\ :sup:`H`\ ``*C``,
      ``C*Q``, or ``C*Q``\ :sup:`H` (as specified by left_right and
      trans).


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


