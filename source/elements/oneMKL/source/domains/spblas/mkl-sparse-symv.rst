.. _mkl-sparse-symv:

onemkl::sparse::symv
=================


.. container::


   Computes a sparse matrix-vector product for a symmetric matrix.


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


         .. cpp:function::  void onemkl::sparse::symv (cl::sycl::queue &         queue, onemkl::uplo uplo_val, fp alpha, matrixHandle_t handle,         cl::sycl::buffer<fp, 1> & x, fp beta, cl::sycl::buffer<fp, 1> &         y)

         **Using USM pointers:**


         .. cpp:function::  void onemkl::sparse::symv (cl::sycl::queue &         queue, onemkl::uplo uplo_val, fp alpha, matrixHandle_t handle, fp         \*x, fp beta, fp \*y)

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
         The onemkl::sparse::symv routine computes a sparse matrix-vector
         product over a symmetric part defined as


         ::


                               y := alpha*A*x + beta*y
                            



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
            Specifies which symmetric part is to be processed.


            .. container:: tablenoborder


               .. list-table:: 
                  :header-rows: 1

                  * -  onemkl::uplo::lower 
                    -     The lower symmetric part is                processed.   
                  * -  onemkl::uplo::upper 
                    -     The upper symmetric part is                processed.   




         alpha
            Specifies the scalar ``alpha``.


         handle
            Handle to object containing sparse matrix and other internal
            data. Created using one of the
            onemkl::sparse::set<sparse_matrix_type>structure routines.


            .. container:: Note


               .. rubric:: Note
                  :name: note-2
                  :class: NoteTipHead


               Currently, the only supported case for
               <sparse_matrix_type> is CSR.


         x
            SYCL or USM memory object containing an array of size at
            least equal to the number of columns of input matrix.


         beta
            Specifies the scalar ``beta``.


         y
            SYCL or USM memory object containing an array of size at
            least equal to the number of columns of input matrix.


      .. container:: section
         :name: GUID-2D7BA49D-E937-40A4-AC2F-19685DC4E918


         .. rubric:: Output Parameters
            :name: output-parameters
            :class: sectiontitle


         y
            Overwritten by the updated vector ``y``.


      .. container:: section
         :name: GUID-C97BF68F-B566-4164-95E0-A7ADC290DDE2


         .. rubric:: Example
            :name: example
            :class: sectiontitle


         An example of how to use ``onemkl::sparse::symv`` with SYCL
         buffers or USM can be found in the oneMKL installation
         directory, under:


         ::


            examples/sycl/spblas/sparse_symv_l.cpp


         ::


            examples/sycl/spblas/sparse_symv_l_usm.cpp


   .. container:: familylinks


      .. container:: parentlink


         **Parent topic:** `Sparse BLAS
         Routines <spblas.html>`__


   .. container::

