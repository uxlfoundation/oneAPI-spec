.. _onemkl_lapack_orgtr_scratchpad_size:

orgtr_scratchpad_size
=====================

Computes size of scratchpad memory required for :ref:`onemkl_lapack_orgtr` function.

.. container:: section

  .. rubric:: Description
         
``orgtr_scratchpad_size`` supports the following precisions.

     .. list-table:: 
        :header-rows: 1

        * -  T 
        * -  ``float`` 
        * -  ``double`` 
        
Computes the number of elements of type ``T`` the scratchpad memory to be passed to :ref:`onemkl_lapack_orgtr` function should be able to hold.
Calls to this routine must specify the template parameter explicitly.

orgtr_scratchpad_size
---------------------

.. container:: section

  .. rubric:: Syntax
         
.. cpp:function::  template <typename T>std::int64_t         oneapi::mkl::lapack::orgtr_scratchpad_size(cl::sycl::queue &queue, onemkl::uplo upper_lower,         std::int64_t n, std::int64_t lda)

.. container:: section

  .. rubric:: Input Parameters
         
queue
   Device queue where calculations by :ref:`onemkl_lapack_orgtr` function will be performed.

upper_lower
   Must be ``uplo::upper`` or ``uplo::lower``. Uses the same
   ``upper_lower`` as supplied to :ref:`onemkl_lapack_sytrd`.

n
   The order of the matrix :math:`Q` :math:`(0 \le n)`.

lda
   The leading dimension of ``a`` :math:`(n \le \text{lda})`.

.. container:: section

  .. rubric:: Return Value
         
The number of elements of type ``T`` the scratchpad memory to be passed to :ref:`onemkl_lapack_orgtr` function should be able to hold.

**Parent topic:** :ref:`onemkl_lapack-singular-value-eigenvalue-routines`


