==========
Containers
==========

The container classes permit multiple threads to
simultaneously invoke certain methods on the same container.

Like STL, oneAPI Threading Building Blocks(
TBB) containers are templated with respect to an
``allocator`` argument. Each container uses its
``allocator`` to allocate memory for user-visible items. A
container may use a different allocator for strictly internal structures.

.. toctree::

   containers/container_range_concept.rst
   containers/tbb_hash_compare_cls.rst
   containers/node_handles_cls.rst
   containers/concurrent_map_cls.rst
   containers/concurrent_set_cls.rst
   containers/concurrent_unordered_map_cls.rst
   containers/concurrent_unordered_set_cls.rst
   containers/concurrent_hash_map_cls.rst
   containers/concurrent_queue_cls.rst
   containers/concurrent_bounded_queue_cls.rst
   containers/concurrent_priority_queue_cls.rst
   containers/concurrent_vector.rst
