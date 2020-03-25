.. _gesvd_get_lwork:

gesvd_get_lwork
===============


.. container::


   Computes the worksize needed for the function
   `gesvd <gesvd.html>`__. This
   routine belongs to the ``onemkl::lapack``\ namespace.


   .. container:: section
      :name: GUID-814D7756-F1E2-4417-A0EA-B4294B8303D4


      .. rubric:: Syntax
         :name: syntax
         :class: sectiontitle


      .. container:: dlsyntaxpara


         .. cpp:function::  template <typename fp>void         gesvd_get_lwork(queue &exec_queue, job jobu, job jobvt,         std::int64_t m, std::int64_t n, std::int64_t lda, std::int64_t         ldu, std::int64_t ldvt, std::int64_t &lwork)

         ``gesvd_get_lwork`` supports the following precisions.


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


      Computes the worksize needed for the singular value decomposition
      of a general rectangular matrix
      (`gesvd <gesvd.html>`__).
      Calls to this routine must specify the template parameter
      explicitly.


   .. container:: section
      :name: GUID-F841BA63-D4EE-4C75-9831-BB804CEA8622


      .. rubric:: Input Parameters
         :name: input-parameters
         :class: sectiontitle


      exec_queue
         The queue where the routine should be executed.


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
      :name: GUID-F0C3D97D-E883-4070-A1C2-4FE43CC37D12


      .. rubric:: Output Parameters
         :name: output-parameters
         :class: sectiontitle


      lwork
         The integer lwork contains the size of the buffer needed for
         computations in
         `gesvd <gesvd.html>`__.


   .. container:: section
      :name: GUID-C97BF68F-B566-4164-95E0-A7ADC290DDE2


      .. rubric:: Example
         :name: example
         :class: sectiontitle


      An example of how to use ``gesvd_get_lwork``\ can be found in the
      oneMKL installation directory, under:


      ::


         examples/sycl/lapack/gesvd.cpp


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** `LAPACK
      Routines <lapack.html>`__


.. container::

