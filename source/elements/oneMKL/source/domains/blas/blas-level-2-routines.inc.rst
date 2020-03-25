.. _blas-level-2-routines:

BLAS Level 2 Routines
=====================


.. container::


   This section describes BLAS Level 2 routines, which perform
   matrix-vector operations. The following table lists the BLAS Level 2
   routine groups and the data types associated with them.


   .. container:: tablenoborder


      .. list-table:: 
         :header-rows: 1

         * -     Routine or Function Group with SYCL Buffer
           -     Routine or Function Group with USM
           -     Data Types     
           -     Description     
         * -           \ `gbmv <gbmv.html>`__\    
           -           \ `gbmv <gbmv-usm-version.html>`__\    
           -     float, double, std::complex<float>,       std::complex<double>    
           -     Matrix-vector product using a general band matrix          
         * -           \ `gemv <gemv.html>`__\    
           -           \ `gemv <gemv-usm-version.html>`__\    
           -     float, double, std::complex<float>,       std::complex<double>    
           -     Matrix-vector product using a general matrix     
         * -           \ `ger <ger.html>`__\    
           -           \ `ger <ger-usm-version.html>`__\    
           -     float, double     
           -     Rank-1 update of a general matrix     
         * -           \ `gerc <gerc.html>`__\    
           -           \ `gerc <gerc-usm-version.html>`__\    
           -     std::complex<float>, std::complex<double>     
           -     Rank-1 update of a conjugated general matrix     
         * -           \ `geru <geru.html>`__\    
           -           \ `geru <geru-usm-version.html>`__\    
           -     std::complex<float>, std::complex<double>     
           -     Rank-1 update of a general matrix, unconjugated          
         * -           \ `hbmv <hbmv.html>`__\    
           -           \ `hbmv <hbmv-usm-version.html>`__\    
           -     std::complex<float>, std::complex<double>     
           -     Matrix-vector product using a Hermitian band matrix          
         * -           \ `hemv <hemv.html>`__\    
           -           \ `hemv <hemv-usm-version.html>`__\    
           -     std::complex<float>, std::complex<double>     
           -     Matrix-vector product using a Hermitian matrix          
         * -           \ `her <her.html>`__\    
           -           \ `her <her-usm-version.html>`__\    
           -     std::complex<float>, std::complex<double>     
           -     Rank-1 update of a Hermitian matrix     
         * -           \ `her2 <her2.html>`__\    
           -           \ `her2 <her2-usm-version.html>`__\    
           -     std::complex<float>, std::complex<double>     
           -     Rank-2 update of a Hermitian matrix     
         * -           \ `hpmv <hpmv.html>`__\    
           -           \ `hpmv <hpmv-usm-version.html>`__\    
           -     std::complex<float>, std::complex<double>     
           -     Matrix-vector product using a Hermitian packed matrix          
         * -           \ `hpr <hpr.html>`__\    
           -           \ `hpr <hpr-usm-version.html>`__\    
           -     std::complex<float>, std::complex<double>     
           -     Rank-1 update of a Hermitian packed matrix     
         * -           \ `hpr2 <hpr2.html>`__\    
           -           \ `hpr2 <hpr2-usm-version.html>`__\    
           -     std::complex<float>, std::complex<double>     
           -     Rank-2 update of a Hermitian packed matrix     
         * -           \ `sbmv <sbmv.html>`__\    
           -           \ `sbmv <sbmv-usm-version.html>`__\    
           -     float, double     
           -     Matrix-vector product using symmetric band matrix          
         * -           \ `spmv <spmv.html>`__\    
           -           \ `spmv <spmv-usm-version.html>`__\    
           -     float, double     
           -     Matrix-vector product using a symmetric packed matrix          
         * -           \ `spr <spr.html>`__\    
           -           \ `spr <spr-usm-version.html>`__\    
           -     float, double     
           -     Rank-1 update of a symmetric packed matrix     
         * -           \ `spr2 <spr2.html>`__\    
           -           \ `spr2 <spr2-usm-version.html>`__\    
           -     float, double     
           -     Rank-2 update of a symmetric packed matrix     
         * -           \ `symv <symv.html>`__\    
           -           \ `symv <symv-usm-version.html>`__\    
           -     float, double     
           -     Matrix-vector product using a symmetric matrix          
         * -           \ `syr <syr.html>`__\    
           -           \ `syr <syr-usm-version.html>`__\    
           -     float, double     
           -     Rank-1 update of a symmetric matrix     
         * -           \ `syr2 <syr2.html>`__\    
           -           \ `syr2 <syr2-usm-version.html>`__\    
           -     float, double     
           -     Rank-2 update of a symmetric matrix     
         * -           \ `tbmv <tbmv.html>`__\    
           -           \ `tbmv <tbmv-usm-version.html>`__\    
           -     float, double, std::complex<float>,       std::complex<double>    
           -     Matrix-vector product using a triangular band matrix          
         * -           \ `tbsv <tbsv.html>`__\    
           -           \ `tbsv <tbsv-usm-version.html>`__\    
           -     float, double, std::complex<float>,       std::complex<double>    
           -     Solution of a linear system of equations with a       triangular band matrix    
         * -           \ `tpmv <tpmv.html>`__\    
           -           \ `tpmv <tpmv-usm-version.html>`__\    
           -     float, double, std::complex<float>,       std::complex<double>    
           -     Matrix-vector product using a triangular packed matrix          
         * -           \ `tpsv <tpsv.html>`__\    
           -           \ `tpsv <tpsv-usm-version.html>`__\    
           -     float, double, std::complex<float>,       std::complex<double>    
           -     Solution of a linear system of equations with a       triangular packed matrix    
         * -           \ `trmv <trmv.html>`__\    
           -           \ `trmv <trmv-usm-version.html>`__\    
           -     float, double, std::complex<float>,       std::complex<double>    
           -     Matrix-vector product using a triangular matrix          
         * -           \ `trsv <trsv.html>`__\    
           -           \ `trsv <trsv-usm-version.html>`__\    
           -     float, double, std::complex<float>,       std::complex<double>    
           -     Solution of a linear system of equations with a       triangular matrix    




.. toctree::
    :hidden:

    gbmv
    gbmv-usm-version
    gemv
    gemv-usm-version
    ger
    ger-usm-version
    gerc
    gerc-usm-version
    geru
    geru-usm-version
    hbmv
    hbmv-usm-version
    hemv
    hemv-usm-version
    her
    her-usm-version
    her2
    her2-usm-version
    hpmv
    hpmv-usm-version
    hpr
    hpr-usm-version
    hpr2
    hpr2-usm-version
    sbmv
    sbmv-usm-version
    spmv
    spmv-usm-version
    spr
    spr-usm-version
    spr2
    spr2-usm-version
    symv
    symv-usm-version
    syr
    syr-usm-version
    syr2
    syr2-usm-version
    tbmv
    tbmv-usm-version
    tbsv
    tbsv-usm-version
    tpmv
    tpmv-usm-version
    tpsv
    tpsv-usm-version
    trmv
    trmv-usm-version
    trsv
    trsv-usm-version
