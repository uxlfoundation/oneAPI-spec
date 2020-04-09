========================
Container Range Concepts
========================


Summary
-------

View set of items in a container as a recursively
divisible range.

Requirements
------------

A Container Range is a 
**Range** with the further requirements listed in below.

= ========================================================================================
\ Additional Requirements on a Container Range R: Pseudo-Signature, Semantics
==========================================================================================
\ ``R::value_type``
  \
  Item type
------------------------------------------------------------------------------------------
\ ``R::reference``
  \
  Item reference type
------------------------------------------------------------------------------------------
\ ``R::const_reference``
  \
  Item const reference type
------------------------------------------------------------------------------------------
\ ``R::difference_type``
  \
  Type for difference of two iterators
------------------------------------------------------------------------------------------
\ ``R::iterator``
  \
  Iterator type for range
------------------------------------------------------------------------------------------
\ ``R::iterator R::begin()``
  \
  First item in range
------------------------------------------------------------------------------------------
\ ``R::iterator R::end()``
  \
  One past last item in range
------------------------------------------------------------------------------------------
\ ``R::size_type R::grainsize() const``
  \
  Grain size
------------------------------------------------------------------------------------------
= ========================================================================================


Model Types
-----------

Classes 
``concurrent_hash_map`` and 
``concurrent_vector`` both have member types 
``range_type`` and 
``const_range_type`` that model a Container Range.

Use the range types in conjunction with 
``parallel_for``, 
``parallel_reduce``, and 
``parallel_scan`` to iterate over items in a container.

See also:

* :doc:`concurrent_hash_map <concurrent_hash_map_cls>`
* :doc:`concurrent_vector <concurrent_vector>`
* :doc:`parallel_for <../algorithms/functions/parallel_for_func>`
* :doc:`parallel_reduce <../algorithms/functions/parallel_reduce_func>`
* :doc:`parallel_scan <../algorithms/functions/parallel_scan_func>`
* :doc:`Range Concept <../general/named_requirements/range>`
* :doc:`Capacity <concurrent_hash_map_cls/capacity_map_cls>`
* :doc:`Parallel Iteration <concurrent_vector/parallel_iteration>`
