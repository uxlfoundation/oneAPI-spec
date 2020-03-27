
ungtr
=====


.. container::


   Generates the complex unitary matrix Q determined by
   `hetrd <hetrd.html>`__. This
   routine belongs to the ``onemkl::lapack``\ namespace.


   .. container:: section
      :name: GUID-F63E0AF3-10D3-4519-8E52-7D9D036AF7F8


      .. rubric:: Syntax
         :class: sectiontitle


      .. cpp:function::  void ungtr(queue &exec_queue, uplo upper_lower,      std::int64_t n, buffer<T,1> &a, std::int64_t lda, buffer<T,1>      &tau, buffer<T,1> &work, std::int64_t lwork,      buffer<std::int64_t,1> &info)

      ``ungtr`` supports the following precisions.


      .. list-table:: 
         :header-rows: 1

         * -  T 
         * -  ``std::complex<float>`` 
         * -  ``std::complex<double>`` 




.. container:: section
   :name: GUID-55A1AE6C-AEA9-43CF-8DB7-805409488D85


   .. rubric:: Description
      :class: sectiontitle


   The routine explicitly generates the ``n``-by-``n`` unitary matrix
   ``Q`` formed by
   `?hetrd <hetrd.html>`__ when
   reducing a complex Hermitian matrix ``A`` to tridiagonal form:
   ``A = Q*T*QH``. Use this routine after a call to
   `?hetrd <hetrd.html>`__.


.. container:: section
   :name: GUID-26A5866D-0DF8-4835-8776-E5E73F0C657A


   .. rubric:: Input Parameters
      :class: sectiontitle


   exec_queue
      The queue where the routine should be executed.


   upper_lower
      Must be ``uplo::upper`` or ``uplo::lower``. Uses the same
      ``upper_lower`` as supplied to
      `hetrd <hetrd.html>`__


   n
      The order of the matrix ``Q``\ ``(0≤n)``.


   a
      The buffer a returned by
      `hetrd <hetrd.html>`__. The
      second dimension of a must be at least ``max(1, n)``.


   lda
      The leading dimension of a\ ``(n≤lda)``.


   tau
      The buffer tau returned by
      `hetrd <hetrd.html>`__. The
      dimension of tau must be at least ``max(1, n-1)``.


   lwork
      The size of the work array (``lwork≥n``). Should be computed by
      `ungtr_get_lwork <ungtr_get_lwork.html>`__.


.. container:: section
   :name: GUID-F0C3D97D-E883-4070-A1C2-4FE43CC37D12


   .. rubric:: Output Parameters
      :class: sectiontitle


   a
      Overwritten by the unitary matrix ``Q``.


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


   An example of how to use ``ungtr``\ can be found in the oneMKL
   installation directory, under:


   ::


      examples/sycl/lapack/orgtr.cpp


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** `LAPACK
      Routines <lapack.html>`__


