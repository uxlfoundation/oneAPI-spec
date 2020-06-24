.. _onemkl_lapack_getri:

getri
=====


.. container::


   Computes the inverse of an LU-factored general matrix determined by
   :ref:`onemkl_lapack_getrf`.


      ``getri`` supports the following precisions.


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


   The routine computes the inverse ``inv(A)`` of a general matrix
   ``A``. Before calling this routine, call
   :ref:`onemkl_lapack_getrf`
   to factorize ``A``.


getri (BUFFER Version)
----------------------

.. container::

   .. container:: section


      .. rubric:: Syntax
         :class: sectiontitle


      .. cpp:function::  void onemkl::lapack::getri(cl::sycl::queue &queue,      std::int64_t n, cl::sycl::buffer<T,1> &a, std::int64_t lda,      cl::sycl::buffer<std::int64_t,1> &ipiv, cl::sycl::buffer<T,1> &scratchpad, std::int64_t      scratchpad_size)

.. container:: section


   .. rubric:: Input Parameters
      :class: sectiontitle


   queue
      The queue where the routine should be executed.


   n
      The order of the matrix ``A``\ ``(0≤n)``.


   a
      The buffer ``a`` as returned by
      :ref:`onemkl_lapack_getrf`. Must
      be of size at least ``lda*max(1,n)``.


   lda
      The leading dimension of a\ ``(n≤lda)``.


   ipiv
      The buffer as returned by
      :ref:`onemkl_lapack_getrf`. The
      dimension of ipiv must be at least ``max(1, n)``.


   scratchpad_size
      Size of scratchpad memory as a number of floating point elements of type T.
      Size should not be less than the value returned by :ref:`onemkl_lapack_getri_scratchpad_size` function.


.. container:: section


   .. rubric:: Output Parameters
      :class: sectiontitle


   a
      Overwritten by the n-by-n matrix ``A``.


   scratchpad
      Buffer holding scratchpad memory to be used by routine for storing intermediate results.


   .. container:: section


      .. rubric:: Throws
         :class: sectiontitle


      onemkl::lapack::exception
         Exception is thrown in case of problems happened during calculations. The ``info`` code of the problem can be obtained by `get_info()` method of exception object:

         If ``info=-i``, the ``i``-th parameter had an illegal value.

         If ``info`` equals to value passed as scratchpad size, and ``get_detail()`` returns non zero, then passed scratchpad is of insufficient size, and required size should not be less than value return by ``get_detail()`` method of exception object.


getri (USM Version)
----------------------

.. container::

   .. container:: section


      .. rubric:: Syntax
         :class: sectiontitle


      .. cpp:function::  cl::sycl::event onemkl::lapack::getri(cl::sycl::queue &queue,      std::int64_t n, T *a, std::int64_t lda, std::int64_t *ipiv, T *scratchpad, std::int64_t      scratchpad_size, const cl::sycl::vector_class<cl::sycl::event> &events = {})

.. container:: section


   .. rubric:: Input Parameters
      :class: sectiontitle


   queue
      The queue where the routine should be executed.


   n
      The order of the matrix ``A``\ ``(0≤n)``.


   a
      The array as returned by
      :ref:`onemkl_lapack_getrf`. Must
      be of size at least ``lda*max(1,n)``.


   lda
      The leading dimension of a\ ``(n≤lda)``.


   ipiv
      The array as returned by
      :ref:`onemkl_lapack_getrf`. The
      dimension of ipiv must be at least ``max(1, n)``.


   scratchpad_size
      Size of scratchpad memory as a number of floating point elements of type T.
      Size should not be less than the value returned by :ref:`onemkl_lapack_getri_scratchpad_size` function.

   events
      List of events to wait for before starting computation. Defaults to empty list.


.. container:: section


   .. rubric:: Output Parameters
      :class: sectiontitle


   a
      Overwritten by the n-by-n matrix ``A``.


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


      **Parent topic:** :ref:`onemkl_lapack-linear-equation-routines` 


