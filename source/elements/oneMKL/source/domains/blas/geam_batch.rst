.. SPDX-FileCopyrightText: 2022 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. _onemkl_blas_geam_batch:

geam_batch
==========

Computes a group of out-of-place scaled matrix additions using general
matrices.

``geam_batch`` is an alias for :ref:`onemkl_blas_omatadd_batch` and has exactly the
same API. See the full documentation at :ref:`onemkl_blas_omatadd_batch`.


.. _onemkl_blas_geam_batch_buffer:

geam_batch (Buffer Version)
---------------------------

**Strided API**

.. rubric:: Syntax

.. code-block:: cpp

   namespace oneapi::mkl::blas::column_major {
       void geam_batch(sycl::queue &queue,
                       oneapi::mkl::transpose transa,
                       oneapi::mkl::transpose transb,
                       std::int64_t m,
                       std::int64_t n,
                       T alpha,
                       sycl::buffer<T, 1> &a,
                       std::int64_t lda,
                       std::int64_t stride_a,
                       T beta,
                       sycl::buffer<T, 1> &b,
                       std::int64_t ldb,
                       std::int64_t stride_b,
                       sycl::buffer<T, 1> &c,
                       std::int64_t ldc,
                       std::int64_t stride_c,
                       std::int64_t batch_size);
   }
.. code-block:: cpp

   namespace oneapi::mkl::blas::row_major {
       void geam_batch(sycl::queue &queue,
                       oneapi::mkl::transpose transa,
                       oneapi::mkl::transpose transb,
                       std::int64_t m,
                       std::int64_t n,
                       T alpha,
                       sycl::buffer<T, 1> &a,
                       std::int64_t lda,
                       std::int64_t stride_a,
                       T beta,
                       sycl::buffer<T, 1> &b,
                       std::int64_t ldb,
                       std::int64_t stride_b,
                       sycl::buffer<T, 1> &c,
                       std::int64_t ldc,
                       std::int64_t stride_c,
                       std::int64_t batch_size);
   }


.. _onemkl_blas_geam_batch_usm:
   
geam_batch (USM Version)
------------------------

**Group API**

.. rubric:: Syntax

.. code-block:: cpp

   namespace oneapi::mkl::blas::column_major {
       sycl::event geam_batch(sycl::queue &queue,
                              const oneapi::mkl::transpose *transa_array,
                              const oneapi::mkl::transpose *transb_array,
                              const std::int64_t *m_array,
                              const std::int64_t *n_array,
                              const T *alpha_array,
                              const T **a_array,
                              const std::int64_t *lda_array,
                              const T *beta_array,
                              const T **b_array,
                              const std::int64_t *ldb_array,
                              const T **c_array,
                              const std::int64_t *ldc_array,
                              std::int64_t group_count,
                              const std::int64_t *groupsize,
                              const std::vector<sycl::event> &dependencies = {});
   }
.. code-block:: cpp

   namespace oneapi::mkl::blas::row_major {
       sycl::event geam_batch(sycl::queue &queue,
                              const oneapi::mkl::transpose *transa_array,
                              const oneapi::mkl::transpose *transb_array,
                              const std::int64_t *m_array,
                              const std::int64_t *n_array,
                              const T *alpha_array,
                              const T **a_array,
                              const std::int64_t *lda_array,
                              const T *beta_array,
                              const T **b_array,
                              const std::int64_t *ldb_array,
                              const T **c_array,
                              const std::int64_t *ldc_array,
                              std::int64_t group_count,
                              const std::int64_t *groupsize,
                              const std::vector<sycl::event> &dependencies = {});
   }

**Strided API**

.. rubric:: Syntax

.. code-block:: cpp

   namespace oneapi::mkl::blas::column_major {
       sycl::event geam_batch(sycl::queue &queue,
                              oneapi::mkl::transpose transa,
                              oneapi::mkl::transpose transb,
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
                              const std::vector<sycl::event> &dependencies = {});
   }
.. code-block:: cpp

   namespace oneapi::mkl::blas::row_major {
       sycl::event geam_batch(sycl::queue &queue,
                              oneapi::mkl::transpose transa,
                              oneapi::mkl::transpose transb,
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
                              const std::vector<sycl::event> &dependencies = {});
   }


   **Parent topic:** :ref:`blas-like-extensions`
