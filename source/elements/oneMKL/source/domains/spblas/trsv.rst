.. _onemkl_sparse_trsv:

trsv
====

Solves a system of linear equations for a triangular sparse matrix.

.. rubric:: Description and Assumptions

Refer to :ref:`onemkl_sparse_supported_types` for a
list of supported ``<fp>`` and ``<intType>``.
The oneapi::mkl::sparse::trsv routine solves a system of linear equations
for a square matrix:


::


         op(A)*y =  x


where ``A`` is a triangular sparse matrix of size ``m`` rows by
``m`` columns, op is a matrix modifier for matrix ``A``, ``alpha``
is a scalar, and ``x`` and ``y`` are dense vectors of length at least
``m``.

.. _onemkl_sparse_trsv_buffer:

trsv (Buffer version)
---------------------

.. rubric:: Syntax

.. cpp:function::  void oneapi::mkl::sparse::trsv (sycl::queue & queue,      oneapi::mkl::uplo uplo_val, oneapi::mkl::transpose transpose_val, oneapi::mkl::diag      diag_val, matrix_handle_t handle, sycl::buffer<fp, 1> & x,      sycl::buffer<fp, 1> & y)

.. container:: section


   .. rubric:: Input Parameters


   queue
        Specifies the SYCL command queue which will be used for SYCL
        kernels execution.


   uplo_val
        Specifies which part is to be processed. The possible options are
        described in :ref:`onemkl_enum_uplo` enum class.


   transpose_val
         Specifies operation ``op()`` on input matrix. The possible options
         are described in :ref:`onemkl_enum_transpose` enum class.


   diag_val
            Specifies if the diagonal is unit or not. The possible options
            are described in :ref:`onemkl_enum_diag` enum class.


   handle
      Handle to object containing sparse matrix and other internal
      data. Created using the
      oneapi::mkl::sparse::set_csr_data routine.


   x
        SYCL memory object containing an array of size at least
        equal to the number of columns of input matrix if ``op`` =
        oneapi::mkl::transpose::nontrans and at least the number of rows of
        input matrix otherwise.



   y
        SYCL memory object containing an array of size at least
        equal to the number of rows of input matrix if ``op`` =
        oneapi::mkl::transpose::nontrans and at least the number of columns of
        input matrix otherwise.


.. container:: section


    .. rubric:: Output Parameters
         :class: sectiontitle


    y
       SYCL memory object containing an array of size at least ``nRows`` filled with the solution to the system of linear equations.

.. container:: section

    .. rubric:: Return Values
         :class: sectiontitle

    None

.. _onemkl_sparse_trsv_usm:

trsv (USM version)
------------------

.. rubric:: Syntax

.. cpp:function::  sycl::event oneapi::mkl::sparse::trsv (sycl::queue & queue,      oneapi::mkl::uplo uplo_val, oneapi::mkl::transpose transpose_val, oneapi::mkl::diag      diag_val, matrix_handle_t handle, fp *x, fp *y, const sycl::vector_class<sycl::event> & dependencies = {})


.. container:: section


   .. rubric:: Input Parameters


   queue
        Specifies the SYCL command queue which will be used for SYCL
        kernels execution.


   uplo_val
        Specifies which part is to be processed. The possible options are
        described in :ref:`onemkl_enum_uplo` enum class.


   transpose_val
         Specifies operation ``op()`` on input matrix. The possible options
         are described in :ref:`onemkl_enum_transpose` enum class.


   diag_val
            Specifies if the diagonal is unit or not. The possible options
            are described in :ref:`onemkl_enum_diag` enum class.


   handle
        Handle to object containing sparse matrix and other internal
        data. Created using the
        oneapi::mkl::sparse::set_csr_data routine.


   x
        USM object containing an array of size at least
        equal to the number of columns of input matrix if ``op`` =
        oneapi::mkl::transpose::nontrans and at least the number of rows of
        input matrix otherwise.



   y
        USM object containing an array of size at least
        equal to the number of rows of input matrix if ``op`` =
        oneapi::mkl::transpose::nontrans and at least the number of columns of
        input matrix otherwise.


   dependencies
         List of events that oneapi::mkl::sparse::trmv routine depends on.
         If omitted, defaults to no dependencies.





.. container:: section


    .. rubric:: Output Parameters
         :class: sectiontitle


    y
       USM object containing an array of size at least ``nRows`` filled with the solution to the system of linear equations.

.. container:: section

    .. rubric:: Return Values
         :class: sectiontitle

    Output event that can be waited upon or added as a
    dependency for the completion of trmv routine.

.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** :ref:`onemkl_spblas`


