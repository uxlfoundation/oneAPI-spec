.. _onemkl_lapack_getri_batch:

onemkl::lapack::getri_batch
===========================


.. container::


   Computes the inverses of a batch of LU-factored matrices determined
   by :ref:`onemkl_lapack_getrf_batch`.


         ``getri_batch`` supports the following precisions.


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


      The routine computes the inverses ``A``\ :sub:`i`\ :sup:`-1` of a
      batch of general matrices ``A``\ :sub:`i`, ``A``\ :sub:`2`, …,
      ``A``\ :sub:`batch_size` . Before calling this routine, call
      :ref:`onemkl_lapack_getrf_batch`
      to compute the LU factorization of ``A``\ :sub:`i`,
      ``A``\ :sub:`2`, …, ``A``\ :sub:`batch_size`.

onemkl::lapack::getri_batch (BUFFER Version)
--------------------------------------------

.. container::

   .. container:: section


      .. rubric:: Syntax
         :class: sectiontitle


      .. container:: dlsyntaxpara


         .. cpp:function::  void onemkl::lapack::getri_batch(cl::sycl::queue &queue,         std::vector<std::int64_t> const& n, std::vector<cl::sycl::buffer<T,1>>         &a, std::vector<std::int64_t> const& lda,         std::vector<cl::sycl::buffer<std::int64_t,1>> & ipiv,         std::vector<cl::sycl::buffer<std::int64_t,1>> &info)


   .. container:: section


      .. rubric:: Input Parameters
         :class: sectiontitle


      queue
         The queue where the routine should be executed.


      n
         A vector, ``n[i]`` is order of the matrix
         ``A``\ :sub:`i`\ ``(0≤n[i])``.


      a
         A vector of buffers returned by
         :ref:`onemkl_lapack_getrf_batch`.
         ``a[i]`` must be of size at least ``lda[i]*max(1, n[i])``.


      lda
         A vector, ``lda[i]`` is the leading dimension of
         ``a[i] (n[i]≤lda[i])``.


      ipiv
         A vector of buffers returned by
         :ref:`onemkl_lapack_getrf_batch`.
         . The dimension of ``ipiv[i]`` must be at least
         ``max(1, n[i])``.


   .. container:: section


      .. rubric:: Output Parameters
         :class: sectiontitle


      a
         ``a[i]`` is overwritten by the ``n[i]``-by-``n[i]`` inverse
         matrix ``A``\ :sub:`i`\ :sup:`-1`.


      info
         Vector of buffers containing error information.


         If ``info[i]=0``, the execution is successful.


         If ``info[i]=-k``, the ``k``-th parameter had an illegal value.


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** :ref:`onemkl_lapack-like-extensions-routines` 


