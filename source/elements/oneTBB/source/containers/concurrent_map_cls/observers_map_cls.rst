=========
Observers
=========

The following table provides information on the members of the
``concurrent_map`` and ``concurrent_multimap``
template classes.

= ========================================================================================
\ Member, Description
==========================================================================================
\ ``allocator_type get_allocator() const``
  \
  **Returns**: a copy of the allocator associated with ``*this``.
------------------------------------------------------------------------------------------
\ ``key_compare key_comp() const``
  \
  **Returns**: key comparison functor associated with ``*this``.
------------------------------------------------------------------------------------------
\ ``value_compare value_comp() const``
  \
  **Returns**: functor using to compare ``value_type`` objects by invoking key_comp()
  on the first elements of the pairs.
------------------------------------------------------------------------------------------
= ========================================================================================
