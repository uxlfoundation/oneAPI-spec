.. _unmtr:

unmtr
=====


.. container::


   Multiplies a complex matrix by the complex unitary matrix Q
   determined by
   `hetrd <hetrd.html>`__. This
   routine belongs to the ``onemkl::lapack``\ namespace.


   .. container:: section
      :name: GUID-D89B0E48-3A4E-47F4-B51F-834297BD7620


      .. rubric:: Syntax
         :name: syntax
         :class: sectiontitle


      .. cpp:function::  void unmtr(queue &exec_queue, side left_right,      uplo upper_lower, transpose trans, std::int64_t m, std::int64_t n,      buffer<T,1> &a, std::int64_t lda, buffer<T,1> &tau, buffer<T,1>      &c, std::int64_t ldc, buffer<T,1> &work, std::int64_t lwork,      buffer<std::int64_t,1> &info)

      ``unmtr`` supports the following precisions.


      .. list-table:: 
         :header-rows: 1

         * -  T 
         * -  ``std::complex<float>`` 
         * -  ``std::complex<double>`` 




.. container:: section
   :name: GUID-34264668-20E3-4AB0-B24F-776357284A13


   .. rubric:: Description
      :name: description
      :class: sectiontitle


   The routine multiplies a complex matrix ``C`` by ``Q`` or
   ``Q``\ :sup:`H`, where ``Q`` is the unitary matrix ``Q`` formed by
   `?hetrd <hetrd.html>`__
   when reducing a complex Hermitian matrix ``A`` to tridiagonal form:
   ``A = Q*T*QH``. Use this routine after a call to
   `?hetrd <hetrd.html>`__.


   Depending on the parameters left_right and trans, the routine can
   form one of the matrix products ``Q*C``, ``Q``\ :sup:`H`\ ``*C``,
   ``C*Q``, or ``C*Q``\ :sup:`H` (overwriting the result on ``C``).


.. container:: section
   :name: GUID-F841BA63-D4EE-4C75-9831-BB804CEA8622


   .. rubric:: Input Parameters
      :name: input-parameters
      :class: sectiontitle


   In the descriptions below, ``r`` denotes the order of ``Q``:


   .. container:: tablenoborder


      .. list-table:: 
         :header-rows: 1

         * -  ``r``\ =\ ``m`` 
           -  if ``left_right = side::left`` 
         * -  ``r``\ =\ ``n`` 
           -  if ``left_right = side::right`` 




   exec_queue
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
      `hetrd <hetrd.html>`__.


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
      The buffer a returned by
      `?hetrd <hetrd.html>`__.


   lda
      The leading dimension of a\ ``(max(1,r)≤lda)``.


   tau
      The buffer tau returned by
      `?hetrd <hetrd.html>`__. The
      dimension of tau must be at least ``max(1,r-1)``.


   c
      The buffer c contains the matrix ``C``. The second dimension of c
      must be at least ``max(1,n)``.


   ldc
      The leading dimension of c\ ``(max(1,n)≤ldc)``.


   lwork
      The size of the work array (``lwork≥n``). Should be computed by
      `unmtr_get_lwork <unmtr_get_lwork.html>`__.


.. container:: section
   :name: GUID-F0C3D97D-E883-4070-A1C2-4FE43CC37D12


   .. rubric:: Output Parameters
      :name: output-parameters
      :class: sectiontitle


   c
      Overwritten by the product ``Q*C``, ``Q``\ :sup:`H`\ ``*C``,
      ``C*Q``, or ``C*Q``\ :sup:`H` (as specified by left_right and
      trans).


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


   An example of how to use ``unmtr``\ can be found in the oneMKL
   installation directory, under:


   ::


      examples/sycl/lapack/ormtr.cpp


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** `LAPACK
      Routines <lapack.html>`__


.. container::

