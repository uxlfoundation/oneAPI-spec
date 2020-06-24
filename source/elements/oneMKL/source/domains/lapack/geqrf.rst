.. _onemkl_lapack_geqrf:

geqrf
=====


.. container::


   Computes the ``QR`` factorization of a general ``m``-by-``n`` matrix.


      ``geqrf`` supports the following precisions:


      .. list-table:: 
         :header-rows: 1

         * -  T 
         * -  ``float`` 
         * -  ``double`` 
         * -  ``std::complex<float>`` 
         * -  ``std::complex<double>`` 




.. container:: section


   .. rubric:: Description
      :class: sectiontitle


   The routine forms the ``QR`` factorization of a general
   ``m``-by-``n`` matrix ``A``. No pivoting is performed.


   The routine does not form the matrix ``Q`` explicitly. Instead, ``Q``
   is represented as a product of ``min(m, n)`` elementary
   reflectors. Routines are provided to work with ``Q`` in this
   representation.


geqrf (BUFFER Version)
----------------------

.. container::

   .. container:: section


      .. rubric:: Syntax
         :class: sectiontitle


      .. cpp:function::  void onemkl::lapack::geqrf(cl::sycl::queue &queue, std::int64_t m, std::int64_t n, cl::sycl::buffer<T,1> &a, std::int64_t lda, cl::sycl::buffer<T,1> &tau, cl::sycl::buffer<T,1> &scratchpad, std::int64_t scratchpad_size)


.. container:: section


   .. rubric:: Input Parameters
      :class: sectiontitle


   queue
      The queue where the routine should be executed.


   m
      The number of rows in the matrix ``A`` (``0≤m``).


   n
      The number of columns in ``A`` (``0≤n``).


   a
      Buffer holding input matrix ``A``. Must have size at least
      ``lda``\ \*\ ``n``.


   lda
      The leading dimension of ``A``; at least ``max(1, m)``.


   scratchpad_size
      Size of scratchpad memory as a number of floating point elements of type T.
      Size should not be less than the value returned by :ref:`onemkl_lapack_geqrf_scratchpad_size` function.


.. container:: section


   .. rubric:: Output Parameters
      :class: sectiontitle


   a
      Output buffer, overwritten by the factorization data as follows:


      The elements on and above the diagonal of the array contain the
      ``min(m,n)``-by-``n`` upper trapezoidal matrix ``R`` (``R`` is upper
      triangular if ``m≥n``); the elements below the diagonal, with the
      array tau, represent the orthogonal matrix ``Q`` as a product of
      ``min(m,n)`` elementary reflectors.


   tau
      Output buffer, size at least ``max(1, min(m, n))``. Contains scalars
      that define elementary reflectors for the matrix ``Q`` in its
      decomposition in a product of elementary reflectors.


   scratchpad
      Buffer holding scratchpad memory to be used by routine for storing intermediate results.


   .. container:: section


      .. rubric:: Throws
         :class: sectiontitle


      onemkl::lapack::exception
         Exception is thrown in case of problems happened during calculations. The ``info`` code of the problem can be obtained by `get_info()` method of exception object:

         If ``info=-i``, the ``i``-th parameter had an illegal value.

         If ``info`` equals to value passed as scratchpad size, and ``get_detail()`` returns non zero, then passed scratchpad is of insufficient size, and required size should not be less than value return by ``get_detail()`` method of exception object.


geqrf (USM Version)
----------------------

.. container::

   .. container:: section


      .. rubric:: Syntax
         :class: sectiontitle


      .. cpp:function:: cl::sycl::event  onemkl::lapack::geqrf(cl::sycl::queue &queue, std::int64_t m, std::int64_t n, T *a, std::int64_t lda, T *tau, T *scratchpad, std::int64_t scratchpad_size, const cl::sycl::vector_class<cl::sycl::event> &events = {})


.. container:: section


   .. rubric:: Input Parameters
      :class: sectiontitle


   queue
      The queue where the routine should be executed.


   m
      The number of rows in the matrix ``A`` (``0≤m``).


   n
      The number of columns in ``A`` (``0≤n``).


   a
      Pointer to memory holding input matrix ``A``. Must have size at least
      ``lda``\ \*\ ``n``.


   lda
      The leading dimension of ``A``; at least ``max(1, m)``.

   scratchpad_size
      Size of scratchpad memory as a number of floating point elements of type T.
      Size should not be less than the value returned by :ref:`onemkl_lapack_geqrf_scratchpad_size` function.

   events
      List of events to wait for before starting computation. Defaults to empty list.


.. container:: section


   .. rubric:: Output Parameters
      :class: sectiontitle


   a
      Overwritten by the factorization data as follows:

      The elements on and above the diagonal of the array contain the
      ``min(m,n)``-by-``n`` upper trapezoidal matrix ``R`` (``R`` is upper
      triangular if ``m≥n``); the elements below the diagonal, with the
      array tau, represent the orthogonal matrix ``Q`` as a product of
      ``min(m,n)`` elementary reflectors.


   tau
      Array, size at least ``max(1, min(m, n))``. Contains scalars
      that define elementary reflectors for the matrix ``Q`` in its
      decomposition in a product of elementary reflectors.


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


      **Parent topic:** :ref:`onemkl_lapack-linear-equation-routines`


