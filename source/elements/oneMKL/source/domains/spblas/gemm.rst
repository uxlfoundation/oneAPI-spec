.. SPDX-FileCopyrightText: 2019-2020 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. _onemkl_sparse_gemm:

gemm
====

Computes a sparse matrix times dense matrix product.

.. rubric:: Description and Assumptions

Refer to :ref:`onemkl_sparse_supported_types` for a list of supported ``<fp>`` and ``<intType>`` types. The oneapi::mkl::sparse::gemm routine computes a sparse matrix-dense
matrix product defined as

.. math::

   C \leftarrow \alpha \cdot \text{op}(A) \cdot \text{op}(B) + \beta \cdot C

where :math:`\alpha` and :math:`\beta` are scalars, :math:`A` is a sparse matrix, :math:`B` and :math:`C` are dense matrices, :math:`\text{op}()` is a matrix modifier for :math:`A` and :math:`B` using the following description:

.. math::

    \text{op}(A) = \begin{cases} A,& \text{ oneapi::mkl::transpose::nontrans}\\ A^{T},& \text{ oneapi::mkl::transpose::trans}\\A^{H},& \text{ oneapi::mkl::transpose::conjtrans} \end{cases}


and :math:`\text{op}(A)` is an ``m``-by-``k`` matrix , :math:`\text{op}(B)` is an ``k``-by-``columns`` matrix, and :math:`C` is an ``m``-by-``columns`` matrix.

Dense matrix storage is in either row-major or column-major format. Sparse matrix formats are compressed sparse row (CSR) formats. 


.. _onemkl_sparse_gemm_buffer:

gemm (Buffer version)
---------------------

.. rubric:: Syntax

.. code-block:: cpp

   namespace oneapi::mkl::sparse {

      void gemm (sycl::queue                          &queue, 
                 oneapi::mkl::layout                  dense_matrix_layout, 
                 oneapi::mkl::transpose               transpose_A, 
                 oneapi::mkl::transpose               transpose_B, 
                 const fp                             alpha, 
                 oneapi::mkl::sparse::matrix_handle_t A_handle, 
                 sycl::buffer<fp, 1>                  &B, 
                 const std::int64_t                   columns, 
                 const std::int64_t                   ldb, 
                 const fp                             beta, 
                 sycl::buffer<fp, 1>                  &C, 
                 const std::int64_t                   ldc);

   }



.. container:: section

    .. rubric:: Input parameters

    queue
         Specifies the SYCL command queue which will be used for SYCL
         kernels execution.


    dense_matrix_layout
         Specifies the storage scheme in memory for the dense matrices. Note that this layout applies to both :math:`B` and :math:`C` dense matrices.
         The possible options are described in :ref:`onemkl_enum_layout` enum class.


    transpose_A
         Specifies operation ``op()`` on input matrix :math:`A`. The possible options
         are described in :ref:`onemkl_enum_transpose` enum class.


    transpose_B
         Specifies operation ``op()`` on input matrix :math:`B`. The possible options
         are described in :ref:`onemkl_enum_transpose` enum class.


    alpha
         Specifies the scalar :math:`\alpha`.


    A_handle
         Handle to object containing sparse matrix, :math:`A`. Created using the oneapi::mkl::sparse::set_csr_data routine.


    B
         The input dense matrix :math:`B` in the sparse matrix-dense matrix product. :math:`B` is a one dimensional SYCL memory object containing an array of size:

      .. list-table::
         :header-rows: 1

         * -
           - ``B`` not transposed
           - ``B`` transposed
         * - Row major
           - ``B`` is an ``k``-by-``columns`` matrix so must have size at least ``k``\ \*\ ``ldb``.
           - ``B`` is an ``columns``-by-``k`` matrix so must have size at least ``columns``\ \*\ ``ldb``
         * - Column major
           - ``B`` is an ``k``-by-``columns`` matrix so must have size at least ``ldb``\ \*\ ``columns``.
           - ``B`` is an ``columns``-by-``k`` matrix so must have size at least ``ldb``\ \*\ ``k``
      
      See :ref:`matrix-storage` for more details.


    columns
         Number of columns of matrix :math:`C`.


    ldb
         Specifies the leading dimension of matrix :math:`B`. It must be positive.

      .. list-table::
         :header-rows: 1

         * -
           - ``B`` not transposed
           - ``B`` transposed
         * - Row major
           - ``ldb`` must be at least ``columns``.
           - ``ldb`` must be at least ``k``.
         * - Column major
           - ``ldb`` must be at least ``k``.
           - ``ldb`` must be at least ``columns``.


    beta
         Specifies the scalar ``beta``.


    C
         The dense matrix input/output array.  A one-dimensional SYCL memory object containing an array of size at least ``m``\ \*\ ``ldc`` if row_major layout is used to store dense matrices
         or at least ``ldc``\ \*\ ``columns`` if column_major layout is used to store dense matrices.


    ldc
         Specifies the leading dimension of matrix :math:`C`.
         Must be positive and at least ``columns`` if row major layout is used to store dense matrices or at least ``m`` if column major layout is used to store dense matrices.


