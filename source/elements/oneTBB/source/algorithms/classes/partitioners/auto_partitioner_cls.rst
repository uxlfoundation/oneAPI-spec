======================
auto_partitioner Class
======================


Summary
-------

Specify that a parallel loop should optimize its range subdivision based
on work-stealing events.

Header
------

.. code:: cpp

   #include "tbb/partitioner.h"


Syntax
------

.. code:: cpp

   class auto_partitioner;


Description
-----------

A loop template with an ``auto_partitioner`` attempts to
minimize range splitting while providing ample opportunities for
work-stealing.

The range subdivision is initially limited to S subranges, where S is
proportional to the number of threads specified by the
``task_scheduler_init`` or ``task_arena``.
Each of these subranges is not divided further unless it is stolen by an
idle thread. If stolen, it is further subdivided to create additional
subranges. Thus a loop template with an
``auto_partitioner`` creates additional subranges only when
necessary to balance load.

.. tip::

   When using ``auto_partitioner`` and a
   ``blocked_range`` for a parallel loop, the body may
   receive a subrange larger than the grain size of the ``blocked_range``.
   Therefore do not assume that the grain size is an upper
   bound on the size of a subrange. Use ``simple_partitioner``
   if an upper bound is required.


Members
-------

.. code:: cpp

   namespace tbb {
       class auto_partitioner {
       public:
           auto_partitioner();
           ~auto_partitioner();
       };
   }

The following table provides additional information on the members of
this template class.

= ========================================================================================
\ Member, Description
==========================================================================================
\ ``auto_partitioner()``
  \
  Construct an ``auto_partitioner``.
------------------------------------------------------------------------------------------
\ ``~auto_partitioner()``
  \
  Destroy this ``auto_partitioner``.
------------------------------------------------------------------------------------------
= ========================================================================================


See also:

* :doc:`task_arena Class <../../../task_scheduler/task_arena_cls>`
