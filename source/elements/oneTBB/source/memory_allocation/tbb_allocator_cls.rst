============================
tbb_allocator Template Class
============================


Summary
-------

Template class for scalable memory allocation if available; possibly non-scalable otherwise.

Syntax
------

.. code:: cpp

   template<typename T> class tbb_allocator


Header
------

.. code:: cpp

   #include "tbb/tbb_allocator.h"


Description
-----------

A ``tbb_allocator`` allocates and frees memory via the oneAPI Threading Building Blocks malloc library if it is available, otherwise it reverts to using malloc and free.

.. tip::

   Set the environment variable ``TBB_VERSION`` to 1 to find out if the TBB malloc library is being used.

 