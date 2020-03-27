.. _ungqr:

ungqr
=====


.. container::


   Generates the complex unitary matrix Q of the QR factorization formed
   by geqrf. This routine belongs to the ``onemkl::lapack``\ namespace.


   .. container:: section
      :name: GUID-9FBC1610-9EB2-4F98-97CF-B74E301DF4AD


      .. rubric:: Syntax
         :class: sectiontitle


      .. cpp:function::  void ungqr(queue &exec_queue, std::int64_t m,      std::int64_t n, std::int64_t k, buffer<T,1> &a, std::int64_t lda,      buffer<T,1> &tau, buffer<T,1> &work, std::int64_t lwork,      buffer<std::int64_t,1> &info)

      ``ungqr`` supports the following precisions.


      .. list-table:: 
         :header-rows: 1

         * -  T 
         * -  ``std::complex<float>`` 
         * -  ``std::complex<double>`` 




.. container:: section
   :name: GUID-6E26AE63-E2AA-4D9F-B690-7FA8A0882B6F


   .. rubric:: Description
      :class: sectiontitle


   The routine generates the whole or part of ``m``-by-``m`` unitary
   matrix ``Q`` of the ``QR`` factorization formed by the routines
   `?geqrf <geqrf.html>`__.


   Usually ``Q`` is determined from the ``QR`` factorization of an ``m``
   by ``p`` matrix ``A`` with ``m≥p``. To compute the whole matrix
   ``Q``, use:


   ::


       onemkl::ungqr(queue, m, m, p, a, lda, tau, work, lwork, info)


   To compute the leading ``p`` columns of ``Q`` (which form an
   orthonormal basis in the space spanned by the columns of ``A``):


   ::


       onemkl::ungqr(queue, m, p, p, a, lda, tau, work, lwork, info)


   To compute the matrix ``Q``\ :sup:`k` of the ``QR`` factorization of
   the leading ``k`` columns of the matrix ``A``:


   ::


       onemkl::ungqr(queue, m, m, k, a, lda, tau, work, lwork, info)


   To compute the leading ``k`` columns of ``Q``\ :sup:`k` (which form
   an orthonormal basis in the space spanned by the leading ``k``
   columns of the matrix ``A``):


   ::


       onemkl::ungqr(queue, m, k, k, a, lda, tau, work, lwork, info)


.. container:: section
   :name: GUID-F841BA63-D4EE-4C75-9831-BB804CEA8622


   .. rubric:: Input Parameters
      :class: sectiontitle


   exec_queue
      The queue where the routine should be executed.


   m
      The number of rows in the matrix ``A`` (``m ≤0``).


   n
      The number of columns in the matrix ``A`` (``0≤n``).


   k
      The number of elementary reflectors whose product defines the
      matrix ``Q`` (``0≤k≤n``).


   a
      The buffer a returned by
      `geqrf <geqrf.html>`__.


   lda
      The leading dimension of a (``lda ≤m``).


   tau
      The buffer tau returned by
      `geqrf <geqrf.html>`__.


   lwork
      The size of the work array (``lwork  ≥n``). Must be computed by
      `ungqr_get_lwork <ungqr_get_lwork.html>`__.


.. container:: section
   :name: GUID-F0C3D97D-E883-4070-A1C2-4FE43CC37D12


   .. rubric:: Output Parameters
      :class: sectiontitle


   a
      Overwritten by ``n`` leading columns of the ``m``-by-``m``
      orthogonal matrix ``Q``.


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


   An example of how to use ``ungqr``\ can be found in the oneMKL
   installation directory, under:


   ::


      examples/sycl/lapack/ungqr.cpp


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** `LAPACK
      Routines <lapack.html>`__


