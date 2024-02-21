.. SPDX-FileCopyrightText: 2024 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. _onemkl_sparse_data_handles:

Data handles
============

.. _onemkl_sparse_dense_vector_handle:

Dense vector handle
-------------------

.. rubric:: Definition

.. code-block:: cpp

   namespace oneapi::mkl::sparse {

       struct dense_vector_handle;
       using dense_vector_handle_t = dense_vector_handle*;

   }

.. container:: section

   .. rubric:: Description

   Defines ``dense_vector_handle_t`` as an opaque pointer to the incomplete type
   ``dense_vector_handle``. Each backend may provide a different
   implementation of the type ``dense_vector_handle``.

   See related functions:

   - :ref:`onemkl_sparse_create_dense_vector`
   - :ref:`onemkl_sparse_set_dense_vector_data`
   - :ref:`onemkl_sparse_destroy_dense_vector`

.. _onemkl_sparse_dense_matrix_handle:

Dense matrix handle
-------------------

.. rubric:: Definition

.. code-block:: cpp

   namespace oneapi::mkl::sparse {

       struct dense_matrix_handle;
       using dense_matrix_handle_t = dense_matrix_handle*;

   }

.. container:: section

   .. rubric:: Description

   Defines ``dense_matrix_handle_t`` as an opaque pointer to the incomplete type
   ``dense_matrix_handle``. Each backend may provide a different
   implementation of the type ``dense_matrix_handle``.

   See related functions:

   - :ref:`onemkl_sparse_create_dense_matrix`
   - :ref:`onemkl_sparse_set_dense_matrix_data`
   - :ref:`onemkl_sparse_destroy_dense_matrix`

.. _onemkl_sparse_matrix_handle:

Sparse matrix handle
--------------------

.. rubric:: Definition

.. code-block:: cpp

   namespace oneapi::mkl::sparse {

       struct matrix_handle;
       using matrix_handle_t = matrix_handle*;

   }

.. container:: section

   .. rubric:: Description

   Defines ``matrix_handle_t`` as an opaque pointer to the incomplete type
   ``matrix_handle``. Each backend may provide a different
   implementation of the type ``matrix_handle``.

   See related functions:

   - :ref:`onemkl_sparse_create_coo_matrix`
   - :ref:`onemkl_sparse_create_csr_matrix`
   - :ref:`onemkl_sparse_set_coo_matrix_data`
   - :ref:`onemkl_sparse_set_csr_matrix_data`
   - :ref:`onemkl_sparse_set_matrix_property`
   - :ref:`onemkl_sparse_destroy_sparse_matrix`

   See a description of the supported :ref:`sparse formats<onemkl_sparse_format_descriptions>`.

.. toctree::
   :hidden:

   create_dense_vector
   create_dense_matrix
   create_coo_matrix
   create_csr_matrix
   set_dense_vector_data
   set_dense_matrix_data
   set_coo_matrix_data
   set_csr_matrix_data
   destroy_dense_vector
   destroy_dense_matrix
   destroy_sparse_matrix
   set_matrix_property
   format-descriptions

**Parent topic:** :ref:`onemkl_spblas`
