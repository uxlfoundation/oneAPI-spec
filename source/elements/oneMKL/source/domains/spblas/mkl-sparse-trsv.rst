.. _mkl-sparse-trsv:

onemkl::sparse::trsv
====================


.. container::


   Solves a system of linear equations for a triangular sparse matrix.


   .. container:: section
      :name: GUID-D7939766-BD30-4A72-BBB2-B0F0E5C6BA76


      .. rubric:: Syntax
         :name: syntax
         :class: sectiontitle


      .. container:: Note


         .. rubric:: Note
            :name: note
            :class: NoteTipHead


         Currently, complex types are not supported.


      **Using SYCL buffers:**


      .. cpp:function::  void onemkl::sparse::trsv (cl::sycl::queue & queue,      onemkl::uplo uplo_val, onemkl::transpose transpose_val, onemkl::diag      diag_val, matrixHandle_t handle, cl::sycl::buffer<fp, 1> & x,      cl::sycl::buffer<fp, 1> & y)

      **Using USM pointers:**


      .. cpp:function::  void onemkl::sparse::trsv (cl::sycl::queue & queue,      onemkl::uplo uplo_val, onemkl::transpose transpose_val, onemkl::diag      diag_val, matrixHandle_t handle, fp \*x, fp \*y)

      .. rubric:: Include Files
         :name: include-files
         :class: sectiontitle


      -  mkl_spblas_sycl.hpp


      .. rubric:: Description
         :name: description
         :class: sectiontitle


      .. rubric:: Note
         :name: note-1
         :class: NoteTipHead


      Refer to `Supported
      Types <supported-types.html>`__ for a
      list of supported ``<fp>`` and ``<intType>``, and refer to
      `Exceptions <exceptions.html>`__
      for a detailed description of the exceptions thrown.
      The onemkl::sparse::trsv routine solves a system of linear equations
      for a square matrix:


      ::


         op(A)*y =  x              


      where ``A`` is a triangular sparse matrix of size ``m`` rows by
      ``m`` columns, op is a matrix modifier for matrix ``A``, ``alpha``
      is a scalar, and ``x`` and ``y`` are vectors of length at least
      ``m``.


   .. container:: section
      :name: GUID-7F07A52E-4DDB-4C1B-AB92-E66C7641AED3


      .. rubric:: Input Parameters
         :name: input-parameters
         :class: sectiontitle


      queue
         Specifies the SYCL command queue which will be used for SYCL
         kernels execution.


      uplo_val
         Specifies if the input matrix is an upper triangular or a lower
         triangular matrix.


         .. container:: tablenoborder


            .. list-table:: 
               :header-rows: 1

               * -  onemkl::uplo::lower 
                 -     The lower triangular matrix part is             processed.   
               * -  onemkl::uplo::upper 
                 -     The upper triangular matrix part is             processed.   




      transpose_val
         Specifies operation ``op()`` on input matrix.


         .. container:: tablenoborder


            .. list-table:: 
               :header-rows: 1

               * -  onemkl::transpose::nontrans 
                 -     Non-transpose, ``op(A)`` = ``A``.    
               * -  onemkl::transpose::trans 
                 -     Transpose, ``op(A)`` = ``A``\ :sup:`T`.    
               * -  onemkl::transpose::conjtrans 
                 -     Conjugate transpose, ``op(A)`` =             ``A``\ :sup:`H`.   




         .. container:: Note


            .. rubric:: Note
               :name: note-2
               :class: NoteTipHead


            Currently, the only supported case for operation is
            onemkl::transpose::nontrans.


      diag_val
         Specifies if the input matrix has a unit diagonal or not.


         .. container:: tablenoborder


            .. list-table:: 
               :header-rows: 1

               * -  onemkl::diag::nonunit 
                 -     Diagonal elements might not be equal to             one.   
               * -  onemkl::diag::unit 
                 -     Diagonal elements are equal to one.    




      handle
         Handle to object containing sparse matrix and other internal
         data. Created using one of the
         onemkl::sparse::set<sparse_matrix_type>structure routines.


         .. container:: Note


            .. rubric:: Note
               :name: note-3
               :class: NoteTipHead


            Currently, the only supported case for <sparse_matrix_type>
            is CSR.


      x
         SYCL or USM memory object containing an array of size at least
         equal to the number of columns of input matrix if ``op`` =
         onemkl::transpose::nontrans and at least the number of rows of
         input matrix otherwise. It is the input vector ``x``


      y
         SYCL or USM memory object containing an array of size at least
         equal to the number of columns of input matrix if ``op`` =
         onemkl::transpose::nontrans and at least the number of rows of
         input matrix otherwise.


   .. container:: section
      :name: GUID-36823FC7-2AEA-42BC-A07F-0036A76E7BAE


      .. rubric:: Output Parameters
         :name: output-parameters
         :class: sectiontitle


      y
         SYCL or USM memory object containing an array of size at least
         ``nRows`` filled with the solution to the system of linear
         equations.


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** `Sparse BLAS
      Routines <spblas.html>`__


.. container::

