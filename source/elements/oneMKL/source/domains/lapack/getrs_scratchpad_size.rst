.. _onemkl_lapack_getrs_scratchpad_size:

getrs_scratchpad_size
=====================


.. container::


   Computes size of scratchpad memory required for :ref:`onemkl_lapack_getrs` function.


         ``getrs_scratchpad_size`` supports the following precisions.


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


      Computes the number of elements of type T the scratchpad memory to be passed to :ref:`onemkl_lapack_getrs` function should be able to hold.
      Calls to this routine must specify the template parameter
      explicitly.


getrs_scratchpad_size
---------------------

.. container::

   .. container:: section


      .. rubric:: Syntax
         :class: sectiontitle


      .. container:: dlsyntaxpara


         .. cpp:function::  template <typename T>std::int64_t         onemkl::lapack::getrs_scratchpad_size(cl::sycl::queue &queue, onemkl::transpose trans, std::int64_t n, std::int64_t nrhs, std::int64_t         lda, std::int64_t ldb)

   .. container:: section


      .. rubric:: Input Parameters
         :class: sectiontitle


      queue
         Device queue where calculations by :ref:`onemkl_lapack_getrs` function will be performed.

      trans
         Indicates the form of the equations:

         If ``trans=onemkl::transpose::nontrans``, then ``A*X = B`` is solved
         for ``X``.

         If ``trans=onemkl::transpose::trans``, then ``AT*X = B`` is solved
         for ``X``.

         If ``trans=onemkl::transpose::conjtrans``, then ``AH*X = B`` is
         solved for ``X``.

      n
         The order of the matrix ``A``\ ``(0≤n)`` and the number of rows in matrix
         ``B(0≤n)``.

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


      The number of elements of type T the scratchpad memory to be passed to :ref:`onemkl_lapack_getrs` function should be able to hold.


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** :ref:`onemkl_lapack-linear-equation-routines` 


