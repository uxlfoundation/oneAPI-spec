
getri
=====


.. container::


   Computes the inverse of an LU-factored general matrix determined by
   `getrf <getrf.html>`__.This
   routine belongs to the ``onemkl::lapack``\ namespace.


   .. container:: section
      :name: GUID-4E4EBE80-34FC-4800-A5DC-CE70693B32F9


      .. rubric:: Syntax
         :class: sectiontitle


      .. cpp:function::  void getri_get_lwork(queue &exec_queue,      std::int64_t n, buffer<T,1> &a, std::int64_t lda,      buffer<std::int64_t,1> &ipiv, buffer<T,1> &work, std::int64_t      lwork, buffer<std::int64_t,1> &info)

      ``getri`` supports the following precisions.


      .. list-table:: 
         :header-rows: 1

         * -  T 
         * -  ``float`` 
         * -  ``double`` 
         * -  ``std::complex<float>`` 
         * -  ``std::complex<double>`` 




.. container:: section
   :name: GUID-7DD2B57C-5331-47B0-9C18-7BF816B60676


   .. rubric:: Description
      :class: sectiontitle


   The routine computes the inverse ``inv(A)`` of a general matrix
   ``A``. Before calling this routine, call
   `?getrf <getrf.html>`__
   to factorize ``A``.


.. container:: section
   :name: GUID-26A5866D-0DF8-4835-8776-E5E73F0C657A


   .. rubric:: Input Parameters
      :class: sectiontitle


   exec_queue
      The queue where the routine should be executed.


   n
      The order of the matrix ``A``\ ``(0≤n)``.


   a
      The buffer a returned by
      `getrf <getrf.html>`__. Must
      be of size at least ``lda*max(1,n)``.


   lda
      The leading dimension of a\ ``(n≤lda)``.


   ipiv
      The buffer as returned by
      `getrf <getrf.html>`__ . The
      dimension of ipiv must be at least ``max(1, n)``.


   lwork
      The size of the work array ``(lwork≥n)``. Should be computed by
      `getri_get_lwork <getri_get_lwork.html>`__.


.. container:: section
   :name: GUID-399F00E4-1E32-4114-AC10-5A1B420E474E


   .. rubric:: Output Parameters
      :class: sectiontitle


   a
      Overwritten by the n-by-n matrix ``A``.


   work
      Buffer workspace for internal computations.


   info
      Buffer containing error information.


      If ``info=0``, the execution is successful.


      If ``info=-i``, the ``i``-th parameter had an illegal value.


.. container:: section
   :name: GUID-C97BF68F-B566-4164-95E0-A7ADC290DDE2


   .. rubric:: Example
      :class: sectiontitle


   An example of how to use ``getri``\ can be found in the oneMKL
   installation directory, under:


   ::


      examples/sycl/lapack/getri.cpp


.. container:: section
   :name: GUID-3B00B441-C7C0-4D8A-A819-41037F1E5862


   .. rubric:: Known Limitations
      :name: known-limitations
      :class: sectiontitle


   GPU support is for only real precisions.


   For GPU support, errors are reported through the info parameter, but
   computation does not halt for an algorithmic error.


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** `LAPACK
      Routines <lapack.html>`__


