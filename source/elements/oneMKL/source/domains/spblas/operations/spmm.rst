.. SPDX-FileCopyrightText: 2024 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. _onemkl_sparse_spmm_header:

spmm
====

Computes a sparse matrix-dense matrix product.

.. rubric:: Description and Assumptions

The ``oneapi::mkl::sparse::spmm`` routine computes a sparse matrix-dense matrix
product defined as:

.. math::

   C \leftarrow \alpha \cdot \text{op}(A) \cdot \text{op}(B) + \beta \cdot C

where :math:`\alpha` and :math:`\beta` are scalars, :math:`A` is a sparse
matrix, :math:`B` and :math:`C` are dense matrices, :math:`\text{op}()` is a
matrix modifier for :math:`A` and :math:`B` using the following description:

.. math::

    \text{op}(A) = \begin{cases} A,& \text{oneapi::mkl::transpose::nontrans}\\
                                 A^\mathsf{T},& \text{oneapi::mkl::transpose::trans}\\
                                 A^\mathsf{H},& \text{oneapi::mkl::transpose::conjtrans}
                   \end{cases}

and :math:`\text{op}(A)` is an ``m``-by-``k`` matrix , :math:`\text{op}(B)` is
an ``k``-by-``n`` matrix, and :math:`C` is an ``m``-by-``n`` matrix.

.. _onemkl_sparse_spmm_descr:

spmm_descr
----------

.. rubric:: Definition

.. code-block:: cpp

   namespace oneapi::mkl::sparse {

       struct spmm_descr;
       using spmm_descr_t = spmm_descr*;

   }

.. container:: section

   .. rubric:: Description

   Defines ``spmm_descr_t`` as an opaque pointer to the incomplete type
   ``spmm_descr``. Each backend may provide a different implementation of the
   type ``spmm_descr``.

.. _onemkl_sparse_init_spmm_descr:

init_spmm_descr
---------------

.. rubric:: Syntax

.. code-block:: cpp

   namespace oneapi::mkl::sparse {

       void init_spmm_descr (sycl::queue                       &queue,
                             oneapi::mkl::sparse::spmm_descr_t *p_spmm_descr);

   }

.. container:: section

   .. rubric:: Input parameters

   queue
      The SYCL command queue which will be used for SYCL kernels execution.

   p_spmm_descr
      The address of the ``p_spmm_descr`` object to be initialized. Must only be
      called on an uninitialized ``spmm_descr_t`` object.

.. container:: section

   .. rubric:: Output parameters

   p_spmm_descr
      On return, the address is updated to point to a newly allocated and
      initialized ``spmm_descr_t`` object that can be used to perform spmm.

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

.. _onemkl_sparse_release_spmm_descr:

release_spmm_descr
------------------

.. rubric:: Syntax

.. code-block:: cpp

   namespace oneapi::mkl::sparse {

       void release_spmm_descr (sycl::queue                       &queue,
                                oneapi::mkl::sparse::spmm_descr_t spmm_descr);

   }

.. container:: section

   .. rubric:: Input parameters

   queue
      The SYCL command queue which will be used for SYCL kernels execution.

   spmm_descr
      Descriptor initialized with ``init_spmm_descr``.

.. container:: section

   .. rubric:: Throws

   This function shall throw the following exceptions if the associated
   condition is detected. An implementation may throw additional
   implementation-specific exception(s) in case of error conditions not covered
   here.

   | :ref:`oneapi::mkl::invalid_argument<onemkl_exception_invalid_argument>`
   | :ref:`oneapi::mkl::unimplemented<onemkl_exception_unimplemented>`
   | :ref:`oneapi::mkl::unsupported_device<onemkl_exception_unsupported_device>`

.. _onemkl_sparse_spmm_alg:

spmm_alg
--------

.. rubric:: Syntax

