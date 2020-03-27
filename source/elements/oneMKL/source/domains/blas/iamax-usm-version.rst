.. _iamax-usm-version:

iamax (USM Version)
===================


.. container::


   Finds the index of the element with the largest absolute value in a
   vector.


   .. container:: section
      :name: GUID-D1ABF76D-DB39-4C23-A217-EA2C7C6D1325


      .. rubric:: Syntax
         :class: sectiontitle


      .. container:: dlsyntaxpara


         .. cpp:function::  event iamax(queue &exec_queue, std::int64_t n,         const T \*x, std::int64_t incx, T_res \*result, const         vector_class<event> &dependencies = {})

         The USM version of iamax supports the following precisions.


         .. list-table:: 
            :header-rows: 1

            * -  T 
            * -  ``float`` 
            * -  ``double`` 
            * -  ``std::complex<float>`` 
            * -  ``std:complex<double>`` 




   .. container:: section
      :name: GUID-822D7950-256E-406D-9305-61F761080E69


      .. rubric:: Description
         :class: sectiontitle


      The iamax routines return an index ``i``\ such that ``x``\ [``i``]
      has the maximum absolute value of all elements in vector ``x``
      (real variants), or such that ``|Re(x[i])| + |Im(x[i])|`` is
      maximal (complex variants).


      .. container:: Note


         .. rubric:: Note
            :class: NoteTipHead


         The index is zero-based.


      If either ``n`` or ``incx`` are not positive, the routine returns
      ``0``.


      If more than one vector element is found with the same largest
      absolute value, the index of the first one encountered is
      returned.


      If the vector contains ``NaN`` values, then the routine returns
      the index of the first ``NaN``.


   .. container:: section
      :name: GUID-CE43FE84-2066-4095-BB7E-0691CD045443


      .. rubric:: Input Parameters
         :class: sectiontitle


      exec_queue
         The queue where the routine should be executed.


      n
         The number of elements in vector ``x``.


      x
         The pointer to the input vector ``x``. The array holding the
         input vector ``x`` must be of size at least (1 + (``n`` -
         1)*abs(``incx``)). See `Matrix and Vector
         Storage <../matrix-storage.html>`__ for
         more details.


      incx
         The stride of vector ``x``.


      dependencies
         List of events to wait for before starting computation, if any.
         If omitted, defaults to no dependencies.


   .. container:: section
      :name: ARGUMENTS_EC9F05BE9B09443F8BC59207D5EA40F1


      .. rubric:: Output Parameters
         :class: sectiontitle


      result
         The pointer to where the zero-based index ``i`` of the maximal
         element is stored.


   .. container:: section
      :name: GUID-FE9BC089-7D9E-470F-B1B6-2679FBFC249F


      .. rubric:: Return Values
         :name: return-values
         :class: sectiontitle


      Output event to wait on to ensure computation is complete.


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** :ref:`blas-level-1-routines`
      


