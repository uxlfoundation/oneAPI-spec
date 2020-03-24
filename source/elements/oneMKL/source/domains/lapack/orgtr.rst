.. _orgtr:

orgtr
=====


.. container::


   Generates the real orthogonal matrix Q determined by
   `?sytrd <sytrd.html>`__. This
   routine belongs to the ``onemkl::lapack``\ namespace.


   .. container:: section
      :name: GUID-76E7621F-DE84-46C0-A273-B1526247494F


      .. rubric:: Syntax
         :name: syntax
         :class: sectiontitle


      .. cpp:function::  void orgtr(queue &exec_queue, uplo upper_lower,      std::int64_t n, buffer<T,1> &a, std::int64_t lda, buffer<T,1>      &tau, buffer<T,1> &work, std::int64_t lwork,      buffer<std::int64_t,1> &info)

      ``orgtr`` supports the following precisions.


      .. list-table:: 
         :header-rows: 1

         * -  T 
         * -  ``float`` 
         * -  ``double`` 




.. container:: section
   :name: GUID-EB340156-9410-4811-B15A-75F220C2D2D7


   .. rubric:: Description
      :name: description
      :class: sectiontitle


   The routine explicitly generates the ``n``-by-``n`` orthogonal matrix
   ``Q`` formed by
   `sytrd <sytrd.html>`__ when
   reducing a real symmetric matrix ``A`` to tridiagonal form:
   ``A = Q*T*QT``. Use this routine after a call to
   `sytrd <sytrd.html>`__.


.. container:: section
   :name: GUID-26A5866D-0DF8-4835-8776-E5E73F0C657A


   .. rubric:: Input Parameters
      :name: input-parameters
      :class: sectiontitle


   exec_queue
      The queue where the routine should be executed.


   upper_lower
      Must be ``uplo::upper`` or ``uplo::lower``. Uses the same
      ``upper_lower`` as supplied
      to\ `sytrd <sytrd.html>`__


   n
      The order of the matrix ``Q``\ ``(0≤n)``.


   a
      The buffer a returned by
      `sytrd <sytrd.html>`__. The
      second dimension of a must be at least ``max(1,n)``.


   lda
      The leading dimension of a\ ``(n≤lda)``.


   tau
      The buffer tau returned by
      `sytrd <sytrd.html>`__. The
      dimension of tau must be at least ``max(1, n-1)``.


   lwork
      The size of the work array ``(lwork≥n)``. Should be computed by
      `orgtr_get_lwork <orgtr_get_lwork.html>`__.


.. container:: section
   :name: GUID-F0C3D97D-E883-4070-A1C2-4FE43CC37D12


   .. rubric:: Output Parameters
      :name: output-parameters
      :class: sectiontitle


   a
      Overwritten by the orthogonal matrix ``Q``.


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


   An example of how to use ``orgtr``\ can be found in the oneMKL
   installation directory, under:


   ::


      examples/sycl/lapack/orgtr.cpp


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** `LAPACK
      Routines <lapack.html>`__


.. container::

