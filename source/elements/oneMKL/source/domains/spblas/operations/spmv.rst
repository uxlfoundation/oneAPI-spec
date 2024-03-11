.. SPDX-FileCopyrightText: 2024 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. _onemkl_sparse_spmv_header:

spmv
====

Computes a sparse matrix-dense vector product.

.. rubric:: Description and Assumptions

The ``oneapi::mkl::sparse::spmv`` routine computes a sparse matrix-dense vector
product defined as:

.. math::

      y \leftarrow \alpha \cdot \text{op}(A) \cdot x + \beta \cdot y

where :math:`\alpha` and :math:`\beta` are scalars, :math:`A` is a sparse
matrix, :math:`x` and :math:`y` are dense vectors, :math:`\text{op}()` is a
matrix modifier for :math:`A` using the following description:

.. math::

    \text{op}(A) = \begin{cases} A,& \text{oneapi::mkl::transpose::nontrans}\\
                                 A^{T},& \text{oneapi::mkl::transpose::trans}\\
                                 A^{H},& \text{oneapi::mkl::transpose::conjtrans}
                   \end{cases}

and :math:`\text{op}(A)` is an ``m``-by-``n`` matrix , :math:`x` is a vector of
size ``n`` and :math:`y` is a vector of size ``m``.

.. _onemkl_sparse_spmv_descr:

spmv_descr
----------

.. rubric:: Definition

.. code-block:: cpp

   namespace oneapi::mkl::sparse {
       struct spmv_descr;
       using spmv_descr_t = spmv_descr*;
   }

.. container:: section

   .. rubric:: Description

   Defines ``spmv_descr_t`` as an opaque pointer to the incomplete type
   ``spmv_descr``. Each backend may provide a different implementation of the
   type ``spmv_descr``.

.. _onemkl_sparse_init_spmv_descr:

init_spmv_descr
---------------

.. rubric:: Syntax

.. code-block:: cpp

   namespace oneapi::mkl::sparse {

       void init_spmv_descr (sycl::queue                       &queue,
                             oneapi::mkl::sparse::spmv_descr_t *p_spmv_descr);

   }

.. container:: section

   .. rubric:: Input parameters

   queue
      The SYCL command queue which will be used for SYCL kernels execution.

   p_spmv_descr
      The address of the ``p_spmv_descr`` object to be initialized. Must only be
      called on an uninitialized ``spmv_descr_t`` object.

.. container:: section

   .. rubric:: Output parameters

   p_spmv_descr
      On return, the address is updated to point to a newly allocated and
      initialized ``spmv_descr_t`` object that can be used to perform spmv.

.. container:: section

   .. rubric:: Throws

   This function shall throw the following exceptions if the associated
   condition is detected. An implementation may throw additional
   implementation-specific exception(s) in case of error conditions not covered
   here.

   | :ref:`oneapi::mkl::host_bad_alloc<onemkl_exception_host_bad_alloc>`
   | :ref:`oneapi::mkl::invalid_argument<onemkl_exception_invalid_argument>`
   | :ref:`oneapi::mkl::unimplemented<onemkl_exception_unimplemented>`
   | :ref:`oneapi::mkl::unsupported_device<onemkl_exception_unsupported_device>`

.. _onemkl_sparse_release_spmv_descr:

release_spmv_descr
------------------

.. rubric:: Syntax

.. code-block:: cpp

   namespace oneapi::mkl::sparse {

       void release_spmv_descr (sycl::queue                       &queue,
                                oneapi::mkl::sparse::spmv_descr_t spmv_descr);

   }

.. container:: section

   .. rubric:: Input parameters

   queue
      The SYCL command queue which will be used for SYCL kernels execution.

   spmv_descr
      Descriptor initialized with ``init_spmv_descr``.

.. container:: section

   .. rubric:: Throws

   This function shall throw the following exceptions if the associated
   condition is detected. An implementation may throw additional
   implementation-specific exception(s) in case of error conditions not covered
   here.

   | :ref:`oneapi::mkl::invalid_argument<onemkl_exception_invalid_argument>`
   | :ref:`oneapi::mkl::unimplemented<onemkl_exception_unimplemented>`
   | :ref:`oneapi::mkl::unsupported_device<onemkl_exception_unsupported_device>`

