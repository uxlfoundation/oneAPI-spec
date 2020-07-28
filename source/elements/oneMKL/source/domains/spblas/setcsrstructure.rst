.. _onemkl_sparse_set_csr_data:

set_csr_data
============

Takes a matrix handle and the input CSR matrix arrays and fills the internal CSR data structure.

.. rubric:: Description and Assumptions


Refer to :ref:`onemkl_sparse_supported_types` for a
list of supported ``<fp>`` and ``<intType>``.
The mkl::sparse::set_csr_data routine takes a matrix handle
for a sparse matrix of dimensions *num_rows* -by- *num_cols*
represented in the CSR format, and fills the internal
CSR data structure.


.. _onemkl_sparse_set_csr_data_buffer:

set_csr_data (Buffer version)
-----------------------------

.. rubric:: Syntax

.. cpp:function::  void oneapi::mkl::sparse::set_csr_data (matrix_handle_t handle, intType num_rows, intType num_cols, oneapi::mkl::index_base index, sycl::buffer<intType, 1> & row_ptr, sycl::buffer<intType, 1> & col_ind, sycl::buffer<fp, 1> & val)


.. container:: section

    .. rubric:: Input Parameters

    handle
         Handle to object containing sparse matrix and other internal
         data for subsequent DPC++ Sparse BLAS operations.


    num_rows
         Number of rows of the input matrix .


    num_cols
         Number of columns of the input matrix .


    index
         Indicates how input arrays are indexed.
         The possible options are
         described in :ref:`onemkl_enum_index_base` enum class.


    row_ptr
         SYCL memory object containing an array of length
         ``num_rows+1``. Refer to :ref:`onemkl_sparse_csr` format
         for detailed description of ``row_ptr``.


    col_ind
         SYCL memory object which stores an array containing the
         column indices in ``index``-based numbering.
         Refer to :ref:`onemkl_sparse_csr` format for detailed
         description of ``col_ind``.


    val
         SYCL memory object which stores an array containing
         non-zero elements of the input matrix. Refer to
         :ref:`onemkl_sparse_csr` format for detailed description of ``val``.


.. container:: section


    .. rubric:: Output Parameters
         :class: sectiontitle


handle
     Handle to object containing sparse matrix and other internal
     data for subsequent SYCL Sparse BLAS operations.


.. _onemkl_sparse_set_csr_data_usm:

set_csr_data (USM version)
--------------------------

.. rubric:: Syntax

.. cpp:function::  void oneapi::mkl::sparse::set_csr_data (matrixHandle_t handle, intType num_rows, intType num_cols, oneapi::mkl::index_base index, intType *row_ptr, intType *col_ind, fp *val)


.. container:: section

    .. rubric:: Input Parameters

    handle
         Handle to object containing sparse matrix and other internal
         data for subsequent DPC++ Sparse BLAS operations.


    num_rows
         Number of rows of the input matrix .


    num_cols
         Number of columns of the input matrix .


    index
         Indicates how input arrays are indexed.
         The possible options are
         described in :ref:`onemkl_enum_index_base` enum class.


    row_ptr
         USM object containing an array of length
         ``num_rows+1``. Refer to :ref:`onemkl_sparse_csr` format for
         detailed description of ``row_ptr``


    col_ind
         USM object which stores an array containing the
         column indices in ``index``-based numbering.
         Refer to :ref:`onemkl_sparse_csr` format for detailed
         description of ``col_ind``


    val
         USM object which stores an array containing
         non-zero elements of the input matrix. Refer to
         :ref:`onemkl_sparse_csr` format for detailed description of ``val``


.. container:: section

    .. rubric:: Output Parameters
         :class: sectiontitle


handle
     Handle to object containing sparse matrix and other internal
     data for subsequent SYCL Sparse BLAS operations.


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** :ref:`onemkl_spblas`



