.. SPDX-FileCopyrightText: 2024 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. _onemkl_sparse_create_csr_matrix:

create_csr_matrix
=================

Initializes a ``matrix_handle_t`` object with the provided CSR data.

.. rubric:: Description and Assumptions

The ``oneapi::mkl::sparse::create_csr_matrix`` function initializes the
``matrix_handle_t`` object with the provided data.

In the case of buffers, the reference count of the provided buffer is
incremented which extends the lifetime of the underlying buffer until the sparse
matrix handle is destroyed with ``destroy_sparse_matrix`` or the data is reset
with ``set_csr_matrix_data``.

In the case of USM, the object does not take ownership of the data.

The ``oneapi::mkl::sparse::create_csr_matrix`` function defined below takes in
the number of non-zero elements in the sparse matrix as an argument. However, in
certain math operations where the output is a sparse matrix, e.g., sparse matrix
addition (sparse matrix + sparse matrix = sparse matrix), and multiplication of
two sparse matrices, the number of non-zero elements in the output sparse matrix
is not known in advance and must be calculated as part of the operation API.
Such APIs are currently not a part of the current oneMKL Specification, but will
be added in the future. Therefore, it is important for the ``create_csr_matrix``
API to be able to handle multiple calls to build the sparse matrix as function
arguments become known and arrays are allocated with the correct sizes. In
particular, the ``create_csr_matrix`` API must handle the case where the number
of non-zero elements in the matrix are unknown and the matrix arrays are
``nullptr`` or zero-sized ``sycl::buffer`` objects as applicable. This behavior
is currently left to be implementation-defined, but may be clarified in the
oneMKL Specification in the future.

See :ref:`onemkl_sparse_matrix_handle`.

.. _onemkl_sparse_create_csr_matrix_buffer:

create_csr_matrix (Buffer version)
----------------------------------

.. rubric:: Syntax

.. code-block:: cpp

   namespace oneapi::mkl::sparse {

       template <typename dataType, typename indexType>
       void create_csr_matrix (sycl::queue                          &queue,
                               oneapi::mkl::sparse::matrix_handle_t *p_smhandle,
                               std::int64_t                         num_rows,
                               std::int64_t                         num_cols,
                               std::int64_t                         nnz,
                               index_base                           index,
                               sycl::buffer<indexType, 1>           &row_ptr,
                               sycl::buffer<indexType, 1>           &col_ind,
                               sycl::buffer<dataType, 1>            &val);

   }

.. container:: section

   .. rubric:: Template parameters

   dataType
      See :ref:`supported template types<onemkl_sparse_supported_types>`.

   indexType
      See :ref:`supported template types<onemkl_sparse_supported_types>`.

.. container:: section

   .. rubric:: Input parameters

   queue
      The SYCL command queue which will be used for SYCL kernels execution.

   p_smhandle
      The address of the ``p_smhandle`` object to be initialized. Must only be
      called on an uninitialized ``matrix_handle_t`` object.

   num_rows
      Number of rows of the provided data ``val``. Must be at least 0.

   num_cols
      Number of columns of the provided data ``val``. Must be at least 0.

   nnz
      Number of non-zero entries in the matrix (which may include explicit
      zeros). Must be at least 0.

   index
      Indicates how input arrays are indexed. The possible options are described
      in :ref:`onemkl_enum_index_base` enum class.

   row_ptr
      Buffer of length ``num_rows+1``. Refer to :ref:`onemkl_sparse_csr` format
      for detailed description of ``row_ptr``.

   col_ind
      Buffer of length ``nnz`` containing the column indices in ``index``-based
      numbering. Refer to :ref:`onemkl_sparse_csr` format for detailed
      description of ``col_ind``.

   val
      Buffer of length ``nnz`` containing non-zero elements (and possibly
      explicit zeros) of the input matrix. Refer to :ref:`onemkl_sparse_csr`
      format for detailed description of ``val``.

.. container:: section

   .. rubric:: Output parameters

   p_smhandle
      On return, the address is updated to point to a newly allocated and
      initialized ``matrix_handle_t`` object that can be filled and used to
      perform sparse BLAS operations.