.. _onemkl_sparse_spmv_alg:

spmv_alg
--------

.. rubric:: Syntax

.. code-block:: cpp

   namespace oneapi::mkl::sparse {

       enum class spmv_alg {
           default_alg,
           coo_alg1,
           coo_alg2,
           csr_alg1,
           csr_alg2,
           csr_alg3,
       };

   }

.. list-table::
   :header-rows: 1
   :widths: 10 30 45

   * - Value
     - Description
     - Backend equivalent
   * - ``default_alg``
     - Default algorithm.
     - | MKL: N/A
       | cuSPARSE: ``CUSPARSE_SPMV_ALG_DEFAULT``
       | rocSPARSE: ``rocsparse_spmv_alg_default``
   * - ``coo_alg1``
     - Default algorithm for COO format.
     - | MKL: N/A
       | cuSPARSE: ``CUSPARSE_SPMV_COO_ALG1``
       | rocSPARSE: ``rocsparse_spmv_alg_coo``
   * - ``coo_alg2``
     - Deterministic algorithm for COO format.
     - | MKL: N/A
       | cuSPARSE: ``CUSPARSE_SPMV_COO_ALG2``
       | rocSPARSE: ``rocsparse_spmv_alg_coo_atomic``
   * - ``csr_alg1``
     - Default algorithm for CSR format.
     - | MKL: N/A
       | cuSPARSE: ``CUSPARSE_SPMV_CSR_ALG1``
       | rocSPARSE: ``rocsparse_spmv_alg_csr_adaptive``
   * - ``csr_alg2``
     - Deterministic algorithm for CSR format.
     - | MKL: N/A
       | cuSPARSE: ``CUSPARSE_SPMV_CSR_ALG2``
       | rocSPARSE: ``rocsparse_spmv_alg_csr_stream``
   * - ``csr_alg3``
     - LRB variant of the algorithm for CSR format.
     - | MKL: N/A
       | cuSPARSE: N/A
       | rocSPARSE: ``rocsparse_spmv_alg_csr_lrb``

.. _onemkl_sparse_spmv:

spmv
----

.. rubric:: Syntax

.. code-block:: cpp

   namespace oneapi::mkl::sparse {

       void spmv_buffer_size(
           sycl::queue                                &queue,
           oneapi::mkl::transpose                     opA,
           void*                                      alpha,
           oneapi::mkl::sparse::matrix_view           A_view,
           oneapi::mkl::sparse::matrix_handle_t       A_handle,
           oneapi::mkl::sparse::dense_vector_handle_t x_handle,
           void*                                      beta,
           oneapi::mkl::sparse::dense_vector_handle_t y_handle,
           oneapi::mkl::sparse::spmv_alg              alg,
           oneapi::mkl::sparse::spmv_descr_t          spmv_descr,
           std::size_t                                &temp_buffer_size,
       );

       void spmv_optimize(
           sycl::queue                                &queue,
           oneapi::mkl::transpose                     opA,
           void*                                      alpha,
           oneapi::mkl::sparse::matrix_view           A_view,
           oneapi::mkl::sparse::matrix_handle_t       A_handle,
           oneapi::mkl::sparse::dense_vector_handle_t x_handle,
           void*                                      beta,
           oneapi::mkl::sparse::dense_vector_handle_t y_handle,
           oneapi::mkl::sparse::spmv_alg              alg,
           oneapi::mkl::sparse::spmv_descr_t          spmv_descr,
           sycl::buffer<std::uint8_t, 1>              workspace,
       );

       sycl::event spmv_optimize(
           sycl::queue                                &queue,
           oneapi::mkl::transpose                     opA,
           void*                                      alpha,
           oneapi::mkl::sparse::matrix_view           A_view,
           oneapi::mkl::sparse::matrix_handle_t       A_handle,
           oneapi::mkl::sparse::dense_vector_handle_t x_handle,
           void*                                      beta,
           oneapi::mkl::sparse::dense_vector_handle_t y_handle,
           oneapi::mkl::sparse::spmv_alg              alg,
           oneapi::mkl::sparse::spmv_descr_t          spmv_descr,
           void*                                      workspace,
           const std::vector<sycl::event>             &dependencies = {},
       );

       sycl::event spmv(
           sycl::queue                                &queue,
           oneapi::mkl::transpose                     opA,
           void*                                      alpha,
           oneapi::mkl::sparse::matrix_view           A_view,
           oneapi::mkl::sparse::matrix_handle_t       A_handle,
           oneapi::mkl::sparse::dense_vector_handle_t x_handle,
           void*                                      beta,
           oneapi::mkl::sparse::dense_vector_handle_t y_handle,
           oneapi::mkl::sparse::spmv_alg              alg,
           oneapi::mkl::sparse::spmv_descr_t          spmv_descr,
           const std::vector<sycl::event>             &dependencies = {},
       );

   }

