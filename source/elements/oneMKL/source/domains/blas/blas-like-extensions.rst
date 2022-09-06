.. SPDX-FileCopyrightText: 2019-2020 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. _blas-like-extensions:

BLAS-like Extensions
====================


.. container::


   oneAPI Math Kernel Library DPC++ provides additional routines to
   extend the functionality of the BLAS routines. These include routines
   to compute many independent vector-vector and matrix-matrix operations.

   The following table lists the BLAS-like extensions with their descriptions.


   .. container:: tablenoborder


      .. list-table:: 
         :header-rows: 1

         * -     Routines
           -     Description     
         * -     :ref:`onemkl_blas_axpy_batch`   
           -     Computes groups of vector-scalar products added to a vector.
         * -     :ref:`onemkl_blas_gemm_batch`   
           -     Computes groups of matrix-matrix products with general matrices.   
         * -     :ref:`onemkl_blas_trsm_batch`   
           -     Solves a triangular matrix equation for a group of matrices.   
         * -     :ref:`onemkl_blas_gemmt`   
           -     Computes a matrix-matrix product with general matrices, but updates
                 only the upper or lower triangular part of the result matrix.
         * -     :ref:`onemkl_blas_gemm_bias`   
           -     Computes a matrix-matrix product using general integer matrices with bias
         * -     :ref:`onemkl_blas_imatcopy`
           -     Computes an in-place matrix transposition or copy.
         * -     :ref:`onemkl_blas_omatcopy`
           -     Computes an out-of-place matrix transposition or copy.
         * -     :ref:`onemkl_blas_omatcopy2`
           -     Computes a two-strided out-of-place matrix transposition or copy.
         * -     :ref:`onemkl_blas_omatadd`
           -     Computes scaled matrix addition with possibly transposed arguments.
         * -     :ref:`onemkl_blas_imatcopy_batch`
           -     Computes groups of in-place matrix transposition or copy operations.
         * -     :ref:`onemkl_blas_omatcopy_batch`
           -     Computes groups of out-of-place matrix transposition or copy operations.
         * -     :ref:`onemkl_blas_omatadd_batch`
           -     Computes groups of scaled matrix additions.
 




.. toctree::
    :hidden:

    axpy_batch
    axpby
    copy_batch
    dgmm_batch
    gemm_batch
    gemv_batch
    syrk_batch
    trsm_batch
    gemmt
    gemm_bias
    imatcopy
    omatcopy
    omatcopy2
    omatadd
    imatcopy_batch
    omatcopy_batch
    omatadd_batch

**Parent topic:** :ref:`onemkl_blas`
