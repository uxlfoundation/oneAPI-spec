.. _rotg-usm-version:

rotg (USM Version)
==================


.. container::


   Computes the parameters for a Givens rotation.


   .. container:: section
      :name: GUID-E4B6E693-AC8C-4BB3-A197-3EB9E905B925


      .. rubric:: Syntax
         :class: sectiontitle


      .. container:: dlsyntaxpara


         .. cpp:function::  event rotg(queue &exec_queue, T \*a, T \*b,         T_real \*c, T \*s, const vector_class<event> &dependencies =         {})

         The USM version of ``rotg`` supports the following precisions.


         .. list-table:: 
            :header-rows: 1

            * -  T 
              -  T_res 
            * -  ``float`` 
              -  ``float`` 
            * -  ``double`` 
              -  ``double`` 
            * -  ``std::complex<float>`` 
              -  ``float`` 
            * -  ``std::complex<double>`` 
              -  ``double`` 




   .. container:: section
      :name: GUID-5614B81D-C736-4714-88AB-29B38F9B3589


      .. rubric:: Description
         :class: sectiontitle


      Given the Cartesian coordinates ``(a, b)`` of a point, the rotg
      routines return the parameters ``c``, ``s``, ``r``, and ``z``
      associated with the Givens rotation. The parameters ``c`` and
      ``s`` define a unitary matrix such that:


      The parameter ``z`` is defined such that if \|\ ``a``\ \| >
      \|\ ``b``\ \|, ``z`` is ``s``; otherwise if ``c`` is not 0 ``z``
      is 1/``c``; otherwise ``z`` is 1.


   .. container:: section
      :name: GUID-C2003328-15AA-4DF0-A417-40BECCA7DEA3


      .. rubric:: Input Parameters
         :class: sectiontitle


      exec_queue
         The queue where the routine should be executed


      a
         Pointer to the ``x``-coordinate of the point.


      b
         Pointer to the ``y``-coordinate of the point.


      dependencies
         List of events to wait for before starting computation, if any.
         If omitted, defaults to no dependencies.


   .. container:: section
      :name: GUID-3B7937E3-2DF7-49A3-8F1E-2C9406BB4E88


      .. rubric:: Output Parameters
         :class: sectiontitle


      a
         Pointer to the parameter ``r`` associated with the Givens
         rotation.


      b
         Pointer to the parameter ``z`` associated with the Givens
         rotation.


      c
         Pointer to the parameter ``c`` associated with the Givens
         rotation.


      s
         Pointer to the parameter ``s`` associated with the Givens
         rotation.


   .. container:: section
      :name: GUID-FE9BC089-7D9E-470F-B1B6-2679FBFC249F


      .. rubric:: Return Values
         :class: sectiontitle


      Output event to wait on to ensure computation is complete.


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** :ref:`blas-level-1-routines`
      


