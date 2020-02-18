============
Partitioners
============


Summary
-------

A partitioner specifies how a loop template should partition its work among threads.

Partitioner Types
-----------------

The default behavior of the loop templates ``parallel_for``,
``parallel_reduce``, and ``parallel_scan`` tries to recursively
split a range into enough parts to keep processors busy, not necessarily splitting as finely
as possible. An optional partitioner parameter enables other behaviors to be specified, as
shown in the table below. The first column of the table shows how the formal parameter is
declared in the loop templates. An ``affinity_partitioner`` is passed by
non-const reference because it is updated to remember where loop iterations run.
The template ``parallel_deterministic_reduce`` supports ``simple_partitioner`` and ``static_partitioner`` only.


= ========================================================================================
\ Partitioners: Partitioner, Loop Behavior
==========================================================================================
\ ``const auto_partitioner& (default)``
  \
  Performs sufficient splitting to balance load, not necessarily splitting as
  finely as ``Range::is_divisible`` permits. When used with classes
  such as ``blocked_range``, the selection of an appropriate
  grain size is less important, and often acceptable performance can be achieved
  with the default grain size of 1.
------------------------------------------------------------------------------------------
\ ``affinity_partitioner&``
  \
  Similar to ``auto_partitioner``, but improves cache affinity by its
  choice of mapping subranges to worker threads. It can improve performance
  significantly when a loop is re-executed over the same data set, and the data
  set fits in the cache.
  
  ``affinity_partitioner`` uses proportional splitting when it is
  enabled for a ``Range``.
------------------------------------------------------------------------------------------
\ ``const static_partitioner&``
  \
  Distributes range iterations among worker threads as uniformly as possible,
  without a possibility for further load balancing. Similarly to
  ``affinity_partitioner``, maps subranges to worker threads. The
  work distribution and mapping are deterministic and only depend on the number of
  range iterations, its grain size and the number of threads.
------------------------------------------------------------------------------------------
\ ``const simple_partitioner&`` (default for parallel_deterministic_reduce)
  \
  Recursively splits a range until it is no longer divisible. The
  ``Range::is_divisible`` function is wholly responsible for deciding
  when recursive splitting halts. When used with classes such as
  ``blocked_range``, the selection of an appropriate grain size is
  critical to enabling concurrency while limiting overheads (see the discussion in
  the blocked_range Template Class section).
------------------------------------------------------------------------------------------
= ========================================================================================


See also:

* :doc:`parallel_for Template Function <parallel_for_func>`
* :doc:`parallel_reduce Template Function <parallel_reduce_func>`
* :doc:`parallel_scan Template Function <parallel_scan_func>`
* :doc:`blocked_range Template Class <range_concept/blocked_range_cls>`

.. toctree::

   partitioners/auto_partitioner_cls.rst
   partitioners/affinity_partitioner.rst
   partitioners/static_partitioner.rst
   partitioners/simple_partitioner_cls.rst
