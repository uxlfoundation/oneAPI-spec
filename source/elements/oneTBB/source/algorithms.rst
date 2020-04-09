==========
Algorithms
==========

Most parallel algorithms provided by oneAPI Threading Building Blocks are generic. They operate on all
types that model the necessary concepts. Parallel algorithms may be nested. For
example, the body of a ``parallel_for`` can invoke another ``parallel_for``.

.. caution::

   When the body of an outer parallel algorithm invokes another parallel
   algorithm, it may cause the outer body to be re-entered for a different
   iteration of the outer algorithm.
   
   For example, if the outer body holds a global lock while calling an
   inner parallel algorithm, the body will deadlock if the re-entrant invocation
   attempts to acquire the same global lock. This ill-formed example is a special
   case of a general rule that code should not hold a lock while calling code
   written by another author.

Functions
---------

.. toctree::
   :titlesonly:

   algorithms/functions/parallel_for_func.rst
   algorithms/functions/parallel_reduce_func.rst
   algorithms/functions/parallel_deterministic_reduce_func.rst
   algorithms/functions/parallel_scan_func.rst

   algorithms/functions/parallel_do_func.rst
   algorithms/functions/parallel_for_each_func.rst

   algorithms/functions/parallel_invoke_func.rst
   algorithms/functions/variadic_parallel_invoke_func.rst
   algorithms/functions/parallel_pipeline_func.rst
   algorithms/functions/parallel_sort_func.rst

Classes
-------

Blocked ranges
~~~~~~~~~~~~~~

Predefined models of range concept.

.. toctree::
   :titlesonly:

   algorithms/classes/blocked_ranges/blocked_range_cls.rst
   algorithms/classes/blocked_ranges/blocked_range2d_cls.rst
   algorithms/classes/blocked_ranges/blocked_range3d_cls.rst
   algorithms/classes/blocked_ranges/blocked_rangeNd_cls.rst

.. _Partitioners:

Partitioners
~~~~~~~~~~~~

The default behavior of the loop templates ``parallel_for``, ``parallel_reduce``, and ``parallel_scan``
tries to recursively split a range into enough parts to keep processors busy, not necessarily splitting
as finely as possible. An optional partitioner parameter enables other behaviors to be specified.

.. toctree::
   :titlesonly:

   algorithms/classes/partitioners/auto_partitioner_cls.rst
   algorithms/classes/partitioners/affinity_partitioner.rst
   algorithms/classes/partitioners/static_partitioner.rst
   algorithms/classes/partitioners/simple_partitioner_cls.rst

Split tags
~~~~~~~~~~

.. toctree::
   :titlesonly:

   algorithms/classes/split_tags/proportional_split_cls.rst
   algorithms/classes/split_tags/split_cls.rst
