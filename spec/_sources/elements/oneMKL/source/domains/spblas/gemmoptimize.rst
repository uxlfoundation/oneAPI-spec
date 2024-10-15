.. SPDX-FileCopyrightText: 2023 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. _onemkl_sparse_optimize_gemm:

optimize_gemm
=============

Performs internal optimizations for oneapi::mkl::sparse::gemm by analyzing
the matrix structure.

.. rubric:: Description and Assumptions

The oneapi::mkl::sparse::optimize_gemm routine analyzes matrix structure
and performs optimizations. Optimized data is then stored in
the handle.

In contrast to other optimization routines in Sparse BLAS domain
which are done solely based on the sparse matrix pattern, 
two versions of the ``sparse::optimize_gemm`` routine are provided for preparing different
optimizations for ``sparse::gemm`` routine.  In particular, if the shape
of the dense matrix right hand side, :math:`B`, is unknown or widely varying in 
subsequent calls to ``sparse::gemm`` then a user might reasonably
only wish to perform optimizations for ``:sparse::gemm`` with respect 
to the sparse matrix structure.  However, if one or more particular shapes of :math:`B` 
is available, then each :math:`B` shape can be provided as an additional hint 
along with the sparse matrix pattern in the call to ``sparse::optimize_gemm``.  This 
second version of the API with :math:`B` shape should be callable one or 
more times and may allow libraries to provide more targeted performance 
optimizations.

.. _onemkl_sparse_optimize_gemm_A:

optimize_gemm (based on Sparse Matrix)
--------------------------------------

.. rubric:: Syntax

.. code-block:: cpp

   namespace oneapi::mkl::sparse {

      sycl::event optimize_gemm (sycl::queue                          &queue,
                                 oneapi::mkl::transpose               transpose_A,
                                 oneapi::mkl::sparse::matrix_handle_t A_handle,
                                 const std::vector<sycl::event>       &dependencies = {});

   }

.. container:: section

    .. rubric:: Input Parameters

    queue
         Specifies the SYCL command queue which will be used for SYCL
         kernels execution.


    transpose_A
         Specifies operation ``op()`` on input matrix :math:`A`. The possible options
         are described in :ref:`onemkl_enum_transpose` enum class.


    A_handle
       Handle to object containing sparse matrix and other internal
       data. Created using one of ``oneapi::mkl::sparse::set_csr_data`` or
       ``oneapi::mkl::sparse::set_coo_data`` routines.


    dependencies
       List of events that oneapi::mkl::sparse::optimize_gemm routine depends on.


.. container:: section

    .. rubric:: Output Parameters
         :class: sectiontitle

    handle
        Handle might be updated with some internal optimized data by this routine.

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
    dependency for the completion of optimize_gemm routine.


.. _onemkl_sparse_optimize_gemm_AB:

optimize_gemm (based on Both Input Matrices)
--------------------------------------------

.. rubric:: Syntax

.. code-block:: cpp

   namespace oneapi::mkl::sparse {

      sycl::event optimize_gemm (sycl::queue                          &queue,
                                 oneapi::mkl::transpose               transpose_A,
                                 oneapi::mkl::transpose               transpose_B,
                                 oneapi::mkl::layout                  dense_matrix_layout,
                                 const std::int64_t                   columns,
                                 oneapi::mkl::sparse::matrix_handle_t A_handle,
                                 const std::vector<sycl::event>       &dependencies = {});

   }

.. container:: section

    .. rubric:: Input Parameters

    queue
         Specifies the SYCL command queue which will be used for SYCL
         kernels execution.


    transpose_A
         Specifies operation ``op()`` on input matrix :math:`A`. The possible options
         are described in :ref:`onemkl_enum_transpose` enum class.


    transpose_B
         Specifies operation ``op()`` on input matrix :math:`B`. The possible options
         are described in :ref:`onemkl_enum_transpose` enum class.


    dense_matrix_layout
         Specifies the storage scheme in memory for the dense matrices. Note that this layout applies to both :math:`B` and :math:`C` dense matrices.
         The possible options are described in :ref:`onemkl_enum_layout` enum class.


    columns
         Number of columns of matrix :math:`C`.


    handle
       Handle to object containing sparse matrix and other internal
       data. Created using one of ``oneapi::mkl::sparse::set_csr_data`` or
       ``oneapi::mkl::sparse::set_coo_data`` routines.


    dependencies
       List of events that oneapi::mkl::sparse::optimize_gemm routine depends on.


.. container:: section

    .. rubric:: Output Parameters
         :class: sectiontitle

    handle
        Handle might be updated with some internal optimized data by this routine.

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
    dependency for the completion of optimize_gemm routine.


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** :ref:`onemkl_spblas`
