.. SPDX-FileCopyrightText: 2024 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. _onemkl_sparse_set_csr_matrix_data:

set_csr_matrix_data
===================

Reset the data of a ``matrix_handle_t`` object with the provided CSR data.

.. rubric:: Description and Assumptions

The ``oneapi::mkl::sparse::set_csr_matrix_data`` function sets new data to the
``matrix_handle_t`` object with the provided data.

In the case of buffers, the reference count of the provided buffer is
incremented which extends the lifetime of the underlying buffer until the
``smhandle`` is destroyed with ``release_sparse_matrix`` or the data is reset
with ``set_csr_matrix_data``.

In the case of USM, the object does not take ownership of the data.

Also see :ref:`onemkl_sparse_init_csr_matrix`.

.. _onemkl_sparse_set_csr_matrix_data_buffer:

set_csr_matrix_data (Buffer version)
------------------------------------

.. rubric:: Syntax

.. code-block:: cpp

   namespace oneapi::mkl::sparse {

       template <typename dataType, typename indexType>
       void set_csr_matrix_data (sycl::queue                          &queue,
                                 oneapi::mkl::sparse::matrix_handle_t smhandle,
                                 std::int64_t                         num_rows,
                                 std::int64_t                         num_cols,
                                 std::int64_t                         nnz,
                                 index_base                           index,
                                 sycl::buffer<indexType, 1>           row_ptr,
                                 sycl::buffer<indexType, 1>           col_ind,
                                 sycl::buffer<dataType, 1>            val);

   }

.. container:: section

   .. rubric:: Template parameters

   dataType
      See :ref:`supported template types<onemkl_sparse_supported_types>`. Must
      be the same type as was used when creating the ``matrix_handle_t``.

   indexType
      See :ref:`supported template types<onemkl_sparse_supported_types>`. Must
      be the same type as was used when creating the ``matrix_handle_t``.

.. container:: section

   .. rubric:: Input parameters

   queue
      The SYCL command queue which will be used for SYCL kernels execution.

   smhandle
      Handle already initialized with :ref:`onemkl_sparse_init_csr_matrix`.

   num_rows
      Number of rows of the provided data ``val``. Must be at least 0.

   num_cols
      Number of columns of the provided data ``val``. Must be at least 0.

   nnz
      The number of explicit entries, also known as Number of Non-Zero elements.
      Must be at least 0.

   index
      Indicates how input arrays are indexed. The possible options are described
      in :ref:`onemkl_enum_index_base` enum class.

   row_ptr
      Buffer of length at least ``num_rows+1``. Refer to
      :ref:`onemkl_sparse_csr` format for detailed description of ``row_ptr``.

   col_ind
      Buffer of length at least ``nnz`` containing the column indices in
      ``index``-based numbering. Refer to :ref:`onemkl_sparse_csr` format for
      detailed description of ``col_ind``.

   val
      Buffer of length at least ``nnz``. Contains the data of the input matrix
      which is not implicitly zero. The remaining input values are implicit
      zeros. Refer to :ref:`onemkl_sparse_csr` format for detailed description
      of ``val``.

.. container:: section

   .. rubric:: Notes

   - The parameters ``num_rows``, ``num_cols`` and ``nnz`` may be zero if and
     only if ``row_ptr``, ``col_ind`` and ``val`` are zero-sized, otherwise they
     must be strictly greater than zero.

.. container:: section

   .. rubric:: Throws

   This function shall throw the following exceptions if the associated
   condition is detected. An implementation may throw additional
   implementation-specific exception(s) in case of error conditions not covered
   here.

   | :ref:`oneapi::mkl::invalid_argument<onemkl_exception_invalid_argument>`
   | :ref:`oneapi::mkl::unimplemented<onemkl_exception_unimplemented>`
   | :ref:`oneapi::mkl::uninitialized<onemkl_exception_uninitialized>`
   | :ref:`oneapi::mkl::unsupported_device<onemkl_exception_unsupported_device>`

.. _onemkl_sparse_set_csr_matrix_data_usm:

set_csr_matrix_data (USM version)
---------------------------------

.. rubric:: Syntax

.. code-block:: cpp

   namespace oneapi::mkl::sparse {

       template <typename dataType, typename indexType>
       void set_csr_matrix_data (sycl::queue                          &queue,
                                 oneapi::mkl::sparse::matrix_handle_t smhandle,
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
      See :ref:`supported template types<onemkl_sparse_supported_types>`. Must
      be the same type as was used when creating the ``matrix_handle_t``.

   indexType
      See :ref:`supported template types<onemkl_sparse_supported_types>`. Must
      be the same type as was used when creating the ``matrix_handle_t``.

.. container:: section

   .. rubric:: Input parameters

   queue
      The SYCL command queue which will be used for SYCL kernels execution.

   smhandle
      Handle already initialized with :ref:`onemkl_sparse_init_csr_matrix`.

   num_rows
      Number of rows of the provided data ``val``. Must be at least 0.

   num_cols
      Number of columns of the provided data ``val``. Must be at least 0.

   nnz
      The number of explicit entries, also known as Number of Non-Zero elements.
      Must be at least 0.

   index
      Indicates how input arrays are indexed. The possible options are described
      in :ref:`onemkl_enum_index_base` enum class.

   row_ptr
      USM pointer of length at least ``num_rows+1``. Refer to
      :ref:`onemkl_sparse_csr` format for detailed description of ``row_ptr``.
      The data must be accessible on the device.

   col_ind
      USM pointer of length at least ``nnz`` containing the column indices in
      ``index``-based numbering. Refer to :ref:`onemkl_sparse_csr` format for
      detailed description of ``col_ind``. The data must be accessible on the
      device.

   val
      USM pointer of length at least ``nnz``. Contains the data of the input
      matrix which is not implicitly zero. The remaining input values are
      implicit zeros. Refer to :ref:`onemkl_sparse_csr` format for detailed
      description of ``val``. The data must be accessible on the device. Using a
      USM pointer with a smaller allocated memory size is undefined behavior.

.. container:: section

   .. rubric:: Notes

   - The parameters ``num_rows``, ``num_cols`` and ``nnz`` may be zero if and
     only if ``row_ptr``, ``col_ind`` and ``val`` are null pointers, otherwise
     they must be strictly greater than zero.

.. container:: section

   .. rubric:: Throws

   This function shall throw the following exceptions if the associated
   condition is detected. An implementation may throw additional
   implementation-specific exception(s) in case of error conditions not covered
   here.

   | :ref:`oneapi::mkl::invalid_argument<onemkl_exception_invalid_argument>`
   | :ref:`oneapi::mkl::unimplemented<onemkl_exception_unimplemented>`
   | :ref:`oneapi::mkl::uninitialized<onemkl_exception_uninitialized>`
   | :ref:`oneapi::mkl::unsupported_device<onemkl_exception_unsupported_device>`

**Parent topic:** :ref:`onemkl_sparse_data_handles`
