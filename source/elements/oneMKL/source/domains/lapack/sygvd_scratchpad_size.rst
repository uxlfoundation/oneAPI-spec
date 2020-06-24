.. _onemkl_lapack_sygvd_scratchpad_size:

sygvd_scratchpad_size
=====================


.. container::


   Computes size of scratchpad memory required for :ref:`onemkl_lapack_sygvd` function.


         ``sygvd_scratchpad_size`` supports the following precisions.


         .. list-table:: 
            :header-rows: 1

            * -  T 
            * -  ``float`` 
            * -  ``double`` 




   .. container:: section


      .. rubric:: Description
         :class: sectiontitle


      Computes the number of elements of type T the scratchpad memory to be passed to :ref:`onemkl_lapack_sygvd` function should be able to hold.
      Calls to this routine must specify the template parameter explicitly.


sygvd_scratchpad_size
---------------------

.. container::

   .. container:: section


      .. rubric:: Syntax
         :class: sectiontitle


      .. container:: dlsyntaxpara


         .. cpp:function::  template <typename T>std::int64_t         onemkl::lapack::sygvd_scratchpad_size(cl::sycl::queue &queue, std::int64_t itype, onemkl::job         jobz, onemkl::uplo upper_lower, std::int64_t n, std::int64_t lda,         std::int64_t ldb)

   .. container:: section


      .. rubric:: Input Parameters
         :class: sectiontitle


      queue
         Device queue where calculations by :ref:`onemkl_lapack_sygvd` function will be performed.


      itype
         Must be 1 or 2 or 3. Specifies the problem type to be solved:


         if ``itype = 1``, the problem type is ``A*x = lambda*B*x``;


         if ``itype = 2``, the problem type is ``A*B*x = lambda*x``;


         if ``itype = 3``, the problem type is ``B*A*x = lambda*x``.


      jobz
         Must be ``job::novec`` or ``job::vec``.


         If ``jobz = job::novec``, then only eigenvalues are computed.


         If ``jobz = job::vec``, then eigenvalues and eigenvectors are
         computed.


      upper_lower
         Must be ``uplo::upper`` or ``uplo::lower``.


         If ``upper_lower = job::upper``, a and b store the upper
         triangular part of ``A`` and ``B``.


         If ``upper_lower = job::lower``, a and b stores the lower
         triangular part of ``A`` and ``B``.


      n
         The order of the matrices ``A`` and ``B``\ ``(0≤n)``.


      lda
         The leading dimension of a.


      ldb
         The leading dimension of b.


   .. container:: section


      .. rubric:: Throws
         :class: sectiontitle


      onemkl::lapack::exception
         Exception is thrown in case of incorrect argument value is supplied.
         Position of wrong argument can be determined by `get_info()` method of exception object.


   .. container:: section


      .. rubric:: Return Value
         :class: sectiontitle


      The number of elements of type T the scratchpad memory to be passed to :ref:`onemkl_lapack_sygvd` function should be able to hold.


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** :ref:`onemkl_lapack-singular-value-eigenvalue-routines`


