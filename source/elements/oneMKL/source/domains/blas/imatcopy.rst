.. SPDX-FileCopyrightText: 2022 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. _onemkl_blas_imatcopy:

imatcopy
========

Computes an in-place scaled matrix transpose or copy operation
using a general matrix.

.. _onemkl_blas_imatcopy_description:

.. rubric:: Description

The ``imatcopy`` routine performs an in-place scaled
matrix copy or transposition.

The operation is defined as:

.. math::

      AB \leftarrow \alpha * op(AB)

where:

op(X) is one of op(X) = X, or op(X) = X\ :sup:`T`, or op(X) = X\ :sup:`H`,

``alpha`` is a scalar,

``AB`` is a matrix to be transformed in place,

and ``AB`` is ``m`` x ``n`` on input.

``imatcopy`` supports the following precisions:

   .. list-table::
      :header-rows: 1

      * -  T 
      * -  ``float`` 
      * -  ``double`` 
      * -  ``std::complex<float>`` 
      * -  ``std::complex<double>`` 

.. _onemkl_blas_imatcopy_buffer:

imatcopy (Buffer Version)
-------------------------

.. rubric:: Syntax

.. code-block:: cpp

   namespace oneapi::mkl::blas::column_major {
       void imatcopy(sycl::queue &queue,
                     oneapi::mkl::transpose trans,
                     std::int64_t m,
                     std::int64_t n,
                     T alpha,
                     sycl::buffer<T, 1> &ab,
                     std::int64_t lda,
                     std::int64_t ldb);
   }
.. code-block:: cpp

   namespace oneapi::mkl::blas::row_major {
       void imatcopy(sycl::queue &queue,
                     oneapi::mkl::transpose trans,
                     std::int64_t m,
                     std::int64_t n,
                     T alpha,
                     sycl::buffer<T, 1> &ab,
                     std::int64_t lda,
                     std::int64_t ldb);
   }

.. container:: section

   .. rubric:: Input Parameters

   queue
      The queue where the routine should be executed.

   trans
      Specifies op(``AB``), the transposition operation applied to the
      matrix ``AB``. See :ref:`onemkl_datatypes` for more details.

   m
      Number of rows of ``AB`` on input. Must be at least zero.

   n
      Number of columns of ``AB`` on input. Must be at least zero.

   alpha
      Scaling factor for the matrix transposition or copy.

   ab
      Buffer holding the input/output matrix ``AB``. Must have size as follows:

      .. list-table::
         :header-rows: 1
     
         * -
           - ``trans`` = ``transpose::nontrans``
           - ``trans`` = ``transpose::trans`` or ``trans`` = ``transpose::conjtrans``
         * - Column major
           - Size of array ``ab`` must be at least max(``lda``, ``ldb``) * ``n``
           - Size of array ``ab`` must be at least max(``lda``*``n``, ``ldb``*``m``)
         * - Row major
           - Size of array ``ab`` must be at least max(``lda``, ``ldb``) * ``m``
           - Size of array ``ab`` must be at least max(``lda``*``m``, ``ldb``*``n``)

   lda
      The leading dimension of the matrix ``AB`` on input. It must be
      positive, and must be at least ``m`` if column major layout is
      used, and at least ``n`` if row-major layout is used.

   ldb
      The leading dimension of the matrix ``AB`` on output. It must be positive.

      .. list-table::
         :header-rows: 1

         * -
           - ``trans`` = ``transpose::nontrans``
           - ``trans`` = ``transpose::trans`` or ``trans`` = ``transpose::conjtrans``
         * - Column major
           - ``ldb`` must be at least ``m``.
           - ``ldb`` must be at least ``n``.
         * - Row major
           - ``ldb`` must be at least ``n``.
           - ``ldb`` must be at least ``m``.

.. container:: section

   .. rubric:: Output Parameters

   ab
      Output buffer, overwritten by ``alpha`` * op(``AB``).

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
      

.. _onemkl_blas_imatcopy_usm:

imatcopy (USM Version)
----------------------

.. rubric:: Syntax

.. code-block:: cpp

   namespace oneapi::mkl::blas::column_major {
       sycl::event imatcopy(sycl::queue &queue,
                            oneapi::mkl::transpose trans,
                            std::int64_t m,
                            std::int64_t n,
                            T alpha,
                            const T *ab,
                            std::int64_t lda,
                            std::int64_t ldb,
                            const std::vector<sycl::event> &dependencies = {});
.. code-block:: cpp

   namespace oneapi::mkl::blas::row_major {
       sycl::event imatcopy(sycl::queue &queue,
                            oneapi::mkl::transpose trans,
                            std::int64_t m,
                            std::int64_t n,
                            T alpha,
                            const T *ab,
                            std::int64_t lda,
                            std::int64_t ldb,
                            const std::vector<sycl::event> &dependencies = {});

.. container:: section

   .. rubric:: Input Parameters

   queue
      The queue where the routine will be executed.

   trans
      Specifies op(``AB``), the transposition operation applied to the
      matrix ``AB``.

   m
      Number of rows for the matrix ``AB`` on input. Must be at least zero.

   n
      Number of columns for the matrix ``AB`` on input. Must be at least zero.

   alpha
      Scaling factor for the matrix transpose or copy operation.

   ab
         Pointer to input/output matrix ``AB``. Must have size as follows:

      .. list-table::
         :header-rows: 1
     
         * -
           - ``trans`` = ``transpose::nontrans``
           - ``trans`` = ``transpose::trans`` or ``trans`` = ``transpose::conjtrans``
         * - Column major
           - Size of array ``ab`` must be at least max(``lda``, ``ldb``) * ``n``
           - Size of array ``ab`` must be at least max(``lda``*``n``, ``ldb``*``m``)
         * - Row major
           - Size of array ``ab`` must be at least max(``lda``, ``ldb``) * ``m``
           - Size of array ``ab`` must be at least max(``lda``*``m``, ``ldb``*``n``)

   lda
      Leading dimension of the matrix ``AB`` on input. If matrices are stored
      using column major layout, ``lda`` must be at least ``m``. If matrices
      are stored using row major layout, ``lda`` must be at least ``n``. 
      Must be positive.

   ldb
      Leading dimension of the matrix ``AB`` on output. Must be positive.

      .. list-table::
         :header-rows: 1

         * -
           - ``trans`` = ``transpose::nontrans``
           - ``trans`` = ``transpose::trans`` or ``trans`` = ``transpose::conjtrans``
         * - Column major
           - ``ldb`` must be at least ``m``.
           - ``ldb`` must be at least ``n``.
         * - Row major
           - ``ldb`` must be at least ``n``.
           - ``ldb`` must be at least ``m``.

   dependencies
      List of events to wait for before starting computation, if any.
      If omitted, defaults to no dependencies.

.. container:: section

   .. rubric:: Output Parameters

   ab
      Pointer to output matrix ``AB`` overwritten by ``alpha`` * op(``AB``).

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

