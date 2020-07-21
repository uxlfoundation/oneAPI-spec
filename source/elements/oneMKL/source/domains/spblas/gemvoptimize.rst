.. _onemkl_sparse_optimize_gemv:

optimize_gemv
=============

Performs internal optimizations for oneapi::mkl::sparse::gemv by analyzing
the matrix structure.

.. rubric:: Description and Assumptions

The oneapi::mkl::sparse::optimize_gemv routine analyzes matrix structure
and performs optimizations. Optimized data is then stored in
the handle.


.. _onemkl_sparse_optimize_gemv_buffer:

optimize_gemv (Buffer version)
------------------------------

.. rubric:: Syntax

.. cpp:function::  void oneapi::mkl::sparse::optimize_gemv         (sycl::queue & queue, oneapi::mkl::transpose transpose_val,         matrix_handle_t handle)


.. container:: section

    .. rubric:: Input Parameters

    queue
         Specifies the SYCL command queue which will be used for SYCL
         kernels execution.


    transpose_val
         Specifies operation ``op()`` on input matrix. The possible options
         are described in :ref:`onemkl_enum_transpose` enum class.


    handle
       Handle to object containing sparse matrix and other internal
       data. Created using the
       oneapi::mkl::sparse::set_csr_data routine.


.. container:: section

    .. rubric:: Return Values
       :class: sectiontitle

    None

.. _onemkl_sparse_optimize_gemv_usm:

optimize_gemv (USM version)
---------------------------

.. rubric:: Syntax

.. cpp:function::  sycl::event oneapi::mkl::sparse::optimize_gemv         (sycl::queue & queue, oneapi::mkl::transpose transpose_val,         matrix_handle_t handle, sycl::vector_class<sycl::event> & dependencies)


.. container:: section

    .. rubric:: Input Parameters

    queue
         Specifies the SYCL command queue which will be used for SYCL
         kernels execution.


    transpose_val
         Specifies operation ``op()`` on input matrix. The possible options
         are described in :ref:`onemkl_enum_transpose` enum class.


    handle
       Handle to object containing sparse matrix and other internal
       data. Created using the
       oneapi::mkl::sparse::set_csr_data routine.


    dependencies
       List of events that oneapi::mkl::sparse::optimize_gemv routine depends on.


.. container:: section

    .. rubric:: Return Values
       :class: sectiontitle

    Output event that can be waited upon or added as a
    dependency for the completion of optimize_gemv routine.

.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** :ref:`onemkl_spblas`
