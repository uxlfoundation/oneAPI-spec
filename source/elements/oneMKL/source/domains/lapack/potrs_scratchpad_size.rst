.. _onemkl_lapack_potrs_scratchpad_size:

onemkl::lapack::potrs_scratchpad_size
=====================================


.. container::


   Computes size of scratchpad memory required for :ref:`onemkl_lapack_potrs` function.


         ``potrs_scratchpad_size`` supports the following precisions.


         .. list-table:: 
            :header-rows: 1

            * -  T 
            * -  ``float`` 
            * -  ``double`` 
            * -  ``std::complex<float>`` 
            * -  ``std::complex<double>`` 




   .. container:: section


      .. rubric:: Description
         :class: sectiontitle


      Computes the number of elements of type T the scratchpad memory to be passed to :ref:`onemkl_lapack_potrs` function should be able to hold.
      Calls to this routine must specify the template parameter
      explicitly.


onemkl::lapack::potrs_scratchpad_size
-------------------------------------

.. container::

   .. container:: section


      .. rubric:: Syntax
         :class: sectiontitle


      .. container:: dlsyntaxpara


         .. cpp:function::  template <typename T>std::int64_t         onemkl::lapack::potrs_scratchpad_size(cl::sycl::queue &queue, onemkl::uplo upper_lower, std::int64_t n, std::int64_t nrhs, std::int64_t         lda, std::int64_t ldb)

   .. container:: section


      .. rubric:: Input Parameters
         :class: sectiontitle


      queue
         Device queue where calculations by :ref:`onemkl_lapack_potrs` function will be performed.

      upper_lower
         Indicates how the input matrix has been factored:

         If ``upper_lower = onemkl::uplo::upper``, the upper triangle   ``U`` of ``A`` is stored, where ``A`` = ``U``\ :sup:`T`\ \*\ ``U``   for real data, ``A`` = ``U``\ :sup:`H`\ \*\ ``U`` for complex data.

         If ``upper_lower = onemkl::uplo::lower``, the lower triangle   ``L`` of ``A`` is stored, where ``A`` = ``L``\ \*\ ``L``\ :sup:`T`   for real data, ``A`` = ``L``\ \*\ ``L``\ :sup:`H` for complex   data.

      n
         The order of matrix ``A`` (``0≤n``).

      nrhs
         The number of right-hand sides (``0≤nrhs``).

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


      The number of elements of type T the scratchpad memory to be passed to :ref:`onemkl_lapack_potrs` function should be able to hold.


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** :ref:`onemkl_lapack-linear-equation-routines` 


