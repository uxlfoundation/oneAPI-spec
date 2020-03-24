.. _orgbr_get_lwork:

orgbr_get_lwork
===============


.. container::


   Computes the worksize needed for the function
   `orgbr <orgbr.html>`__. This
   routine belongs to the ``onemkl::lapack``\ namespace.


   .. container:: section
      :name: GUID-814D7756-F1E2-4417-A0EA-B4294B8303D4


      .. rubric:: Syntax
         :name: syntax
         :class: sectiontitle


      .. container:: dlsyntaxpara


         .. cpp:function::  template <typename fp_real>void         orgbr_get_lwork(queue &exec_queue, generate gen, std::int64_t         m, std::int64_t n, std::int64_t k, std::int64_t lda,         std::int64_t &lwork)

         ``orgbr_get_lwork`` supports the following precisions.


         .. list-table:: 
            :header-rows: 1

            * -  T 
            * -  ``float`` 
            * -  ``double`` 




   .. container:: section
      :name: GUID-A3A0248F-23B3-4E74-BDA2-BB8D23F19A50


      .. rubric:: Description
         :name: description
         :class: sectiontitle


      Computes the worksize needed for generating the real orthogonal
      matrix ``Q`` or ``P``\ :sup:`T` determined by
      `gebrd <gebrd.html>`__. Calls
      to this routine must specify the template parameter explicitly.


   .. container:: section
      :name: GUID-F841BA63-D4EE-4C75-9831-BB804CEA8622


      .. rubric:: Input Parameters
         :name: input-parameters
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
         returned ``(0≤m)``.


         If ``gen = generate::q``, ``m ≥ n ≥ min(m, k)``.


         If ``gen = generate::p``, ``n ≥ m ≥ min(n, k)``.


      n
         The number of rows in the matrix ``Q`` or ``P``\ :sup:`T` to be
         returned ``(0≤n)``. See ``m`` for constraints.


      k
         If ``gen = generate::q``, the number of columns in the original
         ``m``-by-``k`` matrix reduced by
         `gebrd <gebrd.html>`__.


         If ``gen = generate::p``, the number of rows in the original
         ``k``-by-``n`` matrix reduced by
         `gebrd <gebrd.html>`__.


      lda
         The leading dimension of a.


   .. container:: section
      :name: GUID-F0C3D97D-E883-4070-A1C2-4FE43CC37D12


      .. rubric:: Output Parameters
         :name: output-parameters
         :class: sectiontitle


      lwork
         The integer lwork contains the size of the buffer needed for
         computations in
         `orgbr <orgbr.html>`__.


   .. container:: section
      :name: GUID-C97BF68F-B566-4164-95E0-A7ADC290DDE2


      .. rubric:: Example
         :name: example
         :class: sectiontitle


      An example of how to use ``orgbr_get_lwork``\ can be found in the
      oneMKL installation directory, under:


      ::


         examples/sycl/lapack/orgbr.cpp


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** `LAPACK
      Routines <lapack.html>`__


.. container::

