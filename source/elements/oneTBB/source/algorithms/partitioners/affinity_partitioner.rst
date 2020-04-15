====================
affinity_partitioner
====================
**[algorithms.affinity_partitioner]**

Hint that loop iterations should be assigned to threads in a way that optimizes for cache affinity.

An ``affinity_partitioner`` hints that execution of a loop template should use the same task affinity pattern
for splitting the work as used by previous execution of the loop (or another loop) with the same ``affinity_partitioner`` object.

``affinity_partitioner`` uses proportional splitting when it is enabled for a :doc:`Range <../../general/named_requirements/algorithms/range>` type.

Unlike the other partitioners, it is important that the same ``affinity_partitioner`` object
be passed to the loop templates to be optimized for affinity.

The ``affinity_partitioner`` class satisfies the *CopyConstructibe* requirement from ISO C++ [utility.arg.requirements] section.


.. code:: cpp

    // Defined in header <tbb/partitioner.h>

    namespace tbb {

       class affinity_partitioner {
       public:
           affinity_partitioner() = default;
           ~affinity_partitioner() = default;
       };

    }

See also:

* :doc:`Range <../../general/named_requirements/algorithms/range>`

