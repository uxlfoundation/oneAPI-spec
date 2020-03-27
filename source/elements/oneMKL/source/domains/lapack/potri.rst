.. _potri:

potri
=====


.. container::


   Computes the inverse of a symmetric (Hermitian) positive-definite
   matrix using the Cholesky factorization. This routine belongs to the
   ``onemkl::lapack``\ namespace.


   .. container:: section
      :name: GUID-04971DD3-D455-4898-9876-68AA07155B4E


      .. rubric:: Syntax
         :name: syntax
         :class: sectiontitle


      .. cpp:function::  void potri(queue &exec_queue, uplo upper_lower,      std::int64_t n, buffer<T,1> &a, std::int64_t lda,      buffer<std::int64_t,1> &info)

      potri supports the following precisions.


      .. list-table:: 
         :header-rows: 1

         * -  T 
         * -  ``float`` 
         * -  ``double`` 
         * -  ``std::complex<float>`` 
         * -  ``std::complex<double>`` 




.. container:: section
   :name: GUID-810993B2-2E94-47BF-8510-01671D72DD28


   .. rubric:: Description
      :name: description
      :class: sectiontitle


   The routine computes the inverse ``inv(A)`` of a symmetric positive
   definite or, for complex flavors, Hermitian positive-definite matrix
   ``A``. Before calling this routine, call
   `potrf <potrf.html>`__
   to factorize ``A``.


.. container:: section
   :name: GUID-EBB8D6F9-1305-4469-8328-E46B8B6402B8


   .. rubric:: Input Parameters
      :name: input-parameters
      :class: sectiontitle


   .. list-table:: 
      :header-rows: 1

      * -     exec_queue    
        -      The queue where the routine should be executed.    
      * -     uplo    
        -     Indicates how the input matrix ``A`` has been    factored:      If ``uplo = onemkl::uplo::upper``, the upper   triangle of ``A`` is stored.       If   ``uplo = onemkl::uplo::lower``, the lower triangle of ``A`` is   stored.   
      * -     n    
        -      Specifies the order of the matrix    ``A``\ (``0≤n``).   
      * -     a    
        -      Contains the factorization of the matrix ``A``, as    returned by   `potrf <potrf.html>`__.   The second dimension of ``a`` must be at least ``max(1, n)``.   
      * -     lda    
        -      The leading dimension of ``a``.     




.. container:: section
   :name: GUID-5F045D15-A28B-4028-A2A9-6F1C4A1C26DE


   .. rubric:: Output Parameters
      :name: output-parameters
      :class: sectiontitle


   .. list-table:: 
      :header-rows: 1

      * -     a    
        -     Overwritten by the upper or lower triangle of the inverse    of ``A``. Specified by ``uplo``.   
      * -     info    
        -     Buffer containing error information    




.. container:: section
   :name: EXAMPLE_5EF48B8A07D849EA84A74FE22F0D5B24


   .. rubric:: Example
      :name: example
      :class: sectiontitle


   An example of how to use ``potri``\ can be found in the oneMKL
   installation directory, under:


   ::


      examples/sycl/lapack/potri.cpp


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** `LAPACK
      Routines <lapack.html>`__