.. container:: section

    .. rubric:: Output Parameters
         :class: sectiontitle


    C
       Dense matrix output is overwritten by the updated matrix, :math:`C`.

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

.. _onemkl_sparse_gemm_usm:

gemm (USM version)
---------------------

.. rubric:: Syntax

.. code-block:: cpp

   namespace oneapi::mkl::sparse {

      sycl::event gemm (sycl::queue                           &queue, 
                        oneapi::mkl::layout                   dense_matrix_layout, 
                        oneapi::mkl::transpose                transpose_A, 
                        oneapi::mkl::transpose                transpose_B, 
                        const fp                              alpha, 
                        oneapi::mkl::sparse::matrix_handle_t  A_handle, 
                        const fp                              *B, 
                        const std::int64_t                    columns, 
                        const std::int64_t                    ldb, 
                        const fp                              beta, 
                        const fp                              *C, 
                        const std::int64_t                    ldc,
                        const std::vector<sycl::event>        &dependencies = {});

   }


.. container:: section

    .. rubric:: Input parameters

    queue
         Specifies the SYCL command queue which will be used for SYCL
         kernels execution.


    dense_matrix_layout
         Specifies the storage scheme in memory for the dense matrices. Note that this layout applies to both :math:`B` and :math:`C` dense matrices.
         The possible options are described in :ref:`onemkl_enum_layout` enum class.


    transpose_A
         Specifies operation ``op()`` on input matrix :math:`A`. The possible options
         are described in :ref:`onemkl_enum_transpose` enum class.


    transpose_B
         Specifies operation ``op()`` on input matrix :math:`B`. The possible options
         are described in :ref:`onemkl_enum_transpose` enum class.


    alpha
         Specifies the scalar :math:`\alpha`.


    A_handle
         Handle to object containing sparse matrix, :math:`A`. Created using the oneapi::mkl::sparse::set_csr_data routine.


    B 
         The dense matrix in the sparse-dense matrix product. A device accessible USM object containing an array of size:

      .. list-table::
         :header-rows: 1

         * -
           - ``B`` not transposed
           - ``B`` transposed
         * - Row major
           - ``B`` is an ``k``-by-``columns`` matrix so must have size at least ``k``\ \*\ ``ldb``.
           - ``B`` is an ``columns``-by-``k`` matrix so must have size at least ``columns``\ \*\ ``ldb``
         * - Column major
           - ``B`` is an ``k``-by-``columns`` matrix so must have size at least ``ldb``\ \*\ ``columns``.
           - ``B`` is an ``columns``-by-``k`` matrix so must have size at least ``ldb``\ \*\ ``k``
      
      See :ref:`matrix-storage` for more details.


    columns
         Number of columns of matrix :math:`C`.


    ldb
         Specifies the leading dimension of matrix :math:`B`. It must be positive.

      .. list-table::
         :header-rows: 1

         * -
           - ``B`` not transposed
           - ``B`` transposed
         * - Row major
           - ``ldb`` must be at least ``columns``.
           - ``ldb`` must be at least ``k``.
         * - Column major
           - ``ldb`` must be at least ``k``.
           - ``ldb`` must be at least ``columns``.


    beta
         Specifies the scalar ``beta``.


    C
         The dense matrix input/output array.  A device accessible USM object containing an array of size at least ``m``\ \*\ ``ldc`` if row_major layout is used to store dense matrices
         or at least ``ldc``\ \*\ ``columns`` if column_major layout is used to store dense matrices.

    ldc
         Specifies the leading dimension of matrix :math:`C`.
         Must be positive and at least ``columns`` if row major layout is used to store dense matrices or at least ``m`` if column major layout is used to store dense matrices.

    dependencies
         List of events that oneapi::mkl::sparse::gemm routine depends on.
         If omitted, defaults to no dependencies.

.. container:: section

    .. rubric:: Output Parameters
         :class: sectiontitle


    C
       Dense matrix output is overwritten by the updated matrix :math:`C`.


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

.. container:: section

    .. rubric:: Return Values
         :class: sectiontitle

    Output event that can be waited upon or added as a
    dependency for the completion of gemm routine.


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** :ref:`onemkl_spblas`
