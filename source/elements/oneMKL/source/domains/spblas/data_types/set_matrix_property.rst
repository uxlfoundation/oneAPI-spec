.. SPDX-FileCopyrightText: 2024 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. _onemkl_sparse_set_matrix_property:

set_matrix_property
===================

Matrix properties
-----------------

.. container:: section

   .. code:: cpp

      namespace oneapi::mkl::sparse {

          enum class matrix_property {
             symmetric,
             sorted,
          };

      }

   Matrix properties are optional and "strong" guarantees. Unlike
   :ref:`onemkl_sparse_matrix_view`, the user must ensure that the handle's data
   holds all the given properties. A property can be set as a hint for backends
   to optimize some operations. Multiple properties can be set to the same handle.

   .. list-table::
      :header-rows: 1
      :widths: 20 80

      * - Value
        - Description
      * - ``symmetric``
        - Guarantees that the user-provided matrix data are symmetric, meaning
          the matrix is square, the user data contain both lower and upper
          triangular regions, and that its transpose is equal to itself.
      * - ``sorted``
        - | Guarantees that the user-provided matrix data has some sorting
            property.
          | For CSR this guarantees that the column indices are sorted in
            ascending order for a given row.
          | For COO this guarantees that the indices are sorted by row then by
            column in ascending order.

set_matrix_property
-------------------

Set a property to a ``matrix_handle_t`` object.

.. rubric:: Description and Assumptions

The ``oneapi::mkl::sparse::set_matrix_property`` function sets a property to a
matrix handle.

.. rubric:: Syntax

.. code-block:: cpp

   namespace oneapi::mkl::sparse {

       bool set_matrix_property (sycl::queue                          &queue,
                                 oneapi::mkl::sparse::matrix_handle_t smhandle,
                                 matrix_property                      property);

   }

.. container:: section

   .. rubric:: Input parameters

   queue
      The SYCL command queue which will be used for SYCL kernels execution.

   smhandle
      Initialized sparse matrix handle.

   property
      Matrix property to set.

.. container:: section

   .. rubric:: Return Values

   Return whether the property was set to the backend's handle. A backend may
   not have an equivalent property.

.. container:: section

   .. rubric:: Throws

   This function shall throw the following exceptions if the associated
   condition is detected. An implementation may throw additional
   implementation-specific exception(s) in case of error conditions not covered
   here.

   | :ref:`oneapi::mkl::invalid_argument<onemkl_exception_invalid_argument>`
   | :ref:`oneapi::mkl::unimplemented<onemkl_exception_unimplemented>`
   | :ref:`oneapi::mkl::uninitialized<onemkl_exception_uninitialized>`
   | :ref:`oneapi::mkl::unsupported_device<onemkl_exception_unsupported_device>`

**Parent topic:** :ref:`onemkl_sparse_data_handles`
