.. _geqrf:

geqrf
=====


.. container::


   Computes the QR factorization of a general m-by-n matrix. This
   routine belongs to the ``onemkl::lapack``\ namespace.


   .. container:: section
      :name: GUID-814D7756-F1E2-4417-A0EA-B4294B8303D4


      .. rubric:: Syntax
         :name: syntax
         :class: sectiontitle


      .. cpp:function::  void geqrf(queue &exec_queue, std::int64_t m,      std::int64_t n, buffer<T,1> &a, std::int64_t lda, buffer<T,1>      &tau, buffer<T,1> &work, std::int64_t lwork, buffer<T,1> &info)

      ``geqrf`` supports the following precisions:


      .. list-table:: 
         :header-rows: 1

         * -  T 
         * -  ``float`` 
         * -  ``double`` 
         * -  ``std::complex<float>`` 
         * -  ``std::complex<double>`` 




.. container:: section
   :name: GUID-A3A0248F-23B3-4E74-BDA2-BB8D23F19A50


   .. rubric:: Description
      :name: description
      :class: sectiontitle


   The routine forms the ``QR`` factorization of a general
   ``m``-by-``n`` matrix ``A``. No pivoting is performed.


   The routine does not form the matrix ``Q`` explicitly. Instead, ``Q``
   is represented as a product of min(``m``, ``n``) elementary
   reflectors. Routines are provided to work with ``Q`` in this
   representation.


.. container:: section
   :name: GUID-F841BA63-D4EE-4C75-9831-BB804CEA8622


   .. rubric:: Input Parameters
      :name: input-parameters
      :class: sectiontitle


   exec_queue
      The queue where the routine should be executed.


   m
      The number of rows in the matrix ``A`` (``0≤m``).


   n
      The number of columns in ``A`` (``0≤n``).


   a
      Buffer holding input matrix ``A``. The buffer a contains the
      matrix ``A``. The second dimension of a must be at least
      ``max(1, n)``.


   lda
      The leading dimension of a; at least max(1, m).


   lwork
      The size of the ``work`` array (``lwork≥n``). Must be computed by
      `geqrf_get_lwork <geqrf_get_lwork.html>`__.


.. container:: section
   :name: GUID-F0C3D97D-E883-4070-A1C2-4FE43CC37D12


   .. rubric:: Output Parameters
      :name: output-parameters
      :class: sectiontitle


   a
      Overwritten by the factorization data as follows:


      The elements on and above the diagonal of the array contain the
      min(m,n)-by-``n`` upper trapezoidal matrix ``R`` (``R`` is upper
      triangular if m≥n); the elements below the diagonal, with the
      array tau, present the orthogonal matrix ``Q`` as a product of
      min(m,n) elementary reflectors.


   tau
      Array, size at least max (1, min(``m``, ``n``)). Contains scalars
      that define elementary reflectors for the matrix ``Q`` in its
      decomposition in a product of elementary reflectors.


   work
      Workspace for internal computations.


   info
      Buffer containing error information.


      If ``info = 0``, the execution is successful.


      If ``info = -i``, the ``i``-th parameter had an illegal value.


.. container:: section
   :name: GUID-C97BF68F-B566-4164-95E0-A7ADC290DDE2


   .. rubric:: Example
      :name: example
      :class: sectiontitle


   An example of how to use ``geqrf``\ can be found in the oneMKL
   installation directory, under:


   ::


      examples/sycl/lapack/geqrf.cpp


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** `LAPACK
      Routines <lapack.html>`__


.. container::

