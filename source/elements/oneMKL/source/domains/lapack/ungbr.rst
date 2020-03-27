.. _ungbr:

ungbr
=====


.. container::


   Generates the complex unitary matrix Q or P\ :sup:`t` determined by
   `gebrd <gebrd.html>`__. This
   routine belongs to the ``onemkl::lapack``\ namespace.


   .. container:: section
      :name: GUID-758AC930-F817-42F6-9BB8-7CC3E0E016CE


      .. rubric:: Syntax
         :name: syntax
         :class: sectiontitle


      .. cpp:function::  void ungbr(queue &exec_queue, generate gen,      std::int64_t m, std::int64_t n, std::int64_t k, buffer<T,1> &a,      std::int64_t lda, buffer<T,1> &tau, buffer<T,1> &work,      std::int64_t lwork, buffer<std::int64_t,1> &info)

      ``ungbr`` supports the following precisions.


      .. list-table:: 
         :header-rows: 1

         * -  T 
         * -  ``std::complex<float>`` 
         * -  ``std::complex<double>`` 




.. container:: section
   :name: GUID-5132BBC6-DD56-4CC5-B9FE-236BAB6A11C4


   .. rubric:: Description
      :name: description
      :class: sectiontitle


   The routine generates the whole or part of the unitary matrices ``Q``
   and ``P``\ :sup:`H` formed by the routines
   `gebrd <gebrd.html>`__.
   Use this routine after a call to cgebrd/zgebrd. All valid
   combinations of arguments are described in *Input Parameters*; in
   most cases you need the following:


   To compute the whole ``m``-by-``m`` matrix ``Q``, use:


   ::


      ungbr(queue, generate::q, m, m, n, a, …)


   (note that the buffer\ ``a`` must have at least ``m`` columns).


   To form the ``n`` leading columns of ``Q`` if ``m > n``, use:


   ::


      ungbr(queue, generate::q, m, n, n, a, …)


   To compute the whole ``n``-by-``n`` matrix ``P``\ :sup:`T`, use:


   ::


      ungbr(queue, generate::p, n, n, m, a, …)


   (note that the array ``a`` must have at least ``n`` rows).


   To form the ``m`` leading rows of ``P``\ :sup:`T` if ``m < n``, use:


   ::


      ungbr(queue, generate::p, m, n, m, a, …)


.. container:: section
   :name: GUID-26A5866D-0DF8-4835-8776-E5E73F0C657A


   .. rubric:: Input Parameters
      :name: input-parameters
      :class: sectiontitle


   exec_queue
      The queue where the routine should be executed.


   gen
      Must be ``generate::q`` or ``generate::p``.


      If ``gen = generate::q``, the routine generates the matrix ``Q``.


      If ``gen = generate::p``, the routine generates the matrix
      ``P``\ :sup:`T`.


   m
      The number of rows in the matrix ``Q`` or ``P``\ :sup:`T` to be
      returned ``(0 ≤ m)``.


      If ``gen = generate::q``, ``m ≥ n ≥ min(m, k)``.


      If ``gen = generate::p``, ``n ≥ m ≥ min(n, k)``.


   n
      The number of columns in the matrix ``Q`` or ``P``\ :sup:`T` to be
      returned ``(0 ≤ n)``. See m for constraints.


   k
      If ``gen = generate::q``, the number of columns in the original
      ``m``-by-``k`` matrix reduced by
      `gebrd <gebrd.html>`__.


      If ``gen = generate::p``, the number of rows in the original
      ``k``-by-``n`` matrix reduced by
      `gebrd <gebrd.html>`__.


   a
      The buffer a returned by
      `gebrd <gebrd.html>`__.


   lda
      The leading dimension of a.


   tau
      For gen\ ``= generate::q``, the array tauq as returned by gebrd.
      For gen\ ``= generate::p``, the array taup as returned by gebrd.


      The dimension of tau must be at least ``max(1, min(m, k))`` for
      gen\ ``=generate::q``, or ``max(1, min(m, k))`` for
      gen\ ``= generate::p``.


   lwork
      The size of the work array. Must be computed by
      `ungbr_get_lwork <ungbr_get_lwork.html>`__.


.. container:: section
   :name: GUID-399F00E4-1E32-4114-AC10-5A1B420E474E


   .. rubric:: Output Parameters
      :name: output-parameters
      :class: sectiontitle


   a
      Overwritten by n leading columns of the m-by-m unitary matrix
      ``Q`` or ``P``\ :sup:`T`, (or the leading rows or columns thereof)
      as specified by gen, m, and n.


   work
      Workspace for internal computations.


   info
      Buffer containing error information.


      If ``info=0``, the execution is successful.


      If ``info=-i``, the ``i``-th parameter had an illegal value.


.. container:: section
   :name: GUID-C97BF68F-B566-4164-95E0-A7ADC290DDE2


   .. rubric:: Example
      :name: example
      :class: sectiontitle


   An example of how to use ``ungbr``\ can be found in the oneMKL
   installation directory, under:


   ::


      examples/sycl/lapack/orgbr.cpp


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** `LAPACK
      Routines <lapack.html>`__


