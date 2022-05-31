.. SPDX-FileCopyrightText: 2022 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. _imatcopy_batch:

imatcopy_batch
==============

Computes a group of in-place scaled matrix transpose or copy operations
using general matrices.

.. _onemkl_blas_imatcopy_batch_description:

.. rubric:: Description

The ``imatcopy_batch`` routines perform a series of in-place scaled matrix
copies or transpositions. They are batched versions of :ref:`onemkl_blas_imatcopy`,
but the ``imatcopy_batch`` routines perform their operations with
groups of matrices. Each group contains matrices with the same parameters.

``imatcopy_batch`` supports the following precisions:

   .. list-table::
      :header-rows: 1

      * -  T 
      * -  ``half``
      * -  ``float`` 
      * -  ``double`` 
      * -  ``std::complex<float>`` 
      * -  ``std::complex<double>`` 

.. _onemkl_blas_imatcopy_batch:

imatcopy_batch (Buffer Version)
-------------------------------

.. rubric:: Description
        
The operation for the strided API is defined as:
::

   for i = 0 … batch_size – 1
       AB is a matrix at offset i * stride in ab_array
       AB = alpha * op(AB)
   end for

where:

op(X) is one of op(X) = X, or op(X) = X\ :sup:`T`, or op(X) = X\ :sup:`H`,

``alpha`` is a scalar,

``AB`` is a matrix to be transformed in place,

and ``AB`` is ``m`` x ``n``.

The ``ab_array`` buffer contains all the input matrices. The stride
between matrices is given by the ``stride`` parameter. The total
number of matrices in ``ab_array`` is given by the ``batch_size``
parameter.

**Strided API**

.. rubric:: Syntax

.. code-block:: cpp

   namespace oneapi::mkl::blas::column_major {
       void imatcopy_batch(queue &queue, transpose trans,
                           std::int64_t m, std::int64_t n, T alpha,
                           cl::sycl::buffer<T, 1> &ab, std::int64_t lda,
                           std::int64_t ldb, std::int64_t stride,
                           std::int64_t batch_size);
   }
.. code-block:: cpp

   namespace oneapi::mkl::blas::row_major {
       void imatcopy_batch(queue &queue, transpose trans,
                           std::int64_t m, std::int64_t n, T alpha,
                           cl::sycl::buffer<T, 1> &ab, std::int64_t lda,
                           std::int64_t ldb, std::int64_t stride,
                           std::int64_t batch_size);
   }

.. container:: section

   .. rubric:: Input Parameters

   queue
      The queue where the routine should be executed.

   trans
      Specifies op(``AB``), the transposition operation applied to the
      matrices ``AB``. See :ref:`onemkl_datatypes` for more details.

   m
      Number of rows of ``AB``. Must be at least zero.


   n
      Number of columns of ``AB``. Must be at least zero.

   alpha
      Scaling factor for the matrix transpositions or copies.

   ab_array
      Buffer holding the input matrices ``AB`` with size ``stride`` * ``batch_size``.

   lda
      The leading dimension of the matrices ``A``. It must be
      positive, and must be at least ``m`` if column major layout is
      used, and at least ``n`` if row-major layout is used.

   ldb
      The leading dimension of the matrices``B``. It must be positive.

      .. list-table::
         :header-rows: 1

         * -
           - ``AB`` not transposed
           - ``AB`` transposed
         * - Column major
           - ``ldb`` must be at least ``m``.
           - ``ldb`` must be at least ``n``.
         * - Row major
           - ``ldb`` must be at least ``n``.
           - ``ldb`` must be at least ``m``.

   stride
      Stride between different ``AB`` matrices. It must be at least 
      ``max(ldb,lda)*max(ka, kb)``, where:

      - ``ka`` is ``m`` if column major layout is used or ``n`` if row major
         layout is used

      - ``kb`` is ``n`` if column major layout is used and AB is not
         transposed, or ``m`` otherwise

   batch_size
      Specifies the number of matrix transposition or copy operations to perform.

.. container:: section

   .. rubric:: Output Parameters

   ab
      Output buffer, overwritten by ``batch_size`` matrix matrix transposition
      operations of the form ``alpha`` * op(``AB``).





   

   
imatcopy_batch (USM Version)
----------------------------

The operation for the group API is defined as:
::

   idx = 0
   for i = 0 … group_count – 1
       m,n, alpha, lda, ldb and group_size at position i in their respective arrays
       for j = 0 … group_size – 1
           AB is a matrix at position idx in AB_array
           AB = alpha * op(AB)
           idx := idx + 1
       end for
   end for

where:

