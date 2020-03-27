.. _rotm-usm-version:

rotm (USM Version)
==================


.. container::


   Performs modified Givens rotation of points in the plane.


   .. container:: section
      :name: GUID-F8F2E2EB-1704-454D-BE45-C055D6F4E7D6


      .. rubric:: Syntax
         :name: syntax
         :class: sectiontitle


      .. container:: dlsyntaxpara


         .. cpp:function::  event rotm(queue &exec_queue, std::int64_t n,         T \*x, std::int64_t incx, T \*y, std::int64_t incy, T \*param,         const vector_class<event> &dependencies = {})

         The USM version of ``rotm`` supports the following precisions.


         .. list-table:: 
            :header-rows: 1

            * -  T 
            * -  ``float`` 
            * -  ``double`` 




   .. container:: section
      :name: GUID-856650C6-2998-4452-A34A-DF6CB801087D


      .. rubric:: Description
         :name: description
         :class: sectiontitle


      Given two vectors ``x`` and ``y``, each vector element of these
      vectors is replaced as follows:


      | 
      | |image0|


      for ``i`` from 1 to ``n``, where ``H`` is a modified Givens
      transformation matrix.


   .. container:: section
      :name: GUID-A615800D-734E-4997-BB91-1C76AEEE9EC2


      .. rubric:: Input Parameters
         :name: input-parameters
         :class: sectiontitle


      exec_queue
         The queue where the routine should be executed.


      n
         Number of elements in vector ``x``.


      x
         Pointer to the input vector ``x``. The array holding the vector
         ``x`` must be of size at least (1 + (``n`` - 1)*abs(``incx``)).
         See `Matrix and Vector
         Storage <../matrix-storage.html>`__ for
         more details.


      incx
         Stride of vector x.


      yparam
         Pointer to the input vector ``y``. The array holding the vector
         ``y`` must be of size at least (1 + (``n`` - 1)*abs(``incy``)).
         See `Matrix and Vector
         Storage <../matrix-storage.html>`__ for
         more details.


      incy
         Stride of vector y.


      param
         Pointer to an array of size 5. The elements of the ``param``
         array are:


         ``param``\ [0] contains a switch, ``flag``,


         ``param``\ [1-4] contain *h\ 11*,\ *h\ 21*, *h\ 12*,\ *h\ 22*
         respectively, the components of the modified Givens
         transformation matrix ``H``.


         Depending on the values of ``flag``, the components of ``H`` are
         set as follows:


         | ``flag =``\ ``-1.0``:
         | |image1|


         | ``flag =``\ ``0.0``:
         | |image2|


         | ``flag =``\ ``1.0``:
         | |image3|


         | ``flag =``\ ``-2.0``:
         | |image4|


         In the last three cases, the matrix entries of 1.0, -1.0, 0.0
         are assumed based on the value of ``flag`` and are not required
         to be set in the ``param`` vector.


      dependencies
         List of events to wait for before starting computation, if any.
         If omitted, defaults to no dependencies.


   .. container:: section
      :name: GUID-062D805B-68FF-41F6-8D9A-329C92A77EA3


      .. rubric:: Output Parameters
         :name: output-parameters
         :class: sectiontitle


      x
         Pointer to the updated array ``x``.


      y
         Pointer to the updated array ``y``.


   .. container:: section
      :name: GUID-FE9BC089-7D9E-470F-B1B6-2679FBFC249F


      .. rubric:: Return Values
         :name: return-values
         :class: sectiontitle


      Output event to wait on to ensure computation is complete.


.. container:: familylinks


   .. container:: parentlink


      **Parent topic:** :ref:`blas-level-1-routines`
      



.. |image0| image:: ../equations/GUID-67FC4AB3-40CB-441F-BA9F-88BAAC78Cee1.png
.. |image1| image:: ../equations/GUID-67FC4AB3-40CB-441F-BA9F-88BAAC78Cee2.png
.. |image2| image:: ../equations/GUID-67FC4AB3-40CB-441F-BA9F-88BAAC78Cee3.png
.. |image3| image:: ../equations/GUID-67FC4AB3-40CB-441F-BA9F-88BAAC78Cee4.png
.. |image4| image:: ../equations/GUID-67FC4AB3-40CB-441F-BA9F-88BAAC78Cee5.png

