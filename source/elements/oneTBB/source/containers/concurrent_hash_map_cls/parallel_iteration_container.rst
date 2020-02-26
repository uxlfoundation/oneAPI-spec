==================
Parallel Iteration
==================

Types 
``const_range_type`` and 
``range_type`` model the Container Range concept. The
types differ only in that the bounds for a 
``const_range_type`` are of type 
``const_iterator``, whereas the bounds for a 
``range_type`` are of type iterator.

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
\ ``const_range_type range( size_t grainsize=1 ) const``
  \
  Constructs a 
  ``const_range_type`` representing all keys in
  the table. The parameter 
  ``grainsize`` is in units of hash table buckets.
  Each bucket typically has on average about one key-value pair.
  
  **Returns**: 
  ``const_range_type`` object for the table.
------------------------------------------------------------------------------------------
\ ``range_type range( size_t grainsize=1 )``
  \
  **Returns**: 
  ``range_type`` object for the table.
------------------------------------------------------------------------------------------
= ========================================================================================


See also:

* :doc:`concurrent_unordered_map <../concurrent_unordered_map_cls>`
