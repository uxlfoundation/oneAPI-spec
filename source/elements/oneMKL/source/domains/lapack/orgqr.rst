.. _orgqr:

orgqr
=====


.. container::


   Generates the real orthogonal matrix Q of the QR factorization formed
   by geqrf. This routine belongs to the ``onemkl::lapack``\ namespace.


   .. container:: section
      :name: GUID-3F04D25E-F895-49D5-85AA-C299292217FD


      .. rubric:: Syntax
         :class: sectiontitle


      .. cpp:function::  void orgqr(queue &exec_queue, std::int64_t m,      std::int64_t n, std::int64_t k, buffer<T,1> &a, std::int64_t lda,      buffer<T,1> &tau, buffer<T,1> &work, std::int64_t &lwork,      buffer<std::int64_t,1> &info)

      ``orgqr`` supports the following precisions.


      .. list-table:: 
         :header-rows: 1

         * -  T 
         * -  ``float`` 
         * -  ``double`` 




.. container:: section
   :name: GUID-90DD94AE-0D40-4207-B84D-D6B6A24D209A


   .. rubric:: Description
      :class: sectiontitle


   The routine generates the whole or part of ``m``-by-``m`` orthogonal
   matrix ``Q`` of the ``QR`` factorization formed by the routine
   `?geqrf <geqrf.html>`__.


   Usually ``Q`` is determined from the ``QR`` factorization of an ``m``
   by ``p`` matrix ``A`` with ``m≥p``. To compute the whole matrix
   ``Q``, use:


   ::


      onemkl::orgqr(queue, m, m, p, a, lda, tau, work, lwork, info)


   To compute the leading ``p`` columns of ``Q`` (which form an
   orthonormal basis in the space spanned by the columns of ``A``):


   ::


      onemkl::orgqr(queue, m, p, p, a, lda, tau, work, lwork, info)


   To compute the matrix ``Q``\ :sup:`k` of the ``QR`` factorization of
   leading ``k`` columns of the matrix ``A``:


   ::


      onemkl::orgqr(queue, m, m, k, a, lda, tau, work, lwork, info)


   To compute the leading ``k`` columns of ``Q``\ :sup:`k` (which form
   an orthonormal basis in the space spanned by leading ``k`` columns of
   the matrix ``A``):


   ::


      onemkl::orgqr(queue, m, k, k, a, lda, tau, work, lwork, info)


.. container:: section
   :name: GUID-F841BA63-D4EE-4C75-9831-BB804CEA8622


   .. rubric:: Input Parameters
      :class: sectiontitle


   exec_queue
      The queue where the routine should be executed.


   m
      The number of rows in the matrix ``A`` (``0≤m``).


   n
      The number of columns in the matrix ``A`` (``0≤n``).


   k
      The number of elementary reflectors whose product defines the
      matrix ``Q`` (``0≤k≤n``).


   a
      The buffer a returned by
      `geqrf <geqrf.html>`__.


   lda
      The leading dimension of a (``lda≤m``).


   tau
      The buffer returned by
      `geqrf <geqrf.html>`__.


   lwork
      The size of the work array (``lwork≥n``). Must be computed by
      orgqr_get_lwork.


.. container:: section
   :name: GUID-F0C3D97D-E883-4070-A1C2-4FE43CC37D12


   .. rubric:: Output Parameters
      :class: sectiontitle


   a
      Overwritten by n leading columns of the m-by-m orthogonal matrix
      ``Q``.


   work
      Workspace for internal computations.


   info
      Buffer containing error information.


      If ``info=0``, the execution is successful.


      If ``info=-i``, the ``i``-th parameter had an illegal value.


.. container:: section
   :name: GUID-C97BF68F-B566-4164-95E0-A7ADC290DDE2


   .. rubric:: Example
      :class: sectiontitle


   An example of how to use ``orgqr``\ should be found in the oneMKL
   installation directory, under:


   ::


      examples/sycl/lapack/orgqr.cpp


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** `LAPACK
      Routines <lapack.html>`__


