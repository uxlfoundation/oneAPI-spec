.. _potrs:

potrs
=====


.. container::


   Solves a system of linear equations with a Cholesky-factored
   symmetric (Hermitian) positive-definite coefficient matrix. This
   routine belongs to the ``onemkl::lapack``\ namespace.


   .. container:: section
      :name: GUID-19EC4349-151E-4907-B0FC-4800475DB3BA


      .. rubric:: Syntax
         :name: syntax
         :class: sectiontitle


      .. cpp:function::  void potrs(queue &exec_queue, uplo upper_lower,      std::int64_t n, std::int64_t nrhs, buffer<T,1> &a, std::int64_t      lda, buffer<T,1> &b, std::int64_t ldb, buffer<std::int64_t,1>      &info)

      potrs supports the following precisions.


      .. list-table:: 
         :header-rows: 1

         * -  T 
         * -  ``float`` 
         * -  ``double`` 
         * -  ``std::complex<float>`` 
         * -  ``std::complex<double>`` 




.. container:: section
   :name: GUID-676EF153-39BB-4321-98D5-2250576203D7


   .. rubric:: Description
      :name: description
      :class: sectiontitle


   The routine solves for ``X`` the system of linear equations
   ``A*X = B`` with a symmetric positive-definite or, for complex data,
   Hermitian positive-definite matrix ``A``, given the Cholesky
   factorization of ``A``:


   .. list-table:: 
      :header-rows: 1

      * -  ``A = UT*U`` for real data, ``A = UH*U`` for complex data 
        -  if ``uplo=onemkl::uplo::upper`` 
      * -  ``A = L*LT`` for real data, ``A = L*LH`` for complex data 
        -  if ``uplo=onemkl::uplo::lower`` 




   where ``L`` is a lower triangular matrix and ``U`` is upper
   triangular. The system is solved with multiple right-hand sides
   stored in the columns of the matrix ``B``.


   Before calling this routine, you must call
   `potrf <potrf.html>`__ to compute
   the Cholesky factorization of ``A``.


.. container:: section
   :name: GUID-01EBC633-D795-4CD8-A614-9FA0D45EA8F6


   .. rubric:: Input Parameters
      :name: input-parameters
      :class: sectiontitle


   .. list-table:: 
      :header-rows: 1

      * -     exec_queue    
        -      The queue where the routine should be executed.    
      * -     uplo    
        -     Indicates how the input matrix has been factored:          If ``uplo = onemkl::uplo::upper``, the upper triangle   ``U`` of ``A`` is stored, where ``A`` = ``U``\ :sup:`T`\ \*\ ``U``   for real data, ``A`` = ``U``\ :sup:`H`\ \*\ ``U`` for complex data.         If ``uplo = onemkl::uplo::lower``, the lower triangle   ``L`` of ``A`` is stored, where ``A`` = ``L``\ \*\ ``L``\ :sup:`T`   for real data, ``A`` = ``L``\ \*\ ``L``\ :sup:`H` for complex   data.   
      * -     n    
        -      The order of matrix ``A`` (``0≤n``).\     
      * -     nrhs    
        -      The number of right-hand sides (``0≤nrhs``).    
      * -     a    
        -     Buffer containing the factorization of the matrix A, as    returned by   `potrf <potrf.html>`__.   The second dimension of ``a`` must be at least ``max(1, n)``.   
      * -     lda    
        -      The leading dimension of ``a``.     
      * -     b    
        -     The array ``b`` contains the matrix ``B`` whose columns    are the right-hand sides for the systems of equations. The second   dimension of ``b`` must be at least ``max(1,nrhs)``.   
      * -     ldb    
        -      The leading dimension of ``b``.     




.. container:: section
   :name: GUID-81F0ECBE-0BDC-452C-9FFC-D467A44518A5


   .. rubric:: Output Parameters
      :name: output-parameters
      :class: sectiontitle


   .. list-table:: 
      :header-rows: 1

      * -     b    
        -     Overwritten by the solution matrix ``X``.    
      * -     info    
        -     Buffer containing error information.      If    ``info = 0``, the execution is successful.       If   ``info`` = ``i``, the ``i``-th parameter had an illegal   value.      If ``info`` = ``i``, the ``i``-th diagonal   element of the Cholesky factor is zero , and the solve could not be   completed.    




.. container:: section
   :name: EXAMPLE_5EF48B8A07D849EA84A74FE22F0D5B24


   .. rubric:: Example
      :name: example
      :class: sectiontitle


   An example of how to use ``potrs``\ can be found in the oneMKL
   installation directory, under:


   ::


      examples/sycl/lapack/potrs.cpp


.. container:: section
   :name: GUID-3B00B441-C7C0-4D8A-A819-41037F1E5862


   .. rubric:: Known Limitations
      :name: known-limitations
      :class: sectiontitle


   GPU support is for only real precisions.


   GPU support for this function does not include error reporting through
   the info parameter.


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** `LAPACK
      Routines <lapack.html>`__


