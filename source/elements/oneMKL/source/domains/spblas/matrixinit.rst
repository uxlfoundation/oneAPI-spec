.. SPDX-FileCopyrightText: 2019-2020 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. _onemkl_sparse_init_matrix_handle:

init_matrix_handle
==================


Initializes a matrix_handle_t object to default values.


.. rubric:: Description and Assumptions

The oneapi::mkl::sparse::init_matrix_handle function initializes the
``matrix_handle_t`` object with default values.


.. rubric:: Syntax


.. code-block:: cpp

   namespace oneapi::mkl::sparse {

      void init_matrix_handle (sycl::queue                          &queue,
                               oneapi::mkl::sparse::matrix_handle_t *p_handle);

   }

.. container:: section


    .. rubric:: Input parameters

    queue
       The SYCL command queue which will be used for SYCL kernels execution.

    p_handle
       The address of the sparse::matrix_handle_t ``p_handle`` object to be initialized.
       This initialization routine must only be called on an uninitialized matrix_handle_t object.

.. container:: section

    .. rubric:: Output parameters

    p_handle
       On return, the address is updated to point to a newly allocated and initialized matrix_handle_t object
       that can be filled and used to perform sparse BLAS operations.


.. container:: section

    .. rubric:: Throws
         :class: sectiontitle

    This routine shall throw the following exceptions if the associated condition is detected.
    An implementation may throw additional implementation-specific exception(s)
    in case of error conditions not covered here.

    | :ref:`oneapi::mkl::device_bad_alloc<onemkl_exception_device_bad_alloc>`
    | :ref:`oneapi::mkl::host_bad_alloc<onemkl_exception_host_bad_alloc>`
    | :ref:`oneapi::mkl::invalid_argument<onemkl_exception_invalid_argument>`
    | :ref:`oneapi::mkl::unimplemented<onemkl_exception_unimplemented>`
    | :ref:`oneapi::mkl::uninitialized<onemkl_exception_uninitialized>`
    | :ref:`oneapi::mkl::unsupported_device<onemkl_exception_unsupported_device>`

.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** :ref:`onemkl_spblas`
