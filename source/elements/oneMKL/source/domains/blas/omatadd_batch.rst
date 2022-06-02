.. SPDX-FileCopyrightText: 2022 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. _onemkl_blas_omatadd_batch:

omatadd_batch
=============

Computes a group of out-of-place scaled matrix additions using general
matrices.

.. _onemkl_blas_omatadd_batch_description:

.. rubric:: Description

The ``omatadd_batch`` routines perform a series of out-of-place scaled matrix
additions. They are batched versions of :ref:`onemkl_blas_omatadd`,
but the ``omatadd_batch`` routines perform their operations with
groups of matrices. Each group contains matrices with the same parameters.

The matrices are always in a strided format for this API.

``omatadd_batch`` supports the following precisions:

   .. list-table::
      :header-rows: 1

      * -  T 
      * -  ``float`` 
      * -  ``double`` 
      * -  ``std::complex<float>`` 
      * -  ``std::complex<double>`` 

.. _onemkl_blas_omatadd_batch_buffer:

omatadd_batch (Buffer Version)
------------------------------

.. rubric:: Description

The operation of ``omatadd_batch`` is defined as:
::

   for i = 0 … batch_size – 1
       A is a matrix at offset i * stridea in a
       B is a matrix at offset i * strideb in b
       C is a matrix at offset i * stridec in c
       C = alpha * op(A) + beta * op(B)
   end for

where:

op(X) is one of op(X) = X, or op(X) = X\ :sup:`T`, or op(X) = X\ :sup:`H`,

``alpha`` and ``beta`` are scalars,

``A`` and ``B`` are input matrices while ``C`` is an output matrix,

``C`` is ``m`` x ``n``,

``A`` is ``m`` x ``n`` if the ``op(A)`` is not transposed or ``n`` by ``m`` if it is,

and ``B`` is ``m`` x ``n`` if the ``op(B)`` is not transposed or ``n`` by ``m`` if it is.

The ``a`` and ``b`` buffers contain all the input matrices while the
``c`` buffer contains all the output matrices. The locations of the
individual matrices within the buffer are given by the ``stride_a``,
``stride_b``, and ``stride_c`` parameters, while the total number of
matrices in each buffer is given by the ``batch_size`` parameter.

.. rubric:: Syntax

.. code-block:: cpp

   namespace oneapi::mkl::blas::column_major {
       void omatadd_batch(queue &queue, transpose transa,
                          transpose transb,
                          std::int64_t m, std::int64_t n,
                          T alpha, cl::sycl::buffer<T, 1> &a,
                          std::int64_t lda, std::int64_t stride_a,
                          T beta, cl::sycl::buffer<T, 1> &b,
                          std::int64_t ldb, std::int64_t stride_b,
                          cl::sycl::buffer<T, 1> &c, std::int64_t ldc,
                          std::int64_t stride_c,
                          std::int64_t batch_size);
   }
.. code-block:: cpp

   namespace oneapi::mkl::blas::row_major {
       void omatadd_batch(queue &queue, transpose transa,
                          transpose transb,
                          std::int64_t m, std::int64_t n,
                          T alpha, cl::sycl::buffer<T, 1> &a,
                          std::int64_t lda, std::int64_t stride_a,
                          T beta, cl::sycl::buffer<T, 1> &b,
                          std::int64_t ldb, std::int64_t stride_b,
                          cl::sycl::buffer<T, 1> &c, std::int64_t ldc,
                          std::int64_t stride_c,
                          std::int64_t batch_size);
   }

