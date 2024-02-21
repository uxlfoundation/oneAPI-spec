.. SPDX-FileCopyrightText: 2024 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. _onemkl_spblas:

Sparse BLAS
===========

.. container::

   Sparse BLAS routines provide basic operations on sparse vectors and matrices.

.. container:: tablenoborder

   .. list-table::
      :header-rows: 1

      * - Routines and Objects
        - Description
      * - :ref:`onemkl_sparse_data_handles`
        - Matrix and vector handle types
      * - :ref:`onemkl_sparse_spsv_header`
        - Solve a linear system with a triangular sparse matrix
      * - :ref:`onemkl_sparse_spmv_header`
        - Compute the product of a sparse matrix with a dense vector
      * - :ref:`onemkl_sparse_spmm_header`
        - Compute the product of a sparse matrix with a dense matrix

.. toctree::
   :hidden:

   data_types/data_handles
   operations/spsv
   operations/spmv
   operations/spmm
   matrix_view
   supported-types

**Parent topic:** :ref:`onemkl_sparse_linear_algebra`
