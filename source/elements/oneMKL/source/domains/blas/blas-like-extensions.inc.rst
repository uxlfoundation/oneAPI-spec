.. _blas-like-extensions:

BLAS-like Extensions
====================


.. container::


   oneAPI Math Kernel Library DPC++ provides additional routines to
   extend the functionality of the BLAS routines. These include routines
   to compute many independent matrix-matrix products.

   The following table lists the BLAS-like Extensions groups and the data types
   associated with them.


   .. container:: tablenoborder


      .. list-table:: 
         :header-rows: 1

         * -     Routine or Function Group with SYCL Buffer
           -     Data Types     
           -     Description     
         * -           \ `gemm_batch <gemm_batch.html>`__\    
           -     float, double, std::complex<float>,       std::complex<double>    
           -     Computes groups of matrix-matrix product with general       matrices.   
         * -           \ `trsm_batch <trsm_batch.html>`__\    
           -     float, double, std::complex<float>,       std::complex<double>    
           -     Solves a triangular matrix equation for a group of       matrices.   
         * -           \ `gemmt <gemmt.html>`__\    
           -     float, double, std::complex<float>,       std::complex<double>    
           -     Computes a matrix-matrix product with general matrices, but updates
                 only the upper or lower triangular part of the result matrix.
         * -           \ `gemm_ext <gemm_ext.html>`__\    
           -     half, float, double, std::complex<float>,       std::complex<double>
                 int8_t, uint8_t, int32_t    
           -     Computes a matrix-matrix product with general matrices
 




.. toctree::
    :hidden:

    gemm_batch
    gemm_ext
    gemmt
    gemmt-usm-version
    trsm_batch
