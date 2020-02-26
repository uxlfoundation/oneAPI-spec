===========
Hash Policy
===========

The following table provides additional information on the members
of this template class.

= ========================================================================================
\ Member, Description
==========================================================================================
\ ``float load_factor() const``
  \
  **Returns**: Average number of elements per bucket.
------------------------------------------------------------------------------------------
\ ``float max_load_factor() const``
  \
  **Returns**: Maximum size of a bucket. If insertion of an
  item causes a bucket to be bigger, the implementation may repartition or
  increase the number of buckets.
------------------------------------------------------------------------------------------
\ ``void max_load_factor(float z)``
  \
  Set maximum size for a bucket to 
  ``z``.
------------------------------------------------------------------------------------------
\ ``void rehash(size_type n)``
  \
  **Requirements**: 
  ``n`` must be a power of two.
  
  **Effects**: No effect if current number of buckets is at
  least 
  ``n``. Otherwise increases number of
  buckets to 
  ``n``.
------------------------------------------------------------------------------------------
= ========================================================================================
