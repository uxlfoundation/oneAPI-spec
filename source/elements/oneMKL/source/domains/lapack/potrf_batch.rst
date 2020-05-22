
potrf_batch
===========


.. container::


   Computes the Cholesky factorizations of a batch of symmetric
   (Hermitian) positive-definite matrices. This routine belongs to the
   ``onemkl::lapack``\ namespace.


   .. container:: section
      :name: GUID-814D7756-F1E2-4417-A0EA-B4294B8303D4


      .. rubric:: Syntax
         :class: sectiontitle


      .. container:: dlsyntaxpara


         .. cpp:function::  void potrf_batch(queue &exec_queue,         std::vector< onemkl::uplo > const& uplo, std::vector<std::int64_t>         const& n, std::vector<buffer<T,1>> &a,         std::vector<std::int64_t> const& lda,         std::vector<buffer<std::int64_t,1>> &info)

         ``potrf_batch`` supports the following precisions.


         .. list-table:: 
            :header-rows: 1

            * -  T 
            * -  ``float`` 
            * -  ``double`` 
            * -  ``std::complex<float>`` 
            * -  ``std::complex<double>`` 




   .. container:: section
      :name: GUID-A3A0248F-23B3-4E74-BDA2-BB8D23F19A50


      .. rubric:: Description
         :class: sectiontitle


      The routine forms the Cholesky factorizations of a batch of
      symmetric positive-definite or, for complex data, Hermitian
      positive-definite matrices ``A``\ :sub:`1`, ``A``\ :sub:`2`, …,
      ``A``\ :sub:`1batch_size`


      ``A``\ :sub:`i` = ``U``\ :sub:`i`\ :sup:`T` \* ``U``\ :sub:`i` for
      real data, If ``uplo[i] = onemkl::uplo::upper``


      ``A``\ :sub:`i` = ``U``\ :sub:`i`\ :sup:`H` \* ``U``\ :sub:`i` for
      complex data.


      ``A``\ :sub:`i` = ``L``\ :sub:`i`\ :sup:`T` \* ``L``\ :sub:`i` for
      real data, If ``uplo[i] = onemkl::uplo::lower``


      ``A``\ :sub:`i` = ``L``\ :sub:`i`\ :sup:`H` \* ``L``\ :sub:`i` for
      complex data.


      Where ``L``\ :sub:`i` is a lower triangular matrix and
      ``U``\ :sub:`i` is an upper triangular matrix.


   .. container:: section
      :name: GUID-F841BA63-D4EE-4C75-9831-BB804CEA8622


      .. rubric:: Input Parameters
         :class: sectiontitle


      exec_queue
         The queue where the routine should be executed.


      uplo
         A vector, ``uplo[i]`` indicates whether the upper or lower
         triangular part of the matrix ``A``\ :sub:`i` is stored and how
         ``A``\ :sub:`i` is factored:


         If ``uplo = onemkl::upper``, then buffer ``a[i]`` stores the upper
         triangular part of ``A``\ :sub:`i` and the strictly lower
         triangular part of the matrix is not referenced.


         If ``uplo = onemkl::lower``, then buffer ``a[i]`` stores the lower
         triangular part of ``A``\ :sub:`i` and the strictly upper
         triangular part of the matrix is not referenced.


      n
         A vector, ``n[i]`` is the number of columns of the batch matrix
         ``A``\ :sub:`i`\ ``(0≤n[i])``.


      a
         A vector of buffers, ``a[i]`` stores the matrix
         ``A``\ :sub:`i`. ``a[i]`` must be of size at least
         ``lda[i]*max(1, n[i])``.


      lda
         A vector, ``lda[i]`` is the leading dimension of
         ``a[i] (n[i]≤lda[i])``.


   .. container:: section
      :name: GUID-F0C3D97D-E883-4070-A1C2-4FE43CC37D12


      .. rubric:: Output Parameters
         :class: sectiontitle


      a
         ``a[i]`` is overwritten by the Cholesky factor ``U``\ :sub:`i`
         or ``L``\ :sub:`i`, as specified by ``uplo[i]`` .


      info
         Vector of buffers containing error information.


         If ``info[i]=0``, the execution is successful.


         If ``info[i]=k``, the leading minor of order ``k`` (and
         therefore the matrix ``A``\ :sub:`i` itself) is not
         positive-definite, and the factorization could not be
         completed. This may indicate an error in forming the matrix
         ``A``\ :sub:`i`.


         If ``info[i]=-k``, the ``k``-th parameter had an illegal value.


   .. container:: section
      :name: GUID-C97BF68F-B566-4164-95E0-A7ADC290DDE2


      .. rubric:: Example
         :class: sectiontitle


      An example of how to use potrf_batch can be found in the oneMKL
      installation directory, under:


      ::


         examples/sycl/lapack/CHOLESKY_batch.cpp


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** `LAPACK
      Routines <lapack.html>`__