- ``op(X)`` is one of ``op(X) = X``, ``op(X) = X'``, or
  ``op(X) = conjg(X')``
- ``alpha`` is a scalar
- AB is a matrix to be transformed in place

The strided API is available with USM pointers or buffer arguments for the
input and output arrays, while the group API is available only with USM
pointers.

For the strided API, the single buffer or array AB contains all the matrices
to be transformed in place. The locations of the individual matrices within
the buffer or array are given by stride lengths, while the number of
matrices is given by the ``batch_size`` parameter.

For the group API, the matrices are given by arrays of pointers. AB
represents a matrix stored at the address pointed to by ``ab_array``.
The number of entries in ``ab_array`` is ``total_batch_count`` = the sum of
all the ``group_size`` entries.

API
***

Syntax
------

**Strided API**

USM arrays:

.. code-block::

   event imatcopy_batch(queue &queue,
      transpose trans,
      std::int64_t m,
      std::int64_t n,
      T alpha,
      const T *ab,
      std::int64_t lda,
      std::int64_t ldb,
      std::int64_t stride,
      std::int64_t batch_size,
      const vector_class<event> &dependencies = {});

Buffer arrays:

.. code-block::

   void imatcopy_batch(queue &queue, transpose trans,
      std::int64_t m, std::int64_t n, T alpha,
      cl::sycl::buffer<T, 1> &ab, std::int64_t lda,
      std::int64_t ldb, std::int64_t stride,
      std::int64_t batch_size);

**Group API**

.. code-block::

   event imatcopy_batch(queue &queue, const transpose *trans_array,
                        const std::int64_t *m_array,
                        const std::int64_t *n_array,
                        const T *alpha_array, T **ab_array,
                        const std::int64_t *lda_array,
                        const std::int64_t *ldb_array,
                        std::int64_t group_count,
                        const std::int64_t *groupsize,
                        const vector_class<event> &dependencies = {});

Input Parameters
----------------

**Strided API**

trans
   Specifies ``op(AB)``, the transposition operation applied to the
   matrices AB.

m
   Number of rows for each matrix AB on input. Must be at least 0.

n
   Number of columns for each matrix AB on input. Must be at least 0.

alpha
   Scaling factor for the matrix transpose or copy operation.

ab
   Buffer holding the matrices AB. Must have size at least
   ``stride*batch_size``.

lda
   Leading dimension of the AB matrices on input. If matrices are stored
   using column major layout, ``lda`` must be at least ``m``. If matrices
   are stored using row major layout, ``lda`` must be at least ``n``. 
   Must be positive.

ldb
   Leading dimension of the AB matrices on output. If matrices are stored
   using column major layout, ``ldb`` must be at least ``m`` if AB is not
   transposed or ``n`` if AB is transposed. If matrices are stored using
   row major layout, ``ldb`` must be at least ``n`` if AB is not transposed
   or at least ``m`` if AB is transposed. Must be positive.

stride
   Stride between the different AB matrices. It must be at least
   ``max(ldb,lda)*max(ka, kb)``, where:

   - ``ka`` is ``m`` if column major layout is used or ``n`` if row major
      layout is used

   - ``kb`` is ``n`` if column major layout is used and  AB is not
      transposed, or ``m`` otherwise

batch_size
   Specifies the number of matrices to transpose or copy.

dependencies
   List of events to wait for before starting computation, if any.
   If omitted, defaults to no dependencies.

**Group API**

trans_array
   Array of size ``group_count``. Each element ``i`` in the array specifies
   ``op(AB)`` the transposition operation applied to the matrices AB.

m_array
   Array of size ``group_count`` of number of rows of AB on input. Each
   must be at least 0.

n_array
   Array of size ``group_count`` of number of columns of AB on input. Each
   must be at least 0.

alpha_array
   Array of size ``group_count`` containing scaling factors for the matrix
   transpositions or copies.

ab_array
   Array of size ``total_batch_count``, holding pointers to arrays used to
   store AB matrices.

lda_array
   Array of size ``group_count``. The leading dimension of the matrix input
   AB. If matrices are stored using column major layout, ``lda_array[i]``
   must be at least ``m_array[i]``. If matrices are stored using row major
   layout, ``lda_array[i]`` must be at least ``n_array[i]``.
   Must be positive.

ldb_array
   Array of size ``group_count``. The leading dimension of the output matrix
   AB. Each entry ``ldb_array[i]`` must be positive and at least:

   - ``m_array[i]`` if column major layout is used and AB is not transposed

   - ``m_array[i]`` if row major layout is used and AB is transposed (AB')

   - ``n_array[i]`` otherwise

group_count
   Number of groups. Must be at least 0.

group_size
   Array of size ``group_count``. The element ``group_size[i]`` is the
   number of matrices in the group ``i``. Each element in ``group_size``
   must be at least 0.

dependencies
   List of events to wait for before starting computation, if any.
   If omitted, defaults to no dependencies.

Output Parameters
-----------------

**Strided API**

ab
   Output buffer, overwritten by ``batch_size`` matrix multiply operations
   of the form ``alpha*op(AB)``.

**Group API**

ab_array
   Output array of pointers to AB matrices, overwritten by
   ``total_batch_count`` matrix transpose or copy operations of the form
   ``alpha*op(AB)``.
