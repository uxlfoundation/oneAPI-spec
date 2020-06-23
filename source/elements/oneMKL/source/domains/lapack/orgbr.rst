.. _onemkl_lapack_orgbr:

orgbr
=====


.. container::


   Generates the real orthogonal matrix ``Q`` or ``P``\ :sup:`T`
   determined by
   :ref:`onemkl_lapack_gebrd`.


      ``orgbr`` supports the following precisions.


      .. list-table:: 
         :header-rows: 1

         * -  T 
         * -  ``float`` 
         * -  ``double`` 




.. container:: section


   .. rubric:: Description
      :class: sectiontitle


   The routine generates the whole or part of the orthogonal matrices
   ``Q`` and ``P``\ :sup:`T` formed by the routines
   :ref:`onemkl_lapack_gebrd`.
   All valid combinations of arguments are described in *Input parameters*. In
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


orgbr (BUFFER Version)
----------------------

.. container::

   .. container:: section


      .. rubric:: Syntax
         :class: sectiontitle


      .. cpp:function::  void onemkl::lapack::orgbr(cl::sycl::queue &queue, onemkl::generate gen,      std::int64_t m, std::int64_t n, std::int64_t k, cl::sycl::buffer<T,1> &a,      std::int64_t lda, cl::sycl::buffer<T,1> &tau, cl::sycl::buffer<T,1> &scratchpad,      std::int64_t scratchpad_size)

.. container:: section


   .. rubric:: Input Parameters
      :class: sectiontitle


   queue
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
      :ref:`onemkl_lapack_gebrd`.


      If gen\ ``= generate::p``, the number of rows in the original
      ``k``-by-n matrix reduced by
      :ref:`onemkl_lapack_gebrd`.


   a
      The buffer ``a`` as returned by
      :ref:`onemkl_lapack_gebrd`.


   lda
      The leading dimension of a.


   tau
      Buffer, size ``min (m,k)`` if gen\ ``= generate::q``, size
      ``min(n,k)`` if gen\ ``= generate::p``. Scalar factor of the
      elementary reflectors, as returned by :ref:`onemkl_lapack_gebrd` in the array tauq
      or taup.


   scratchpad_size
      Size of scratchpad memory as a number of floating point elements of type T.
      Size should not be less than the value returned by :ref:`onemkl_lapack_orgbr_scratchpad_size` function.


.. container:: section


   .. rubric:: Output Parameters
      :class: sectiontitle


   a
      Overwritten by n leading columns of the m-by-m orthogonal matrix
      ``Q`` or ``P``\ :sup:`T` (or the leading rows or columns thereof)
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


orgbr (USM Version)
----------------------

.. container::

   .. container:: section


      .. rubric:: Syntax
         :class: sectiontitle


      .. cpp:function::  cl::sycl::event onemkl::lapack::orgbr(cl::sycl::queue &queue, onemkl::generate gen,      std::int64_t m, std::int64_t n, std::int64_t k, T *a,      std::int64_t lda, T *tau, T *scratchpad,      std::int64_t scratchpad_size, const cl::sycl::vector_class<cl::sycl::event> &events = {})

.. container:: section


   .. rubric:: Input Parameters
      :class: sectiontitle


   queue
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
      :ref:`onemkl_lapack_gebrd`.


      If gen\ ``= generate::p``, the number of rows in the original
      ``k``-by-n matrix reduced by
      :ref:`onemkl_lapack_gebrd`.


   a
      Pointer to array ``a`` as returned by
      :ref:`onemkl_lapack_gebrd`.


   lda
      The leading dimension of a.


   tau
      Pointer to array of size ``min (m,k)`` if gen\ ``= generate::q``, size
      ``min(n,k)`` if gen\ ``= generate::p``. Scalar factor of the
      elementary reflectors, as returned by :ref:`onemkl_lapack_gebrd` in the array tauq
      or taup.


   scratchpad_size
      Size of scratchpad memory as a number of floating point elements of type T.
      Size should not be less than the value returned by :ref:`onemkl_lapack_orgbr_scratchpad_size` function.

   events
      List of events to wait for before starting computation. Defaults to empty list.


.. container:: section


   .. rubric:: Output Parameters
      :class: sectiontitle


   a
      Overwritten by n leading columns of the m-by-m orthogonal matrix
      ``Q`` or ``P``\ :sup:`T` (or the leading rows or columns thereof)
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


