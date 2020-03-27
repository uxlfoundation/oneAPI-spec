.. _hpr-usm-version:

hpr (USM Version)
=================


.. container::


   Computes a rank-1 update of a Hermitian packed matrix.


   .. container:: section
      :name: GUID-61DC4DBA-9357-4129-B8A3-931E2E7335D4


      .. rubric:: Syntax
         :class: sectiontitle


      .. container:: dlsyntaxpara


         .. cpp:function::  event hpr(queue &exec_queue, uplo upper_lower,         std::int64_t n, T alpha, const T \*x, std::int64_t incx, T \*a,         const vector_class<event> &dependencies = {})

         The USM version of\ ``hpr`` supports the following precisions.


         .. list-table:: 
            :header-rows: 1

            * -  T 
            * -  ``std::complex<float>`` 
            * -  ``std::complex<double>`` 




   .. container:: section
      :name: GUID-02B8128C-02CE-4D5C-BE5D-DFD088C90475


      .. rubric:: Description
         :class: sectiontitle


      The hpr routines compute a scalar-vector-vector product and add
      the result to a Hermitian packed matrix. The operation is defined
      as


     


         A <- alpha*x*x :sup:`H` + A


      where:


      ``alpha`` is scalar,


      ``A`` is an ``n``-by-``n`` Hermitian matrix, supplied in packed
      form,


      ``x`` is a vector of length ``n``.


   .. container:: section
      :name: GUID-E1436726-01FE-4206-871E-B905F59A96B4


      .. rubric:: Input Parameters
         :class: sectiontitle


      exec_queue
         The queue where the routine should be executed.


      upper_lower
         Specifies whether ``A`` is upper or lower triangular. See
         :ref:`onemkl_datatypes` for
         more details.


      n
         Number of rows and columns of ``A``. Must be at least zero.


      alpha
         Scaling factor for the matrix-vector product.


      x
         Pointer to input vector ``x``. The array holding input vector
         ``x`` must be of size at least (1 + (``n`` - 1)*abs(``incx``)).
         See `Matrix and Vector
         Storage <../matrix-storage.html>`__ for
         more details.


      incx
         Stride of vector ``x``.


      a
         Pointer to input matrix ``A``. The array holding input matrix
         ``A`` must have size at least (``n``\ \*(``n``-1))/2. See
         `Matrix and Vector
         Storage <../matrix-storage.html>`__ for
         more details.


         The imaginary part of the diagonal elements need not be set and
         are assumed to be zero


      dependencies
         List of events to wait for before starting computation, if any.
         If omitted, defaults to no dependencies.


   .. container:: section
      :name: GUID-7261182A-450B-46F5-8C61-7133597D3530


      .. rubric:: Output Parameters
         :class: sectiontitle


      a
         Pointer to the updated upper triangular part of the Hermitian
         matrix ``A`` if ``upper_lower =upper``, or the updated lower
         triangular part of the Hermitian matrix ``A`` if
         ``upper_lower =lower``.


         The imaginary parts of the diagonal elements are set to zero.


   .. container:: section
      :name: GUID-FE9BC089-7D9E-470F-B1B6-2679FBFC249F


      .. rubric:: Return Values
         :name: return-values
         :class: sectiontitle


      Output event to wait on to ensure computation is complete.


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** :ref:`blas-level-2-routines`
      


