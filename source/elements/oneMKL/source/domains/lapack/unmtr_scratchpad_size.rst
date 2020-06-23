.. _onemkl_lapack_unmtr_scratchpad_size:

unmtr_scratchpad_size
=====================


.. container::


   Computes size of scratchpad memory required for :ref:`onemkl_lapack_unmtr` function.


         ``unmtr_scratchpad_size`` supports the following precisions.


         .. list-table:: 
            :header-rows: 1

            * -  T 
            * -  ``std::complex<float>`` 
            * -  ``std::complex<double>`` 




   .. container:: section


      .. rubric:: Description
         :class: sectiontitle


      Computes the number of elements of type T the scratchpad memory to be passed to :ref:`onemkl_lapack_unmtr` function should be able to hold.
      Calls to this routine must specify the template parameter explicitly.


unmtr_scratchpad_size
---------------------

.. container::

   .. container:: section


      .. rubric:: Syntax
         :class: sectiontitle


      .. container:: dlsyntaxpara


         .. cpp:function::  template <typename T>std::int64_t         onemkl::lapack::unmtr_scratchpad_size(cl::sycl::queue &queue, onemkl::side left_right, onemkl::uplo         upper_lower, onemkl::transpose trans, std::int64_t m, std::int64_t n,         std::int64_t lda, std::int64_t ldc)

   .. container:: section


      .. rubric:: Input Parameters
         :class: sectiontitle


      queue
         Device queue where calculations by :ref:`onemkl_lapack_unmtr` function will be performed.


      left_right
         Must be either ``side::left`` or ``side::right``.


         If ``left_right=side::left``, ``Q`` or ``Q``\ :sup:`H` is
         applied to ``C`` from the left.


         If ``left_right=side::right``, ``Q`` or ``Q``\ :sup:`H` is
         applied to ``C`` from the right.


      upper_lower
         Must be either ``uplo::upper`` or ``uplo::lower``. Uses the
         same upper_lower as supplied to
         :ref:`onemkl_lapack_hetrd`.


      trans
         Must be either ``transpose::nontrans`` or
         ``transpose::conjtrans``.


         If ``trans=transpose::nontrans``, the routine multiplies ``C``
         by ``Q``.


         If ``trans=transpose::conjtrans``, the routine multiplies ``C``
         by ``Q``\ :sup:`H`.


      m
         The number of rows in the matrix ``C`` (``m≥0``).


      n
         The number of columns the matrix ``C`` (``n≥0``).


      k
         The number of elementary reflectors whose product defines the
         matrix ``Q`` (``0≤k≤n``).


      lda
         The leading dimension of a\ ``(max(1,r)≤lda)``.


      ldc
         The leading dimension of c\ ``(max(1,n)≤ldc)``.


   .. container:: section


      .. rubric:: Throws
         :class: sectiontitle


      onemkl::lapack::exception
         Exception is thrown in case of incorrect argument value is supplied.
         Position of wrong argument can be determined by `get_info()` method of exception object.


   .. container:: section


      .. rubric:: Return Value
         :class: sectiontitle


      The number of elements of type T the scratchpad memory to be passed to :ref:`onemkl_lapack_unmtr` function should be able to hold.


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** :ref:`onemkl_lapack-singular-value-eigenvalue-routines` 


