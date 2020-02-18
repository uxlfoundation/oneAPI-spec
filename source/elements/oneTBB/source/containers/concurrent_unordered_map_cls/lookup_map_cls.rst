======
Lookup
======

The following table provides additional information on the members
of the template classes
``concurrent_unordered_map`` and
``concurrent_unordered_multimap``
.

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
  in the map that are equivalent to 
  ``k``.
------------------------------------------------------------------------------------------
\ ``std::pair<const_iterator, const_iterator> equal_range(const key_type& k) const``
  \
  **Returns**
  
  Range containing all keys in the map that
  are equivalent to 
  ``k``.
------------------------------------------------------------------------------------------
= ========================================================================================

The following table provides additional information on the members
only available in the ``concurrent_unordered_map`` template class.

= ========================================================================================
\ Member, Description
==========================================================================================
\ ``mapped_type& operator[](const key_type& k)``
  \
  Inserts a new item if item with key
  equivalent to 
  ``k`` is not already present.
  
  **Returns**: Reference to 
  ``x.second`` , where 
  ``x`` is item in map with key equivalent to
  
  ``k``.
------------------------------------------------------------------------------------------
\ ``mapped_type& at( const key_type& k )``
  \
  Throws exception if item with key
  equivalent to 
  ``k`` is not already present.
  
  **Returns**: Reference to 
  ``x.second``, where 
  ``x`` is the item in map with key equivalent to 
  ``k``.
------------------------------------------------------------------------------------------
\ ``const mapped_type& at(const key_type& k) const``
  \
  Throws exception if item with key
  equivalent to 
  ``k`` is not already present.
  
  **Returns**: Const reference to 
  ``x.second``, where 
  ``x`` is the item in map with key
  equivalent to 
  ``k``.
------------------------------------------------------------------------------------------
= ========================================================================================
