=========
Observers
=========

The following table provides information on the members of the
``concurrent_set`` and ``concurrent_multiset``
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
  **Returns**: the same as ``key_comp()``.
------------------------------------------------------------------------------------------
= ========================================================================================
