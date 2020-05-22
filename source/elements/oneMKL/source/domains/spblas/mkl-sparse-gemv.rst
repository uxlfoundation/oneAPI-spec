.. _mkl-sparse-gemv:

onemkl::sparse::gemv
====================


.. container::


   Computes a sparse matrix-dense vector product.


   .. container:: section
      :name: GUID-8FF718C9-D9AE-42A7-9A2A-A47DCEBB13D4


      .. rubric:: Syntax
         :class: sectiontitle


      .. container:: Note


         .. rubric:: Note
            :class: NoteTipHead


         Complex types are not currently supported.


      **Using SYCL buffers:**


      .. cpp:function::  void onemkl::sparse::gemv (cl::sycl::queue & queue,      onemkl::transpose transpose_val, fp alpha, matrixHandle_t handle,      cl::sycl::buffer<fp, 1> & x, fp beta, cl::sycl::buffer<fp, 1> &      y)

      **Using USM pointers:**


      .. cpp:function::  void onemkl::sparse::gemv (cl::sycl::queue & queue,      onemkl::transpose transpose_val, fp alpha, matrixHandle_t handle, fp      *x, fp beta, fp *y)

      .. rubric:: Include Files
         :class: sectiontitle


      -  mkl_spblas_sycl.hpp


      .. rubric:: Description
         :class: sectiontitle


      .. rubric:: Note
         :class: NoteTipHead


      Refer to `Supported
      Types <supported-types.html>`__ for a
      list of supported ``<fp>`` and ``<intType>`` and refer to
      `Exceptions <exceptions.html>`__
      for a detailed description of the exceptions thrown.
      The onemkl::sparse::gemv routine computes a sparse matrix-vector
      product defined as


      ::


                           y := alpha*op(A)*x + beta*y
                         



      where:


      ``alpha`` and ``beta`` are scalars, ``x`` and ``y`` are vectors.


   .. container:: section
      :name: GUID-7F07A52E-4DDB-4C1B-AB92-E66C7641AED3


      .. rubric:: Input Parameters
         :class: sectiontitle


      queue
         Specifies the SYCL command queue which will be used for SYCL
         kernels execution.


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
               :class: NoteTipHead


            Currently, the only supported case for ``operation`` is
            onemkl::transpose::nontrans.


      alpha
         Specifies the scalar ``alpha``.


      handle
         Handle to object containing sparse matrix and other internal
         data. Created using one of the
         onemkl::sparse::set<sparse_matrix_type>structure routines.


         .. container:: Note


            .. rubric:: Note
               :class: NoteTipHead


            Currently, the only supported case for <sparse_matrix_type>
            is CSR.


      x
         SYCL or USM memory object containing an array of size at least
         equal to the number of columns of input matrix if ``op`` =
         onemkl::transpose::nontrans and at least the number of rows of
         input matrix otherwise.


      beta
         Specifies the scalar ``beta``.


      y
         SYCL or USM memory object containing an array of size at least
         equal to the number of columns of input matrix if ``op`` =
         onemkl::transpose::nontrans and at least the number of rows of
         input matrix otherwise.


   .. container:: section
      :name: GUID-2D7BA49D-E937-40A4-AC2F-19685DC4E918


      .. rubric:: Output Parameters
         :class: sectiontitle


      y
         Overwritten by the updated vector ``y``.


   .. container:: section
      :name: GUID-DB2452C7-1F50-4557-9515-D4CB96A735ED


      .. rubric:: Return Values
         :class: sectiontitle


      None


   .. container:: section
      :name: GUID-D29288F7-48C3-44EC-B6AC-489E263FF3A9


      .. rubric:: Example
         :class: sectiontitle


      An example of how to use onemkl::sparse::gemv with SYCL buffers or
      USM can be found in the oneMKL installation directory, under:


      ::


         examples/sycl/spblas/sparse_gemv.cpp


      ::


         examples/sycl/spblas/sparse_gemv_usm.cpp


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** `Sparse BLAS
      Routines <spblas.html>`__


