.. _mkl-sparse-trmv:

onemkl::sparse::trmv
====================


.. container::


   Computes a sparse matrix-dense vector product over upper or lower
   triangular parts of the matrix.


   .. container:: section
      :name: GUID-8FF718C9-D9AE-42A7-9A2A-A47DCEBB13D4


      .. rubric:: Syntax
         :name: syntax
         :class: sectiontitle


      .. container:: Note


         .. rubric:: Note
            :name: note
            :class: NoteTipHead


         Currently, complex types are not supported.


      **Using SYCL buffers:**


      .. container:: dlsyntaxpara


         .. cpp:function::  void onemkl::sparse::trmv (cl::sycl::queue &         queue, onemkl::uplo uplo_val, onemkl::transpose transpose_val,         onemkl::diag diag_val, fp alpha, matrixHandle_t handle,         cl::sycl::buffer<fp, 1> & x, fp beta, cl::sycl::buffer<fp, 1> &         y)

         **Using USM pointers:**


         .. cpp:function::  void onemkl::sparse::trmv (cl::sycl::queue &         queue, onemkl::uplo uplo_val, onemkl::transpose transpose_val,         onemkl::diag diag_val, fp alpha, matrixHandle_t handle, fp \*x, fp         beta, fp \*y)

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
         list of supported ``<fp>`` and ``<intType>`` and refer to
         `Exceptions <exceptions.html>`__
         for a detailed description of the exceptions thrown.
         The onemkl::sparse::trmv routine computes a sparse matrix-vector
         product over a triangular part defined as


         ::


                              y := alpha* (op)A*x + beta*y
                            



         where:


         ``alpha`` and ``beta`` are scalars, and\ ``x`` and ``y`` are
         vectors.


      .. container:: section
         :name: GUID-7F07A52E-4DDB-4C1B-AB92-E66C7641AED3


         .. rubric:: Input Parameters
            :name: input-parameters
            :class: sectiontitle


         queue
            Specifies the SYCL command queue which will be used for SYCL
            kernels execution.


         uplo_val
            Specifies which triangular matrix is to be processed.


            .. container:: tablenoborder


               .. list-table:: 
                  :header-rows: 1

                  * -  onemkl::uplo::lower 
                    -     The lower triangular matrix part is                processed.   
                  * -  onemkl::uplo::upper 
                    -     The upper triangular matrix part is                processed.   




         transpose_val
            Specifies operation ``op()`` on input matrix.


            .. container:: tablenoborder


               .. list-table:: 
                  :header-rows: 1

                  * -  onemkl::transpose::nontrans 
                    -     Non-transpose, ``op(A)`` = ``A``.    
                  * -  onemkl::transpose::trans 
                    -     Transpose, ``op(A)`` =                ``A``\ :sup:`T`.   
                  * -  onemkl::transpose::conjtrans 
                    -     Conjugate transpose, ``op(A)`` =                ``A``\ :sup:`H`.   




            .. container:: Note


               .. rubric:: Note
                  :name: note-2
                  :class: NoteTipHead


               Currently, the only supported case for ``operation`` is
               onemkl::transpose::nontrans.


         diag_val
            Specifies if the input matrix has a unit diagonal or not.


            .. container:: tablenoborder


               .. list-table:: 
                  :header-rows: 1

                  * -  onemkl::diag::nonunit 
                    -     Diagonal elements might not be equal to                one.   
                  * -  onemkl::diag::unit 
                    -     Diagonal elements are equal to one.    




         alpha
            Specifies the scalar ``alpha``.


         handle
            Handle to object containing sparse matrix and other internal
            data. Created using one of the
            onemkl::sparse::set<sparse_matrix_type>structure routines.


            .. container:: Note


               .. rubric:: Note
                  :name: note-3
                  :class: NoteTipHead


               Currently, the only supported case for
               <sparse_matrix_type> is CSR.


         x
            SYCL or USM memory object containing an array of size at
            least equal to the number of columns of input matrix if op =
            onemkl::transpose::nontrans and at least the number of rows of
            input matrix otherwise.


         beta
            Specifies the scalar ``beta``.


         y
            SYCL or USM memory object containing an array of size at
            least equal to the number of columns of input matrix if op =
            onemkl::transpose::nontrans and at least the number of rows of
            input matrix otherwise.


      .. container:: section
         :name: GUID-2D7BA49D-E937-40A4-AC2F-19685DC4E918


         .. rubric:: Output Parameters
            :name: output-parameters
            :class: sectiontitle


         y
            Overwritten by the updated vector ``y``.


   .. container:: familylinks


      .. container:: parentlink


         **Parent topic:** `Sparse BLAS
         Routines <spblas.html>`__


   
