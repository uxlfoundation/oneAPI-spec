.. SPDX-FileCopyrightText: 2024 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. _onemkl_sparse_set_coo_data:

set_coo_data
============

Takes a matrix handle and the input COO matrix arrays and fills the internal COO data structure.

.. rubric:: Description and Assumptions


Refer to :ref:`onemkl_sparse_supported_types` for a
list of supported ``<fp>`` and ``<intType>``.
The mkl::sparse::set_coo_data routine takes a matrix handle
for a sparse matrix of dimensions *nrows* -by- *ncols*
represented in the COO format, and fills the internal
COO data structure.

The mkl::sparse::set_coo_data routine defined below takes in the
number of non-zero elements in the sparse matrix as an argument.
However, in certain math operations where the output is a sparse matrix,
e.g., sparse matrix addition (sparse matrix + sparse matrix = sparse matrix),
and multiplication of two sparse matrices, the number of non-zero
elements in the output sparse matrix is not known in advance and
must be calculated as part of the operation/API. Such APIs are currently
not a part of the current oneMKL Specification, but will be added in the
future. Therefore, it is important for the set_coo_data API to be able
to handle mutliple calls to build the sparse matrix as function arguments
become known and arrays are allocated with the correct sizes. In particular,
the set_coo_data API must handle the case where the number of non-zero
elements in the matrix are unknown and the matrix arrays are ``nullptr``
or zero-sized ``sycl::buffer`` objects as applicable. This behavior is
currently left to be implementation-defined, but may be clarified in the
oneMKL Specification in the future.

.. _onemkl_sparse_set_coo_data_buffer:

set_coo_data (Buffer version)
-----------------------------

.. rubric:: Syntax

.. code-block:: cpp

   namespace oneapi::mkl::sparse {

      void set_coo_data (sycl::queue                           &queue,
                         oneapi::mkl::sparse::matrix_handle_t  handle,
                         const intType                         nrows,
                         const intType                         ncols,
                         const intType                         nnz,
                         oneapi::mkl::index_base               index,
                         sycl::buffer<intType, 1>              &row_ind,
                         sycl::buffer<intType, 1>              &col_ind,
                         sycl::buffer<fp, 1>                   &val);

   }

.. container:: section

    .. rubric:: Input Parameters

    queue
         The SYCL command queue which will be used for SYCL kernel execution.

    handle
         Handle to object containing sparse matrix and other internal
         data for subsequent DPC++ Sparse BLAS operations.


    nrows
         Number of rows of the input matrix.


    ncols
         Number of columns of the input matrix.


    nnz
         Number of non-zero entries in the matrix (which may include explicit
         zeros).


    index
         Indicates how input arrays are indexed.
         The possible options are
         described in :ref:`onemkl_enum_index_base` enum class.


    row_ind
         SYCL memory object which stores an array of length ``nnz``
         containing row indices in ``index``-based numbering.
         Refer to :ref:`onemkl_sparse_coo` format for detailed
         description of ``row_ind``.


    col_ind
         SYCL memory object which stores an array of length ``nnz``
         containing column indices in ``index``-based numbering.
         Refer to :ref:`onemkl_sparse_coo` format for detailed
         description of ``col_ind``.


    val
         SYCL memory object which stores an array of length ``nnz``
         containing non-zero elements (and possibly explicit zeros) of the
         input matrix. Refer to :ref:`onemkl_sparse_coo` format for detailed
         description of ``val``.


.. container:: section


    .. rubric:: Output Parameters
         :class: sectiontitle


    handle
         Handle to object containing sparse matrix and other internal
         data for subsequent SYCL Sparse BLAS operations.

