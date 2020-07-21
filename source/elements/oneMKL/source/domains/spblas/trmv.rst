.. _onemkl_sparse_trmv:

trmv
====

Computes a sparse matrix-dense vector product over upper or lower triangular matrix parts.

.. rubric:: Description and Assumptions

Refer to :ref:`onemkl_sparse_supported_types` for a
list of supported ``<fp>`` and ``<intType>``.
The oneapi::mkl::sparse::trmv routine computes a sparse matrix-dense vector
product over a triangular part defined as

::

                     y := alpha*op(A)*x + beta*y


where:


``alpha`` and ``beta`` are scalars, ``x`` and ``y`` are dense vectors, ``A`` is a sparse matrix.


.. _onemkl_sparse_trmv_buffer:

trmv (Buffer version)
---------------------

.. rubric:: Syntax

.. cpp:function::  void oneapi::mkl::sparse::trmv (sycl::queue &         queue, oneapi::mkl::uplo uplo_val, oneapi::mkl::transpose transpose_val,         oneapi::mkl::diag diag_val, fp alpha, matrix_handle_t handle,         sycl::buffer<fp, 1> & x, fp beta, sycl::buffer<fp, 1> &         y)

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


   alpha
        Specifies the scalar ``alpha``.


   handle
      Handle to object containing sparse matrix and other internal
      data. Created using the
      oneapi::mkl::sparse::set_csr_data routine.


   x
        SYCL memory object containing an array of size at least
        equal to the number of columns of input matrix if ``op`` =
        oneapi::mkl::transpose::nontrans and at least the number of rows of
        input matrix otherwise.


   beta
        Specifies the scalar ``beta``.


   y
        SYCL memory object containing an array of size at least
        equal to the number of rows of input matrix if ``op`` =
        oneapi::mkl::transpose::nontrans and at least the number of columns of
        input matrix otherwise.


.. container:: section


    .. rubric:: Output Parameters
         :class: sectiontitle


    y
       Overwritten by the updated vector ``y``.

.. container:: section

    .. rubric:: Return Values
         :class: sectiontitle

    None

.. _onemkl_sparse_trmv_usm:

trmv (USM version)
------------------

.. rubric:: Syntax

.. cpp:function::  sycl::event oneapi::mkl::sparse::trmv (sycl::queue &         queue, oneapi::mkl::uplo uplo_val, oneapi::mkl::transpose transpose_val,         oneapi::mkl::diag diag_val, fp alpha, matrix_handle_t handle, fp *x, fp         beta, fp *y, const sycl::vector_class<sycl::event> & dependencies = {})

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


   alpha
        Specifies the scalar ``alpha``.


   handle
        Handle to object containing sparse matrix and other internal
        data. Created using the
        oneapi::mkl::sparse::set_csr_data routine.


   x
        USM object containing an array of size at least
        equal to the number of columns of input matrix if ``op`` =
        oneapi::mkl::transpose::nontrans and at least the number of rows of
        input matrix otherwise.



   beta
        Specifies the scalar ``beta``.


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
       Overwritten by the updated vector ``y``.

.. container:: section

    .. rubric:: Return Values
         :class: sectiontitle

    Output event that can be waited upon or added as a
    dependency for the completion of trmv routine.


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** :ref:`onemkl_spblas`

