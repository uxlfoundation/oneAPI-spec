.. _geru-usm-version:

geru (USM Version)
==================


.. container::


   Computes a rank-1 update (unconjugated) of a general complex matrix.


   .. container:: section
      :name: GUID-5942D28E-EDD6-4759-B19E-FBB51F35125B


      .. rubric:: Syntax
         :class: sectiontitle


      .. container:: dlsyntaxpara


         .. cpp:function::  event geru(queue &exec_queue, std::int64_t m,         std::int64_t n, T alpha, const T \*x, std::int64_t incx, const         T \*y, std::int64_t incy, T \*a, std::int64_t lda, const         vector_class<event> &dependencies = {})

         The USM version of ``geru`` supports the following precisions.


         .. list-table:: 
            :header-rows: 1

            * -  T 
            * -  ``std::complex<float>`` 
            * -  ``std::complex<double>`` 




   .. container:: section
      :name: GUID-75ECE219-BA77-48E8-B13B-FB504DD60CD4


      .. rubric:: Description
         :class: sectiontitle


      The geru routines routines compute a scalar-vector-vector product
      and add the result to a general matrix. The operation is defined
      as


     


         A <- alpha*x*y :sup:`T` + A


      where:


      ``alpha`` is a scalar,


      ``A`` is an ``m``-by-``n`` matrix,


      ``x`` is a vector of length ``m``,


      ``y`` is a vector of length ``n``.


   .. container:: section
      :name: GUID-E1436726-01FE-4206-871E-B905F59A96B4


      .. rubric:: Input Parameters
         :class: sectiontitle


      exec_queue
         The queue where the routine should be executed.


      m
         Number of rows of ``A``. Must be at least zero.


      n
         Number of columns of ``A``. Must be at least zero.


      alpha
         Scaling factor for the matrix-vector product.


      x
         Pointer to the input vector ``x``. The array holding input
         vector ``x`` must be of size at least (1 + (``m`` -
         1)*abs(``incx``)). See `Matrix and Vector
         Storage <../matrix-storage.html>`__ for
         more details.


      incx
         Stride of vector ``x``.


      y
         Pointer to input/output vector ``y``. The array holding
         input/output vector ``y`` must be of size at least (1 + (``n``
         - 1)*abs(``incy``)). See `Matrix and Vector
         Storage <../matrix-storage.html>`__ for
         more details.


      incy
         Stride of vector ``y``.


      a
         Pointer to input matrix ``A``. The array holding input matrix
         ``A`` must have size at least ``lda``\ \*\ ``n``. See `Matrix
         and Vector
         Storage <../matrix-storage.html>`__ for
         more details.


      lda
         Leading dimension of matrix ``A``. Must be at least ``m``, and
         positive.


      dependencies
         List of events to wait for before starting computation, if any.
         If omitted, defaults to no dependencies.


   .. container:: section
      :name: GUID-6E9315E9-DDCF-485D-8BDF-AB4BF8448BE1


      .. rubric:: Output Parameters
         :class: sectiontitle


      a
         Pointer to the updated matrix ``A``.


   .. container:: section
      :name: GUID-FE9BC089-7D9E-470F-B1B6-2679FBFC249F


      .. rubric:: Return Values
         :name: return-values
         :class: sectiontitle


      Output event to wait on to ensure computation is complete.


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** :ref:`blas-level-2-routines`
      


