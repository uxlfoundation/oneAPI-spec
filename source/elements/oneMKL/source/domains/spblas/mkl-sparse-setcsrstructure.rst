.. _mkl-sparse-setcsrstructure:

onemkl::sparse::setCSRstructure
===============================


.. container::


   Creates a handle for a CSR matrix.


   .. container:: section
      :name: GUID-EBB08B57-1328-49DB-A83D-F8574FCE76DB


      .. rubric:: Syntax
         :name: syntax
         :class: sectiontitle


      **Using SYCL buffers:**


      .. cpp:function::  void onemkl::sparse::setCSRstructure (matrixHandle_t      handle, intType nRows, intType nCols, onemkl::index_base index,      cl::sycl::buffer<intType, 1> & rowIndex, cl::sycl::buffer<intType,      1> & colIndex, cl::sycl::buffer<fp, 1> & values)

      **Using USM pointers:**


      .. cpp:function::  void onemkl::sparse::setCSRstructure (matrixHandle_t      handle, intType nRows, intType nCols, onemkl::index_base index,      intType \*rowIndex, intType \*colIndex, fp \*values)

      .. rubric:: Include Files
         :name: include-files
         :class: sectiontitle


      -  mkl_spblas_sycl.hpp


      .. rubric:: Description
         :name: description
         :class: sectiontitle


      The onemkl::sparse::setCSRstructure routine creates a handle for a
      sparse matrix of dimensions ``nRows``-by-``nCols`` represented in
      the CSR format..


      .. rubric:: Note
         :name: note
         :class: NoteTipHead


      Refer to `Supported
      Types <supported-types.html>`__ for a
      list of supported ``<fp>`` and ``<intType>``, and refer to
      `Exceptions <exceptions.html>`__
      for a detailed description of the exceptions thrown.


      .. rubric:: Input Parameters
         :name: input-parameters
         :class: sectiontitle


      handle
         Handle to object containing sparse matrix and other internal
         data for subsequent SYCL Sparse BLAS operations.


      nRows
         Number of rows of the input matrix .


      nCols
         Number of columns of the input matrix .


      Index
         Indicates how input arrays are indexed.


         .. list-table:: 
            :header-rows: 1

            * -     onemkl::index_base::zero    
              -     Zero-based (C-style) indexing: indices start at          0.   
            * -     onemkl::index_base::one    
              -     One-based (Fortran-style) indexing: indices start          at 1.   




      rowIndex
         SYCL or USM memory object containing an array of length
         ``m+1``. This array contains row indices, such that
         ``rowsIndex[i]`` - ``indexing`` is the first index of row ``i``
         in the arrays ``values`` and ``colIndex. indexing`` takes 0 for
         zero-based indexing and 1 for one-based indexing. Refer to
         ``pointerB`` and ``pointerE`` array description in `Sparse BLAS
         CSR Matrix Storage
         Format <https://software.intel.com/en-us/mkl-developer-reference-c-sparse-blas-csr-matrix-storage-format>`__
         for more details.


         .. container:: Note


            .. rubric:: Note
               :name: note-1
               :class: NoteTipHead


            Refer to `Three Array Variation of CSR
            Format <https://software.intel.com/en-us/mkl-developer-reference-c-sparse-blas-csr-matrix-storage-format>`__
            for more details.


      colIndex
         SYCL or USM memory object which stores an array containing the
         column indices in ``index``-based numbering (``index`` takes 0
         for zero-based indexing and 1 for one-based indexing) for each
         non-zero element of the input matrix. Its length is at least
         ``nrows``.


      values
         SYCL or USM memory object which stores an array containing
         non-zero elements of the input matrix. Its length is equal to
         length of the ``colIndex`` array. Refer to the values array
         description in `Sparse BLAS CSR Matrix Storage
         Format <https://software.intel.com/en-us/mkl-developer-reference-c-sparse-blas-csr-matrix-storage-format>`__
         for more details.


   .. container:: section
      :name: GUID-E7B97F4D-A214-4FB7-85A6-A653F913CE4F


      .. rubric:: Output Parameters
         :name: output-parameters
         :class: sectiontitle


      handle
         Handle to object containing sparse matrix and other internal
         data for subsequent Sycl Sparse BLAS operations.


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** `Sparse BLAS
      Routines <spblas.html>`__


.. container::

