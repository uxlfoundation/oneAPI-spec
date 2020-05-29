.. _onemkl_lapack_gesvd_scratchpad_size:

onemkl::lapack::gesvd_scratchpad_size
=====================================


.. container::


   Computes size of scratchpad memory required for :ref:`onemkl_lapack_gesvd` function.


         ``gesvd_scratchpad_size`` supports the following precisions.


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


      Computes the number of elements of type T the scratchpad memory to be passed to :ref:`onemkl_lapack_gesvd` function should be able to hold.
      Calls to this routine must specify the template parameter
      explicitly.


onemkl::lapack::gesvd_scratchpad_size
-------------------------------------

.. container::

   .. container:: section


      .. rubric:: Syntax
         :class: sectiontitle


      .. container:: dlsyntaxpara


         .. cpp:function::  template <typename T>std::int64_t         onemkl::lapack::gesvd_scratchpad_size(cl::sycl::queue &queue, onemkl::job jobu, onemkl::job jobvt,         std::int64_t m, std::int64_t n, std::int64_t lda, std::int64_t         ldu, std::int64_t ldvt)

   .. container:: section


      .. rubric:: Input Parameters
         :class: sectiontitle


      queue
         Device queue where calculations by :ref:`onemkl_lapack_gesvd` function will be performed.


      jobu
         Must be ``job::allvec``, ``job::somevec``,
         ``job::overwritevec``, or ``job::novec``. Specifies options for
         computing all or part of the matrix ``U``.


         If ``jobu = job::allvec``, all ``m`` columns of ``U`` are
         returned in the buffer u;


         if ``jobu = job::somevec``, the first ``min(m, n)`` columns of
         ``U`` (the left singular vectors) are returned in the buffer v;


         if ``jobu = job::overwritevec``, the first ``min(m, n)``
         columns of ``U`` (the left singular vectors) are overwritten on
         the buffer a;


         if ``jobu = job::novec``, no columns of ``U`` (no left singular
         vectors) are computed.


      jobvt
         Must be ``job::allvec``, ``job::somevec``,
         ``job::overwritevec``, or ``job::novec``. Specifies options for
         computing all or part of the matrix *V\ T/V\ H*.


         If ``jobvt = job::allvec``, all n columns of *V\ T/V\ H* are
         returned in the buffer vt;


         if ``jobvt = job::somevec``, the first ``min(m, n)`` columns of
         *V\ T/V\ H* (the left singular vectors) are returned in the
         buffer vt;


         if ``jobvt = job::overwritevec``, the first ``min(m, n)``
         columns of *V\ T/V\ H* (the left singular vectors) are
         overwritten on the buffer a;


         if ``jobvt = job::novec``, no columns of *V\ T/V\ H* (no left
         singular vectors) are computed.


      m
         The number of rows in the matrix ``A`` (``0≤m``).


      n
         The number of columns in the matrix ``A`` (``0≤n``).


      lda
         The leading dimension of a.


      ldu
         The leading dimension of u.


      ldvt
         The leading dimension of vt.


   .. container:: section


      .. rubric:: Throws
         :class: sectiontitle


      onemkl::lapack::exception
         Exception is thrown in case of incorrect argument value is supplied.
         Position of wrong argument can be determined by `get_info()` method of exception object.


   .. container:: section


      .. rubric:: Return Value
         :class: sectiontitle


      The number of elements of type T the scratchpad memory to be passed to :ref:`onemkl_lapack_gesvd` function should be able to hold.


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** :ref:`onemkl_lapack-singular-value-eigenvalue-routines` 


