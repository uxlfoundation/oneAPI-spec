.. _onemkl_lapack_ormqr:

ormqr
=====

Multiplies a real matrix by the orthogonal matrix :math:`Q` of the QR
factorization formed by :ref:`onemkl_lapack_geqrf`.

.. container:: section

  .. rubric:: Description
      
``ormqr`` supports the following precisions.

    .. list-table:: 
       :header-rows: 1
 
       * -  T 
       * -  ``float`` 
       * -  ``double`` 
       * -  ``std::complex<float>`` 
       * -  ``std::complex<double>`` 

The routine multiplies a real matrix :math:`C` by :math:`Q` or
:math:`Q^{T}`, where :math:`Q` is the orthogonal matrix :math:`Q` of the
QR factorization formed by the routine
:ref:`onemkl_lapack_geqrf`.

Depending on the parameters ``left_right`` and ``trans``, the routine
can form one of the matrix products :math:`QC`, :math:`Q^TC`, :math:`CQ`, or
:math:`CQ^T` (overwriting the result on :math:`C`).

ormqr (Buffer Version)
----------------------

.. container:: section

  .. rubric:: Syntax
         
.. cpp:function::  void oneapi::mkl::lapack::ormqr(cl::sycl::queue &queue, onemkl::side left_right, onemkl::transpose trans, std::int64_t m, std::int64_t n, std::int64_t k, cl::sycl::buffer<T,1> &a, std::int64_t lda, cl::sycl::buffer<T,1> &tau, cl::sycl::buffer<T,1> &c, std::int64_t ldc, cl::sycl::buffer<T,1> &scratchpad, std::int64_t scratchpad_size)

.. container:: section

  .. rubric:: Input Parameters

queue
   The queue where the routine should be executed.

left_right
   If ``left_right=onemkl::side::left``, :math:`Q` or :math:`Q^{T}` is
   applied to :math:`C` from the left.

   If ``left_right=onemkl::side::right``, :math:`Q` or :math:`Q^{T}` is
   applied to :math:`C` from the right.

trans
   If ``trans=onemkl::transpose::trans``, the routine multiplies :math:`C`
   by :math:`Q`.

   If ``trans=onemkl::transpose::nontrans``, the routine multiplies
   :math:`C` by :math:`Q^{T}`.

m
   The number of rows in the matrix :math:`A` (:math:`0 \le m`).

n
   The number of columns in the matrix :math:`A` (:math:`0 \le n \le m`).

k
   The number of elementary reflectors whose product defines the
   matrix :math:`Q` (:math:`0 \le k \le n`).

a
   The buffer ``a`` as returned by :ref:`onemkl_lapack_geqrf`.
   The second dimension of ``a`` must be at least :math:`\max(1,k)`.

lda
   The leading dimension of ``a``.

tau
   The buffer ``tau`` as returned by :ref:`onemkl_lapack_geqrf`.
   The second dimension of ``a`` must be at least :math:`\max(1,k)`.

c
   The buffer ``c`` contains the matrix :math:`C`. The second dimension of ``c``
   must be at least :math:`\max(1,n)`.

ldc
   The leading dimension of ``c``.

scratchpad_size
   Size of scratchpad memory as a number of floating point elements of type ``T``.
   Size should not be less than the value returned by :ref:`onemkl_lapack_ormqr_scratchpad_size` function.

.. container:: section

  .. rubric:: Output Parameters
      
c
   Overwritten by the product :math:`QC`, :math:`Q^{T}C`, :math:`CQ`, or
   :math:`CQ^{T}` (as specified by left_right and trans).

scratchpad
   Buffer holding scratchpad memory to be used by routine for storing intermediate results.

ormqr (USM Version)
----------------------

.. container:: section

  .. rubric:: Syntax
         
.. cpp:function::  cl::sycl::event oneapi::mkl::lapack::ormqr(cl::sycl::queue &queue, onemkl::side left_right, onemkl::transpose trans, std::int64_t m, std::int64_t n, std::int64_t k, T *a, std::int64_t lda, T *tau, T *c, std::int64_t ldc, T *scratchpad, std::int64_t scratchpad_size, const cl::sycl::vector_class<cl::sycl::event> &events = {})

.. container:: section

  .. rubric:: Input Parameters

queue
   The queue where the routine should be executed.

left_right
   If ``left_right=onemkl::side::left``, :math:`Q` or :math:`Q^{T}` is
   applied to :math:`C` from the left.

   If ``left_right=onemkl::side::right``, :math:`Q` or :math:`Q^{T}` is
   applied to :math:`C` from the right.

trans
   If ``trans=onemkl::transpose::trans``, the routine multiplies :math:`C`
   by :math:`Q`.

   If ``trans=onemkl::transpose::nontrans``, the routine multiplies
   :math:`C` by :math:`Q^{T}`.

m
   The number of rows in the matrix :math:`A` (:math:`0 \le m`).

n
   The number of columns in the matrix :math:`A` (:math:`0 \le n \le m`).

k
   The number of elementary reflectors whose product defines the
   matrix :math:`Q` (:math:`0 \le k \le n`).

a
   The pointer to ``a`` as returned by :ref:`onemkl_lapack_geqrf`.
   The second dimension of ``a`` must be at least :math:`\max(1,k)`.

lda
   The leading dimension of ``a``.

tau
   The pointer to ``tau`` as returned by :ref:`onemkl_lapack_geqrf`.
   The second dimension of ``a`` must be at least :math:`\max(1,k)`.

c
   The pointer to the matrix :math:`C`. The second dimension of ``c``
   must be at least :math:`\max(1,n)`.

ldc
   The leading dimension of ``c``.

scratchpad_size
   Size of scratchpad memory as a number of floating point elements of type ``T``.
   Size should not be less than the value returned by :ref:`onemkl_lapack_ormqr_scratchpad_size` function.

events
   List of events to wait for before starting computation. Defaults to empty list.

.. container:: section

  .. rubric:: Output Parameters
      
c
   Overwritten by the product :math:`QC`, :math:`Q^{T}C`, :math:`CQ`, or
   :math:`CQ^{T}` (as specified by left_right and trans).

scratchpad
   Pointer to scratchpad memory to be used by routine for storing intermediate results.

.. container:: section

  .. rubric:: Return Values

Output event to wait on to ensure computation is complete.

**Parent topic:** :ref:`onemkl_lapack-linear-equation-routines`

