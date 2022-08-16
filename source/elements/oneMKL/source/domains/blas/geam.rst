.. SPDX-FileCopyrightText: 2022 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. _onemkl_blas_geam:

geam
====

Computes a sum of two general matrices, with optional transposes.

``geam`` is an alias for :ref:`onemkl_blas_omatadd` and has exactly the same API.
See the full documentation at :ref:`onemkl_blas_omatadd`.


.. _onemkl_blas_geam_buffer:

geam (Buffer Version)
---------------------

.. rubric:: Syntax

.. code-block:: cpp

   namespace oneapi::mkl::blas::column_major {
       void geam(sycl::queue &queue,
                 oneapi::mkl::transpose transa,
                 oneapi::mkl::transpose transb,
                 std::int64_t m,
                 std::int64_t n,
                 T alpha,
                 sycl::buffer<T, 1> &a,
                 std::int64_t lda,
                 T beta,
                 sycl::buffer<T, 1> &b,
                 std::int64_t ldb,
                 sycl::buffer<T, 1> &c,
                 std::int64_t ldc)
   }
.. code-block:: cpp

   namespace oneapi::mkl::blas::row_major {
       void geam(sycl::queue &queue,
                 oneapi::mkl::transpose transa,
                 oneapi::mkl::transpose transb,
                 std::int64_t m,
                 std::int64_t n,
                 T alpha,
                 sycl::buffer<T, 1> &a,
                 std::int64_t lda,
                 T beta,
                 sycl::buffer<T, 1> &b,
                 std::int64_t ldb,
                 sycl::buffer<T, 1> &c,
                 std::int64_t ldc)
   }


.. _onemkl_blas_geam_usm:
   
geam (USM Version)
------------------

.. rubric:: Syntax

.. code-block:: cpp

   namespace oneapi::mkl::blas::column_major {
       sycl::event geam(sycl::queue &queue,
                        oneapi::mkl::transpose transa,
                        oneapi::mkl::transpose transb,
                        std::int64_t m,
                        std::int64_t n,
                        T alpha,
                        const T *a,
                        std::int64_t lda,
                        T beta,
                        T *b,
                        std::int64_t ldb,
                        T *c,
                        std::int64_t ldc,
                        const std::vector<sycl::event> &dependencies = {});
   }
.. code-block:: cpp

   namespace oneapi::mkl::blas::row_major {
       sycl::event geam(sycl::queue &queue,
                        oneapi::mkl::transpose transa,
                        oneapi::mkl::transpose transb,
                        std::int64_t m,
                        std::int64_t n,
                        T alpha,
                        const T *a,
                        std::int64_t lda,
                        T beta,
                        T *b,
                        std::int64_t ldb,
                        T *c,
                        std::int64_t ldc,
                        const std::vector<sycl::event> &dependencies = {});
   }


**Parent topic:** :ref:`blas-like-extensions`

