.. _onemkl_lapack-like-extensions-routines:

LAPACK-like Extensions Routines
===============================


.. container::


   oneAPI Math Kernel Library DPC++ provides additional routines to
   extend the functionality of the LAPACK routines. These include routines
   to compute many independent factorizations, linear equation solutions, and similar.
   The following table lists the LAPACK-like Extensions routine groups.


   .. container:: tablenoborder


      .. list-table:: 
         :header-rows: 1

         * -     Routines
           -     Description     
         * -     :ref:`onemkl_lapack_geqrf_batch`
           -     Computes the QR factorizations of a batch of general matrices.
         * -     :ref:`onemkl_lapack_getrf_batch`
           -     Computes the LU factorizations of a batch of general matrices.   
         * -     :ref:`onemkl_lapack_getri_batch`
           -     Computes the inverses of a batch of LU-factored general matrices.   
         * -     :ref:`onemkl_lapack_getrs_batch`
           -     Solves systems of linear equations with a batch of LU-factored square coefficient matrices, with multiple right-hand sides.    
         * -     :ref:`onemkl_lapack_orgqr_batch`
           -     Generates the real orthogonal/complex unitary matrix ``Q``\ :sub:`i` of the QR factorization formed by geqrf_batch.
         * -     :ref:`onemkl_lapack_potrf_batch`
           -     Computes the Cholesky factorization of a batch of symmetric (Hermitian) positive-definite matrices.   
         * -     :ref:`onemkl_lapack_potrs_batch`
           -     Solves systems of linear equations with a batch of Cholesky-factored symmetric (Hermitian) positive-definite coefficient matrices, with multiple right-hand sides.    




.. toctree::
    :hidden:

    geqrf_batch
    getrf_batch
    getri_batch
    getrs_batch
    orgqr_batch
    potrf_batch
    potrs_batch
