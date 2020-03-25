.. _getrs:

getrs
=====


.. container::


   Solves a system of linear equations with an LU-factored square
   coefficient matrix, with multiple right-hand sides. This routine
   belongs to the ``onemkl::lapack``\ namespace.


   .. container:: section
      :name: GUID-CEF6C997-610F-4BC3-AC33-51ABDE4A9155


      .. rubric:: Syntax
         :name: syntax
         :class: sectiontitle


      .. cpp:function::  void getrs(queue &exec_queue, transpose trans,      std::int64_t n, std::int64_t nrhs, buffer<T,1> &a, std::int64_t      lda, buffer<std::int64_t,1> &ipiv, buffer<T,1> &b, std::int64_t      ldb, buffer<std::int64_t,1> &info)

      ``getrs`` supports the following precisions.


      .. list-table:: 
         :header-rows: 1

         * -  T 
         * -  ``float`` 
         * -  ``double`` 
         * -  ``std::complex<float>`` 
         * -  ``std::complex<double>`` 




.. container:: section
   :name: GUID-67E5209C-15F5-42EC-8B23-94B5B1680A14


   .. rubric:: Description
      :name: description
      :class: sectiontitle


   The routine solves for ``X`` the following systems of linear
   equations:


   .. list-table:: 
      :header-rows: 1

      * -     \ ``A*X = B``\     
        -     if ``trans``\ =\ ``onemkl::transpose::nontrans``\     
      * -     \ ``AT*X = B``\     
        -     if ``trans``\ =\ ``onemkl::transpose::trans``\     
      * -     \ ``AH*X = B``\     
        -     if ``trans``\ =\ ``onemkl::transpose::conjtrans``\     




   Before calling this routine, you must call
   `?getrf <getrf.html>`__
   to compute the ``LU`` factorization of ``A``.


.. container:: section
   :name: GUID-F841BA63-D4EE-4C75-9831-BB804CEA8622


   .. rubric:: Input Parameters
      :name: input-parameters
      :class: sectiontitle


   exec_queue
      The queue where the routine should be executed.


   trans
      Indicates the form of the equations:


      If ``trans=onemkl::transpose::nontrans``, then ``A*X = B`` is solved
      for ``X``.


      If ``trans=onemkl::transpose::trans``, then ``AT*X = B`` is solved
      for ``X``.


      If ``trans=onemkl::transpose::conjtrans``, then ``AH*X = B`` is
      solved for ``X``.


   n
      The order of the matrix ``A`` and the number of rows in matrix
      ``B(0≤n)``.


   nrhs
      The number of right-hand sides (``0≤nrhs``).


   a
      Buffer containing the factorization of the matrix ``A``, as
      returned by ?getrf. The second dimension of a must be at least
      ``max(1, n)``.


   lda
      The leading dimension of a.


   ipiv
      Array, size at least ``max(1, n)``. The ipiv array, as returned by
      ?getrf.


   b
      The array b contains the matrix ``B`` whose columns are the
      right-hand sides for the systems of equations. The second
      dimension of b must be at least ``max(1,nrhs)``.


   ldb
      The leading dimension of b.


.. container:: section
   :name: GUID-F0C3D97D-E883-4070-A1C2-4FE43CC37D12


   .. rubric:: Output Parameters
      :name: output-parameters
      :class: sectiontitle


   b
      The buffer b is overwritten by the solution matrix ``X``.


   info
      Buffer containing error information.


      If ``info = 0``, the execution is successful.


      If ``info = -i``, the ``i``-th parameter had an illegal value.


      If ``info = i``, the ``i``-th diagonal element of ``U`` is zero,
      and the solve could not be completed.


.. container:: section
   :name: GUID-C97BF68F-B566-4164-95E0-A7ADC290DDE2


   .. rubric:: Example
      :name: example
      :class: sectiontitle


   An example of how to use ``getrs``\ can be found in the oneMKL
   installation directory, under:


   ::


      examples/sycl/lapack/getrs.cpp


.. container:: section
   :name: GUID-3B00B441-C7C0-4D8A-A819-41037F1E5862


   .. rubric:: Known Limitations
      :name: known-limitations
      :class: sectiontitle


   For GPU support, errors are reported through the info parameter, but
   computation does not halt for an algorithmic error.


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** `LAPACK
      Routines <lapack.html>`__


.. container::

