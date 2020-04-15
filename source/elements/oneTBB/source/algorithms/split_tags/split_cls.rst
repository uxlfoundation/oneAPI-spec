===========
split Class
===========


Summary
-------

Type for dummy argument of a splitting constructor.

Header
------


.. code:: cpp

   #include "tbb/tbb_stddef.h"


Syntax
------

.. code:: cpp

   class split;


Description
-----------

An argument of type ``split`` is used to distinguish a splitting constructor from a copy constructor.

Members
-------

.. code:: cpp

    
   namespace tbb {
       class split {
       };
   }
