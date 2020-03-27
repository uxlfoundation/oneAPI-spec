.. _sytrf_get_lwork:

sytrf_get_lwork
===============


.. container::


   Computes the worksize needed for the function sytrf. This routine
   belongs to the ``onemkl::lapack``\ namespace.


   .. container:: section
      :name: GUID-814D7756-F1E2-4417-A0EA-B4294B8303D4


      .. rubric:: Syntax
         :class: sectiontitle


      .. container:: dlsyntaxpara


         .. cpp:function::  template <typename fp>void         sytrf_get_lwork(queue &exec_queue, uplo upper_lower,         std::int64_t n, std::int64_t lda, std::int64_t &lwork)

         ``sytrf_get_lwork`` supports the following precisions.


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


      Computes the worksize needed for the Bunch-Kaufman factorization
      of a symmetric matrix
      (`sytrf <sytrf.html>`__).
      Calls to this routine must specify the template parameter
      explicitly.


   .. container:: section
      :name: GUID-F841BA63-D4EE-4C75-9831-BB804CEA8622


      .. rubric:: Input Parameters
         :class: sectiontitle


      exec_queue
         The queue where the routine should be executed.


      upper_lower
         Indicates whether the upper or lower triangular part of *A* is
         stored and how *A* is factored:


         If ``upper_lower=uplo::upper``, the buffer ``a`` stores the
         upper triangular part of the matrix ``A``, and ``A`` is
         factored as ``U*D*UT``.


         If ``upper_lower=uplo::lower``, the buffer ``a`` stores the
         lower triangular part of the matrix ``A``, and ``A`` is
         factored as ``L*D*LT``


      n
         The order of the matrix ``A`` (``0≤n``).


      lda
         The leading dimension of a.


   .. container:: section
      :name: GUID-F0C3D97D-E883-4070-A1C2-4FE43CC37D12


      .. rubric:: Output Parameters
         :class: sectiontitle


      lwork
         The integer lwork contains the size of the buffer needed for
         computations in
         `sytrf <sytrf.html>`__.


   .. container:: section
      :name: GUID-C97BF68F-B566-4164-95E0-A7ADC290DDE2


      .. rubric:: Example
         :class: sectiontitle


      An example of how to use ``sytrf_get_lwork``\ can be found in the
      oneMKL installation directory, under:


      ::


         examples/sycl/lapack/sytrf.cpp


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** `LAPACK
      Routines <lapack.html>`__


