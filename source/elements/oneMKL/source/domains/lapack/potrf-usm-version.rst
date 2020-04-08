.. _potrf-usm-version:

potrf (USM Version)
===================


.. container::


   Computes the Cholesky factorization of a symmetric (Hermitian)
   positive-definite matrix.This routine belongs to the
   ``onemkl::lapack``\ namespace.


   .. container:: section
      :name: GUID-8EAC9176-B4CB-4B1E-B85F-233555DABA1E


      .. rubric:: Syntax
         :class: sectiontitle


      .. container:: dlsyntaxpara


         .. cpp:function::  template<typename data_t> potrf(cl::sycl::queue &queue,         onemkl::uplo upper_lower, std::int64_t n, data_t *a, std::int64_t         lda, std::int64_t &info, cl::sycl::event &e_a_ready)

         The USM version of ``potrf`` supports the following precisions.


         .. list-table:: 
            :header-rows: 1

            * -  T 
            * -  ``float`` 
            * -  ``double`` 
            * -  ``std::complex<float>`` 
            * -  ``std::complex<double>`` 




   .. container:: section
      :name: GUID-FD48832B-27F6-4FEC-A6AC-548E362E02AB


      .. rubric:: Description
         :class: sectiontitle


      The routine forms the Cholesky factorization of a symmetric
      positive-definite or, for complex data, Hermitian
      positive-definite matrix ``A``:


      .. list-table:: 
         :header-rows: 1

         * -  ``A`` = ``U``\ :sup:`T`\ \*\ ``U`` for real data, ``A`` =       ``U``\ :sup:`H`\ \*\ ``U`` for complex data
           -  if upper_lower=\ ``onemkl::uplo::upper`` 
         * -  ``A`` = ``L``\ \*\ ``L``\ :sup:`T` for real data, ``A`` =       ``L``\ \*\ ``L``\ :sup:`H` for complex data
           -  if upper_lower=\ ``onemkl::uplo::lower`` 




      where ``L`` is a lower triangular matrix and ``U`` is upper
      triangular.


   .. container:: section
      :name: GUID-F841BA63-D4EE-4C75-9831-BB804CEA8622


      .. rubric:: Input Parameters
         :class: sectiontitle


      queue
         The queue where the routine should be executed.


      upper_lower
         Indicates whether the upper or lower triangular part of ``A``
         is stored and how ``A`` is factored:


         If upper_lower=\ ``onemkl::uplo::upper``, the array ``a`` stores
         the upper triangular part of the matrix ``A``, and the strictly
         lower triangular part of the matrix is not referenced.


         If upper_lower=\ ``onemkl::uplo::lower``, the array ``a`` stores
         the lower triangular part of the matrix ``A``, and the strictly
         upper triangular part of the matrix is not referenced.


      n
         Specifies the order of the matrix ``A`` (``0≤n``).


      a
         Pointer to input matrix ``A``. The array holding input matrix a
         contains either the upper or the lower triangular part of the
         matrix ``A`` (see upper_lower). The second dimension of a must
         be at least ``max(1, n)``.


      lda
         The leading dimension of a.


      e_a_ready
         Event to wait for before starting computation.


   .. container:: section
      :name: GUID-F0C3D97D-E883-4070-A1C2-4FE43CC37D12


      .. rubric:: Output Parameters
         :class: sectiontitle


      a
         The memory pointed to by pointer a is overwritten by the
         Cholesky factor ``U`` or ``L``, as specified by upper_lower.


      info
         Variable containing error information.


         If ``info=0``, execution was successful.


         If ``info=-i``, the ``i``-th parameter had an illegal value.


         If ``info=i``, the leading minor of order ``i`` (and therefore
         the matrix ``A`` itself) is not positive-definite, and the
         factorization could not be completed. This may indicate an
         error in forming the matrix ``A``.


   .. container:: section
      :name: GUID-ECF823A0-79DB-42F5-87BF-D32CCF1BFAC1


      .. rubric:: Return Values
         :class: sectiontitle


      Output event to wait on to ensure computation is complete.


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** `LAPACK
      Routines <lapack.html>`__


