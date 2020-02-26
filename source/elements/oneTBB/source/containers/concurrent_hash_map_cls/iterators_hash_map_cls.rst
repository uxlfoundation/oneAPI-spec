=========
Iterators
=========

Template class 
``concurrent_hash_map`` supports forward iterators; that
is, iterators that can advance only forwards across a table. Reverse iterators
are not supported. Concurrent operations (``count``, 
``find``, 
``insert``, and 
``erase``) invalidate any existing iterators that point
into the table, An exception to this rule is that 
``count`` and 
``find`` do not invalidate iterators if no insertions or
erasures have occurred after the most recent call to method 
``rehash``.

.. note::

   Do not call concurrent operations, including 
   ``count`` and 
   ``find`` while iterating the table. Use 
   ``concurrent_unordered_map`` if concurrent traversal and
   insertion are required.

The following table provides additional information on the
members of this template class.

= ========================================================================================
\ Member, Description
==========================================================================================
\ ``iterator begin()``
  \
  **Returns**: 
  ``iterator`` pointing to beginning of key-value
  sequence.
------------------------------------------------------------------------------------------
\ ``iterator end()``
  \
  **Returns**
  
  ``iterator`` pointing to end
  of key-value sequence.
------------------------------------------------------------------------------------------
\ ``const_iterator begin() const``
  \
  **Returns**: 
  ``const_iterator`` pointing to the beginning of
  key-value sequence.
------------------------------------------------------------------------------------------
\ ``const_iterator end() const``
  \
  **Returns**: 
  ``const_iterator`` pointing to the end of
  key-value sequence.
------------------------------------------------------------------------------------------
\ ``std::pair<iterator, iterator> equal_range( const Key& key );``
  \
  **Returns**: Pair of iterators 
  ``(i,j)`` such that the half-open range 
  ``[i,j)`` contains all pairs in the map
  (and only such pairs) with keys equal to 
  ``key``. Because the map has no duplicate keys,
  the half-open range is either empty or contains a single pair.
  
  .. tip::

     This method is serial alternative to concurrent 
     ``count`` and 
     ``find`` methods.
  
------------------------------------------------------------------------------------------
\ ``std::pair<const_iterator, const_iterator> equal_range( const Key& key ) const;``
  \
  See 
  ``std::pair<iterator, iterator> equal_range( const Key& key )``.
------------------------------------------------------------------------------------------
= ========================================================================================


See also:

* :doc:`concurrent_unordered_map <../concurrent_unordered_map_cls>`
