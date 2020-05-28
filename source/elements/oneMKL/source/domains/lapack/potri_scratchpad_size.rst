.. _onemkl_lapack_potri_scratchpad_size:

onemkl::lapack::potri_scratchpad_size
=====================================


.. container::


   Computes size of scratchpad memory required for :ref:`onemkl_lapack_potri` function.


         ``potri_scratchpad_size`` supports the following precisions.


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


      Computes the number of elements of type T the scratchpad memory to be passed to :ref:`onemkl_lapack_potri` function should be able to hold.
      Calls to this routine must specify the template parameter
      explicitly.


onemkl::lapack::potri_scratchpad_size
-------------------------------------

.. container::

   .. container:: section


      .. rubric:: Syntax
         :class: sectiontitle


      .. container:: dlsyntaxpara


         .. cpp:function::  template <typename T>std::int64_t         onemkl::lapack::potri_scratchpad_size(cl::sycl::queue &queue, onemkl::uplo upper_lower, std::int64_t n, std::int64_t         lda)

   .. container:: section


      .. rubric:: Input Parameters
         :class: sectiontitle


      queue
         Device queue where calculations by :ref:`onemkl_lapack_potri` function will be performed.

      upper_lower
         Indicates how the input matrix ``A`` has been    factored:

         If ``upper_lower = onemkl::uplo::upper``, the upper   triangle of ``A`` is stored.

         If   ``upper_lower = onemkl::uplo::lower``, the lower triangle of ``A`` is   stored.

      n
         Specifies the order of the matrix    ``A``\ (``0≤n``).

      lda
         The leading dimension of a.


   .. container:: section


      .. rubric:: Throws
         :class: sectiontitle


      onemkl::lapack::exception
         Exception is thrown in case of incorrect argument value is supplied.
         Position of wrong argument can be determined by `get_info()` method of exception object.


   .. container:: section


      .. rubric:: Return Value
         :class: sectiontitle


      The number of elements of type T the scratchpad memory to be passed to :ref:`onemkl_lapack_potri` function should be able to hold.


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** :ref:`onemkl_lapack-linear-equation-routines` 


