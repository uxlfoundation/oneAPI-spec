.. _onemkl_lapack_getrf_batch:

onemkl::lapack::getrf_batch
===========================


.. container::


   Computes the LU factorizations of a batch of general matrices.


         ``getrf_batch`` supports the following precisions.


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


      The routine computes the LU factorizations of a batch of general
      ``m``-by-``n`` matrices ``A``\ :sub:`1`, ``A``\ :sub:`2`, …,
      ``A``\ :sub:`1batch_size` as


      |image0|


      Where ``P``\ :sub:`i` is a permutation matrix, ``L``\ :sub:`i` is
      lower triangular with unit diagonal elements (lower trapezoidal if
      ``m > n``) and ``U`` is upper triangular (upper trapezoidal if
      ``m < n``). The routine uses partial pivoting with row
      interchanges.


onemkl::lapack::getrf_batch (BUFFER Version)
--------------------------------------------

.. container::

   .. container:: section


      .. rubric:: Syntax
         :class: sectiontitle


      .. container:: dlsyntaxpara


         .. cpp:function::  void onemkl::lapack::getrf_batch(cl::sycl::queue &queue,         std::vector<std::int64_t> const& m, std::vector<std::int64_t>         const& n, std::vector<cl::sycl::buffer<T,1>> &a,         std::vector<std::int64_t> const& lda,         std::vector<cl::sycl::buffer<std::int64_t,1>> &ipiv,         std::vector<cl::sycl::buffer<std::int64_t,1>> &info)

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
         A vector of buffers, ``a[i]`` contains the matrix
         ``A``\ :sub:`i`. ``a[i]`` must be of size at least
         ``lda[i]*max(1, n[i])``.


      lda
         A vector, ``lda[i]`` is the leading dimension of
         ``a[i] (m[i]≤lda[i])``.


   .. container:: section


      .. rubric:: Output Parameters
         :class: sectiontitle


      a
         ``a[i]`` is overwritten by ``L``\ :sub:`i` and ``U``\ :sub:`i`.
         The unit diagonal elements of ``L``\ :sub:`i` are not stored.


      ipiv
         A vector of buffers, ``ipiv[i]`` stores the pivot indices. The
         dimension of ``ipiv[i]`` must be at least ``min(m[i], n[i])``.


      info
         Vector of buffers containing error information.


         If ``info[i]=0``, the execution is successful.


         If ``info[i]=k``, ``Ui(k,k)`` is ``0``. The factorization has
         been completed, but ``U``\ :sub:`i` is exactly singular.
         Division by ``0`` will occur if you use the factor
         ``U``\ :sub:`i` for solving a system of linear equations.


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** :ref:`onemkl_lapack-like-extensions-routines` 



.. |image0| image:: ../equations/GUID-0F47CAD3-006C-4A78-B229-413313667ee1.png
   :class: img-middle

