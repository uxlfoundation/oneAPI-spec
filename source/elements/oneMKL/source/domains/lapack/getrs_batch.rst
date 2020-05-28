.. _onemkl_lapack_getrs_batch:

onemkl::lapack::getrs_batch
===========================


.. container::


   Solves a system of linear equations with a batch of LU-factored
   square coefficient matrices, with multiple right-hand sides.


         ``getrs_batch`` supports the following precisions.


         .. list-table:: 
            :header-rows: 1

            * -  T 
            * -  ``float`` 
            * -  ``double`` 
            * -  ``std::complex<float>`` 
            * -  ``std::complex<double>`` 




   .. container:: section


      .. rubric:: Description
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
      :ref:`onemkl_lapack_getrf_batch`
      to compute the LU factorization of ``A``\ :sub:`1`,
      ``A``\ :sub:`2`, …, ``A``\ :sub:`````\ batch_size`.


onemkl::lapack::getrs_batch (BUFFER Version)
--------------------------------------------

.. container::

   .. container:: section


      .. rubric:: Syntax
         :class: sectiontitle


      .. container:: dlsyntaxpara


         .. cpp:function::  void onemkl::lapack::getrs_batch(cl::sycl::queue &queue,         std::vector< onemkl::transpose > const& trans,         std::vector<std::int64_t> const& n, std::vector<std::int64_t>         const& nrhs, std::vector< cl::sycl::buffer<T,1> > & a, std::vector<         std::int64_t > const& lda, std::vector< cl::sycl::buffer<std::int64_t,1>         > & ipiv, std::vector< cl::sycl::buffer<T,1> > &b, std::vector<         std::int64_t > const& ldb, std::vector< cl::sycl::buffer<std::int64_t,1>         > &info)

   .. container:: section


      .. rubric:: Input Parameters
         :class: sectiontitle


      queue
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
         :ref:`onemkl_lapack_getrf_batch`.
         ``a[i]`` must be of size at least ``lda[i]*max(1, n[i])``.


      lda
         A vector, ``lda[i]`` is the leading dimension of
         ``a[i] (n[i]≤lda[i])``.


      ipiv
         A vector of buffers, ipiv is the batch of pivots returned by
         :ref:`onemkl_lapack_getrf_batch`.


      b
         A vector of buffers, ``b[i]`` contains the matrix
         ``B``\ :sub:`i` whose columns are the right-hand sides for the
         systems of equations. The second dimension of ``b``\ :sub:`i`
         must be at least ``max(1,nrhs[i])``.


      ldb
         A vector, ``ldb[i]`` is the leading dimension of ``b[i]``.


   .. container:: section


      .. rubric:: Output Parameters
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


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** :ref:`onemkl_lapack-like-extensions-routines` 


