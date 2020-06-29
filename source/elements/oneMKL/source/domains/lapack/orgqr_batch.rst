.. _onemkl_lapack_orgqr_batch:

orgqr_batch
===========


.. container::


   Generates the orthogonal/unitary matrix ``Q``\ :sub:`i` of the QR
   factorizations for a group of general matrices.


         ``orgqr_batch`` supports the following precisions.


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


      The routine generates the whole or part of the orthogonal/unitary
      matrices ``Q``\ :sub:`1`, ``Q``\ :sub:`2`, …,
      ``Q``\ :sub:`batch_size` of the QR factorizations formed by the
      routine
      :ref:`onemkl_lapack_geqrf_batch`.
      Use this routine after a call to
      :ref:`onemkl_lapack_geqrf_batch`.


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




orgqr_batch (BUFFER Version)
----------------------------

.. container::

   .. container:: section


      .. rubric:: Syntax
         :class: sectiontitle


      .. container:: dlsyntaxpara


         .. cpp:function::  void onemkl::lapack::orgqr_batch(cl::sycl::queue &queue,         std::vector<std::int64_t> const& m, std::vector<std::int64_t>         const& n, std::vector<std::int64_t> const& k, std::vector<         cl::sycl::buffer<T,1> > &a, std::vector< std::int64_t > const& lda,         std::vector< cl::sycl::buffer<T,1> > & tau, std::vector<         cl::sycl::buffer<std::int64_t,1> > &info)

   .. container:: section


      .. rubric:: Input Parameters
         :class: sectiontitle


      queue
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
         :ref:`onemkl_lapack_geqrf_batch`.
         ``a[i]`` must be of size at least ``lda[i]*max(1, n[i])``.


      lda
         A vector, ``lda[i]`` is the leading dimension of
         ``a[i] (m[i]≤lda[i])``.


      tau
         A vector of buffers tau for storing scalars defining elementary
         reflectors, as returned by
         :ref:`onemkl_lapack_geqrf_batch`.


   .. container:: section


      .. rubric:: Output Parameters
         :class: sectiontitle


      a
         ``a[i]`` is overwritten by ``n[i]`` leading columns of the
         ``m[i]``-by-``m[i]`` orthogonal matrix ``Q``\ :sub:`i`.


      info
         Vector of buffers containing error information.


         If ``info[i]=0``, the execution is successful.


         If ``info[i]=-k``, the ``k``-th parameter had an illegal value.


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** :ref:`onemkl_lapack-like-extensions-routines` 


