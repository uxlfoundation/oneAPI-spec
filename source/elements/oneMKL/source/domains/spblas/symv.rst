.. _onemkl_sparse_symv:

symv
====

Computes a sparse matrix-dense vector product for a symmetric part of the sparse matrix.

.. rubric:: Description and Assumptions

Refer to :ref:`onemkl_sparse_supported_types` for a
list of supported ``<fp>`` and ``<intType>``.
The oneapi::mkl::sparse::symv routine computes a sparse matrix-dense vector
product over a symmetric part defined as

::

                     y := alpha*A*x + beta*y


where:


``alpha`` and ``beta`` are scalars, ``x`` and ``y`` are dense vectors, ``A`` is a sparse matrix.

.. _onemkl_sparse_symv_buffer:

symv (Buffer version)
---------------------

.. rubric:: Syntax

.. cpp:function::  void oneapi::mkl::sparse::symv (sycl::queue &         queue, oneapi::mkl::uplo uplo_val, fp alpha, matrix_handle_t handle,         sycl::buffer<fp, 1> & x, fp beta, sycl::buffer<fp, 1> &         y)

.. container:: section


   .. rubric:: Input Parameters


   queue
        Specifies the SYCL command queue which will be used for SYCL
        kernels execution.


   uplo_val
        Specifies which part is to be processed. The possible options are
        described in :ref:`onemkl_enum_uplo` enum class.


   alpha
        Specifies the scalar ``alpha``.


   handle
      Handle to object containing sparse matrix and other internal
      data. Created using the
      oneapi::mkl::sparse::set_csr_data routine.


   x
        SYCL memory object containing an array of size at
        least equal to the number of columns of input matrix.


   beta
        Specifies the scalar ``beta``.


   y
        SYCL memory object containing an array of size at
        least equal to the number of rows of input matrix.


.. container:: section


    .. rubric:: Output Parameters
         :class: sectiontitle


    y
       Overwritten by the updated vector ``y``.

.. container:: section

    .. rubric:: Return Values
         :class: sectiontitle

    None

.. _onemkl_sparse_symv_usm:

symv (USM version)
------------------

.. rubric:: Syntax

.. cpp:function::  sycl::event oneapi::mkl::sparse::symv (sycl::queue &         queue, oneapi::mkl::uplo uplo_val, fp alpha, matrix_handle_t handle, fp         *x, fp beta, fp *y, const sycl::vector_class<sycl::event> & dependencies = {})

.. container:: section


   .. rubric:: Input Parameters


   queue
        Specifies the SYCL command queue which will be used for SYCL
        kernels execution.


   uplo_val
        Specifies which part is to be processed. The possible options are
        described in :ref:`onemkl_enum_uplo` enum class.


   alpha
        Specifies the scalar ``alpha``.


   handle
        Handle to object containing sparse matrix and other internal
        data. Created using the
        oneapi::mkl::sparse::set_csr_data routine.


   x
        USM object containing an array of size at
        least equal to the number of columns of input matrix.


   beta
        Specifies the scalar ``beta``.


   y
        USM object containing an array of size at
        least equal to the number of rows of input matrix.

   dependencies
         List of events that oneapi::mkl::sparse::symv routine depends on.
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
    dependency for the completion of symv routine.


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** :ref:`onemkl_spblas`


   
