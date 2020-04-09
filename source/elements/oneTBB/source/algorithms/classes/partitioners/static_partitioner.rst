========================
static_partitioner Class
========================


Summary
-------

Specify that a parallel algorithm should distribute the work uniformly across threads and
should not do additional load balancing.

Header
------

.. code:: cpp

   #include "tbb/partitioner.h"
         


Syntax
------

.. code:: cpp

   class static_partitioner;


Description
-----------

An algorithm with a ``static_partitioner`` distributes the range across threads
in subranges of approximately equal size. The number of subranges is equal to the number of
threads that can possibly participate in task execution, as specified by
``task_scheduler_init`` and ``task_arena`` classes. These
subranges are not further split.

.. caution::

   ``static_partitioner`` reduces overheads for parallel algorithms
   where the work is originally well-balanced. However, it also limits available
   parallelism, and in case of work imbalance may result in performance loss.

.. caution::

   The regularity of subrange sizes is not guaranteed if the range type does not support
   proportional splitting, or if the grain size is set larger than the
   size of the range divided by the number of threads participating in task execution.

In addition, ``static_partitioner`` uses a deterministic task affinity pattern
to hint the task scheduler how the subranges should be assigned to threads. It might
therefore improve cache locality similarly to ``affinity_partitioner``.

.. tip::

   Use of ``static_partitioner`` is recommended for:
   
   * Parallelizing small well-balanced workloads where enabling additional load balancing
     opportunities would bring more overhead than performance benefits.
   * Porting OpenMP* parallel loops with ``schedule(static)`` if deterministic
     work partitioning across threads is important.
   


Members
-------

.. code:: cpp

   namespace tbb {
       class static_partitioner {
       public:
           static_partitioner();
           ~static_partitioner();
       };
   }
         

The following table provides additional information on the members of this class.

= ========================================================================================
\ Member, Description
==========================================================================================
\ ``static_partitioner()``
  \
  Construct a ``static_partitioner``.
------------------------------------------------------------------------------------------
\ ``~static_partitioner()``
  \
  Destroy this ``static_partitioner``.
------------------------------------------------------------------------------------------
= ========================================================================================


See also:

* :doc:`proportional_split Class <../split_tags/proportional_split_cls>`
* :doc:`Range Concept <../../../general/named_requirements/range>`
* :doc:`task_arena Class <../../../task_scheduler/task_arena_cls>`
