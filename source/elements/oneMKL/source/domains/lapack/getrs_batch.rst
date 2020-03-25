.. _getrs_batch:

getrs_batch
===========


.. container::


   Solves a system of linear equations with a batch of LU-factored
   square coefficient matrices, with multiple right-hand sides. This
   routine belongs to the ``onemkl::lapack``\ namespace.


   .. container:: section
      :name: GUID-814D7756-F1E2-4417-A0EA-B4294B8303D4


      .. rubric:: Syntax
         :name: syntax
         :class: sectiontitle


      .. container:: dlsyntaxpara


         .. cpp:function::  void getrs_batch(queue &exec_queue,         std::vector< onemkl::transpose > const& trans,         std::vector<std::int64_t> const& n, std::vector<std::int64_t>         const& nrhs, std::vector< buffer<T,1> > & a, std::vector<         std::int64_t > const& lda, std::vector< buffer<std::int64_t,1>         > & ipiv, std::vector< buffer<T,1> > &b, std::vector<         std::int64_t > const& ldb, std::vector< buffer<std::int64_t,1>         > &info)

         ``getrs_batch`` supports the following precisions.


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
         :name: description
         :class: sectiontitle


      The routine solves for ``X``\ :sub:`i` the following systems of
      linear equations for a batch of general square matrices
      ``A``\ :sub:`1`, ``A``\ :sub:`2`, …,
      ``A``\ :sub:`````\ batch_size`:


      ``A``\ :sub:`i` \* ``X``\ :sub:`i` = ``B``\ :sub:`i` If
      ``trans[i] = onemkl::transpose::notrans``


      ``A``\ :sub:`i`\ :sup:`T` \* ``X``\ :sub:`i` = ``B``\ :sub:`i` If
      ``trans[i] = onemkl::transpose::trans``


      ``A``\ :sub:`i`\ :sup:`H` \* ``X``\ :sub:`i` = ``B``\ :sub:`i` If
      ``trans[i] = onemkl::transpose::conjtrans``


      Before calling this routine you must call
      `getrf_batch <getrf_batch.html>`__
      to compute the LU factorization of ``A``\ :sub:`1`,
      ``A``\ :sub:`2`, …, ``A``\ :sub:`````\ batch_size`.


   .. container:: section
      :name: GUID-F841BA63-D4EE-4C75-9831-BB804CEA8622


      .. rubric:: Input Parameters
         :name: input-parameters
         :class: sectiontitle


      exec_queue
         The queue where the routine should be executed.


      trans
         A vector, ``trans[i]`` indicates the form of the linear
         equations.


      n
         A vector, ``n[i]`` is the number of columns of the batch matrix
         ``A``\ :sub:`i`\ ``(0≤n[i])``.


      nrhs
         A vector, the number of right hand sides ``(0≤nrhs[i])``.


      a
         A vector of buffers returned by
         `getrf_batch <getrf_batch.html>`__.
         ``a[i]`` must be of size at least ``lda[i]*max(1, n[i])``.


      lda
         A vector, ``lda[i]`` is the leading dimension of
         ``a[i] (n[i]≤lda[i])``.


      ipiv
         A vector of buffers, ipiv is the batch of pivots returned by
         `getrf_batch <getrf_batch.html>`__.


      b
         A vector of buffers, ``b[i]`` contains the matrix
         ``B``\ :sub:`i` whose columns are the right-hand sides for the
         systems of equations. The second dimension of ``b``\ :sub:`i`
         must be at least ``max(1,nrhs[i])``.


      ldb
         A vector, ``ldb[i]`` is the leading dimension of ``b[i]``.


   .. container:: section
      :name: GUID-F0C3D97D-E883-4070-A1C2-4FE43CC37D12


      .. rubric:: Output Parameters
         :name: output-parameters
         :class: sectiontitle


      b
         A vector of buffers, ``b[i]`` is overwritten by the solution
         matrix ``X``\ :sub:`i`.


      info
         Vector of buffers containing error information.


         If ``info[i]=0``, the execution is successful.


         If ``info[i]=k``, the ``k``-th diagonal element of ``U`` is
         zero, and the solve could not be completed.


         If ``info[i]=-k``, the ``k``-th parameter had an illegal value.


   .. container:: section
      :name: GUID-C97BF68F-B566-4164-95E0-A7ADC290DDE2


      .. rubric:: Example
         :name: example
         :class: sectiontitle


      An example of how to use getrs_batchcan be found in the oneMKL
      installation directory, under:


      ::


         examples/sycl/lapack/LU_batch.cpp


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** `LAPACK
      Routines <lapack.html>`__


.. container::

