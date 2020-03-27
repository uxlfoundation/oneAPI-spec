.. _geqrf_batch:

geqrf_batch
===========


.. container::


   Computes the QR factorizations of a batch of general matrices. This
   routine belongs to the ``onemkl::lapack``\ namespace.


   .. container:: section
      :name: GUID-814D7756-F1E2-4417-A0EA-B4294B8303D4


      .. rubric:: Syntax
         :name: syntax
         :class: sectiontitle


      .. container:: dlsyntaxpara


         .. cpp:function::  void geqrf_batch(queue &exec_queue,         std::vector<std::int64_t> const& m, std::vector<std::int64_t>         const& n, std::vector<buffer<T,1>> &a,         std::vector<std::int64_t> const& lda, std::vector<buffer<T,1>>         & tau, std::vector<buffer<std::int64_t,1>> &info)

         ``geqrf_batch`` supports the following precisions.


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


      The routine forms the QR factorizations of a batch of general
      matrices ``A``\ :sub:`1`, ``A``\ :sub:`2`, …,
      ``A``\ :sub:`batch_size`. No pivoting is performed.


      The routine does not form the matrices ``Q``\ :sub:`i` explicitly.
      Instead, ``Q``\ :sub:`i` is represented as a product of
      ``min(mi, ni)`` elementary reflectors. Routines are provided to
      work with ``Q``\ :sub:`i` in this representation.


   .. container:: section
      :name: GUID-F841BA63-D4EE-4C75-9831-BB804CEA8622


      .. rubric:: Input Parameters
         :name: input-parameters
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
         A vector of buffers, ``a[i]`` stores the matrix
         ``A``\ :sub:`i`. ``a[i]`` must be of size at least
         ``lda[i]*max(1, n[i])``.


      lda
         A vector, ``lda[i]`` is the leading dimension of
         ``a[i] (m[i]≤lda[i])``.


   .. container:: section
      :name: GUID-F0C3D97D-E883-4070-A1C2-4FE43CC37D12


      .. rubric:: Output Parameters
         :name: output-parameters
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


   .. container:: section
      :name: GUID-C97BF68F-B566-4164-95E0-A7ADC290DDE2


      .. rubric:: Example
         :name: example
         :class: sectiontitle


      An example of how to use geqrf_batch can be found in the oneMKL
      installation directory, under:


      ::


         examples/sycl/lapack/QR_batch.cpp


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** `LAPACK
      Routines <lapack.html>`__


.. container::

