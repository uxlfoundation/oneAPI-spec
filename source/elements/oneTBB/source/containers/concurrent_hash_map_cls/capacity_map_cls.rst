========
Capacity
========

The following table provides additional information on the members
of this template class.

= ========================================================================================
\ Member, Description
==========================================================================================
\ ``size_type size() const``
  \
  **Returns**: Number of key-value pairs
  in the table.
  
  .. note::

     This method takes constant time, but is
     slower than for most STL containers.
  
------------------------------------------------------------------------------------------
\ ``bool empty() const``
  \
  **Returns**: 
  ``size()==0.``
  
  .. note::

     This method takes constant time, but is
     slower than for most STL containers.
  
------------------------------------------------------------------------------------------
\ ``size_type max_size() const``
  \
  **Returns**: Inclusive upper bound on
  number of key-value pairs that the table can hold.
------------------------------------------------------------------------------------------
\ ``size_type bucket_count() const``
  \
  **Returns**: Current number of internal
  buckets. See method 
  ``rehash`` for discussion of buckets.
------------------------------------------------------------------------------------------
= ========================================================================================


See also:

* :doc:`Hash Policy <../concurrent_unordered_map_cls/hash_policy_map_cls>`
