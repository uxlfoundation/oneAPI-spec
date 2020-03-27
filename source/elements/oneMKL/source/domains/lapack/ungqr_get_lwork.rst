.. _ungqr_get_lwork:

ungqr_get_lwork
===============


.. container::


   Computes the worksize needed for the function ungqr. This routine
   belongs to the ``onemkl::lapack``\ namespace.


   .. container:: section
      :name: GUID-814D7756-F1E2-4417-A0EA-B4294B8303D4


      .. rubric:: Syntax
         :class: sectiontitle


      .. container:: dlsyntaxpara


         .. cpp:function::  template <typename fp_complex>void         ungqr_get_lwork(queue &exec_queue, std::int64_t m, std::int64_t         n, std::int64_t k, std::int64_t lda, std::int64_t &lwork)

         ``ungqr_get_lwork`` supports the following precisions.


         .. list-table:: 
            :header-rows: 1

            * -  T 
            * -  ``std::complex<float>`` 
            * -  ``std::complex<double>`` 




   .. container:: section
      :name: GUID-A3A0248F-23B3-4E74-BDA2-BB8D23F19A50


      .. rubric:: Description
         :class: sectiontitle


      Computes the worksize needed for generating the complex unitary
      matrix ``Q`` of the QR factorization (ungqr). Calls to this
      routine must specify the template parameter explicitly.


   .. container:: section
      :name: GUID-F841BA63-D4EE-4C75-9831-BB804CEA8622


      .. rubric:: Input Parameters
         :class: sectiontitle


      exec_queue
         The queue where the routine should be executed.


      m
         The number of rows in the matrix ``A`` (``0≤m``).


      n
         The number of columns the matrix ``A`` (``0≤n≤m``).


      k
         The number of elementary reflectors whose product defines the
         matrix ``Q`` (``0≤k≤n``).


      lda
         The leading dimension of a.


   .. container:: section
      :name: GUID-F0C3D97D-E883-4070-A1C2-4FE43CC37D12


      .. rubric:: Output Parameters
         :class: sectiontitle


      lwork
         The integer lwork contains the size of the buffer needed for
         computations in ungqr.


   .. container:: section
      :name: GUID-C97BF68F-B566-4164-95E0-A7ADC290DDE2


      .. rubric:: Example
         :class: sectiontitle


      An example of how to use ``ungqr_get_lwork``\ can be found in the
      oneMKL installation directory, under:


      ::


         examples/sycl/lapack/ungqr.cpp


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** `LAPACK
      Routines <lapack.html>`__


