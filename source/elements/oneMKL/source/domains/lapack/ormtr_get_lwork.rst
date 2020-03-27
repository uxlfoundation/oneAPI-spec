.. _ormtr_get_lwork:

ormtr_get_lwork
===============


.. container::


   Computes the worksize needed for the function,
   `ormtr <ormtr.html>`__. This
   routine belongs to the ``onemkl::lapack``\ namespace.


   .. container:: section
      :name: GUID-9FBC1610-9EB2-4F98-97CF-B74E301DF4AD


      .. rubric:: Syntax
         :class: sectiontitle


      .. container:: dlsyntaxpara


         .. cpp:function::  template <typename fp_real>void         ormtr_get_lwork(queue &exec_queue, side left_right, uplo         upper_lower, transpose trans, std::int64_t m, std::int64_t n,         std::int64_t lda, std::int64_t ldc, std::int64_t &lwork)

         ``ormtr_get_lwork`` supports the following precisions.


         .. list-table:: 
            :header-rows: 1

            * -  T 
            * -  ``float`` 
            * -  ``double`` 




   .. container:: section
      :name: GUID-6E26AE63-E2AA-4D9F-B690-7FA8A0882B6F


      .. rubric:: Description
         :class: sectiontitle


      Computes the size of the worksize needed for multiplying a real
      matrix by the real orthogonal matrix ``Q`` determined by
      (`sytrd <sytrd.html>`__).
      Calls to this routine must specify the template parameter
      explicitly.


   .. container:: section
      :name: GUID-26A5866D-0DF8-4835-8776-E5E73F0C657A


      .. rubric:: Input Parameters
         :class: sectiontitle


      In the descriptions below, ``r`` denotes the order of ``Q``:


      .. container:: tablenoborder


         .. list-table:: 
            :header-rows: 1

            * -  ``r = m`` 
              -  if ``left_right = side::left`` 
            * -  ``r = n`` 
              -  if ``left_right = side::right`` 




      exec_queue
         The queue where the routine should be executed.


      left_right
         Must be either ``side::left`` or ``side::right``.


         If ``left_right = side::left``, ``Q`` or ``Q``\ :sup:`T` is
         applied to ``C`` from the left.


         If ``left_right = side::right``, ``Q`` or ``Q``\ :sup:`T` is
         applied to ``C`` from the right.


      upper_lower
         Must be either ``uplo::upper`` or ``uplo::lower``. Uses the
         same ``upper_lower`` as supplied to
         `sytrd <sytrd.html>`__.


      trans
         Must be either ``transpose::nontrans`` or ``transpose::trans``.


         If ``trans = transpose::nontrans``, the routine multiplies
         ``C`` by ``Q``.


         If ``trans = transpose::trans``, the routine multiplies ``C``
         by ``Q``\ :sup:`T`.


      m
         The number of rows in the matrix ``C``\ ``(m ≥ 0)``.


      n
         The number of rows in the matrix ``C``\ ``(n ≥ 0)``.


      lda
         The leading dimension of a\ ``(max(1, r) ≤ lda)``.


      ldc
         The leading dimension of c\ ``(max(1, n) ≤ ldc)``.


   .. container:: section
      :name: GUID-399F00E4-1E32-4114-AC10-5A1B420E474E


      .. rubric:: Output Parameters
         :class: sectiontitle


      lwork
         The integer lwork contains the size of the buffer needed for
         computations in
         `ormtr <ormtr.html>`__.


   .. container:: section
      :name: GUID-C97BF68F-B566-4164-95E0-A7ADC290DDE2


      .. rubric:: Example
         :class: sectiontitle


      An example of how to use ``ormtr_get_lwork``\ can be found in the
      oneMKL installation directory, under:


      ::


         examples/sycl/lapack/ormtr.cpp


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** `LAPACK
      Routines <lapack.html>`__


