.. _ormtr:

ormtr
=====


.. container::


   Multiplies a real matrix by the real orthogonal matrix ``Q``
   determined by
   `?sytrd <sytrd.html>`__. This
   routine belongs to the ``onemkl::lapack``\ namespace.


   .. container:: section
      :name: GUID-CEFFA869-EDA6-4724-83FB-A70F7EC743AC


      .. rubric:: Syntax
         :name: syntax
         :class: sectiontitle


      .. cpp:function::  void ormtr(queue &exec_queue, side left_right,      uplo upper_lower, transpose trans, std::int64_t m, std::int64_t n,      buffer<T,1> &a, std::int64_t lda, buffer<T,1> &tau, buffer<T,1>      &c, std::int64_t ldc, buffer<T,1> &work, std::int64_t lwork,      buffer<std::int64_t,1> &info)

      ``ormtr`` supports the following precisions.


      .. list-table:: 
         :header-rows: 1

         * -  T 
         * -  ``float`` 
         * -  ``double`` 




.. container:: section
   :name: GUID-5DEE53EE-9F11-4E2A-BEC6-8B670D1B1280


   .. rubric:: Description
      :name: description
      :class: sectiontitle


   The routine multiplies a real matrix ``C`` by ``Q`` or
   ``Q``\ :sup:`T`, where ``Q`` is the orthogonal matrix ``Q`` formed by
   `sytrd <sytrd.html>`__ when
   reducing a real symmetric matrix ``A`` to tridiagonal form:
   ``A = Q*T*QT``. Use this routine after a call to
   `sytrd <sytrd.html>`__.


   Depending on the parameters left_right and trans, the routine can
   form one of the matrix products ``Q*C``, ``QT*C``, ``C*Q``, or
   ``C*QT`` (overwriting the result on ``C``).


.. container:: section
   :name: GUID-26A5866D-0DF8-4835-8776-E5E73F0C657A


   .. rubric:: Input Parameters
      :name: input-parameters
      :class: sectiontitle


   In the descriptions below, ``r`` denotes the order of ``Q``:


   .. container:: tablenoborder


      .. list-table:: 
         :header-rows: 1

         * -  ``r = m`` 
           -  if ``left_right = side::left`` 
         * -  ``r = n`` 
           -  if ``left_right = side::right`` 




   exec_queue
      The queue where the routine should be executed.


   left_right
      Must be either ``side::left`` or ``side::right``.


      If ``left_right = side::left``, ``Q`` or ``Q``\ :sup:`T` is
      applied to ``C`` from the left.


      If ``left_right = side::right``, ``Q`` or ``Q``\ :sup:`T` is
      applied to ``C`` from the right.


   upper_lower
      Must be either ``uplo::upper`` or ``uplo::lower``. Uses the same
      ``upper_lower`` as supplied to
      `sytrd <sytrd.html>`__.


   trans
      Must be either ``transpose::nontrans`` or ``transpose::trans``.


      If ``trans = transpose::nontrans``, the routine multiplies ``C``
      by ``Q``.


      If ``trans = transpose::trans``, the routine multiplies ``C`` by
      ``Q``\ :sup:`T`.


   m
      The number of rows in the matrix ``C``\ ``(m ≥ 0)``.


   n
      The number of columns in the matrix ``C``\ ``(n ≥ 0)``.


   a
      The buffer a returned by
      `sytrd <sytrd.html>`__.


   lda
      The leading dimension of a\ ``(max(1, r) ≤ lda)``.


   tau
      The buffer tau returned by
      `sytrd <sytrd.html>`__. The
      dimension of tau must be at least ``max(1, r-1)``.


   c
      The buffer c contains the matrix ``C``. The second dimension of c
      must be at least ``max(1, n)``.


   ldc
      The leading dimension of c\ ``(max(1, n) ≤ ldc)``.


   lwork
      The size of the work array ``(lwork≥n)``. Should be computed by
      `ormtr_get_lwork <ormtr_get_lwork.html>`__.


.. container:: section
   :name: GUID-399F00E4-1E32-4114-AC10-5A1B420E474E


   .. rubric:: Output Parameters
      :name: output-parameters
      :class: sectiontitle


   c
      Overwritten by the product ``Q*C``, ``QT*C``, ``C*Q``, or ``C*QT``
      (as specified by ``left_right`` and ``trans``).


   work
      Workspace for internal computations.


   info
      Buffer containing error information.


      If ``info=0``, the execution is successful.


      If ``info=-i``, the ``i``-th parameter had an illegal value.


.. container:: section
   :name: GUID-C97BF68F-B566-4164-95E0-A7ADC290DDE2


   .. rubric:: Example
      :name: example
      :class: sectiontitle


   An example of how to use ``ormtr``\ can be found in the oneMKL
   installation directory, under:


   ::


      examples/sycl/lapack/ormtr.cpp


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** `LAPACK
      Routines <lapack.html>`__


.. container::

