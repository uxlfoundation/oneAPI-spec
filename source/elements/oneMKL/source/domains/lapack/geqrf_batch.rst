.. _onemkl_lapack_geqrf_batch:

onemkl::lapack::geqrf_batch
===========================


.. container::


   Computes the QR factorizations of a batch of general matrices.


         ``geqrf_batch`` supports the following precisions.


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


      The routine forms the QR factorizations of a batch of general
      matrices ``A``\ :sub:`1`, ``A``\ :sub:`2`, …,
      ``A``\ :sub:`batch_size`. No pivoting is performed.


      The routine does not form the matrices ``Q``\ :sub:`i` explicitly.
      Instead, ``Q``\ :sub:`i` is represented as a product of
      ``min(mi, ni)`` elementary reflectors. Routines are provided to
      work with ``Q``\ :sub:`i` in this representation.


onemkl::lapack::geqrf_batch (BUFFER Version)
--------------------------------------------

.. container::

   .. container:: section


      .. rubric:: Syntax
         :class: sectiontitle


      .. container:: dlsyntaxpara


         .. cpp:function::  void onemkl::lapack::geqrf_batch(cl::sycl::queue &queue,         std::vector<std::int64_t> const& m, std::vector<std::int64_t>         const& n, std::vector<cl::sycl::buffer<T,1>> &a,         std::vector<std::int64_t> const& lda, std::vector<cl::sycl::buffer<T,1>>         & tau, std::vector<cl::sycl::buffer<std::int64_t,1>> &info)


   .. container:: section


      .. rubric:: Input Parameters
         :class: sectiontitle


      queue
         The queue where the routine should be executed.


      m
         A vector, ``m[i]`` is the number of rows of the batch matrix
         ``A``\ :sub:`i`\ ``(0≤m[i])``.


      n
         A vector, ``n[i]`` is the number of columns of the batch matrix
         ``A``\ :sub:`i`\ ``(0≤n[i])``.


      a
         A vector of buffers, ``a[i]`` stores the matrix
         ``A``\ :sub:`i`. ``a[i]`` must be of size at least
         ``lda[i]*max(1, n[i])``.


      lda
         A vector, ``lda[i]`` is the leading dimension of
         ``a[i] (m[i]≤lda[i])``.


   .. container:: section


      .. rubric:: Output Parameters
         :class: sectiontitle


      a
         Overwritten by the factorization data as follows:


         The elements on and above the diagonal of the buffer ``a[i]``
         contain the ``min(m[i],n[i])``-by-``n[i]`` upper trapezoidal
         matrix ``R``\ :sub:`i` (``R``\ :sub:`i` is upper triangular if
         ``m[i]≥n[i]``); the elements below the diagonal, with the array
         ``tau[i]``, present the orthogonal matrix ``Q``\ :sub:`i` as a
         product of ``min(m[i],n[i])`` elementary reflectors.


      tau
         Vector of buffers, where ``tau[i]`` must have size at least
         ``max(1,min(m[i], n[i]))``. Contains scalars that define
         elementary reflectors for the matrix ``Q``\ :sub:`i` in its
         decomposition in a product of elementary reflectors.


      info
         Vector of buffers containing error information.


         If ``info[i]=0``, the execution is successful.


         If ``info[i]=-k``, the ``k``-th parameter had an illegal value.


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** :ref:`onemkl_lapack-like-extensions-routines` 


