.. _blas-level-1-routines:

BLAS Level 1 Routines
=====================


.. container::


   BLAS Level 1 includes routines and functions, which perform
   vector-vector operations. The following table lists the BLAS Level 1
   routine and function groups and the data types associated with them.


   .. container:: tablenoborder


      .. list-table:: 
         :header-rows: 1

         * -     Routine or Function Group with SYCL Buffer
           -     Routine or Function Group with USM
           -     Data Types     
           -     Description     
         * -           \ `asum <asum.html>`__\    
           -           \ `asum <asum-usm-version.html>`__\    
           -     float, double, mixed float and std::complex<float>,       mixed double and std::complex<double>    
           -     Sum of vector magnitudes (functions)     
         * -           \ `axpy <axpy.html>`__\    
           -           \ `axpy <axpy-usm-version.html>`__\    
           -     float, double, std::complex<float>,       std::complex<double>    
           -     Scalar-vector product (routines)     
         * -           \ `copy <copy.html>`__\    
           -           \ `copy <copy-usm-version.html>`__\    
           -     float, double, std::complex<float>,       std::complex<double>    
           -     Copy vector (routines)     
         * -           \ `dot <dot.html>`__\    
           -           \ `dot <dot-usm-version.html>`__\    
           -     float, double, mixed float and double     
           -     Dot product (functions)     
         * -           \ `sdsdot <sdsdot.html>`__\    
           -           \ `sdsdot <sdsdot-usm-version.html>`__\    
           -     mixed float and double     
           -     Dot product with double precision (functions)     
         * -           \ `dotc <dotc.html>`__\    
           -           \ `dotc <dotc-usm-version.html>`__\    
           -     std::complex<float>, std::complex<double>     
           -     Dot product conjugated (functions)     
         * -           \ `dotu <dotu.html>`__\    
           -           \ `dotu <dotu-usm-version.html>`__\    
           -     std::complex<float>, std::complex<double>     
           -     Dot product unconjugated (functions)     
         * -           \ `nrm2 <nrm2.html>`__\    
           -           \ `nrm2 <nrm2-usm-version.html>`__\    
           -     float, double, mixed float and std::complex<float>,       mixed double and std::complex<double>    
           -     Vector 2-norm (Euclidean norm) (functions)     
         * -           \ `rot <rot.html>`__\    
           -           \ `rot <rot-usm-version.html>`__\    
           -     float, double, mixed float and std::complex<float>,       mixed double and std::complex<double>    
           -     Plane rotation of points (routines)     
         * -           \ `rotg <rotg.html>`__\    
           -           \ `rotg <rotg-usm-version.html>`__\    
           -     float, double, std::complex<float>,       std::complex<double>    
           -     Generate Givens rotation of points (routines)     
         * -           \ `rotm <rotm.html>`__\    
           -           \ `rotm <rotm-usm-version.html>`__\    
           -     float, double     
           -     Modified Givens plane rotation of points (routines)          
         * -           \ `rotmg <rotmg.html>`__\    
           -           \ `rotmg <rotmg-usm-version.html>`__\    
           -     float, double     
           -     Generate modified Givens plane rotation of points       (routines)    
         * -           \ `scal <scal.html>`__\    
           -           \ `scal <scal-usm-version.html>`__\    
           -     float, double, std::complex<float>,       std::complex<double>, mixed float and std::complex<float>, mixed      double and std::complex<double>    
           -     Vector-scalar product (routines)     
         * -           \ `swap <swap.html>`__\    
           -           \ `swap <swap-usm-version.html>`__\    
           -     float, double, std::complex<float>,       std::complex<double>    
           -     Vector-vector swap (routines)     
         * -           \ `iamax <iamax.html>`__\    
           -           \ `iamax <iamax-usm-version.html>`__\    
           -     float, double, std::complex<float>,       std::complex<double>    
           -     Index of the maximum absolute value element of a       vector (functions)    
         * -           \ `iamin <iamin.html>`__\    
           -           \ `iamin <iamin-usm-version.html>`__\    
           -     float, double, std::complex<float>,       std::complex<double>    
           -     Index of the minimum absolute value element of a       vector (functions)    

.. toctree::
    :hidden:

    asum
    asum-usm-version
    axpy
    axpy-usm-version
    copy
    copy-usm-version
    dot
    dot-usm-version
    dotc
    dotc-usm-version
    dotu
    dotu-usm-version
    iamax
    iamax-usm-version
    iamin
    iamin-usm-version
    nrm2
    nrm2-usm-version
    rot
    rot-usm-version
    rotg
    rotg-usm-version
    rotm
    rotm-usm-version
    rotmg
    rotmg-usm-version
    scal
    scal-usm-version
    sdsdot
    sdsdot-usm-version
    swap
    swap-usm-version

