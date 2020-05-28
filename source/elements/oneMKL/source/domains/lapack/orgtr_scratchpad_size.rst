.. _onemkl_lapack_orgtr_scratchpad_size:

onemkl::lapack::orgtr_scratchpad_size
=====================================


.. container::


   Computes size of scratchpad memory required for :ref:`onemkl_lapack_orgtr` function.


         ``orgtr_scratchpad_size`` supports the following precisions.


         .. list-table:: 
            :header-rows: 1

            * -  T 
            * -  ``float`` 
            * -  ``double`` 




   .. container:: section


      .. rubric:: Description
         :class: sectiontitle


      Computes the number of elements of type T the scratchpad memory to be passed to :ref:`onemkl_lapack_orgtr` function should be able to hold.
      Calls to this routine must specify the template parameter
      explicitly.


onemkl::lapack::orgtr_scratchpad_size
-------------------------------------

.. container::

   .. container:: section


      .. rubric:: Syntax
         :class: sectiontitle


      .. container:: dlsyntaxpara


         .. cpp:function::  template <typename T>std::int64_t         onemkl::lapack::orgtr_scratchpad_size(cl::sycl::queue &queue, onemkl::uplo upper_lower,         std::int64_t n, std::int64_t lda)

   .. container:: section


      .. rubric:: Input Parameters
         :class: sectiontitle


      queue
         Device queue where calculations by :ref:`onemkl_lapack_orgtr` function will be performed.


      upper_lower
         Must be ``uplo::upper`` or ``uplo::lower``. Uses the same
         ``upper_lower`` as supplied
         to :ref:`onemkl_lapack_sytrd`.


      n
         The order of the matrix ``Q``\ ``(0≤n)``.


      lda
         The leading dimension of a\ ``(n≤lda)``.


   .. container:: section


      .. rubric:: Throws
         :class: sectiontitle


      onemkl::lapack::exception
         Exception is thrown in case of incorrect argument value is supplied.
         Position of wrong argument can be determined by `get_info()` method of exception object.


   .. container:: section


      .. rubric:: Return Value
         :class: sectiontitle


      The number of elements of type T the scratchpad memory to be passed to :ref:`onemkl_lapack_orgtr` function should be able to hold.


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** :ref:`onemkl_lapack-singular-value-eigenvalue-routines` 


