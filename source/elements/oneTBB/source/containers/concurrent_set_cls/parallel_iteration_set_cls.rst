==================
Parallel Iteration
==================

Member types ``const_range_type`` and ``range_type``
of template classes ``concurrent_set`` and ``concurrent_multiset``
model the Container Range concept. The types differ only in that the bounds for a ``const_range_type``
are of type ``const_iterator``, whereas the bounds for a ``range_type`` are of type
``iterator``.

The following table provides information on the members of
``concurrent_set`` and ``concurrent_multiset`` template classes.

= ========================================================================================
\ Member, Description
==========================================================================================
\ ``const_range_type range() const``
  \
  **Returns**: ``const_range_type`` object representing all items in the set.
------------------------------------------------------------------------------------------
\ ``range_type range()``
  \
  **Returns**: ``range_type`` object representing all items in the set.
------------------------------------------------------------------------------------------
= ========================================================================================


See also:

* :doc:`Container Range <../container_range_concept>`