.. container:: section

    .. rubric:: Throws
       :class: sectiontitle

    This routine shall throw the following exceptions if the associated condition is detected.
    An implementation may throw additional implementation-specific exception(s)
    in case of error conditions not covered here.

    | :ref:`oneapi::mkl::computation_error<onemkl_exception_computation_error>`
    | :ref:`oneapi::mkl::device_bad_alloc<onemkl_exception_device_bad_alloc>`
    | :ref:`oneapi::mkl::host_bad_alloc<onemkl_exception_host_bad_alloc>`
    | :ref:`oneapi::mkl::invalid_argument<onemkl_exception_invalid_argument>`
    | :ref:`oneapi::mkl::unimplemented<onemkl_exception_unimplemented>`
    | :ref:`oneapi::mkl::uninitialized<onemkl_exception_uninitialized>`
    | :ref:`oneapi::mkl::unsupported_device<onemkl_exception_unsupported_device>`

.. _onemkl_sparse_set_coo_data_usm:

set_coo_data (USM version)
--------------------------

.. rubric:: Syntax

.. code-block:: cpp

   namespace oneapi::mkl::sparse {

      sycl::event set_coo_data (sycl::queue                           &queue,
                                oneapi::mkl::sparse::matrix_handle_t  handle,
                                const intType                         nrows,
                                const intType                         ncols,
                                const intType                         nnz,
                                oneapi::mkl::index_base               index,
                                intType                               *row_ind,
                                intType                               *col_ind,
                                fp                                    *val,
                                const std::vector<sycl::event>        &dependencies = {});

   }

.. container:: section

    .. rubric:: Input Parameters

    queue
         The SYCL command queue which will be used for SYCL kernel execution.

    handle
         Handle to object containing sparse matrix and other internal
         data for subsequent DPC++ Sparse BLAS operations.


    nrows
         Number of rows of the input matrix.


    ncols
         Number of columns of the input matrix.


    nnz
         Number of non-zero entries in the matrix (which may include explicit
         zeros).


    index
         Indicates how input arrays are indexed.
         The possible options are
         described in :ref:`onemkl_enum_index_base` enum class.


    row_ind
         USM object which stores an array of length ``nnz``
         containing row indices in ``index``-based numbering.
         Refer to :ref:`onemkl_sparse_coo` format for detailed
         description of ``row_ind``


    col_ind
         USM object which stores an array of length ``nnz``
         containing column indices in ``index``-based numbering.
         Refer to :ref:`onemkl_sparse_coo` format for detailed
         description of ``col_ind``


    val
         USM object which stores an array of length ``nnz``
         containing non-zero elements (and possibly explicit zeros) of the
         input matrix. Refer to :ref:`onemkl_sparse_coo` format for
         detailed description of ``val``

    dependencies
         A vector of type const std::vector<sycl::event> & containing the list of events
         that the oneapi::mkl::sparse::set_coo_data routine depends on.

.. container:: section

    .. rubric:: Output Parameters
         :class: sectiontitle


    handle
         Handle to object containing sparse matrix and other internal
         data for subsequent SYCL Sparse BLAS operations.

.. container:: section

    .. rubric:: Return Values
         :class: sectiontitle

    sycl::event
         A sycl::event that can be used to track the completion of asynchronous events
         that were enqueued during the API call that continue the chain of events from the input dependencies.

.. container:: section

    .. rubric:: Throws
       :class: sectiontitle

    This routine shall throw the following exceptions if the associated condition is detected.
    An implementation may throw additional implementation-specific exception(s)
    in case of error conditions not covered here.

    | :ref:`oneapi::mkl::computation_error<onemkl_exception_computation_error>`
    | :ref:`oneapi::mkl::device_bad_alloc<onemkl_exception_device_bad_alloc>`
    | :ref:`oneapi::mkl::host_bad_alloc<onemkl_exception_host_bad_alloc>`
    | :ref:`oneapi::mkl::invalid_argument<onemkl_exception_invalid_argument>`
    | :ref:`oneapi::mkl::unimplemented<onemkl_exception_unimplemented>`
    | :ref:`oneapi::mkl::uninitialized<onemkl_exception_uninitialized>`
    | :ref:`oneapi::mkl::unsupported_device<onemkl_exception_unsupported_device>`

.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** :ref:`onemkl_spblas`
