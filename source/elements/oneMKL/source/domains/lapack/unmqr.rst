.. _unmqr:

unmqr
=====


.. container::


   Multiplies a complex matrix by the unitary matrix Q of the QR
   factorization formed by unmqr. This routine belongs to the
   ``onemkl::lapack``\ namespace.


   .. container:: section
      :name: GUID-E2DDDD96-CB15-4406-9B18-4FEEE533152F


      .. rubric:: Syntax
         :class: sectiontitle


      .. cpp:function::  void unmqr(queue &exec_queue, onemkl::side      left_right, onemkl::transpose trans, std::int64_t m, std::int64_t n,      std::int64_t k, buffer<T,1> &a, std::int64_t lda, buffer<T,1>      &tau, buffer<T,1> &c, std::int64_t ldc, buffer<T,1> &work,      std::int64_t lwork, buffer<std::int64_t,1> &info)

      ``unmqr`` supports the following precisions.


      .. list-table:: 
         :header-rows: 1

         * -  T 
         * -  ``std::complex<float>`` 
         * -  ``std::complex<double>`` 




.. container:: section
   :name: GUID-DBFDC777-2F55-420B-8F38-93DE282836AB


   .. rubric:: Description
      :class: sectiontitle


   The routine multiplies a rectangular complex matrix ``C`` by ``Q`` or
   ``Q``\ :sup:`H`, where ``Q`` is the unitary matrix ``Q`` of the
   ``QR`` factorization formed by the routines
   `?geqrf <geqrf.html>`__.


   Depending on the parameters ``left_right`` and ``trans``, the routine
   can form one of the matrix products ``Q*C``, ``Q``\ :sup:`H`\ ``*C``,
   ``C*Q``, or ``C*Q``\ :sup:`H` (overwriting the result on ``C``).


.. container:: section
   :name: GUID-F841BA63-D4EE-4C75-9831-BB804CEA8622


   .. rubric:: Input Parameters
      :class: sectiontitle


   exec_queue
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
      The buffer ``a`` returned by
      `geqrf <geqrf.html>`__.
      The second dimension of ``a`` must be at least ``max(1,k)``.


   lda
      The leading dimension of ``a``.


   tau
      The buffer ``tau`` returned by
      `geqrf <geqrf.html>`__.
      The second dimension of a must be at least ``max(1,k)``.


   c
      The buffer ``c`` contains the matrix ``C``. The second dimension
      of c must be at least ``max(1,n)``.


   ldc
      The leading dimension of c.


   lwork
      The size of the work array. Should be computed by
      `unmqr_get_lwork <unmqr_get_lwork.html>`__.


      Constraints:


      ``lwork`` ≥ ``max(1, n)`` if
      ``left_right``\ =\ ``onemkl::side::left``


      ``lwork`` ≥ ``max(1, m)`` if
      ``left_right``\ =\ ``onemkl::side::right``


.. container:: section
   :name: GUID-F0C3D97D-E883-4070-A1C2-4FE43CC37D12


   .. rubric:: Output Parameters
      :class: sectiontitle


   c
      Overwritten by the product ``Q``\ \*\ ``C``,
      ``Q``\ :sup:`H`\ \*\ ``C``, ``C``\ \*\ ``Q``, or
      ``C``\ \*\ ``Q``\ :sup:`H` (as specified by ``left_right`` and
      ``trans``).


   work
      Workspace for internal computations.


   info
      Buffer containing error information.


      If ``info=0``, the execution is successful.


      If ``info=-i``, the ``i``-th parameter had an illegal value.


.. container:: section
   :name: GUID-C97BF68F-B566-4164-95E0-A7ADC290DDE2


   .. rubric:: Example
      :class: sectiontitle


   An example of how to use ``unmqr``\ can be found in the oneMKL
   installation directory, under:


   ::


      examples/sycl/lapack/ormqr.cpp


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** `LAPACK
      Routines <lapack.html>`__


