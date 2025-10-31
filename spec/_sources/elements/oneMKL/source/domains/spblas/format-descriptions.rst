.. SPDX-FileCopyrightText: 2019-2024 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. _onemkl_sparse_format_descriptions:

Sparse storage formats
======================

There are a variety of matrix storage formats available for
representing sparse matrices. Two popular formats are the
coordinate (COO) format, and the compressed sparse row (CSR)
format.

.. container:: section

    .. _onemkl_sparse_coo:

    .. rubric:: COO

    The COO format is the simplest sparse matrix format,
    represented by three arrays, *row_ind*, *col_ind*
    and *val*, and an *index* parameter. Each non-zero
    element, *i* in the sparse matrix is represented by its
    row index, column index, and value, that is,
    *(row_ind[i], col_ind[i], val[i])*. The entries need not
    be in a sorted order.

    .. container:: tablenoborder

         .. list-table::

            * - nrows
              - Number of rows in the sparse matrix.
            * - ncols
              - Number of columns in the sparse matrix.
            * - nnz
              - Number of non-zero entries in the sparse matrix (which may include explicit zeros).
                This is also the length of the *row_ind*, *col_ind* and *val* arrays.
            * - index
              - Parameter that is used to specify whether the matrix has zero or one-based indexing.
            * - val
              - An array of length ``nnz`` that contains the non-zero elements of the sparse matrix
                not necessarily in any sorted order.
            * - row_ind
              - An integer array of length ``nnz``. Contains row indices for non-zero elements
                stored in the *val* array such that *row_ind[i]* is the row number (using zero-
                or one-based indexing) of the element of the sparse matrix stored in *val[i]*.
            * - col_ind
              - An integer array of length ``nnz``. Contains column indices for non-zero elements
                stored in the *val* array such that *col_ind[i]* is the column number (using zero-
                or one-based indexing) of the element of the sparse matrix stored in *val[i]*.


A sparse matrix can be represented in a COO format in a following way (assuming one-based indexing):

.. math::
   A = \left(\begin{matrix}
             1 &  0 & 2\\
             0 & -1 & 4\\
             3 &  0 & 0\\
             \end{matrix}\right)


+------------+------------------------------------------------------------+
| nrows      | 3                                                          |
+------------+------------------------------------------------------------+
| ncols      | 3                                                          |
+------------+------------------------------------------------------------+
| nnz        | 5                                                          |
+------------+------------------------------------------------------------+
| index      | 1                                                          |
+------------+------------+-----------+-----------+-----------+-----------+
| row_ind    | 1          | 1         | 2         | 2         | 3         |
+------------+------------+-----------+-----------+-----------+-----------+
| col_ind    | 1          | 3         | 2         | 3         | 1         |
+------------+------------+-----------+-----------+-----------+-----------+
| val        | 1          | 2         | -1        | 4         | 3         |
+------------+------------+-----------+-----------+-----------+-----------+


.. container:: section

    .. _onemkl_sparse_csr:

    .. rubric:: CSR

    The CSR format is one of the most popular sparse matrix
    storage formats, represented by three arrays,
    *row_ptr*, *col_ind* and *val*, and an *index*
    parameter.

    .. container:: tablenoborder

         .. list-table::

            * - nrows
              - Number of rows in the sparse matrix.
            * - ncols
              - Number of columns in the sparse matrix.
            * - nnz
              - Number of non-zero entries in the sparse matrix (which may include explicit zeros).
                This is also the length of the *col_ind* and *val* arrays.
            * - index
              - Parameter that is used to specify whether the matrix has zero or one-based indexing.
            * - val
              - An array of length ``nnz`` that contains the non-zero elements of the sparse matrix
                stored row by row.
            * - col_ind
              - An integer array of length ``nnz``. Contains column indices for non-zero elements
                stored in the *val* array such that *col_ind[i]* is the column number (using zero-
                or one-based indexing) of the element of the sparse matrix stored in *val[i]*.
            * - row_ptr
              - An integer array of size equal to ``nrows + 1``.  Element j of this integer array
                gives the position of the element in the *val* array that is first non-zero element in a
                row j of A. Note that this position is equal to *row_ptr[j] - index*. Last element of
                the *row_ptr* array (*row_ptr[nrows]*) stores the sum of,
                number of nonzero elements and *index* (*nnz* + *index*).


A sparse matrix can be represented in a CSR format in a following way (assuming zero-based indexing):

.. math::
   A = \left(\begin{matrix}
             1 &  0 & 2\\
             0 & -1 & 4\\
             3 &  0 & 0\\
             \end{matrix}\right)


+------------+------------------------------------------------------------+
| nrows      | 3                                                          |
+------------+------------------------------------------------------------+
| ncols      | 3                                                          |
+------------+------------------------------------------------------------+
| nnz        | 5                                                          |
+------------+------------------------------------------------------------+
| index      | 0                                                          |
+------------+------------+-----------+-----------+-----------+-----------+
| row_ptr    | 0          | 2         | 4         | 5         |           |
+------------+------------+-----------+-----------+-----------+-----------+
| col_ind    | 0          | 2         | 1         | 2         | 0         |
+------------+------------+-----------+-----------+-----------+-----------+
| val        | 1          | 2         | -1        | 4         | 3         |
+------------+------------+-----------+-----------+-----------+-----------+


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** :ref:`onemkl_spblas`
