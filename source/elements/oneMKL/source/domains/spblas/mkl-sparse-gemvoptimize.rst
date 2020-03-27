.. _mkl-sparse-gemvoptimize:

onemkl::sparse::gemvOptimize
============================


.. container::


   Performs internal optimizations for onemkl::sparse::gemv by analyzing
   the matrix structure.


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


      The API is the same when using SYCL buffers or USM pointers.


      .. container:: dlsyntaxpara


         .. cpp:function::  void onemkl::sparse::gemvOptimize         (cl::sycl::queue & queue, onemkl::transpose transpose_val,         matrixHandle_t handle)

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
         The onemkl::sparse::gemvOptimize routine analyzes matrix structure
         and performs optimizations. Optimized data is then stored in
         the handle.


         .. rubric:: Input Parameters
            :name: input-parameters
            :class: sectiontitle


         queue
            Specifies the SYCL command queue which will be used for SYCL
            kernels execution.


         transpose_val
            Specifies operation ``op()`` on input matrix.


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


   .. container::