.. container:: section

   .. rubric:: Input Parameters

   queue
      The queue where the routine should be executed.

   transa
      Specifies op(``A``), the transposition operation applied to the
      matrices ``A``. See :ref:`onemkl_datatypes` for more details.

   transb
      Specifies op(``B``), the transposition operation applied to the
      matrices ``B``. See :ref:`onemkl_datatypes` for more details.

   m
      Number of rows for the result matrix ``C``. Must be at least zero.

   n
      Number of columns for the result matrix ``C``. Must be at least zero.

   alpha
      Scaling factor for the matrices ``A``.

   a
      Buffer holding the input matrices ``A``. Must have size at least ``stride_a`` * ``batch_size``.

   lda
      The leading dimension of the matrices ``A``. It must be positive.

      .. list-table::
         :header-rows: 1

         * -
           - ``A`` not transposed
           - ``A`` transposed
         * - Column major
           - ``lda`` must be at least ``m``.
           - ``lda`` must be at least ``n``.
         * - Row major
           - ``lda`` must be at least ``n``.
           - ``lda`` must be at least ``m``.

   stride_a
      Stride between the different ``A`` matrices within the buffer.

      .. list-table::
         :header-rows: 1

         * -
           - ``A`` not transposed
           - ``A`` transposed
         * - Column major
           - ``stride_a`` must be at least ``lda*n``.
           - ``stride_a`` must be at least ``lda*m``.
         * - Row major
           - ``stride_a`` must be at least ``lda*m``.
           - ``stride_a`` must be at least ``lda*n``.

   beta
      Scaling factor for the matrices ``B``.

   b
      Buffer holding the input matrices ``B``. Must have size at least
      ``stride_b`` * ``batch_size``.

   ldb
      The leading dimension of the ``B`` matrices. It must be positive.

      .. list-table::
         :header-rows: 1

         * -
           - ``B`` not transposed
           - ``B`` transposed
         * - Column major
           - ``ldb`` must be at least ``m``.
           - ``ldb`` must be at least ``n``.
         * - Row major
           - ``ldb`` must be at least ``n``.
           - ``ldb`` must be at least ``m``.

   stride_b
      Stride between different ``B`` matrices.

      .. list-table::
         :header-rows: 1

         * -
           - ``B`` not transposed
           - ``B`` transposed
         * - Column major
           - ``stride_b`` must be at least ``ldb`` x ``n``.
           - ``stride_b`` must be at least ``ldb`` x ``m``.
         * - Row major
           - ``stride_b`` must be at least ``ldb`` x ``m``.
           - ``stride_b`` must be at least ``ldb`` x ``n``.

   c
      Buffer holding the output matrices ``C``. Must have size at least
      ``stride_c`` * ``batch_size``.

   ldc
      Leading dimension of the C matrices. If matrices are stored using
      column major layout, ``ldc`` must be at least ``m``. If matrices are
      stored using row major layout, ``ldc`` must be at least ``n``. Must be
      positive.

   stride_c
      Stride between the different C matrices. If matrices are stored using
      column major layout, ``stride_c`` must be at least ``ldc*n``. If matrices
      are stored using row major layout, ``stride_c`` must be at least
      ``ldc*m``.

   batch_size
      Specifies the number of matrix transposition or copy operations to perform.

.. container:: section

   .. rubric:: Output Parameters

   c
      Output buffer, overwritten by ``batch_size`` matrix addition operations
      of the form ``alpha*op(A) + beta*op(B)``. Must have size at least
      ``stride_c*batch_size``.

.. container:: section

   .. rubric:: Throws

   This routine shall throw the following exceptions if the associated
   condition is detected. An implementation may throw additional
   implementation-specific exception(s) in case of error conditions
   not covered here.

   :ref:`oneapi::mkl::invalid_argument<onemkl_exception_invalid_argument>`
       
   
   :ref:`oneapi::mkl::unsupported_device<onemkl_exception_unsupported_device>`
       

   :ref:`oneapi::mkl::host_bad_alloc<onemkl_exception_host_bad_alloc>`
       

   :ref:`oneapi::mkl::device_bad_alloc<onemkl_exception_device_bad_alloc>`
       

   :ref:`oneapi::mkl::unimplemented<onemkl_exception_unimplemented>`
      

.. _onemkl_blas_omatadd_batch_usm:
   
omatadd_batch (USM Version)
----------------------------

.. rubric:: Description

The matrices are always in a strided format for this API.

The operation for the strided API is defined as:
::

   for i = 0 … batch_size – 1
       A is a matrix at offset i * stridea in a
       B is a matrix at offset i * strideb in b
       C is a matrix at offset i * stridec in c
       C = alpha * op(A) + beta * op(B)
   end for
   
where:

op(X) is one of op(X) = X, or op(X) = X\ :sup:`T`, or op(X) = X\ :sup:`H`,

``alpha`` and ``beta`` are scalars,

``A`` and ``B`` are input matrices while ``C`` is an output matrix,

``C`` is ``m`` x ``n``,

``A`` is ``m`` x ``n`` if the ``op(A)`` is not transposed or ``n`` by ``m`` if it is,

and ``B`` is ``m`` x ``n`` if the ``op(B)`` is not transposed or ``n`` by ``m`` if it is.

The ``a`` and ``b`` arrays contain all the input matrices while the
``c`` array contains all the output matrices. The locations of the
individual matrices within the buffer are given by the ``stride_a``,
``stride_b``, and ``stride_c`` parameters, while the total number of
matrices in each buffer is given by the ``batch_size`` parameter.


**API**

.. rubric:: Syntax

.. code-block:: cpp

   namespace oneapi::mkl::blas::column_major {
       event omatadd_batch(queue &queue,
           transpose transa,
           transpose transb,
           std::int64_t m,
           std::int64_t n,
           T alpha,
           const T *a,
           std::int64_t lda,
           std::int64_t stride_a,
           T beta,
           T *b,
           std::int64_t ldb,
           std::int64_t stride_b,
           T *c,
           std::int64_t ldc,
           std::int64_t stride_c,
           std::int64_t batch_size,
           const std::vector<event> &dependencies = {});
   }
