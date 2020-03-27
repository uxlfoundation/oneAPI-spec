
orgbr
=====


.. container::


   Generates the real orthogonal matrix ``Q`` or ``P``\ :sup:`T`
   determined by
   `gebrd <gebrd.html>`__. This
   routine belongs to the ``onemkl::lapack``\ namespace.


   .. container:: section
      :name: GUID-8A4CB9DA-644B-400E-91C7-78BBD3E3FDAA


      .. rubric:: Syntax
         :class: sectiontitle


      .. cpp:function::  void orgbr(queue &exec_queue, generate gen,      std::int64_t m, std::int64_t n, std::int64_t k, buffer<T,1> &a,      std::int64_t lda, buffer<T,1> &tau, buffer<T,1> &work,      std::int64_t lwork, buffer<std::int64_t,1> &info)

      ``orgbr`` supports the following precisions.


      .. list-table:: 
         :header-rows: 1

         * -  T 
         * -  ``float`` 
         * -  ``double`` 




.. container:: section
   :name: GUID-D3C6AFAC-CF9D-4ACC-8AE7-4A80C12DC86B


   .. rubric:: Description
      :class: sectiontitle


   The routine generates the whole or part of the orthogonal matrices
   ``Q`` and ``P``\ :sup:`T` formed by the routines
   `gebrd <gebrd.html>`__/.
   Use this routine after a call to sgebrd/dgebrd. All valid
   combinations of arguments are described in *Input parameters*. In
   most cases you need the following:


   To compute the whole ``m``-by-``m`` matrix ``Q``:


   ::


      orgbr(queue, generate::q, m, m, n, a, …)


   (note that the array ``a`` must have at least ``m`` columns).


   To form the ``n`` leading columns of ``Q`` if ``m > n``:


   ::


      orgbr(queue, generate::q, m, n, n, a, …)


   To compute the whole ``n``-by-``n`` matrix ``P``\ :sup:`T`:


   ::


      orgbr(queue, generate::p, n, n, m, a, …)


   (note that the array ``a`` must have at least ``n`` rows).


   To form the ``m`` leading rows of ``P``\ :sup:`T` if ``m < n``:


   ::


      orgbr(queue, generate::p, m, n, m, a, …)


.. container:: section
   :name: GUID-F841BA63-D4EE-4C75-9831-BB804CEA8622


   .. rubric:: Input Parameters
      :class: sectiontitle


   exec_queue
      The queue where the routine should be executed.


   gen
      Must be ``generate::q`` or ``generate::p``.


      If gen\ ``= generate::q``, the routine generates the matrix ``Q``.


      If gen\ ``= generate::p``, the routine generates the matrix
      ``P``\ :sup:`T`.


   m
      The number of rows in the matrix ``Q`` or ``P``\ :sup:`T` to be
      returned ``(0≤m)``.


      If gen\ ``= generate::q``, ``m ≥ n ≥ min(m, k)``.


      If gen\ ``= generate::p``, ``n ≥ m ≥ min(n, k)``.


   n
      The number of rows in the matrix ``Q`` or ``P``\ :sup:`T` to be
      returned ``(0≤n)``. See m for constraints.


   k
      If gen\ ``= generate::q``, the number of columns in the original
      ``m``-by-k matrix reduced by
      `gebrd <gebrd.html>`__.


      If gen\ ``= generate::p``, the number of rows in the original
      ``k``-by-n matrix reduced by
      `gebrd <gebrd.html>`__.


   a
      The buffer a returned by
      `gebrd <gebrd.html>`__.


   lda
      The leading dimension of a.


   tau
      Buffer, size ``min (m,k)`` if gen\ ``= generate::q``, size
      ``min(n,k)`` if gen\ ``= generate::p``. Scalar factor of the
      elementary reflectors, as returned by ``gebrd`` in the array tauq
      or taup.


   lwork
      The size of the work array. Must be computed by
      `orgbr_get_lwork <orgqr_get_lwork.html>`__.


.. container:: section
   :name: GUID-BDC93D26-A415-4030-8222-D0EA7B5FC76B


   .. rubric:: Output Parameters
      :class: sectiontitle


   a
      Overwritten by n leading columns of the m-by-m orthogonal matrix
      ``Q`` or ``P``\ :sup:`T` (or the leading rows or columns thereof)
      as specified by gen, m, and n.


   work
      Workspace for internal computations.


   info
      Buffer containing error information.


      If info\ ``= 0``, the execution is successful.


      If info\ ``= -i``, the ``i``-th parameter had an illegal value.


.. container:: section
   :name: GUID-C97BF68F-B566-4164-95E0-A7ADC290DDE2


   .. rubric:: Example
      :class: sectiontitle


   An example of how to use ``orgbr``\ can be found in the oneMKL
   installation directory, under:


   ::


      examples/sycl/lapack/orgbr.cpp


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** `LAPACK
      Routines <lapack.html>`__


