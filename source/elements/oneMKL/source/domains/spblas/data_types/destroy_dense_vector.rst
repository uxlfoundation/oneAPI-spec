.. SPDX-FileCopyrightText: 2024 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. _onemkl_sparse_destroy_dense_vector:

destroy_dense_vector
====================

Destroys a ``dense_vector_handle_t`` object.

.. rubric:: Description and Assumptions

The ``oneapi::mkl::sparse::destroy_dense_vector`` function frees the resources
allocated for the handle.

If a buffer was provided, its reference count is decremented.

If a USM pointer was provided, the data is not free'd.

.. rubric:: Syntax

.. code-block:: cpp

   namespace oneapi::mkl::sparse {

       void destroy_dense_vector (sycl::queue                                &queue,
                                  oneapi::mkl::sparse::dense_vector_handle_t dvhandle);

   }

.. container:: section

   .. rubric:: Input parameters

   queue
      The SYCL command queue which will be used for SYCL kernels execution.

   dvhandle
      Handle initialized with :ref:`onemkl_sparse_create_dense_vector`.

.. container:: section

   .. rubric:: Throws

   This function shall throw the following exceptions if the associated
   condition is detected. An implementation may throw additional
   implementation-specific exception(s) in case of error conditions not covered
   here.

   | :ref:`oneapi::mkl::invalid_argument<onemkl_exception_invalid_argument>`
   | :ref:`oneapi::mkl::unimplemented<onemkl_exception_unimplemented>`
   | :ref:`oneapi::mkl::unsupported_device<onemkl_exception_unsupported_device>`

**Parent topic:** :ref:`onemkl_sparse_data_handles`
