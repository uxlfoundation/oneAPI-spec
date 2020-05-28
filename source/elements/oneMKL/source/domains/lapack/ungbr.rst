.. _onemkl_lapack_ungbr:

onemkl::lapack::ungbr
=====================


.. container::


   Generates the complex unitary matrix Q or P\ :sup:`t` determined by
   :ref:`onemkl_lapack_gebrd`.


      ``ungbr`` supports the following precisions.


      .. list-table:: 
         :header-rows: 1

         * -  T 
         * -  ``std::complex<float>`` 
         * -  ``std::complex<double>`` 




.. container:: section


   .. rubric:: Description
      :class: sectiontitle


   The routine generates the whole or part of the unitary matrices ``Q``
   and ``P``\ :sup:`H` formed by the routines
   :ref:`onemkl_lapack_gebrd`.
   All valid combinations of arguments are described in *Input Parameters*; in
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


onemkl::lapack::ungbr (BUFFER Version)
--------------------------------------

.. container::

   .. container:: section


      .. rubric:: Syntax
         :class: sectiontitle


      .. cpp:function::  void onemkl::lapack::ungbr(cl::sycl::queue &queue, onemkl::generate gen,      std::int64_t m, std::int64_t n, std::int64_t k, cl::sycl::buffer<T,1> &a,      std::int64_t lda, cl::sycl::buffer<T,1> &tau, cl::sycl::buffer<T,1> &scratchpad,      std::int64_t scratchpad_size)

.. container:: section


   .. rubric:: Input Parameters
      :class: sectiontitle


   queue
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
      ``m``-by-``k`` matrix returned by
      :ref:`onemkl_lapack_gebrd`.


      If ``gen = generate::p``, the number of rows in the original
      ``k``-by-``n`` matrix returned by
      :ref:`onemkl_lapack_gebrd`.


   a
      The buffer ``a`` as returned by
      :ref:`onemkl_lapack_gebrd`.


   lda
      The leading dimension of a.


   tau
      For gen\ ``= generate::q``, the array ``tauq`` as returned by :ref:`onemkl_lapack_gebrd`.
      For gen\ ``= generate::p``, the array ``taup`` as returned by :ref:`onemkl_lapack_gebrd`.


      The dimension of tau must be at least ``max(1, min(m, k))`` for
      gen\ ``=generate::q``, or ``max(1, min(m, k))`` for
      gen\ ``= generate::p``.


   scratchpad_size
      Size of scratchpad memory as a number of floating point elements of type T.
      Size should not be less than the value returned by :ref:`onemkl_lapack_ungbr_scratchpad_size` function.


.. container:: section


   .. rubric:: Output Parameters
      :class: sectiontitle


   a
      Overwritten by n leading columns of the m-by-m unitary matrix
      ``Q`` or ``P``\ :sup:`T`, (or the leading rows or columns thereof)
      as specified by gen, m, and n.


   scratchpad
      Buffer holding scratchpad memory to be used by routine for storing intermediate results.


   .. container:: section


      .. rubric:: Throws
         :class: sectiontitle


      onemkl::lapack::exception
         Exception is thrown in case of problems happened during calculations. The ``info`` code of the problem can be obtained by `get_info()` method of exception object:

         If ``info=-i``, the ``i``-th parameter had an illegal value.

         If ``info`` equals to value passed as scratchpad size, and ``get_detail()`` returns non zero, then passed scratchpad is of insufficient size, and required size should not be less than value return by ``get_detail()`` method of exception object.


onemkl::lapack::ungbr (USM Version)
--------------------------------------

.. container::

   .. container:: section


      .. rubric:: Syntax
         :class: sectiontitle


      .. cpp:function::  cl::sycl::event onemkl::lapack::ungbr(cl::sycl::queue &queue, onemkl::generate gen,      std::int64_t m, std::int64_t n, std::int64_t k, T *a, std::int64_t lda, T *tau, T *scratchpad, std::int64_t scratchpad_size, const cl::sycl::vector_class<cl::sycl::event> &events = {})

.. container:: section


   .. rubric:: Input Parameters
      :class: sectiontitle


   queue
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
      ``m``-by-``k`` matrix returned by
      :ref:`onemkl_lapack_gebrd`.


      If ``gen = generate::p``, the number of rows in the original
      ``k``-by-``n`` matrix returned by
      :ref:`onemkl_lapack_gebrd`.


   a
      The pointer to ``a`` as returned by
      :ref:`onemkl_lapack_gebrd`.


   lda
      The leading dimension of a.


   tau
      For gen\ ``= generate::q``, the array ``tauq`` as returned by :ref:`onemkl_lapack_gebrd`.
      For gen\ ``= generate::p``, the array ``taup`` as returned by :ref:`onemkl_lapack_gebrd`.


      The dimension of tau must be at least ``max(1, min(m, k))`` for
      gen\ ``=generate::q``, or ``max(1, min(m, k))`` for
      gen\ ``= generate::p``.


   scratchpad_size
      Size of scratchpad memory as a number of floating point elements of type T.
      Size should not be less than the value returned by :ref:`onemkl_lapack_ungbr_scratchpad_size` function.

   events
      List of events to wait for before starting computation. Defaults to empty list.


.. container:: section


   .. rubric:: Output Parameters
      :class: sectiontitle


   a
      Overwritten by n leading columns of the m-by-m unitary matrix
      ``Q`` or ``P``\ :sup:`T`, (or the leading rows or columns thereof)
      as specified by gen, m, and n.


   scratchpad
      Pointer to scratchpad memory to be used by routine for storing intermediate results.


   .. container:: section


      .. rubric:: Throws
         :class: sectiontitle


      onemkl::lapack::exception
         Exception is thrown in case of problems happened during calculations. The ``info`` code of the problem can be obtained by `get_info()` method of exception object:

         If ``info=-i``, the ``i``-th parameter had an illegal value.

         If ``info`` equals to value passed as scratchpad size, and ``get_detail()`` returns non zero, then passed scratchpad is of insufficient size, and required size should not be less than value return by ``get_detail()`` method of exception object.


   .. container:: section


      .. rubric:: Return Values
         :class: sectiontitle


      Output event to wait on to ensure computation is complete.


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** :ref:`onemkl_lapack-singular-value-eigenvalue-routines` 


