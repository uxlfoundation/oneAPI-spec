.. _getri_batch:

getri_batch
===========


.. container::


   Computes the inverses of a batch of LU-factored matrices determined
   by `getrf_batch <getrf_batch.html>`__.
   This routine belongs to the ``onemkl::lapack``\ namespace.


   .. container:: section
      :name: GUID-814D7756-F1E2-4417-A0EA-B4294B8303D4


      .. rubric:: Syntax
         :name: syntax
         :class: sectiontitle


      .. container:: dlsyntaxpara


         .. cpp:function::  void getri_batch(queue &exec_queue,         std::vector<std::int64_t> const& n, std::vector<buffer<T,1>>         &a, std::vector<std::int64_t> const& lda,         std::vector<buffer<std::int64_t,1>> & ipiv,         std::vector<buffer<std::int64_t,1>> &info)

         ``getri_batch`` supports the following precisions.


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


      The routine computes the inverses ``A``\ :sub:`i`\ :sup:`-1` of a
      batch of general matrices ``A``\ :sub:`i`, ``A``\ :sub:`2`, …,
      ``A``\ :sub:`batch_size` . Before calling this routine, call
      `getrf_batch <getrf_batch.html>`__
      to compute the LU factorization of ``A``\ :sub:`i`,
      ``A``\ :sub:`2`, …, ``A``\ :sub:`batch_size`.


   .. container:: section
      :name: GUID-F841BA63-D4EE-4C75-9831-BB804CEA8622


      .. rubric:: Input Parameters
         :name: input-parameters
         :class: sectiontitle


      exec_queue
         The queue where the routine should be executed.


      n
         A vector, ``n[i]`` is order of the matrix
         ``A``\ :sub:`i`\ ``(0≤n[i])``.


      a
         A vector of buffers returned by
         `getrf_batch <getrf_batch.html>`__.
         ``a[i]`` must be of size at least ``lda[i]*max(1, n[i])``.


      lda
         A vector, ``lda[i]`` is the leading dimension of
         ``a[i] (n[i]≤lda[i])``.


      ipiv
         A vector of buffers returned by
         `getrf_batch <getrf_batch.html>`__
         . The dimension of ``ipiv[i]`` must be at least
         ``max(1, n[i])``.


   .. container:: section
      :name: GUID-F0C3D97D-E883-4070-A1C2-4FE43CC37D12


      .. rubric:: Output Parameters
         :name: output-parameters
         :class: sectiontitle


      a
         ``a[i]`` is overwritten by the ``n[i]``-by-``n[i]`` inverse
         matrix ``A``\ :sub:`i`\ :sup:`-1`.


      info
         Vector of buffers containing error information.


         If ``info[i]=0``, the execution is successful.


         If ``info[i]=-k``, the ``k``-th parameter had an illegal value.


   .. container:: section
      :name: GUID-C97BF68F-B566-4164-95E0-A7ADC290DDE2


      .. rubric:: Example
         :name: example
         :class: sectiontitle


      An example of how to use getri_batchcan be found in the oneMKL
      installation directory, under:


      ::


         examples/sycl/lapack/LU_batch.cpp


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** `LAPACK
      Routines <lapack.html>`__


.. container::

