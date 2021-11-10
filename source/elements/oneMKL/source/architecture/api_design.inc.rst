.. SPDX-FileCopyrightText: 2019-2020 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

.. _onemkl_api_design:

API Design
-----------

This section discusses the general features of oneMKL API design. In particular, it covers the use of namespaces and data types from C++, from DPC++ and new ones introduced for oneMKL APIs.

.. _onemkl_namespaces:

oneMKL namespaces
++++++++++++++++++

The oneMKL library uses C++ namespaces to organize routines by mathematical domain.  All oneMKL objects and routines shall be contained within the ``oneapi::mkl`` base namespace.  The individual oneMKL domains use a secondary namespace layer as follows:

========================  =======================================================================================================
namespace                 oneMKL domain or content
========================  =======================================================================================================
``oneapi::mkl``           oneMKL base namespace, contains general oneMKL data types, objects, exceptions and routines
``oneapi::mkl::blas``     Dense linear algebra routines from BLAS and BLAS like extensions. The oneapi::mkl::blas namespace should contain two namespaces column_major and row_major to support both matrix layouts. See :ref:`onemkl_blas`
``oneapi::mkl::lapack``   Dense linear algebra routines from LAPACK and LAPACK like extensions. See :ref:`onemkl_lapack`
``oneapi::mkl::sparse``   Sparse linear algebra routines from Sparse BLAS and Sparse Solvers. See :ref:`onemkl_sparse_linear_algebra`
``oneapi::mkl::dft``      Discrete and fast Fourier transformations. See :ref:`onemkl_dft`
``oneapi::mkl::rng``      Random number generator routines. See :ref:`onemkl_rng`
``oneapi::mkl::vm``       Vector mathematics routines, e.g. trigonometric, exponential functions acting on elements of a vector. See :ref:`onemkl_vm`
========================  =======================================================================================================

