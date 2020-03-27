.. _mkl-sparse-trmvoptimize:

onemkl::sparse::trmvOptimize
============================


.. container::


   Performs internal optimizations for onemkl::sparse::trmv by analyzing
   the matrix structure.


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


      The API is the same when using SYCL buffers or USM pointers.


      .. container:: dlsyntaxpara


         .. cpp:function::  void onemkl::sparse::trmvOptimize         (cl::sycl::queue & queue, onemkl::uplo uplo_val, onemkl::transpose         transpose_val, onemkl::diag diag_val, matrixHandle_t handle)

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


         Refer to
         `Exceptions <exceptions.html>`__
         for a detailed description of the exceptions thrown.
         The onemkl::sparse::trmvOptimize routine analyzes matrix structure
         and performs optimizations. Optimized data is then stored in
         the handle.


         .. rubric:: Input Parameters
            :name: input-parameters
            :class: sectiontitle


         queue
            Specifies the SYCL command queue which will be used for SYCL
            kernels execution.


         uplo_val
            Specifies the triangular matrix part for the input matrix.


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


   .. container:: familylinks


      .. container:: parentlink


         **Parent topic:** `Sparse BLAS
         Routines <spblas.html>`__


   
