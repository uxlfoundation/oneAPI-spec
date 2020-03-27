
ungbr_get_lwork
===============


.. container::


   Computes the worksize needed for the function,
   `ungbr <ungbr.html>`__. This
   routine belongs to the ``onemkl::lapack``\ namespace.


   .. container:: section
      :name: GUID-9FBC1610-9EB2-4F98-97CF-B74E301DF4AD


      .. rubric:: Syntax
         :class: sectiontitle


      .. container:: dlsyntaxpara


         .. cpp:function::  template <typename fp_complex>void         ungbr_get_lwork(queue &exec_queue, generate gen, std::int64_t         m, std::int64_t n, std::int64_t k, std::int64_t lda,         std::int64_t &lwork)

         ``ungbr_get_lwork`` supports the following precisions.


         .. list-table:: 
            :header-rows: 1

            * -  T 
            * -  ``std::complex<float>`` 
            * -  ``std::complex<double>`` 




   .. container:: section
      :name: GUID-6E26AE63-E2AA-4D9F-B690-7FA8A0882B6F


      .. rubric:: Description
         :class: sectiontitle


      Computes the worksize needed for generating the complex unitary
      matrix ``Q`` or ``P``\ :sup:`T` determined by
      `gebrd <gebrd.html>`__. Calls
      to this routine must specify the template parameter explicitly.


   .. container:: section
      :name: GUID-26A5866D-0DF8-4835-8776-E5E73F0C657A


      .. rubric:: Input Parameters
         :class: sectiontitle


      exec_queue
         The queue where the routine should be executed.


      gen
         Must be ``generate::q`` or ``generate::p``.


         If ``gen = generate::q``, the routine generates the matrix
         ``Q``.


         If ``gen = generate::p``, the routine generates the matrix
         ``P``\ :sup:`T`.


      m
         The number of rows in the matrix ``Q`` or ``P``\ :sup:`T` to be
         returned ``(0 ≤ m)``.


         If ``gen = generate::q``, ``m ≥ n ≥ min(m, k)``.


         If ``gen = generate::p``, ``n ≥ m ≥ min(n, k)``.


      n
         The number of columns in the matrix ``Q`` or ``P``\ :sup:`T` to
         be returned ``(0 ≤ n)``. See m for constraints.


      k
         If ``gen = generate::q``, the number of columns in the original
         m-by-k matrix reduced by
         `gebrd <gebrd.html>`__.


         If ``gen = generate::p``, the number of rows in the original
         k-by-n matrix reduced by
         `gebrd <gebrd.html>`__.


      lda
         The leading dimension of a.


   .. container:: section
      :name: GUID-399F00E4-1E32-4114-AC10-5A1B420E474E


      .. rubric:: Output Parameters
         :class: sectiontitle


      lwork
         The integer ``lwork`` contains the size of the buffer needed
         for computations in
         `ungbr <ungbr.html>`__.


   .. container:: section
      :name: GUID-C97BF68F-B566-4164-95E0-A7ADC290DDE2


      .. rubric:: Example
         :class: sectiontitle


      An example of how to use ``ungbr_get_lwork``\ can be found in the
      oneMKL installation directory, under:


      ::


         examples/sycl/lapack/orgbr.cpp


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** `LAPACK
      Routines <lapack.html>`__


