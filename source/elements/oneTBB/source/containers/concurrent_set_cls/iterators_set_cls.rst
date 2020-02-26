=========
Iterators
=========

Template classes ``concurrent_set`` and ``concurrent_multiset``
support forward iterators. Reverse iterators are not supported: ``reverse_iterator``
and ``const_reverse_iterator`` member types, ``rbegin()`` and ``rend()``
methods are not available.

Concurrent operations (``count, insert, find``, etc.) do not invalidate any existing
iterators that point into the set. Erasure (``unsafe_erase``, ``unsafe_extract``) does not invalidate iterators
other than those pointing to erased elements.

Note that an iterator obtained via ``begin()`` will no longer point to the first
element in the set if ``insert`` inserts an item before it.

The following table provides information on the members of
``concurrent_set`` and ``concurrent_multiset``.

= ========================================================================================
\ Member, Description
==========================================================================================
\ ``iterator begin()``
  \
  **Returns**: ``iterator`` pointing to the first element in the set.
------------------------------------------------------------------------------------------
\ ``const_iterator begin() const``
  \
  **Returns**: ``const_iterator`` pointing to the first element in the set.
------------------------------------------------------------------------------------------
\ ``const_iterator cbegin() const``
  \
  **Returns**: ``const_iterator`` pointing to the first element in the set.
------------------------------------------------------------------------------------------
\ ``iterator end()``
  \
  **Returns**: ``iterator`` pointing to the immediately past last element in the set.
------------------------------------------------------------------------------------------
\ ``const_iterator end() const``
  \
  **Returns**: ``const_iterator`` pointing to the immediately past last element in the set.
------------------------------------------------------------------------------------------
\ ``const_iterator cend() const``
  \
  **Returns**: ``const_iterator`` pointing to the immediately past last element in the set.
------------------------------------------------------------------------------------------
= ========================================================================================
