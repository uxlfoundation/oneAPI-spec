.. _onemkl_lapack_sytrf:

sytrf
=====


.. container::


   Computes the Bunch-Kaufman factorization of a symmetric matrix.


      sytrf supports the following precisions.


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


   The routine computes the factorization of a real/complex symmetric
   matrix ``A`` using the Bunch-Kaufman diagonal pivoting method. The
   form of the factorization is:


   -  if ``upper_lower=uplo::upper``, ``A`` = ``U*D*U``\ :sup:`T`


   -  if ``upper_lower=uplo::lower``, ``A`` = ``L*D*L``\ :sup:`T`


   where ``A`` is the input matrix, ``U`` and ``L`` are products of
   permutation and triangular matrices with unit diagonal (upper
   triangular for ``U`` and lower triangular for ``L``), and ``D`` is a
   symmetric block-diagonal matrix with 1-by-1 and 2-by-2 diagonal
   blocks. ``U`` and ``L`` have 2-by-2 unit diagonal blocks
   corresponding to the 2-by-2 blocks of ``D``.


sytrf (BUFFER Version)
----------------------

.. container::

   .. container:: section


      .. rubric:: Syntax
         :class: sectiontitle


      .. cpp:function::  void onemkl::lapack::sytrf(cl::sycl::queue &queue, onemkl::uplo upper_lower,      std::int64_t n, cl::sycl::buffer<T,1> &a, std::int64_t lda, cl::sycl::buffer<int_64,1>      &ipiv, cl::sycl::buffer<T,1> &scratchpad, std::int64_t scratchpad_size)

.. container:: section


   .. rubric:: Input Parameters
      :class: sectiontitle


   queue
      The queue where the routine should be executed.

   upper_lower
      Indicates whether the upper or lower triangular part of    ``A`` is stored and how ``A`` is factored:

         If   ``upper_lower=uplo::upper``, the buffer a stores the upper triangular   part of the matrix ``A``, and ``A`` is factored as ``U*D*UT``.

         If ``upper_lower=uplo::lower``, the buffer a stores   the lower triangular part of the matrix ``A``, and ``A`` is factored   as ``L*D*LT``.

   n
      The order of matrix ``A`` (``0≤n``).

   a
      The buffer ``a``, size max(1,lda\*n). The buffer ``a``    contains either the upper or the lower triangular part of the matrix   ``A`` (see ``upper_lower``). The second dimension of ``a`` must be at   least ``max(1, n)``.

   lda
      The leading dimension of ``a``.

   scratchpad_size
      Size of scratchpad memory as a number of floating point elements of type T.
      Size should not be less than the value returned by :ref:`onemkl_lapack_sytrf_scratchpad_size` function.


.. container:: section


   .. rubric:: Output Parameters
      :class: sectiontitle


   a
      The upper or lower triangular part of a is overwritten by    details of the block-diagonal matrix ``D`` and the multipliers used   to obtain the factor ``U`` (or ``L``).

   ipiv
      Buffer, size at least ``max(1, n)``. Contains details of    the interchanges and the block structure of ``D``. If   ``ipiv(i)=k>0``, then ``d``\ :sub:`ii` is a 1-by-1 block, and the   ``i``-th row and column of ``A`` was interchanged with the ``k``-th   row and column.

         If ``upper_lower=onemkl::uplo::upper``   and ``ipiv(i)=ipiv(i-1)=-m<0``, then ``D`` has a 2-by-2 block in   rows/columns ``i`` and ``i``-1, and (``i``-1)-th row and column of   ``A`` was interchanged with the ``m``-th row and   column.

         If ``upper_lower=onemkl::uplo::lower`` and   ``ipiv(i)=ipiv(i+1)=-m<0``, then ``D`` has a 2-by-2 block in   rows/columns ``i`` and ``i``\ +1, and (``i``\ +1)-th row and column   of ``A`` was interchanged with the ``m``-th row and column.

   scratchpad
      Buffer holding scratchpad memory to be used by routine for storing intermediate results.


   .. container:: section


      .. rubric:: Throws
         :class: sectiontitle


      onemkl::lapack::exception
         Exception is thrown in case of problems happened during calculations. The ``info`` code of the problem can be obtained by `get_info()` method of exception object:

         If ``info=-i``, the ``i``-th parameter had an illegal value.

         If ``info=i``, ``d``\ :sub:`ii` is 0. The factorization has been completed, but ``D`` is exactly singular. Division by 0 will occur if you use ``D`` for solving a system of linear equations.

         If ``info`` equals to value passed as scratchpad size, and ``get_detail()`` returns non zero, then passed scratchpad is of insufficient size, and required size should not be less than value return by ``get_detail()`` method of exception object.


