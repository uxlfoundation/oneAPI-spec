======
Lookup
======

The following table provides additional information on the members
of this template class.

= ========================================================================================
\ Member, Description
==========================================================================================
\ ``iterator find(const key_type& k)``
  \
  **Returns**: 
  ``iterator`` pointing to item with key equivalent
  to 
  ``k``, or 
  ``end()`` if no such item exists.
------------------------------------------------------------------------------------------
\ ``const_iterator find(const key_type& k) const``
  \
  **Returns**: 
  ``const_iterator`` pointing to item with key
  equivalent to 
  ``k``, or 
  ``end()`` if no such item exists.
------------------------------------------------------------------------------------------
\ ``size_type count(const key_type& k) const``
  \
  **Returns**: Number of items with keys
  equivalent to 
  ``k``.
------------------------------------------------------------------------------------------
\ ``std::pair<iterator, iterator> equal_range(const key_type& k)``
  \
  **Returns**: Range containing all keys
  in the set that are equivalent to 
  ``k``.
------------------------------------------------------------------------------------------
\ ``std::pair<const_iterator, const_iterator> equal_range(const key_type& k) const``
  \
  **Returns**: Range containing all keys
  in the set that are equivalent to 
  ``k``.
------------------------------------------------------------------------------------------
= ========================================================================================
