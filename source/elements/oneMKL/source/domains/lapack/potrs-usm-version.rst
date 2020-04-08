.. _potrs-usm-version:

potrs (USM Version)
===================


.. container::


   Solves a system of linear equations with a Cholesky-factored
   symmetric (Hermitian) positive-definite coefficient matrix. This
   routine belongs to the onemkl::lapack namespace.


   .. container:: section
      :name: GUID-8EAC9176-B4CB-4B1E-B85F-233555DABA1E


      .. rubric:: Syntax
         :class: sectiontitle


      .. container:: dlsyntaxpara


         ::

           template<typename data_t>
             cl::sycl::event potrs(cl::sycl::queue &queue,         onemkl::uplo upper_lower, std::int64_t n, std::int64_t nrhs,         data_t \*a, std::int64_t lda, data_t \*b, std::int64_t ldb,         std::int64_t &info, cl::sycl::event &e_a_ready, cl::sycl::event         &e_b_ready)

         The USM version of ``potrs`` supports the following precisions.


         .. list-table:: 
            :header-rows: 1

            * -  data_t 
            * -  ``float`` 
            * -  ``double`` 
            * -  ``std::complex<float>`` 
            * -  ``std::complex<double>`` 




   .. container:: section
      :name: GUID-FD48832B-27F6-4FEC-A6AC-548E362E02AB


      .. rubric:: Description
         :class: sectiontitle


      The routine solves for ``X`` the system of linear equations
      ``A``\ \*\ ``X`` = ``B`` with a symmetric positive-definite or,
      for complex data, Hermitian positive-definite matrix A, given the
      Cholesky factorization of ``A``:


      .. list-table:: 
         :header-rows: 1

         * -  ``A`` = ``U``\ :sup:`T`\ \*\ ``U`` for real data, ``A`` =       ``U``\ :sup:`H`\ \*\ ``U`` for complex data
           -  if upper_lower=\ ``onemkl::uplo::upper`` 
         * -  ``A`` = ``L``\ \*\ ``L``\ :sup:`T` for real data, ``A`` =       ``L``\ \*\ ``L``\ :sup:`H` for complex data
           -  if upper_lower=\ ``onemkl::uplo::lower`` 




      where ``L`` is a lower triangular matrix and ``U`` is upper
      triangular. The system is solved with multiple right-hand sides
      stored in the columns of the matrix ``B``.


      Before calling this routine, you must call
      `potrf <potrf.html>`__ to
      compute the Cholesky factorization of A.


   .. container:: section
      :name: GUID-F841BA63-D4EE-4C75-9831-BB804CEA8622


      .. rubric:: Input Parameters
         :class: sectiontitle


      queue
         The queue where the routine should be executed.


      upper_lower
         Indicates how the input matrix has been factored:


         If uplo=\ ``onemkl::uplo::upper``, the upper triangle ``U`` of
         ``A`` is stored, where ``A`` = ``U``\ :sup:`T`\ \*\ ``U`` for
         real data, ``A`` = ``U``\ :sup:`H`\ \*\ ``U`` for complex data.


         If uplo=\ ``onemkl::uplo::lower``, the upper triangle ``L`` of
         ``A`` is stored, where ``A`` = ``L``\ \*\ ``L``\ :sup:`T` for
         real data, ``A`` = ``L``\ \*\ ``L``\ :sup:`H` for complex data.


      n
         The order of matrix ``A`` (0≤n).


      nrhs
         The number of right-hand sides (0≤nrhs).


      a
         Pointer to factorization of the matrix ``A``, as returned by
         `potrf <potrf.html>`__. The
         second dimension of a must be at least max(1, n).


      lda
         The leading dimension of a.


      b
         The array b contains the matrix ``B`` whose columns are the
         right-hand sides for the systems of equations. The second
         dimension of b must be at least max(1,nrhs).


      ldb
         The leading dimension of b.


      e_a_ready
         Event to wait for before starting computation.


      e_b_ready
         Event to wait for before starting computation.


   .. container:: section
      :name: GUID-F0C3D97D-E883-4070-A1C2-4FE43CC37D12


      .. rubric:: Output Parameters
         :class: sectiontitle


      b
         The memory pointed to by pointer b is overwritten by the
         solution matrix ``X``.


      info
         Buffer containing error information.


         If ``info=0``, execution was successful.


         If ``info=-i``, the ``i``-th parameter had an illegal value.


         If ``info=i``, the ``i``-th diagonal element of the Cholesky
         factor is zero , and the solve could not be completed.


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** `LAPACK
      Routines <lapack.html>`__