sytrf (USM Version)
----------------------

.. container::

   .. container:: section


      .. rubric:: Syntax
         :class: sectiontitle


      .. cpp:function::  cl::sycl::event onemkl::lapack::sytrf(cl::sycl::queue &queue, onemkl::uplo upper_lower,      std::int64_t n, T *a, std::int64_t lda, int_64 *ipiv, T *scratchpad, std::int64_t scratchpad_size, const cl::sycl::vector_class<cl::sycl::event> &events = {})

.. container:: section


   .. rubric:: Input Parameters
      :class: sectiontitle


   queue
      The queue where the routine should be executed.

   upper_lower
      Indicates whether the upper or lower triangular part of    ``A`` is stored and how ``A`` is factored:

         If   ``upper_lower=uplo::upper``, the array a stores the upper triangular   part of the matrix ``A``, and ``A`` is factored as ``U*D*UT``.

         If ``upper_lower=uplo::lower``, the array a stores   the lower triangular part of the matrix ``A``, and ``A`` is factored   as ``L*D*LT``.

   n
      The order of matrix ``A`` (``0≤n``).

   a
      The pointer to ``A``, size max(1,lda\*n), containing either the upper or the lower triangular part of the matrix   ``A`` (see ``upper_lower``). The second dimension of ``a`` must be at   least ``max(1, n)``.

   lda
      The leading dimension of ``a``.

   scratchpad_size
      Size of scratchpad memory as a number of floating point elements of type T.
      Size should not be less than the value returned by :ref:`onemkl_lapack_sytrf_scratchpad_size` function.

   events
      List of events to wait for before starting computation. Defaults to empty list.


.. container:: section


   .. rubric:: Output Parameters
      :class: sectiontitle


   a
      The upper or lower triangular part of a is overwritten by    details of the block-diagonal matrix ``D`` and the multipliers used   to obtain the factor ``U`` (or ``L``).

   ipiv
      Pointer to array of size at least ``max(1, n)``. Contains details of    the interchanges and the block structure of ``D``. If   ``ipiv(i)=k>0``, then ``d``\ :sub:`ii` is a 1-by-1 block, and the   ``i``-th row and column of ``A`` was interchanged with the ``k``-th   row and column.

         If ``upper_lower=onemkl::uplo::upper``   and ``ipiv(i)=ipiv(i-1)=-m<0``, then ``D`` has a 2-by-2 block in   rows/columns ``i`` and ``i``-1, and (``i``-1)-th row and column of   ``A`` was interchanged with the ``m``-th row and   column.
         
         If ``upper_lower=onemkl::uplo::lower`` and   ``ipiv(i)=ipiv(i+1)=-m<0``, then ``D`` has a 2-by-2 block in   rows/columns ``i`` and ``i``\ +1, and (``i``\ +1)-th row and column   of ``A`` was interchanged with the ``m``-th row and column.

   scratchpad
      Pointer to scratchpad memory to be used by routine for storing intermediate results.


   .. container:: section


      .. rubric:: Throws
         :class: sectiontitle


      onemkl::lapack::exception
         Exception is thrown in case of problems happened during calculations. The ``info`` code of the problem can be obtained by `get_info()` method of exception object:

         If ``info=-i``, the ``i``-th parameter had an illegal value.

         If ``info=i``, ``d``\ :sub:`ii` is 0. The factorization has been completed, but ``D`` is exactly singular. Division by 0 will occur if you use ``D`` for solving a system of linear equations.

         If ``info`` equals to value passed as scratchpad size, and ``get_detail()`` returns non zero, then passed scratchpad is of insufficient size, and required size should not be less than value return by ``get_detail()`` method of exception object.


   .. container:: section


      .. rubric:: Return Values
         :class: sectiontitle


      Output event to wait on to ensure computation is complete.


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** :ref:`onemkl_lapack-linear-equation-routines` 