.. code-block:: cpp

   namespace oneapi::mkl::sparse {

       enum class spmm_alg {
           default_alg,
           coo_alg1,
           coo_alg2,
           coo_alg3,
           coo_alg4,
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
       | cuSPARSE: ``CUSPARSE_SPMM_ALG_DEFAULT``
       | rocSPARSE: ``rocsparse_spmm_alg_default``
   * - ``coo_alg1``
     - Should provide best performance for COO format, small ``nnz`` and
       column-major layout.
     - | MKL: N/A
       | cuSPARSE: ``CUSPARSE_SPMM_COO_ALG1``
       | rocSPARSE: ``rocsparse_spmm_alg_coo_segmented``
   * - ``coo_alg2``
     - Should provide best performance for COO format and column-major layout.
       Produces deterministic results.
     - | MKL: N/A
       | cuSPARSE: ``CUSPARSE_SPMM_COO_ALG2``
       | rocSPARSE: ``rocsparse_spmm_alg_coo_atomic``
   * - ``coo_alg3``
     - Should provide best performance for COO format and large ``nnz``.
     - | MKL: N/A
       | cuSPARSE: ``CUSPARSE_SPMM_COO_ALG3``
       | rocSPARSE: ``rocsparse_spmm_alg_coo_segmented_atomic``
   * - ``coo_alg4``
     - Should provide best performance for COO format and row-major layout.
     - | MKL: N/A
       | cuSPARSE: ``CUSPARSE_SPMM_COO_ALG4``
       | rocSPARSE: N/A
   * - ``csr_alg1``
     - Should provide best performance for CSR format and column-major layout.
     - | MKL: N/A
       | cuSPARSE: ``CUSPARSE_SPMM_CSR_ALG1``
       | rocSPARSE: ``rocsparse_spmm_alg_csr``
   * - ``csr_alg2``
     - Should provide best performance for CSR format and row-major layout.
     - | MKL: N/A
       | cuSPARSE: ``CUSPARSE_SPMM_CSR_ALG2``
       | rocSPARSE: ``rocsparse_spmm_alg_csr_row_split``
   * - ``csr_alg3``
     - Deterministic algorithm for CSR format.
     - | MKL: N/A
       | cuSPARSE: ``CUSPARSE_SPMM_CSR_ALG3``
       | rocSPARSE: ``rocsparse_spmm_alg_csr_merge``

.. _onemkl_sparse_spmm:

spmm
----

.. rubric:: Syntax

.. code-block:: cpp

   namespace oneapi::mkl::sparse {

       void spmm_buffer_size(
           sycl::queue                                &queue,
           oneapi::mkl::transpose                     opA,
           oneapi::mkl::transpose                     opB,
           void*                                      alpha,
           oneapi::mkl::sparse::matrix_view           A_view,
           oneapi::mkl::sparse::matrix_handle_t       A_handle,
           oneapi::mkl::sparse::dense_matrix_handle_t B_handle,
           void*                                      beta,
           oneapi::mkl::sparse::dense_matrix_handle_t C_handle,
           oneapi::mkl::sparse::spmm_alg              alg,
           oneapi::mkl::sparse::spmm_descr_t          spmm_descr,
           std::size_t                                &temp_buffer_size,
       );

       void spmm_optimize(
           sycl::queue                                &queue,
           oneapi::mkl::transpose                     opA,
           oneapi::mkl::transpose                     opB,
           void*                                      alpha,
           oneapi::mkl::sparse::matrix_view           A_view,
           oneapi::mkl::sparse::matrix_handle_t       A_handle,
           oneapi::mkl::sparse::dense_matrix_handle_t B_handle,
           void*                                      beta,
           oneapi::mkl::sparse::dense_matrix_handle_t C_handle,
           oneapi::mkl::sparse::spmm_alg              alg,
           oneapi::mkl::sparse::spmm_descr_t          spmm_descr,
           sycl::buffer<std::uint8_t, 1>              workspace,
       );

       sycl::event spmm_optimize(
           sycl::queue                                &queue,
           oneapi::mkl::transpose                     opA,
           oneapi::mkl::transpose                     opB,
           void*                                      alpha,
           oneapi::mkl::sparse::matrix_view           A_view,
           oneapi::mkl::sparse::matrix_handle_t       A_handle,
           oneapi::mkl::sparse::dense_matrix_handle_t B_handle,
           void*                                      beta,
           oneapi::mkl::sparse::dense_matrix_handle_t C_handle,
           oneapi::mkl::sparse::spmm_alg              alg,
           oneapi::mkl::sparse::spmm_descr_t          spmm_descr,
           void*                                      workspace,
           const std::vector<sycl::event>             &dependencies = {},
       );

       sycl::event spmm(
           sycl::queue                                &queue,
           oneapi::mkl::transpose                     opA,
           oneapi::mkl::transpose                     opB,
           void*                                      alpha,
           oneapi::mkl::sparse::matrix_view           A_view,
           oneapi::mkl::sparse::matrix_handle_t       A_handle,
           oneapi::mkl::sparse::dense_matrix_handle_t B_handle,
           void*                                      beta,
           oneapi::mkl::sparse::dense_matrix_handle_t C_handle,
           oneapi::mkl::sparse::spmm_alg              alg,
           oneapi::mkl::sparse::spmm_descr_t          spmm_descr,
           const std::vector<sycl::event>             &dependencies = {},
       );

   }

.. container:: section

   .. rubric:: Notes

   - ``spmm_buffer_size`` and ``spmm_optimize`` must be called at least once before ``spmm``
     with the same arguments. ``spmm`` can then be called multiple times.
   - The data of the handles can be reset-ed before each call to ``spmm``.
   - ``spmm_optimize`` and ``spmm`` are asynchronous.
   - The algorithm defaults to ``spmm_alg::default_alg`` if a backend does not
     support the provided algorithm.

   .. rubric:: Input Parameters

   queue
      The SYCL command queue which will be used for SYCL kernels execution.

   opA
      Specifies operation ``op()`` on the input matrix A. The possible options
      are described in :ref:`onemkl_enum_transpose` enum class.

   opB
      Specifies operation ``op()`` on the input matrix B. The possible options
      are described in :ref:`onemkl_enum_transpose` enum class.

   alpha
      Host or USM pointer representing :math:`\alpha`. The USM allocation can be
      on the host or device. Must be of the same type than the handles' data
      type.

   A_view
      Specifies which part of the handle should be read as described by
      :ref:`onemkl_sparse_matrix_view`.

   A_handle
      Sparse matrix handle object representing :math:`A`.

   B_handle
      Dense matrix handle object representing :math:`B`.

   beta
      Host or USM pointer representing :math:`\beta`. The USM allocation can be
      on the host or device. Must be of the same type than the handles' data
      type.

   C_handle
      Dense matrix handle object representing :math:`C`.

   alg
      Specifies the :ref:`spmm algorithm<onemkl_sparse_spmm_alg>` to use.

   spmm_descr
      Initialized :ref:`spmm descriptor<onemkl_sparse_spmm_descr>`.

   temp_buffer_size
      Output buffer size in bytes.

   workspace
      Workspace buffer or USM pointer, must be at least of size
      ``temp_buffer_size`` bytes. If it is a buffer, its lifetime is extended
      until the :ref:`spmm descriptor<onemkl_sparse_spmm_descr>` is released. If
      it is a USM pointer, it must not be free'd until ``spmm`` has completed.
      The data must be accessible on the device and the address aligned on the
      size of the handles' data type.

   dependencies
      List of events to depend on before starting asynchronous tasks that access
      data on the device. Defaults to no dependencies.

.. container:: section

   .. rubric:: Output Parameters

   temp_buffer_size
      Output buffer size in bytes. A temporary workspace of this size must be
      allocated to perform the specified spmm.

   C_handle
      Dense matrix handle object representing :math:`C`, result of the ``spmm``
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
