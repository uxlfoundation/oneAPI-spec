=========
Iterators
=========

Template classes
``concurrent_unordered_set`` and
``concurrent_unordered_multiset``
support forward iterators;
that is, iterators that can advance only forwards across a table. Reverse
iterators are not supported. Concurrent operations (``count, find, insert``) do 
*not* invalidate any existing iterators that point into the table.
Note that an iterator obtained via 
``begin()`` will no longer point to the first item if 
``insert`` inserts an item before it. 
Erasure (``unsafe_erase``) does *not* invalidate iterators
other than those pointing to erased elements.

Methods 
``cbegin`` and 
``cend`` follow C++11 conventions. They return 
``const_iterator`` even if the object is non-const.
The following table provides additional information on the members
of this template class.

= ========================================================================================
\ Member, Description
==========================================================================================
\ ``iterator begin()``
  \
  **Returns**: 
  ``iterator`` pointing to first item in the set.
------------------------------------------------------------------------------------------
\ ``const_iterator begin() const``
  \
  **Returns**: 
  ``const_iterator`` pointing to first item in the
  set.
------------------------------------------------------------------------------------------
\ ``iterator end()``
  \
  **Returns**: 
  ``iterator`` pointing to immediately past last
  item in the set.
------------------------------------------------------------------------------------------
\ ``const_iterator end() const``
  \
  **Returns**: 
  ``const_iterator`` pointing to immediately past
  last item in the set.
------------------------------------------------------------------------------------------
\ ``const_iterator cbegin() const``
  \
  **Returns**: 
  ``const_iterator`` pointing to the first item in
  the set.
------------------------------------------------------------------------------------------
\ ``const_iterator cend() const``
  \
  **Returns**: 
  ``const_iterator`` pointing to immediately after
  the last item in the set.
------------------------------------------------------------------------------------------
= ========================================================================================
