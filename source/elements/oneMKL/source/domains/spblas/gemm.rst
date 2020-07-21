.. _onemkl_sparse_gemm:

gemm
====

Computes a sparse matrix-dense matrix product. Currently, only
ROW-MAJOR layout for dense matrix storage in Data Parallel C++
oneapi::mkl::sparse::gemm functionality is assumed.

.. rubric:: Description and Assumptions

Refer to :ref:`onemkl_sparse_supported_types` for a
list of supported ``<fp>`` and ``<intType>``.
The oneapi::mkl::sparse::gemm routine computes a sparse matrix-dense
matrix product defined as


::

               c := alpha*op(A)*b + beta*c



where:


``alpha`` and ``beta`` are scalars, ``b`` and ``c`` are dense
matrices. ``A`` is a sparse matrix.


.. _onemkl_sparse_gemm_buffer:

gemm (Buffer version)
---------------------

.. rubric:: Syntax

.. cpp:function::  void oneapi::mkl::sparse::gemm (sycl::queue & queue, oneapi::mkl::transpose transpose_val, const fp alpha, matrix_handle_t handle, sycl::buffer<fp, 1> & b, const std::int64_t columns, const std::int64_t ldb, const fp beta, sycl::buffer<fp, 1> & c, const std::int64_t ldc)


.. container:: section

    .. rubric:: Input parameters

    queue
         Specifies the SYCL command queue which will be used for SYCL
         kernels execution.


    transpose_val
         Specifies operation ``op()`` on input matrix. The possible options
         are described in :ref:`onemkl_enum_transpose` enum class.


    alpha
         Specifies the scalar ``alpha``.


    handle
         Handle to object containing sparse matrix and other internal
         data. Created using the
         oneapi::mkl::sparse::set_csr_data routine.


    b
         SYCL memory object containing an array of size at
         least ``rows*ldb``, where ``rows`` = the number of columns
         of matrix ``A`` if ``op`` = oneapi::mkl::transpose::nontrans, or
         ``rows`` = the number of rows of matrix ``A`` otherwise.


    columns
         Number of columns of matrix ``c``.


    ldb
         Specifies the leading dimension of matrix ``b``.


    beta
         Specifies the scalar ``beta``.


    c
         SYCL memory object containing an array of size at
         least ``rows*ldc``, where ``rows`` = the number of rows
         of matrix ``A`` if ``op`` = oneapi::mkl::transpose::nontrans, or
         ``rows`` = the number of columns of matrix ``A`` otherwise.

    ldc
         Specifies the leading dimension of matrix ``c`` . Must be
         equal to  ``columns`` , and it must be positive.


.. container:: section

    .. rubric:: Output Parameters
         :class: sectiontitle


    c
       Overwritten by the updated matrix ``c``.

.. container:: section

    .. rubric:: Return Values
       :class: sectiontitle

    None

.. _onemkl_sparse_gemm_usm:

gemm (USM version)
---------------------

.. rubric:: Syntax

.. cpp:function::  sycl::event oneapi::mkl::sparse::gemm (sycl::queue & queue, oneapi::mkl::transpose transpose_val, const fp alpha, matrix_handle_t handle, const fp *b, const std::int64_t columns, const std::int64_t ldb, const fp beta, fp *c, const std::int64_t ldc, const sycl::vector_class<sycl::event> & dependencies = {})


.. container:: section

    .. rubric:: Input parameters

    queue
         Specifies the SYCL command queue which will be used for SYCL
         kernels execution.


    transpose_val
         Specifies operation ``op()`` on input matrix. The possible options
         are described in :ref:`onemkl_enum_transpose` enum class.


    alpha
         Specifies the scalar ``alpha``.


    handle
         Handle to object containing sparse matrix and other internal
         data. Created using the
         oneapi::mkl::sparse::set_csr_data routine.


    b
         USM object containing an array of size at
         least ``rows*ldb``, where ``rows`` = the number of columns
         of matrix ``A`` if ``op`` = oneapi::mkl::transpose::nontrans, or
         ``rows`` = the number of rows of matrix ``A`` otherwise.


    columns
         Number of columns of matrix ``c``.


    ldb
         Specifies the leading dimension of matrix ``b``.


    beta
         Specifies the scalar ``beta``.


    c
         USM object containing an array of size at
         least ``rows*ldc``, where ``rows`` = the number of rows
         of matrix ``A`` if ``op`` = oneapi::mkl::transpose::nontrans, or
         ``rows`` = the number of columns of matrix ``A`` otherwise.

    ldc
         Specifies the leading dimension of matrix ``c`` . Must be
         equal to ``columns`` , and it must be positive.

    dependencies
         List of events that oneapi::mkl::sparse::gemm routine depends on.
         If omitted, defaults to no dependencies.

.. container:: section

    .. rubric:: Output Parameters
         :class: sectiontitle


    c
       Overwritten by the updated matrix ``c``.

.. container:: section

    .. rubric:: Return Values
         :class: sectiontitle

    Output event that can be waited upon or added as a
    dependency for the completion of gemm routine.


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** :ref:`onemkl_spblas`
