.. _tpsv-usm-version:

tpsv (USM Version)
==================


.. container::


   Solves a system of linear equations whose coefficients are in a
   triangular packed matrix.


   .. container:: section
      :name: GUID-230CF8CA-B38D-4CB6-9917-029FEF53EBED


      .. rubric:: Syntax
         :name: syntax
         :class: sectiontitle


      .. container:: dlsyntaxpara


         .. cpp:function::  event tpsv(queue &exec_queue, uplo         upper_lower, transpose trans, diag unit_nonunit, std::int64_t         n, std::int64_t k, const T \*a, T \*x, std::int64_t incx, const         vector_class<event> &dependencies = {})

         The USM version of ``tpsv`` supports the following precisions.


         .. list-table:: 
            :header-rows: 1

            * -  T 
            * -  ``float`` 
            * -  ``double`` 
            * -  ``std::complex<float>`` 
            * -  ``std::complex<double>`` 




   .. container:: section
      :name: GUID-7AD9F8E2-1343-4A6D-8C6A-F68D934292B7


      .. rubric:: Description
         :name: description
         :class: sectiontitle


      The tpsv routines solve a system of linear equations whose
      coefficients are in a triangular packed matrix. The operation is
      defined as


     


         op(A)*x = b


      where:


      op(``A``) is one of op(``A``) = ``A``, or op(``A``) =
      ``A``\ :sup:`T`, or op(``A``) = ``A``\ :sup:`H`,


      ``A`` is an ``n``-by-``n`` unit or non-unit, upper or lower
      triangular band matrix, supplied in packed form,


      ``b`` and ``x`` are vectors of length ``n``.


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


      trans
         Specifies op(``A``), the transposition operation applied to
         ``A``. See
         :ref:`onemkl_datatypes` for
         more details.


      unit_nonunit
         Specifies whether the matrix ``A`` is unit triangular or not.
         See
         :ref:`onemkl_datatypes` for
         more details.


      n
         Numbers of rows and columns of ``A``. Must be at least zero.


      a
         Pointer to input matrix ``A``. The array holding input matrix
         ``A`` must have size at least (``n``\ \*(``n``\ +1))/2. See
         `Matrix and Vector
         Storage <../matrix-storage.html>`__ for
         more details.


      x
         Pointer to the ``n``-element right-hand side vector ``b``. The
         array holding the ``n``-element right-hand side vector ``b``
         must be of size at least (1 + (``n`` - 1)*abs(``incx``)). See
         `Matrix and Vector
         Storage <../matrix-storage.html>`__ for
         more details.


      incx
         Stride of vector ``x``.


      dependencies
         List of events to wait for before starting computation, if any.
         If omitted, defaults to no dependencies.


   .. container:: section
      :name: GUID-F515C77C-1E84-424B-A00A-874ACBEFBF9E


      .. rubric:: Output Parameters
         :name: output-parameters
         :class: sectiontitle


      x
         Pointer to the solution vector ``x``.


   .. container:: section
      :name: GUID-FE9BC089-7D9E-470F-B1B6-2679FBFC249F


      .. rubric:: Return Values
         :name: return-values
         :class: sectiontitle


      Output event to wait on to ensure computation is complete.


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** :ref:`blas-level-2-routines`
      


.. container::

