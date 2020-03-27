.. _hegvd_get_lwork:

hegvd_get_lwork
===============


.. container::


   Computes the worksize needed for the function,
   `hegvd <hegvd.html>`__. This
   routine belongs to the ``onemkl::lapack``\ namespace.


   .. container:: section
      :name: GUID-9FBC1610-9EB2-4F98-97CF-B74E301DF4AD


      .. rubric:: Syntax
         :class: sectiontitle


      .. container:: dlsyntaxpara


         .. cpp:function::  template <typename fp_complex>void         hegvd_get_lwork(queue &exec_queue, std::int64_t itype, job         jobz, uplo upper_lower, std::int64_t n, std::int64_t lda,         std::int64_t ldb, std::int64_t &lwork, std::int64_t &lrwork,         std::int64_t &liwork)

         ``hegvd_get_lwork`` supports the following precisions.


         .. list-table:: 
            :header-rows: 1

            * -  T 
            * -  ``std::complex<float>`` 
            * -  ``std::complex<double>`` 




   .. container:: section
      :name: GUID-6E26AE63-E2AA-4D9F-B690-7FA8A0882B6F


      .. rubric:: Description
         :class: sectiontitle


      Computes the worksize needed for the computation of eigenvalues or
      eigenvectors of a complex generalized Hermitian positive-definite
      eigenproblem using a divide and conquer method
      (`hegvd <hegvd.html>`__).
      Calls to this routine must specify the template parameter
      explicitly.


   .. container:: section
      :name: GUID-26A5866D-0DF8-4835-8776-E5E73F0C657A


      .. rubric:: Input Parameters
         :class: sectiontitle


      exec_queue
         The queue where the routine should be executed.


      itype
         Must be ``1`` or ``2`` or ``3``. Specifies the problem type to
         be solved:


         if itype\ ``= 1``, the problem type is ``A*x = lambda*B*x``;


         if itype\ ``= 2``, the problem type is ``A*B*x = lambda*x``;


         if itype\ ``= 3``, the problem type is ``B*A*x = lambda*x``.


      jobz
         Must be ``job::novec`` or ``job::vec``.


         If ``jobz = job::novec``, then only eigenvalues are computed.


         If ``jobz = job::vec``, then eigenvalues and eigenvectors are
         computed.


      upper_lower
         Must be ``uplo::upper`` or ``uplo::lower``.


         If ``upper_lower = uplo::upper``, a and b store the upper
         triangular part of ``A`` and ``B``.


         If ``upper_lower = uplo::lower``, a and b store the lower
         triangular part of ``A`` and ``B``.


      n
         The order of the matrices ``A`` and ``B``\ (``0≤n``).


      lda
         The leading dimension of a. Currently lda is not referenced in
         this function.


      ldb
         The leading dimension of b. Currently ldb is not referenced in
         this function.


   .. container:: section
      :name: GUID-399F00E4-1E32-4114-AC10-5A1B420E474E


      .. rubric:: Output Parameters
         :class: sectiontitle


      lwork
         The integer lwork contains the size of the buffer needed for
         computations in
         `hegvd <hegvd.html>`__.


      lrwork
         The integer lrwork contains the size of the buffer needed for
         real precision computations in
         `hegvd <hegvd.html>`__.


      liwork
         The integer liwork contains the size of the integer buffer
         needed for integer computations in
         `hegvd <hegvd.html>`__.


   .. container:: section
      :name: GUID-C97BF68F-B566-4164-95E0-A7ADC290DDE2


      .. rubric:: Example
         :class: sectiontitle


      An example of how to use ``hegvd_get_lwork``\ can be found in the
      oneMKL installation directory, under:


      ::


         examples/sycl/lapack/sygvd.cpp


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** `LAPACK
      Routines <lapack.html>`__


