.. _orgqr_batch:

orgqr_batch
===========


.. container::


   Generates the orthogonal/unitary matrix ``Q``\ :sub:`i` of the QR
   factorizations for a group of general matrices. This routine belongs
   to the ``onemkl::lapack``\ namespace.


   .. container:: section
      :name: GUID-814D7756-F1E2-4417-A0EA-B4294B8303D4


      .. rubric:: Syntax
         :class: sectiontitle


      .. container:: dlsyntaxpara


         .. cpp:function::  void orgqr_batch(queue &exec_queue,         std::vector<std::int64_t> const& m, std::vector<std::int64_t>         const& n, std::vector<std::int64_t> const& k, std::vector<         buffer<T,1> > &a, std::vector< std::int64_t > const& lda,         std::vector< buffer<T,1> > & tau, std::vector<         buffer<std::int64_t,1> > &info)

         ``orgqr_batch`` supports the following precisions.


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


      The routine generates the whole or part of the orthogonal/unitary
      matrices ``Q``\ :sub:`1`, ``Q``\ :sub:`2`, …,
      ``Q``\ :sub:`batch_size` of the QR factorizations formed by the
      routine
      `geqrf_batch <geqrf_batch.html>`__.
      Use this routine after a call to
      `geqrf_batch <geqrf_batch.html>`__.


      Usually ``Q``\ :sub:`i` is determined from the QR factorization of
      an ``m``\ :sub:`i`-by-``p``\ :sub:`i` matrix ``A``\ :sub:`i` with
      ``m``\ :sub:`i`\ ≥\ ``p``\ :sub:`i`. To compute the whole matrix
      ``Q``\ :sub:`i`, use:


      .. container:: tablenoborder


         .. list-table:: 
            :header-rows: 1

            * -  ``m[i]`` 
              -  ``m``\ :sub:`i` 
            * -  ``n[i]`` 
              -  ``m``\ :sub:`i` 
            * -  ``k[i]`` 
              -  ``p``\ :sub:`i` 




      To compute the leading pi columns of ``Q``\ :sub:`i` (which form
      an orthonormal basis in the space spanned by the columns of
      ``A``\ :sub:`i`):


      .. container:: tablenoborder


         .. list-table:: 
            :header-rows: 1

            * -  ``m[i]`` 
              -  ``m``\ :sub:`i` 
            * -  ``n[i]`` 
              -  ``p``\ :sub:`i` 
            * -  ``k[i]`` 
              -  ``p``\ :sub:`i` 




      To compute the matrix ``Qk``\ :sub:`i` of the QR factorization of
      the leading ``k``\ :sub:`i` columns of the matrix ``A``\ :sub:`i`:


      .. container:: tablenoborder


         .. list-table:: 
            :header-rows: 1

            * -  ``m[i]`` 
              -  ``m``\ :sub:`i` 
            * -  ``n[i]`` 
              -  ``m``\ :sub:`i` 
            * -  ``k[i]`` 
              -  ``k``\ :sub:`i` 




      To compute the leading ``k``\ :sub:`i` columns of ``Qk``\ :sub:`i`
      (which form an orthonormal basis in the space spanned by the
      leading ``k``\ :sub:`i` columns of the matrix ``A``\ :sub:`i`):


      .. container:: tablenoborder


         .. list-table:: 
            :header-rows: 1

            * -  ``m[i]`` 
              -  ``m``\ :sub:`i` 
            * -  ``n[i]`` 
              -  ``k``\ :sub:`i` 
            * -  ``k[i]`` 
              -  ``k``\ :sub:`i` 




   .. container:: section
      :name: GUID-F841BA63-D4EE-4C75-9831-BB804CEA8622


      .. rubric:: Input Parameters
         :class: sectiontitle


      exec_queue
         The queue where the routine should be executed.


      m
         A vector, ``m[i]`` is the order of the unitary matrix
         ``Q``\ :sub:`i`\ ``(0≤m[i])``.


      n
         A vector, ``n[i]`` is the number of columns of ``Q``\ :sub:`i`
         to be computed ``(0≤n[i]≤m[i])``.


      k
         A vector, ``k[i]`` is the number of elementary reflectors whose
         product defines the matrix ``Q``\ :sub:`i`\ ``(0≤k[i]≤n[i])``.


      a
         A vector of buffers as returned by
         `geqrf_batch <geqrf_batch.html>`__.
         ``a[i]`` must be of size at least ``lda[i]*max(1, n[i])``.


      lda
         A vector, ``lda[i]`` is the leading dimension of
         ``a[i] (m[i]≤lda[i])``.


      tau
         A vector of buffers tau for storing scalars defining elementary
         reflectors, as returned by
         `geqrf_batch <geqrf_batch.html>`__.


   .. container:: section
      :name: GUID-F0C3D97D-E883-4070-A1C2-4FE43CC37D12


      .. rubric:: Output Parameters
         :class: sectiontitle


      a
         ``a[i]`` is overwritten by ``n[i]`` leading columns of the
         ``m[i]``-by-``m[i]`` orthogonal matrix ``Q``\ :sub:`i`.


      info
         Vector of buffers containing error information.


         If ``info[i]=0``, the execution is successful.


         If ``info[i]=-k``, the ``k``-th parameter had an illegal value.


   .. container:: section
      :name: GUID-C97BF68F-B566-4164-95E0-A7ADC290DDE2


      .. rubric:: Example
         :class: sectiontitle


      An example of how to use orgqr_batch can be found in the oneMKL
      installation directory, under:


      ::


         examples/sycl/lapack/QR_batch.cpp


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** `LAPACK
      Routines <lapack.html>`__