.. container:: section

   .. rubric:: Throws

   This function shall throw the following exceptions if the associated
   condition is detected. An implementation may throw additional
   implementation-specific exception(s) in case of error conditions not covered
   here.

   | :ref:`oneapi::mkl::device_bad_alloc<onemkl_exception_device_bad_alloc>`
   | :ref:`oneapi::mkl::host_bad_alloc<onemkl_exception_host_bad_alloc>`
   | :ref:`oneapi::mkl::invalid_argument<onemkl_exception_invalid_argument>`
   | :ref:`oneapi::mkl::unimplemented<onemkl_exception_unimplemented>`
   | :ref:`oneapi::mkl::unsupported_device<onemkl_exception_unsupported_device>`

.. _onemkl_sparse_create_csr_matrix_usm:

create_csr_matrix (USM version)
-------------------------------

.. rubric:: Syntax

.. code-block:: cpp

   namespace oneapi::mkl::sparse {

       template <typename dataType, typename indexType>
       void create_csr_matrix (sycl::queue                          &queue,
                               oneapi::mkl::sparse::matrix_handle_t *p_smhandle,
                               std::int64_t                         num_rows,
                               std::int64_t                         num_cols,
                               std::int64_t                         nnz,
                               index_base                           index,
                               indexType                            *row_ptr,
                               indexType                            *col_ind,
                               dataType                             *val);

   }

.. container:: section

   .. rubric:: Template parameters

   dataType
      See :ref:`supported template types<onemkl_sparse_supported_types>`.

   indexType
      See :ref:`supported template types<onemkl_sparse_supported_types>`.

.. container:: section

   .. rubric:: Input parameters

   queue
      The SYCL command queue which will be used for SYCL kernels execution.

   p_smhandle
      The address of the ``p_smhandle`` object to be initialized. Must only be
      called on an uninitialized ``matrix_handle_t`` object.

   num_rows
      Number of rows of the provided data ``val``. Must be at least 0.

   num_cols
      Number of columns of the provided data ``val``. Must be at least 0.

   nnz
      Number of non-zero entries in the matrix (which may include explicit
      zeros). Must be at least 0.

   index
      Indicates how input arrays are indexed. The possible options are described
      in :ref:`onemkl_enum_index_base` enum class.

   row_ptr
      USM pointer of length ``num_rows+1``. Refer to :ref:`onemkl_sparse_csr`
      format for detailed description of ``row_ptr``. The data must be
      accessible on the device.

   col_ind
      USM pointer of length ``nnz`` containing the column indices in
      ``index``-based numbering. Refer to :ref:`onemkl_sparse_csr` format for
      detailed description of ``col_ind``. The data must be accessible on the
      device.

   val
      USM pointer of length ``nnz`` containing non-zero elements (and possibly
      explicit zeros) of the input matrix. Refer to :ref:`onemkl_sparse_csr`
      format for detailed description of ``val``. The data must be accessible on
      the device.

.. container:: section

   .. rubric:: Output parameters

   p_smhandle
      On return, the address is updated to point to a newly allocated and
      initialized ``matrix_handle_t`` object that can be filled and used to
      perform sparse BLAS operations.

.. container:: section

   .. rubric:: Throws

   This function shall throw the following exceptions if the associated
   condition is detected. An implementation may throw additional
   implementation-specific exception(s) in case of error conditions not covered
   here.

   | :ref:`oneapi::mkl::device_bad_alloc<onemkl_exception_device_bad_alloc>`
   | :ref:`oneapi::mkl::host_bad_alloc<onemkl_exception_host_bad_alloc>`
   | :ref:`oneapi::mkl::invalid_argument<onemkl_exception_invalid_argument>`
   | :ref:`oneapi::mkl::unimplemented<onemkl_exception_unimplemented>`
   | :ref:`oneapi::mkl::unsupported_device<onemkl_exception_unsupported_device>`

**Parent topic:** :ref:`onemkl_sparse_data_handles`
