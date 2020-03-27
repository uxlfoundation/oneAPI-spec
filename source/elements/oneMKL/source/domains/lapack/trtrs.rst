.. _trtrs:

trtrs
=====


.. container::


   Solves a system of linear equations with a triangular coefficient
   matrix, with multiple right-hand sides. This routine belongs to the
   ``onemkl::lapack``\ namespace.


   .. container:: section
      :name: GUID-DD05B917-D07A-4AB2-A4D0-C5F157BFA28E


      .. rubric:: Syntax
         :class: sectiontitle


      .. cpp:function::  void trtrs(queue &exec_queue, uplo upper_lower,      trans transa, diag unit_diag, std::int64_t n, std::int64_t nrhs,      buffer<T,1> &a, std::int64_t lda, buffer<T,1> &b, std::int64_t      ldb, buffer<std::int64_t,1> &info)

      ``trtrs`` supports the following precisions.


      .. list-table:: 
         :header-rows: 1

         * -  T 
         * -  ``float`` 
         * -  ``double`` 
         * -  ``std::complex<float>`` 
         * -  ``std::complex<double>`` 




.. container:: section
   :name: GUID-E7948713-7484-46A3-84E0-F842AD2659CA


   .. rubric:: Description
      :class: sectiontitle


   The routine solves for ``X`` the following systems of linear
   equations with a triangular matrix ``A``, with multiple right-hand
   sides stored in ``B``:


   .. list-table:: 
      :header-rows: 1

      * -     A*X = B    
        -  
        -     if ``transa`` =\ ``transpose::nontrans``,    
      * -     \ ``AT*X = B``\     
        -  
        -     if ``transa`` =\ ``transpose::trans``,    
      * -     A\ :sup:`H`\ ``*X`` = B    
        -  
        -     if ``transa`` =\ ``transpose::conjtrans`` (for complex    matrices only).   




.. container:: section
   :name: GUID-F99EDA15-1260-44DB-9525-A559CED5E2A5


   .. rubric:: Input Parameters
      :class: sectiontitle


   .. list-table:: 
      :header-rows: 1

      * -     exec_queue    
        -      The queue where the routine should be executed.    
      * -     upper_lower    
        -     Indicates whether ``A`` is upper or lower    triangular:      If upper_lower = ``uplo::upper``, then   ``A`` is upper triangular.      If upper_lower =   ``uplo::lower``, then ``A`` is lower triangular.   
      * -     transa    
        -     If transa = ``transpose::nontrans``, then    ``A``\ \*\ ``X`` = ``B`` is solved for ``X``.      If   transa = ``transpose::trans``, then ``A``\ :sup:`T`\ \*\ ``X`` =   ``B`` is solved for ``X``.      If transa =   ``transpose::conjtrans``, then ``A``\ :sup:`H`\ \*\ ``X`` = ``B`` is   solved for ``X``.   
      * -     unit_diag    
        -     If unit_diag = ``diag::nonunit``, then ``A`` is not a    unit triangular matrix.      If unit_diag = ``diag::unit``,   then ``A`` is unit triangular: diagonal elements of ``A`` are assumed   to be 1 and not referenced in the array a.   
      * -     n    
        -     The order of ``A``; the number of rows in ``B``;    n\ ``≥ 0``.    
      * -     nrhs    
        -     The number of right-hand sides; nrhs\ ``≥ 0``.    
      * -     a    
        -     Buffer containing the matrix ``A``.      The    second dimension of a must be at least ``max(1,n)``.   
      * -     lda    
        -     The leading dimension of ``a``;    lda\ ``≥ max(1, n)``.   
      * -     b    
        -     Buffer containing the matrix ``B`` whose columns are the    right-hand sides for the systems of equations.      The   second dimension of b at least ``max(1,nrhs)``.   
      * -     ldb    
        -     The leading dimension of b; ldb\ ``≥ max(1, n)``.    




.. container:: section
   :name: GUID-CF353725-13B9-4B45-825A-3C027C1A376D


   .. rubric:: Output Parameters
      :class: sectiontitle


   .. list-table:: 
      :header-rows: 1

      * -     b    
        -     Overwritten by the solution matrix ``X``.    




.. container:: section
   :name: GUID-E8FCA070-A357-454F-BD90-DF91270C2E49


   .. rubric:: Info
      :name: info
      :class: sectiontitle


   info
      Buffer containing error information.


      If ``info`` = 0, the execution is successful.


      If ``info`` = -``i``, the ``i``-th parameter had an illegal value.


.. container:: section
   :name: GUID-ACC30BA5-5BDE-4169-95F6-1390ECD55715


   .. rubric:: Example
      :class: sectiontitle


   An example of how to use ``trtrs``\ can be found in the oneMKL
   installation directory, under:


   ::


      examples/sycl/lapack/trtrs.cpp


.. container:: section
   :name: GUID-81F25E52-7E8D-4508-8696-46F51F0A972C


   .. rubric:: Known Limitations
      :name: known-limitations
      :class: sectiontitle


   GPU support for this function does not include error reporting
   through the ``info`` parameter.


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** `LAPACK
      Routines <lapack.html>`__


