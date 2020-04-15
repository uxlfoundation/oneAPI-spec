==================
static_partitioner
==================
**[algorithms.static_partitioner]**

Specify that a parallel algorithm should distribute the work uniformly across threads and
should not do additional load balancing.

An algorithm with a ``static_partitioner`` distributes the range across threads in subranges
of approximately equal size.  The number of subranges is equal to the number of
threads that can possibly participate in task execution, as specified by
:doc:`global_contol <../../task_scheduler/tbb_global_control>` or :doc:`task_arena <../../task_scheduler/task_arena_cls>` classes.
These subranges are not further split.

.. caution::

   The regularity of subrange sizes is not guaranteed if the range type does not support
   proportional splitting, or if the grain size is set larger than the
   size of the range divided by the number of threads participating in task execution.

In addition, ``static_partitioner`` uses a deterministic task affinity pattern to hint the task scheduler
how the subranges should be assigned to threads.

The ``static_partitioner`` class satisfies the *CopyConstructibe* requirement from ISO C++ [utility.arg.requirements] section.

.. tip::

   Use of ``static_partitioner`` is recommended for:

   * Parallelizing small well-balanced workloads where enabling additional load balancing
     opportunities would bring more overhead than performance benefits.
   * Porting OpenMP* parallel loops with ``schedule(static)`` if deterministic
     work partitioning across threads is important.

.. code:: cpp

    // Defined in header <tbb/partitioner.h>

    namespace tbb {

        class static_partitioner {
        public:
           static_partitioner() = default;
           ~static_partitioner() = default;
        };

    }

See also:

* :doc:`Range <../../general/named_requirements/algorithms/range>`

