.. _getrf:

getrf
=====


.. container::


   Computes the LU factorization of a general m-by-n matrix. This
   routine belongs to the ``onemkl::lapack``\ namespace.


   .. container:: section
      :name: GUID-0ACC96DA-0ADD-4950-9AC4-CB3294AFFC48


      .. rubric:: Syntax
         :name: syntax
         :class: sectiontitle


      .. cpp:function::  void getrf(queue &exec_queue, std::int64_t m,      std::int64_t n, buffer<T,1> &a, std::int64_t lda,      buffer<std::int64_t,1> &ipiv, buffer<std::int64_t,1> &info)

      ``getrf`` supports the following precisions.


      .. list-table:: 
         :header-rows: 1

         * -  T 
         * -  ``float`` 
         * -  ``double`` 
         * -  ``std::complex<float>`` 
         * -  ``std::complex<double>`` 




.. container:: section
   :name: GUID-FA3350DD-9097-43B5-995B-6C2DA4AA1749


   .. rubric:: Description
      :name: description
      :class: sectiontitle


   The routine computes the ``LU`` factorization of a general
   ``m``-by-``n`` matrix ``A`` as


   ::


                          A = P*L*U,


   where ``P`` is a permutation matrix, ``L`` is lower triangular with
   unit diagonal elements (lower trapezoidal if ``m > n``) and ``U`` is
   upper triangular (upper trapezoidal if ``m < n``). The routine uses
   partial pivoting, with row interchanges.


.. container:: section
   :name: GUID-F1A7CCFF-5AD0-4C26-A396-F86A1713DBA8


   .. rubric:: Input Parameters
      :name: input-parameters
      :class: sectiontitle


   .. list-table:: 
      :header-rows: 1

      * -     exec_queue    
        -     The queue where the routine should be executed.    
      * -     m    
        -      The number of rows in the matrix ``A`` (``0≤m``).       
      * -     n    
        -      The number of columns in ``A``\ (``0≤n``).    
      * -     a    
        -     Buffer holding input matrix ``A``. The buffer a contains    the matrix ``A``. The second dimension of a must be at least   ``max(1, n)``.   
      * -     lda    
        -     The leading dimension of a.    




.. container:: section
   :name: GUID-3A62166E-6E38-4FE0-9598-E62232A81937


   .. rubric:: Output Parameters
      :name: output-parameters
      :class: sectiontitle


   .. list-table:: 
      :header-rows: 1

      * -     a    
        -     Overwritten by ``L`` and ``U``. The unit diagonal    elements of ``L`` are not stored.    
      * -     ipiv    
        -     Array, size at least ``max(1,min(m, n))``. Contains the    pivot indices; for ``1 ≤i≤min(m, n)``,row ``i`` was interchanged with   row ``ipiv(i)``.   
      * -     info    
        -     Buffer containing error information.      If    ``info=0``, execution is successful.      If ``info=-i``,   the ``i``-th parameter had an illegal value.      If   ``info=i``, ``uii`` is 0. The factorization has been completed, but   ``U`` is exactly singular. Division by 0 will occur if you use the   factor ``U`` for solving a system of linear equations.   




.. container:: section
   :name: GUID-ACC30BA5-5BDE-4169-95F6-1390ECD55715


   .. rubric:: Example
      :name: example
      :class: sectiontitle


   An example of how to use ``getrf``\ can be found in the oneMKL
   installation directory, under:


   ::


      examples/sycl/lapack/getrf.cpp


.. container:: section
   :name: GUID-81F25E52-7E8D-4508-8696-46F51F0A972C


   .. rubric:: Known Limitations
      :name: known-limitations
      :class: sectiontitle


   For GPU support, errors are reported through the info parameter, but
   computation does not halt for an algorithmic error.


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** `LAPACK
      Routines <lapack.html>`__