.. container:: section

   .. rubric:: Notes

   - ``spmv_buffer_size`` and ``spmv_optimize`` must be called at least once before ``spmv``
     with the same arguments. ``spmv`` can then be called multiple times.
   - The data of the handles can be reset-ed before each call to ``spmv``.
   - ``spmv_optimize`` and ``spmv`` are asynchronous.
   - The algorithm defaults to ``spmv_alg::default_alg`` if a backend does not
     support the provided algorithm.

   .. rubric:: Input Parameters

   queue
      The SYCL command queue which will be used for SYCL kernels execution.

   opA
      Specifies operation ``op()`` on the input matrix. The possible options are
      described in :ref:`onemkl_enum_transpose` enum class.

   alpha
      Host or USM pointer representing :math:`\alpha`. The USM allocation can be
      on the host or device. Must be of the same type than the handles' data
      type.

   A_view
      Specifies which part of the handle should be read as described by
      :ref:`onemkl_sparse_matrix_view`.

   A_handle
      Sparse matrix handle object representing :math:`A`.

   x_handle
      Dense vector handle object representing :math:`x`.

   beta
      Host or USM pointer representing :math:`\beta`. The USM allocation can be
      on the host or device. Must be of the same type than the handles' data
      type.

   y_handle
      Dense vector handle object representing :math:`y`.

   alg
      Specifies the :ref:`spmv algorithm<onemkl_sparse_spmv_alg>` to use.

   spmv_descr
      Initialized :ref:`spmv descriptor<onemkl_sparse_spmv_descr>`.

   temp_buffer_size
      Output buffer size in bytes.

   workspace
      Workspace buffer or USM pointer, must be at least of size
      ``temp_buffer_size`` bytes. If it is a buffer, its lifetime is extended
      until the :ref:`spmv descriptor<onemkl_sparse_spmv_descr>` is released. If
      it is a USM pointer, it must not be free'd until ``spmv`` has completed.
      The data must be accessible on the device and the address aligned on the
      size of the handles' data type.

   dependencies
      List of events to depend on before starting asynchronous tasks that access
      data on the device. Defaults to no dependencies.

.. container:: section

   .. rubric:: Output Parameters

   temp_buffer_size
      Output buffer size in bytes. A temporary workspace of this size must be
      allocated to perform the specified spmv.

   y_handle
      Dense vector handle object representing :math:`y`, result of the ``spmv``
      operation.

.. container:: section

   .. rubric:: Return Values

   Output event that can be waited upon or added as a dependency for the
   completion of the function.

.. container:: section

   .. rubric:: Throws

   These functions shall throw the following exceptions if the associated
   condition is detected. An implementation may throw additional
   implementation-specific exception(s) in case of error conditions not covered
   here.

   | :ref:`oneapi::mkl::computation_error<onemkl_exception_computation_error>`
   | :ref:`oneapi::mkl::device_bad_alloc<onemkl_exception_device_bad_alloc>`
   | :ref:`oneapi::mkl::invalid_argument<onemkl_exception_invalid_argument>`
   | :ref:`oneapi::mkl::unimplemented<onemkl_exception_unimplemented>`
   | :ref:`oneapi::mkl::uninitialized<onemkl_exception_uninitialized>`
   | :ref:`oneapi::mkl::unsupported_device<onemkl_exception_unsupported_device>`

**Parent topic:** :ref:`onemkl_spblas`