.. code-block:: cpp

   namespace oneapi::mkl::blas::row_major {
       event omatadd_batch(queue &queue,
           transpose transa,
           transpose transb,
           std::int64_t m,
           std::int64_t n,
           T alpha,
           const T *a,
           std::int64_t lda,
           std::int64_t stride_a,
           T beta,
           T *b,
           std::int64_t ldb,
           std::int64_t stride_b,
           T *c,
           std::int64_t ldc,
           std::int64_t stride_c,
           std::int64_t batch_size,
           const std::vector<event> &dependencies = {});
   }

.. container:: section

   .. rubric:: Input Parameters

   queue
      The queue where the routine should be executed.

   transa
      Specifies op(``A``), the transposition operation applied to the
      matrices ``A``. See :ref:`onemkl_datatypes` for more details.

   transb
      Specifies op(``B``), the transposition operation applied to the
      matrices ``B``. See :ref:`onemkl_datatypes` for more details.

   m
      Number of rows for the result matrix ``C``. Must be at least zero.

   n
      Number of columns for the result matrix ``C``. Must be at least zero.

   alpha
      Scaling factor for the matrices ``A``.

   a
      Array holding the input matrices ``A``. Must have size at least ``stride_a`` * ``batch_size``.

   lda
      The leading dimension of the matrices ``A``. It must be positive.

      .. list-table::
         :header-rows: 1

         * -
           - ``A`` not transposed
           - ``A`` transposed
         * - Column major
           - ``lda`` must be at least ``m``.
           - ``lda`` must be at least ``n``.
         * - Row major
           - ``lda`` must be at least ``n``.
           - ``lda`` must be at least ``m``.

   stride_a
      Stride between the different ``A`` matrices within the array.

      .. list-table::
         :header-rows: 1

         * -
           - ``A`` not transposed
           - ``A`` transposed
         * - Column major
           - ``stride_a`` must be at least ``lda*n``.
           - ``stride_a`` must be at least ``lda*m``.
         * - Row major
           - ``stride_a`` must be at least ``lda*m``.
           - ``stride_a`` must be at least ``lda*n``.

   beta
      Scaling factor for the matrices ``B``.

   b
      Array holding the input matrices ``B``. Must have size at least
      ``stride_b`` * ``batch_size``.

   ldb
      The leading dimension of the ``B`` matrices. It must be positive.

      .. list-table::
         :header-rows: 1

         * -
           - ``B`` not transposed
           - ``B`` transposed
         * - Column major
           - ``ldb`` must be at least ``m``.
           - ``ldb`` must be at least ``n``.
         * - Row major
           - ``ldb`` must be at least ``n``.
           - ``ldb`` must be at least ``m``.

   stride_b
      Stride between different ``B`` matrices.

      .. list-table::
         :header-rows: 1

         * -
           - ``B`` not transposed
           - ``B`` transposed
         * - Column major
           - ``stride_b`` must be at least ``ldb`` x ``n``.
           - ``stride_b`` must be at least ``ldb`` x ``m``.
         * - Row major
           - ``stride_b`` must be at least ``ldb`` x ``m``.
           - ``stride_b`` must be at least ``ldb`` x ``n``.

   c
      Array holding the output matrices ``C``. Must have size at least
      ``stride_c`` * ``batch_size``.

   ldc
      Leading dimension of the C matrices. If matrices are stored using
      column major layout, ``ldc`` must be at least ``m``. If matrices are
      stored using row major layout, ``ldc`` must be at least ``n``. Must be
      positive.

   stride_c
      Stride between the different C matrices. If matrices are stored using
      column major layout, ``stride_c`` must be at least ``ldc*n``. If matrices
      are stored using row major layout, ``stride_c`` must be at least
      ``ldc*m``.

   batch_size
      Specifies the number of matrix transposition or copy operations to perform.

   dependencies
      List of events to wait for before starting computation, if any.
      If omitted, defaults to no dependencies.

.. container:: section

   .. rubric:: Output Parameters

   c
      Output array, overwritten by ``batch_size`` matrix addition operations
      of the form ``alpha*op(A) + beta*op(B)``. Must have size at least
      ``stride_c*batch_size``.

.. container:: section
      
   .. rubric:: Return Values

   Output event to wait on to ensure computation is complete.

.. container:: section

   .. rubric:: Throws

   This routine shall throw the following exceptions if the associated
   condition is detected. An implementation may throw additional
   implementation-specific exception(s) in case of error conditions
   not covered here.

   :ref:`oneapi::mkl::invalid_argument<onemkl_exception_invalid_argument>`


   :ref:`oneapi::mkl::unsupported_device<onemkl_exception_unsupported_device>`
       

   :ref:`oneapi::mkl::host_bad_alloc<onemkl_exception_host_bad_alloc>`
       

   :ref:`oneapi::mkl::device_bad_alloc<onemkl_exception_device_bad_alloc>`
       

   :ref:`oneapi::mkl::unimplemented<onemkl_exception_unimplemented>`
      

   **Parent topic:** :ref:`blas-like-extensions`

