
getrf_batch
===========


.. container::


   Computes the LU factorizations of a batch of general matrices. This
   routine belongs to the ``onemkl::lapack``\ namespace.


   .. container:: section
      :name: GUID-814D7756-F1E2-4417-A0EA-B4294B8303D4


      .. rubric:: Syntax
         :class: sectiontitle


      .. container:: dlsyntaxpara


         .. cpp:function::  void getrf_batch(queue &exec_queue,         std::vector<std::int64_t> const& m, std::vector<std::int64_t>         const& n, std::vector<buffer<T,1>> &a,         std::vector<std::int64_t> const& lda,         std::vector<buffer<std::int64_t,1>> &ipiv,         std::vector<buffer<std::int64_t,1>> &info)

         ``getrf_batch`` supports the following precisions.


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


      The routine computes the LU factorizations of a batch of general
      ``m``-by-``n`` matrices ``A``\ :sub:`1`, ``A``\ :sub:`2`, …,
      ``A``\ :sub:`1batch_size` as


      |image0|


      Where ``P``\ :sub:`i` is a permutation matrix, ``L``\ :sub:`i` is
      lower triangular with unit diagonal elements (lower trapezoidal if
      ``m > n``) and ``U`` is upper triangular (upper trapezoidal if
      ``m < n``). The routine uses partial pivoting with row
      interchanges.


   .. container:: section
      :name: GUID-F841BA63-D4EE-4C75-9831-BB804CEA8622


      .. rubric:: Input Parameters
         :class: sectiontitle


      exec_queue
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
      :name: GUID-F0C3D97D-E883-4070-A1C2-4FE43CC37D12


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


   .. container:: section
      :name: GUID-C97BF68F-B566-4164-95E0-A7ADC290DDE2


      .. rubric:: Example
         :class: sectiontitle


      An example of how to use getrf_batch can be found in the oneMKL
      installation directory, under:


      ::


         examples/sycl/lapack/LU_batch.cpp


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** `LAPACK
      Routines <lapack.html>`__



.. |image0| image:: ../equations/GUID-0F47CAD3-006C-4A78-B229-413313667ee1.png
   :class: img-middle

