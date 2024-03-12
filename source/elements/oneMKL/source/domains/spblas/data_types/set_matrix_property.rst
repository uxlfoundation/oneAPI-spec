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

      enum class matrix_property {
          symmetric,
          sorted,
      };

   TODO: Clarify are the properties meant to be used as a bit mask so multiple
   properties can be set?

   .. list-table::
      :header-rows: 1
      :widths: 20 80

      * - Value
        - Description
      * - ``symmetric``
        - Guarantees that the matrix is symmetric, meaning it must be square and
          its transpose is equal to itself. TODO: Confirm whether the user can
          only provide half of the data in this case?
      * - ``sorted``
        - Guarantees that the column indices are sorted for a given row. Only
          available for the CSR format. TODO: Confirm the description.

set_matrix_property
-------------------

Set a property to a ``matrix_handle_t`` object.

.. rubric:: Description and Assumptions

The ``oneapi::mkl::sparse::set_matrix_property`` function sets a property to a
matrix handle. The property provides stronger guarantees than a :ref:`onemkl_sparse_matrix_view`.

.. rubric:: Syntax

.. code-block:: cpp

   namespace oneapi::mkl::sparse {

       bool set_matrix_property (sycl::queue                          &queue,
                                 oneapi::mkl::sparse::matrix_handle_t smhandle,
                                 matrix_property                      property_value);

   }

.. container:: section

   .. rubric:: Input parameters

   queue
      The SYCL command queue which will be used for SYCL kernels execution.

   smhandle
      Initialized sparse matrix handle.

   property_value
      Matrix property to set.

.. container:: section

   .. rubric:: Return Values

   Return whether the property was set to the backend's handle. A backend may
   not have equivalent properties.

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
