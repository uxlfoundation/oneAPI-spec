.. _onemkl_lapack_ormqr_scratchpad_size:

onemkl::lapack::ormqr_scratchpad_size
=====================================


.. container::


   Computes size of scratchpad memory required for :ref:`onemkl_lapack_ormqr` function.


         ``ormqr_scratchpad_size`` supports the following precisions.


         .. list-table:: 
            :header-rows: 1

            * -  T 
            * -  ``float`` 
            * -  ``double`` 




   .. container:: section


      .. rubric:: Description
         :class: sectiontitle


      Computes the number of elements of type T the scratchpad memory to be passed to :ref:`onemkl_lapack_ormqr` function should be able to hold.
      Calls to this routine must specify the template parameter
      explicitly.


onemkl::lapack::ormqr_scratchpad_size
-------------------------------------

.. container::

   .. container:: section


      .. rubric:: Syntax
         :class: sectiontitle


      .. container:: dlsyntaxpara


         .. cpp:function::  template <typename T>std::int64_t         onemkl::lapack::ormqr_scratchpad_size(cl::sycl::queue &queue, onemkl::side left_right,         onemkl::transpose trans, std::int64_t m, std::int64_t n,         std::int64_t k, std::int64_t lda, std::int64_t ldc,         std::int64_t &scratchpad_size)

   .. container:: section


      .. rubric:: Input Parameters
         :class: sectiontitle


      queue
         Device queue where calculations by :ref:`onemkl_lapack_ormqr` function will be performed.


      left_right
         If ``left_right=onemkl::side::left``, ``Q`` or ``Q``\ :sup:`T` is
         applied to ``C`` from the left.


         If ``left_right=onemkl::side::right``, ``Q`` or ``Q``\ :sup:`T` is
         applied to ``C`` from the right.


      trans
         If ``trans=onemkl::transpose::trans``, the routine multiplies
         ``C`` by ``Q``.


         If ``trans=onemkl::transpose::nontrans``, the routine multiplies
         ``C`` by ``Q``\ :sup:`T`.


      m
         The number of rows in the matrix ``A`` (``0≤m``).


      n
         The number of columns in the matrix ``A`` (``0≤n≤m``).


      k
         The number of elementary reflectors whose product defines the
         matrix ``Q`` (``0≤k≤n``).


      lda
         The leading dimension of ``a``.


      ldc
         The leading dimension of c.


   .. container:: section


      .. rubric:: Throws
         :class: sectiontitle


      onemkl::lapack::exception
         Exception is thrown in case of incorrect argument value is supplied.
         Position of wrong argument can be determined by `get_info()` method of exception object.


   .. container:: section


      .. rubric:: Return Value
         :class: sectiontitle


      The number of elements of type T the scratchpad memory to be passed to :ref:`onemkl_lapack_ormqr` function should be able to hold.


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** :ref:`onemkl_lapack-linear-equation-routines` 