.. note::
   :name: Implementation Requirement

   Inside each oneMKL domain, there are many routines, classes, enums and objects defined which constitute the breadth and scope of that oneMKL domain.  
   It is permitted for a library implementation of the oneMKL specification to implement either all, one or more than one of the domains in oneMKL. However, within an implementation of a specific domain, all relevant routines, classes, enums and objects (including those relevant enums and objects which live outside a particular domain in the general ``oneapi::mkl`` namespace must be both declared and defined in the library so that an application that uses that domain could build and link against that library implementation successfully.

   It is however acceptable to throw the runtime exception :ref:`oneapi::mkl::unimplemented<onemkl_exception_unimplemented>` inside of the routines or class member functions in that domain that have not been fully implemented.  
   For instance, a library may choose to implement the oneMKL BLAS functionality and in particular may choose to implement only the :ref:`onemkl_blas_gemm` api for their library, in which case they must also include all the other blas namespaced routines and throw the :ref:`oneapi::mkl::unimplemented<onemkl_exception_unimplemented>` exception inside all the others.  
   
   In such a case, the implemented routines in such a library should be communicated clearly and easily understood by users of that library.


.. _onemkl_cpp_datatypes:

Standard C++ datatype usage
+++++++++++++++++++++++++++

oneMKL uses C++ STL data types for scalars where applicable:

* Integer scalars are C++ fixed-size integer types (``std::intN_t``, ``std::uintN_t``).
* Complex numbers are represented by C++ ``std::complex`` types.

In general, scalar integer arguments to oneMKL routines are 64-bit integers (``std::int64_t`` or ``std::uint64_t``). Integer vectors and matrices may have varying bit widths, defined on a per-routine basis.

.. _onemkl_dpcpp_datatypes:

DPC++ datatype usage
++++++++++++++++++++

oneMKL uses the following DPC++ data types:

* SYCL queue ``sycl::queue`` for scheduling kernels on a SYCL device. See :ref:`onemkl_queues` for more details.
* SYCL buffer ``sycl::buffer`` for buffer-based memory access. See :ref:`onemkl_buffers` for more details.
* Unified Shared Memory (USM) for pointer-based memory access. See :ref:`onemkl_usm` for more details.
* SYCL event ``sycl::event`` for output event synchronization in oneMKL routines with USM pointers. See :ref:`onemkl_synchronization_with_usm` for more details.
* Vector of SYCL events ``std::vector<sycl::event>`` for input events synchronization in oneMKL routines with USM pointers. See :ref:`onemkl_synchronization_with_usm` for more details.

.. note::
    The class ``sycl::vector_class`` has been removed from SYCL 2020 and the standard class ``std::vector`` should be used instead for vector of SYCL events in oneMKL routines with USM pointers

.. _onemkl_datatypes:

oneMKL defined datatypes
++++++++++++++++++++++++

oneMKL dense and sparse linear algebra routines use scoped enum types as type-safe replacements for the traditional character arguments used in C/Fortran implementations of BLAS and LAPACK. These types all belong to the ``oneapi::mkl`` namespace.  

Each enumeration value comes with two names: A single-character name (the traditional BLAS/LAPACK character) and a longer, more descriptive name. The two names are exactly equivalent and may be used interchangeably.

      .. _onemkl_enum_transpose:

      .. rubric:: transpose
         :name: transpose
         :class: sectiontitle

      The ``transpose`` type specifies whether an input matrix should be
      transposed and/or conjugated. It can take the following values:

      .. container:: tablenoborder

         .. list-table::
            :header-rows: 1

            * -  Short Name
              -  Long Name
              -  Description
            * -  ``transpose::N``
              -  ``transpose::nontrans``
              -  Do not transpose or conjugate the matrix.
            * -  ``transpose::T``
              -  ``transpose::trans``
              -  Transpose the matrix.
            * -  ``transpose::C``
              -  ``transpose::conjtrans``
              -  Perform Hermitian transpose (transpose and conjugate). Only applicable to complex matrices.

      .. _onemkl_enum_uplo:

      .. rubric:: uplo
         :name: uplo
         :class: sectiontitle

      The ``uplo`` type specifies whether the lower or upper triangle of
      a triangular, symmetric, or Hermitian matrix should be accessed.
      It can take the following values:

      .. container:: tablenoborder

         .. list-table::
            :header-rows: 1

            * -  Short Name
              -  Long Name
              -  Description
            * -  ``uplo::U``
              -  ``uplo::upper``
              -  Access the upper triangle of the matrix.
            * -  ``uplo::L``
              -  ``uplo::lower``
              -  Access the lower triangle of the matrix.

      In both cases, elements that are not in the selected triangle are
      not accessed or updated.

      .. _onemkl_enum_diag:

      .. rubric:: diag
         :name: diag
         :class: sectiontitle

      The ``diag`` type specifies the values on the diagonal of a
      triangular matrix. It can take the following values:

      .. container:: tablenoborder

         .. list-table::
            :header-rows: 1

            * -  Short Name
              -  Long Name
              -  Description
            * -  ``diag::N``
              -  ``diag::nonunit``
              -  The matrix is not unit triangular. The diagonal entries are stored with the matrix data.
            * -  ``diag::U``
              -  ``diag::unit``
              -  The matrix is unit triangular (the diagonal entries are all 1's). The diagonal entries in the matrix data are not accessed.

      .. _onemkl_enum_side:

      .. rubric:: side
         :name: side
         :class: sectiontitle

      The ``side`` type specifies the order of matrix multiplication
      when one matrix has a special form (triangular, symmetric, or
      Hermitian):

      .. container:: tablenoborder

         .. list-table::
            :header-rows: 1

            * -  Short Name
              -  Long Name
              -  Description
            * -  ``side::L``
              -  ``side::left``
              -  The special form matrix is on the left in the multiplication.
            * -  ``side::R``
              -  ``side::right``
              -  The special form matrix is on the right in the multiplication.

      .. _onemkl_enum_offset:

      .. rubric:: offset
         :name: offset
         :class: sectiontitle

      The ``offset`` type specifies whether the offset to apply to an
      output matrix is a fix offset, column offset or row offset. It can
      take the following values

      .. container:: tablenoborder

         .. list-table::
            :header-rows: 1

            * -  Short Name
              -  Long Name
              -  Description
            * -  ``offset::F``
              -  ``offset::fix``
              -  The offset to apply to the output matrix is fix, all the inputs in the ``C_offset`` matrix has the same value given by the first element in the ``co`` array.
            * -  ``offset::C``
              -  ``offset::column``
              -  The offset to apply to the output matrix is a column offset, that is to say all the columns in the ``C_offset`` matrix are the same and given by the elements in the ``co`` array.
            * -  ``offset::R``
              -  ``offset::row``
              -  The offset to apply to the output matrix is a row offset, that is to say all the rows in the ``C_offset`` matrix are the same and given by the elements in the ``co`` array.

      .. _onemkl_enum_index_base:

      .. rubric:: index_base
         :name: index_base
         :class: sectiontitle

      The ``index_base`` type specifies how values in index arrays are interpreted. For instance, a sparse matrix stores nonzero values and the
      indices that they correspond to.  The indices are traditionally provided in one of two forms: C/C++-style using zero-based
      indices, or Fortran-style using one-based indices. The ``index_base`` type can take the following values:

      .. container:: tablenoborder

         .. list-table::
            :header-rows: 1

            * -  Name
              -  Description
            * -  ``index_base::zero``
              -  Index arrays for an input matrix are provided using zero-based (C/C++ style) index values.  That is, indices start at 0.
            * -  ``index_base::one``
              -  Index arrays for an input matrix are provided using one-based (Fortran style) index values.  That is, indices start at 1.


      .. _onemkl_enum_layout:

      .. rubric:: layout
         :name: layout
         :class: sectiontitle

      The ``layout`` type specifies how a dense matrix ``A`` with leading dimension ``lda`` is stored as one dimensional array in memory. 
      The layouts are traditionally provided in one of two forms: C/C++-style using ``row_major`` layout,
      or Fortran-style using ``column_major`` layout. The ``layout`` type can take the following values:

      .. container:: tablenoborder

         .. list-table::
            :header-rows: 1

            * -  Short Name
              -  Long Name
              -  Description
            * -  ``layout::R``
              -  ``layout::row_major``
              -  For row major layout, the elements of each row of a dense matrix ``A`` are contiguous in memory while the elements of each column are at distance ``lda`` from the element in the same column and the previous row.
            * -  ``layout::C``
              -  ``layout::col_major``
              -  For column major layout, the elements of each column a dense matrix ``A`` are contiguous in memory while the elements of each row are at distance ``lda`` from the element in the same row and the previous column.


.. note::
        :ref:`onemkl_appendix` may contain other API design decisions or recommendations that may be of use to the general developer of oneMKL, but which may not necessarily be part of the oneMKL specification.


