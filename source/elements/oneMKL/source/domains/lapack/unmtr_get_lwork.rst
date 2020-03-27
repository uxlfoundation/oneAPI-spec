.. _unmtr_get_lwork:

unmtr_get_lwork
===============


.. container::


   Computes the worksize needed for the function
   `unmtr <unmtr.html>`__. This
   routine belongs to the ``onemkl::lapack``\ namespace.


   .. container:: section
      :name: GUID-814D7756-F1E2-4417-A0EA-B4294B8303D4


      .. rubric:: Syntax
         :class: sectiontitle


      .. container:: dlsyntaxpara


         .. cpp:function::  template <typename fp_complex>void         unmtr_get_lwork(queue &exec_queue, side left_right, uplo         upper_lower, transpose trans, std::int64_t m, std::int64_t n,         std::int64_t lda, std::int64_t ldc, std::int64_t &lwork)

         ``unmtr_get_lwork`` supports the following precisions.


         .. list-table:: 
            :header-rows: 1

            * -  T 
            * -  ``std::complex<float>`` 
            * -  ``std::complex<double>`` 




   .. container:: section
      :name: GUID-A3A0248F-23B3-4E74-BDA2-BB8D23F19A50


      .. rubric:: Description
         :class: sectiontitle


      Computes the worksize needed for multiplying a complex matrix by
      the unitary matrix ``Q`` determined by
      `hetrd <hetrd.html>`__. Calls
      to this routine must specify the template parameter explicitly.


   .. container:: section
      :name: GUID-F841BA63-D4EE-4C75-9831-BB804CEA8622


      .. rubric:: Input Parameters
         :class: sectiontitle


      exec_queue
         The queue where the routine should be executed.


      left_right
         Must be either ``side::left`` or ``side::right``.


         If ``left_right=side::left``, ``Q`` or ``Q``\ :sup:`H` is
         applied to ``C`` from the left.


         If ``left_right=side::right``, ``Q`` or ``Q``\ :sup:`H` is
         applied to ``C`` from the right.


      upper_lower
         Must be either ``uplo::upper`` or ``uplo::lower``. Uses the
         same upper_lower as supplied to
         `hetrd <hetrd.html>`__.


      trans
         Must be either ``transpose::nontrans`` or
         ``transpose::conjtrans``.


         If ``trans=transpose::nontrans``, the routine multiplies ``C``
         by ``Q``.


         If ``trans=transpose::conjtrans``, the routine multiplies ``C``
         by ``Q``\ :sup:`H`.


      m
         The number of rows in the matrix ``C`` (``m≥0``).


      n
         The number of columns the matrix ``C`` (``n≥0``).


      k
         The number of elementary reflectors whose product defines the
         matrix ``Q`` (``0≤k≤n``).


      lda
         The leading dimension of a\ ``(max(1,r)≤lda)``.


      ldc
         The leading dimension of c\ ``(max(1,n)≤ldc)``.


   .. container:: section
      :name: GUID-F0C3D97D-E883-4070-A1C2-4FE43CC37D12


      .. rubric:: Output Parameters
         :class: sectiontitle


      lwork
         The integer lwork contains the size of the buffer needed for
         computations in
         `unmtr <unmtr.html>`__.


   .. container:: section
      :name: GUID-C97BF68F-B566-4164-95E0-A7ADC290DDE2


      .. rubric:: Example
         :class: sectiontitle


      An example of how to use ``unmtr_get_lwork``\ can be found in the
      oneMKL installation directory, under:


      ::


         examples/sycl/lapack/ormtr.cpp


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** `LAPACK
      Routines <lapack.html>`__


