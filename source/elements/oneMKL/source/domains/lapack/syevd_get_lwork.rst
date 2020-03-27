.. _syevd_get_lwork:

syevd_get_lwork
===============


.. container::


   Computes the worksize needed for the function,
   `syevd <syevd.html>`__. This
   routine belongs to the ``onemkl::lapack``\ namespace.


   .. container:: section
      :name: GUID-9FBC1610-9EB2-4F98-97CF-B74E301DF4AD


      .. rubric:: Syntax
         :name: syntax
         :class: sectiontitle


      .. container:: dlsyntaxpara


         .. cpp:function::  template <typename fp_real>void         syevd_get_lwork(queue &exec_queue, job jobz, uplo upper_lower,         std::int64_t n, std::int64_t lda, std::int64_t &lwork,         std::int64_t &liwork)

         ``syevd_get_lwork`` supports the following precisions.


         .. list-table:: 
            :header-rows: 1

            * -  T 
            * -  ``float`` 
            * -  ``double`` 




   .. container:: section
      :name: GUID-6E26AE63-E2AA-4D9F-B690-7FA8A0882B6F


      .. rubric:: Description
         :name: description
         :class: sectiontitle


      Computes the worksize needed for the computation of eigenvalues or
      eigenvectors of a real symmetric matrix using divide and conquer
      algorithm
      (`syevd <syevd.html>`__).
      Calls to this routine must specify the template parameter
      explicitly.


   .. container:: section
      :name: GUID-26A5866D-0DF8-4835-8776-E5E73F0C657A


      .. rubric:: Input Parameters
         :name: input-parameters
         :class: sectiontitle


      exec_queue
         The queue where the routine should be executed.


      jobz
         Must be ``job::novec`` or ``job::vec``.


         If ``jobz = job::novec``, then only eigenvalues are computed.


         If ``jobz = job::vec``, then eigenvalues and eigenvectors are
         computed.


      upper_lower
         Must be ``uplo::upper`` or ``uplo::lower``.


         If ``upper_lower = job::upper``, a stores the upper triangular
         part of ``A``.


         If ``upper_lower = job::lower``, a stores the lower triangular
         part of ``A``.


      n
         The order of the matrix ``A`` (``0≤n``).


      lda
         The leading dimension of a. Currently lda is not referenced in
         this function.


   .. container:: section
      :name: GUID-399F00E4-1E32-4114-AC10-5A1B420E474E


      .. rubric:: Output Parameters
         :name: output-parameters
         :class: sectiontitle


      lwork
         The integer lwork contains the size of the buffer needed for
         computations in
         `syevd <syevd.html>`__.


      liwork
         The integer liwork contains the size of the integer buffer
         needed for computations in
         `syevd <syevd.html>`__.


   .. container:: section
      :name: GUID-C97BF68F-B566-4164-95E0-A7ADC290DDE2


      .. rubric:: Example
         :name: example
         :class: sectiontitle


      An example of how to use ``syevd_get_lwork``\ can be found in the
      oneMKL installation directory, under:


      ::


         examples/sycl/lapack/syevd.cpp


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** `LAPACK
      Routines <lapack.html>`__


