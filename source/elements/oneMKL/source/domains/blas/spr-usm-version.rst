.. _spr-usm-version:

spr (USM Version)
=================


.. container::


   Performs a rank-1 update of a symmetric packed matrix.


   .. container:: section
      :name: GUID-34904813-AFD9-4349-9DAC-A7221FBE9F97


      .. rubric:: Syntax
         :name: syntax
         :class: sectiontitle


      .. container:: dlsyntaxpara


         .. cpp:function::  event spr(queue &exec_queue, uplo upper_lower,         std::int64_t n, T alpha, const T \*x, std::int64_t incx, T \*a,         const vector_class<event> &dependencies = {})

         The USM version of ``spr`` supports the following precisions.


         .. list-table:: 
            :header-rows: 1

            * -  T 
            * -  ``float`` 
            * -  ``double`` 




   .. container:: section
      :name: GUID-E387B33A-CA59-45D8-BB01-31DF76C82A0D


      .. rubric:: Description
         :name: description
         :class: sectiontitle


      The spr routines compute a scalar-vector-vector product and add
      the result to a symmetric packed matrix. The operation is defined
      as


     


         A <- alpha*x*x :sup:`T` + A


      where:


      ``alpha`` is scalar,


      ``A`` is an ``n``-by-``n`` symmetric matrix, supplied in packed
      form,


      ``x`` is a vector of length ``n``.


   .. container:: section
      :name: GUID-E1436726-01FE-4206-871E-B905F59A96B4


      .. rubric:: Input Parameters
         :name: input-parameters
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
         ``A`` must have size at least (``n``\ \*(``n``-n))/2. See
         `Matrix and Vector
         Storage <../matrix-storage.html>`__ for
         more details.


      dependencies
         List of events to wait for before starting computation, if any.
         If omitted, defaults to no dependencies.


   .. container:: section
      :name: GUID-9FBC2F3B-EB8F-4733-ABBA-08D5685A761B


      .. rubric:: Output Parameters
         :name: output-parameters
         :class: sectiontitle


      a
         Pointer to the updated upper triangular part of the symmetric
         matrix ``A`` if ``upper_lower =upper``, or the updated lower
         triangular part of the symmetric matrix ``A`` if
         ``upper_lower =lower``.


   .. container:: section
      :name: GUID-FE9BC089-7D9E-470F-B1B6-2679FBFC249F


      .. rubric:: Return Values
         :name: return-values
         :class: sectiontitle


      Output event to wait on to ensure computation is complete.


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** :ref:`blas-level-2-routines`
      


