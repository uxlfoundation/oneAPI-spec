========================
simple_partitioner Class
========================


Summary
-------

Specify that a parallel loop should recursively split its range until
it cannot be subdivided further.

Header
------

.. code:: cpp

   #include "tbb/partitioner.h"


Syntax
------

.. code:: cpp

   class simple_partitioner;


Description
-----------

A 
``simple_partitioner`` specifies that a loop template
should recursively divide its range until for each subrange 
*r*, the condition 
``!r.is_divisible()`` holds. This is the default behavior
of the loop templates that take a range argument.

.. tip::

   When using 
   ``simple_partitioner`` and a 
   ``blocked_range`` for a parallel loop, be careful to
   specify an appropriate grain size for the 
   ``blocked_range``. The default grain size is 1, which may make
   the subranges much too small for efficient execution.


Members
-------

.. code:: cpp

    
   namespace tbb {
       class simple_partitioner {
       public:
           simple_partitioner();
           ~simple_partitioner();
       }
   }

The following table provides additional information on the
members of this template class.

= ========================================================================================
\ Member, Description
==========================================================================================
\ ``simle_partitioner()``
  \
  Construct an 
  ``simple_partitioner``.
------------------------------------------------------------------------------------------
\ ``~simple_partitioner()``
  \
  Destroy this 
  ``simple_partitioner``.
------------------------------------------------------------------------------------------
= ========================================================================================
