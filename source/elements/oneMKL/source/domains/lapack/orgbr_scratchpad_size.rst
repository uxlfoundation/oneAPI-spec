.. _onemkl_lapack_orgbr_scratchpad_size:

onemkl::lapack::orgbr_scratchpad_size
=====================================


.. container::


   Computes size of scratchpad memory required for :ref:`onemkl_lapack_orgbr` function.


         ``orgbr_scratchpad_size`` supports the following precisions.


         .. list-table:: 
            :header-rows: 1

            * -  T 
            * -  ``float`` 
            * -  ``double`` 




   .. container:: section


      .. rubric:: Description
         :class: sectiontitle


      Computes the number of elements of type T the scratchpad memory to be passed to :ref:`onemkl_lapack_orgbr` function should be able to hold.
      Calls to this routine must specify the template parameter explicitly.


onemkl::lapack::orgbr_scratchpad_size
-------------------------------------

.. container::

   .. container:: section


      .. rubric:: Syntax
         :class: sectiontitle


      .. container:: dlsyntaxpara


         .. cpp:function::  template <typename T>std::int64_t         onemkl::lapack::orgbr_scratchpad_size(cl::sycl::queue &queue, onemkl::generate gen, std::int64_t         m, std::int64_t n, std::int64_t k, std::int64_t lda,         std::int64_t &scratchpad_size)

   .. container:: section


      .. rubric:: Input Parameters
         :class: sectiontitle


      queue
         Device queue where calculations by :ref:`onemkl_lapack_orgbr` function will be performed.


      gen
         Must be ``generate::q`` or ``generate::p``.


         If ``gen = generate::q``, the routine generates the matrix
         ``Q``.


         If ``gen = generate::p``, the routine generates the matrix
         ``P``\ :sup:`T`.


      m
         The number of rows in the matrix ``Q`` or ``P``\ :sup:`T` to be
         returned ``(0≤m)``.


         If ``gen = generate::q``, ``m ≥ n ≥ min(m, k)``.


         If ``gen = generate::p``, ``n ≥ m ≥ min(n, k)``.


      n
         The number of rows in the matrix ``Q`` or ``P``\ :sup:`T` to be
         returned ``(0≤n)``. See ``m`` for constraints.


      k
         If ``gen = generate::q``, the number of columns in the original
         ``m``-by-``k`` matrix returned by
         :ref:`onemkl_lapack_gebrd`.


         If ``gen = generate::p``, the number of rows in the original
         ``k``-by-``n`` matrix returned by
         :ref:`onemkl_lapack_gebrd`.


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


      The number of elements of type T the scratchpad memory to be passed to :ref:`onemkl_lapack_orgbr` function should be able to hold.


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** :ref:`onemkl_lapack-singular-value-eigenvalue-routines` 


