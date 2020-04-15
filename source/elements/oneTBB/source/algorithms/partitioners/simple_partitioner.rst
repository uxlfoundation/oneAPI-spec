==================
simple_partitioner
==================
**[algorithms.simple_partitioner]**

Specify that a parallel loop should recursively split its range until it cannot be subdivided further.

A ``simple_partitioner`` specifies that a loop template should recursively divide its range
until for each subrange *r*, the condition ``!r.is_divisible()`` holds.
This is the default behavior of the loop templates that take a range argument.

The ``simple_partitioner`` class satisfies the *CopyConstructibe* requirement from ISO C++ [utility.arg.requirements] section.

.. tip::

   When using ``simple_partitioner`` and a ``blocked_range`` for a parallel loop,
   be careful to specify an appropriate grain size for the ``blocked_range``.
   The default grain size is 1, which may make the subranges much too small for efficient execution.

.. code:: cpp

    // Defined in header <tbb/partitioner.h>

    namespace tbb {

       class simple_partitioner {
       public:
           simple_partitioner() = default;
           ~simple_partitioner() = default;
       };

    }

See also:

* :doc:`Range <../../general/named_requirements/algorithms/range>`

