.. _sytrf:

sytrf
=====


.. container::


   Computes the Bunch-Kaufman factorization of a symmetric matrix. This
   routine belongs to the ``onemkl::lapack``\ namespace.


   .. container:: section
      :name: GUID-5F34A4EC-2BC9-4EB0-9F83-16A880740FB0


      .. rubric:: Syntax
         :class: sectiontitle


      .. cpp:function::  void sytrf(queue &exec_queue, uplo upper_lower,      std::int64_t n, buffer<T,1> &a, std::int64_t lda, buffer<int_64,1>      &ipiv, buffer<T,1> &work, std::int64_t lwork,      buffer<std::int64_t,1> &info)

      sytrf supports the following precisions.


      .. list-table:: 
         :header-rows: 1

         * -  T 
         * -  ``float`` 
         * -  ``double`` 
         * -  ``std::complex<float>`` 
         * -  ``std::complex<double>`` 




.. container:: section
   :name: GUID-5D25BE58-8EB2-4BE1-B262-AFB9EDA29E84


   .. rubric:: Description
      :class: sectiontitle


   The routine computes the factorization of a real/complex symmetric
   matrix ``A`` using the Bunch-Kaufman diagonal pivoting method. The
   form of the factorization is:


   -  if ``upper_lower=uplo::upper``, ``A`` = ``U*D*U``\ :sup:`T`


   -  if ``upper_lower=uplo::lower``, ``A`` = ``L*D*L``\ :sup:`T`


   where ``A`` is the input matrix, ``U`` and ``L`` are products of
   permutation and triangular matrices with unit diagonal (upper
   triangular for ``U`` and lower triangular for ``L``), and ``D`` is a
   symmetric block-diagonal matrix with 1-by-1 and 2-by-2 diagonal
   blocks. ``U`` and ``L`` have 2-by-2 unit diagonal blocks
   corresponding to the 2-by-2 blocks of ``D``.


.. container:: section
   :name: GUID-4EEDE963-6F15-482C-B679-34A5F704484B


   .. rubric:: Input Parameters
      :class: sectiontitle


   .. list-table:: 
      :header-rows: 1

      * -     exec_queue    
        -      The queue where the routine should be executed.    
      * -     upper_lower    
        -     Indicates whether the upper or lower triangular part of    ``A`` is stored and how ``A`` is factored:       If   ``upper_lower=uplo::upper``, the buffer a stores the upper triangular   part of the matrix ``A``, and ``A`` is factored as ``U*D*UT``.         If ``upper_lower=uplo::lower``, the buffer a stores   the lower triangular part of the matrix ``A``, and ``A`` is factored   as ``L*D*LT``.   
      * -     n    
        -     The order of matrix ``A`` (``0≤n``).    
      * -     a    
        -     The buffer ``a``, size max(1,lda\*n). The buffer ``a``    contains either the upper or the lower triangular part of the matrix   ``A`` (see ``upper_lower``). The second dimension of ``a`` must be at   least ``max(1, n)``.   
      * -     lda    
        -      The leading dimension of ``a``.    
      * -     lwork    
        -     The size of the work array. Should be computed by    `sytrf_get_lwork <sytrf_get_lwork.html>`__.   




.. container:: section
   :name: GUID-1D8F271C-059C-4D20-A37A-B522BF1506E0


   .. rubric:: Output Parameters
      :class: sectiontitle


   .. list-table:: 
      :header-rows: 1

      * -     a    
        -     The upper or lower triangular part of a is overwritten by    details of the block-diagonal matrix ``D`` and the multipliers used   to obtain the factor ``U`` (or ``L``).    
      * -     ipiv    
        -     Buffer, size at least ``max(1, n)``. Contains details of    the interchanges and the block structure of ``D``. If   ``ipiv(i)=k>0``, then ``d``\ :sub:`ii` is a 1-by-1 block, and the   ``i``-th row and column of ``A`` was interchanged with the ``k``-th   row and column.      If ``upper_lower=onemkl::uplo::upper``   and ``ipiv(i)=ipiv(i-1)=-m<0``, then ``D`` has a 2-by-2 block in   rows/columns ``i`` and ``i``-1, and (``i``-1)-th row and column of   ``A`` was interchanged with the ``m``-th row and   column.      If ``upper_lower=onemkl::uplo::lower`` and   ``ipiv(i)=ipiv(i+1)=-m<0``, then ``D`` has a 2-by-2 block in   rows/columns ``i`` and ``i``\ +1, and (``i``\ +1)-th row and column   of ``A`` was interchanged with the ``m``-th row and column.   
      * -     work    
        -      Workspace for internal computations.    
      * -     info    
        -     Buffer containing error information:      If    ``info=0``, the execution is successful.      If   ``info=-i``, the ``i``-th parameter had an illegal   value.      If ``info=i``, ``d``\ :sub:`ii` is 0. The   factorization has been completed, but ``D`` is exactly singular.   Division by 0 will occur if you use ``D`` for solving a system of   linear equations.   




.. container:: section
   :name: EXAMPLE_5EF48B8A07D849EA84A74FE22F0D5B24


   .. rubric:: Example
      :class: sectiontitle


   An example of how to use ``sytrf``\ can be found in the oneMKL
   installation directory, under:


   ::


      examples/sycl/lapack/sytrf.cpp


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** `LAPACK
      Routines <lapack.html>`__


