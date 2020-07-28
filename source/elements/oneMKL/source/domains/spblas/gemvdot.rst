.. _onemkl_sparse_gemvdot:

gemvdot
=======

Computes a sparse matrix-dense vector product with dot product.

.. rubric:: Description and Assumptions

Refer to :ref:`onemkl_sparse_supported_types` for a
list of supported ``<fp>`` and ``<intType>``.
The oneapi::mkl::sparse::gemvdot routine computes a sparse
matrix-dense vector product and dot product defined as

::

            y := alpha*op(A)*x + beta*y

::


            d := x * y


where:


``A`` is a general sparse matrix, ``alpha``, ``beta``, and
``d`` are scalars, ``x`` and ``y`` are dense vectors.

.. _onemkl_sparse_gemvdot_buffer:

gemvdot (Buffer version)
------------------------

.. rubric:: Syntax

.. cpp:function::  void oneapi::mkl::sparse::gemvdot (sycl::queue &         queue, oneapi::mkl::transpose transpose_val, fp alpha, matrix_handle_t         handle, sycl::buffer<fp, 1> & x, fp beta,         sycl::buffer<fp, 1> & y, sycl::buffer<fp, 1> & d)


.. container:: section

    .. rubric:: Input Parameters

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

    d
       SYCL scalar memory object used to store the result of dot product.

.. container:: section

    .. rubric:: Output Parameters
         :class: sectiontitle

    y
       Overwritten by the updated vector ``y``.

    d
       Overwritten by the dot product of ``x`` and ``y``.


.. container:: section

    .. rubric:: Return Values
       :class: sectiontitle

    None

.. _onemkl_sparse_gemvdot_usm:

gemvdot (USM version)
------------------------

.. rubric:: Syntax

.. cpp:function::  sycl::event oneapi::mkl::sparse::gemvdot (sycl::queue &         queue, oneapi::mkl::transpose transpose_val, fp alpha, matrixHandle_t         handle, fp *x, fp beta, fp *y, fp *d, const sycl::vector_class<sycl::event> & dependencies = {})

.. container:: section

    .. rubric:: Input Parameters

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

    d
       USM scalar object used to store the result of dot product.

    dependencies
       List of events that oneapi::mkl::sparse::gemvdot routine depends on.
       If omitted, defaults to no dependencies.

.. container:: section

    .. rubric:: Output Parameters
         :class: sectiontitle

    y
       Overwritten by the updated vector ``y``.

    d
       Overwritten by the dot product of ``x`` and ``y``.


.. container:: section

    .. rubric:: Return Values
       :class: sectiontitle

    Output event that can be waited upon or added as a
    dependency for the completion of gemvdot routine.


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** :ref:`onemkl_spblas`

