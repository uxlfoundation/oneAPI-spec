.. _rotmg-usm-version:

rotmg (USM Version)
===================


.. container::


   Computes the parameters for a modified Givens rotation.


   .. container:: section
      :name: GUID-DF41021D-C145-495B-A717-45FB5F36E676


      .. rubric:: Syntax
         :class: sectiontitle


      .. container:: dlsyntaxpara


         .. cpp:function::  event rotmg(queue &exec_queue, T *d1, T *d2, T *x1, T *y1, T *param, const vector_class<event> &dependencies = {})

         The USM version of ``rotmg`` supports the following precisions.


         .. list-table:: 
            :header-rows: 1

            * -  T 
            * -  ``float`` 
            * -  ``double`` 




   .. container:: section
      :name: GUID-5525F11C-A739-487E-A7CC-6886A088035D


      .. rubric:: Description
         :class: sectiontitle


      Given Cartesian coordinates (``x``\ :sub:`1`, ``y``\ :sub:`1`) of
      an input vector, the rotmg routines compute the components of a
      modified Givens transformation matrix ``H`` that zeros the
      ``y``-component of the resulting vector:


      | 
      | |image0|


   .. container:: section
      :name: GUID-21946B3A-A859-4293-8EE7-965328AA6717


      .. rubric:: Input Parameters
         :class: sectiontitle


      exec_queue
         The queue where the routine should be executed.


      d1
         Pointer to the scaling factor for the ``x``-coordinate of the
         input vector.


      d2
         Pointer to the scaling factor for the ``y``-coordinate of the
         input vector.


      x1
         Pointer to the ``x``-coordinate of the input vector.


      y1
         Scalar specifying the ``y``-coordinate of the input vector.


      dependencies
         List of events to wait for before starting computation, if any.
         If omitted, defaults to no dependencies.


   .. container:: section
      :name: GUID-1C0481DB-BB35-4DB7-941F-649EDAA77C6F


      .. rubric:: Output Parameters
         :class: sectiontitle


      d1
         Pointer to the first diagonal element of the updated matrix.


      d2
         Pointer to the second diagonal element of the updated matrix.


      x1
         Pointer to the *x*-coordinate of the rotated vector before
         scaling


      param
         Pointer to an array of size 5.


         The elements of the ``param`` array are:


         ``param[0]`` contains a switch, ``flag``. The other array
         elements ``param[1-4]`` contain the components of the array
         ``H``: ``h``\ :sub:`11`, ``h``\ :sub:`21`, ``h``\ :sub:`12`,
         and ``h``\ :sub:`22`, respectively.


         Depending on the values of ``flag``, the components of ``H``
         are set as follows:


         | ``flag =``\ ``-1.0``:
         | |image1|


         | ``flag =``\ ``0.0``:
         | |image2|


         | ``flag =``\ ``1.0``:
         | |image3|


         | ``flag =``\ ``-2.0``:
         | |image4|


         In the last three cases, the matrix entries of 1.0, -1.0, and
         0.0 are assumed based on the value of ``flag`` and are not
         required to be set in the ``param`` vector.


   .. container:: section
      :name: GUID-FE9BC089-7D9E-470F-B1B6-2679FBFC249F


      .. rubric:: Return Values
         :class: sectiontitle


      Output event to wait on to ensure computation is complete.


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** :ref:`blas-level-1-routines`
      



.. |image0| image:: ../equations/GUID-DA21ECDC-F63E-4971-BA3F-492E69335ee1.png
.. |image1| image:: ../equations/GUID-DA21ECDC-F63E-4971-BA3F-492E69335ee2.png
.. |image2| image:: ../equations/GUID-DA21ECDC-F63E-4971-BA3F-492E69335ee3.png
.. |image3| image:: ../equations/GUID-DA21ECDC-F63E-4971-BA3F-492E69335ee4.png
.. |image4| image:: ../equations/GUID-DA21ECDC-F63E-4971-BA3F-492E69335ee5.png

