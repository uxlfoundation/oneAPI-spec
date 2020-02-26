================
Bucket Interface
================

The bucket interface is similar to the bucket
interface for the C++11 class 
``unordered_map`` and 
``unordered_multimap``, except that the prefix 
``unsafe_`` has been added as a reminder that the methods
are unsafe to use during concurrent insertion.

.. caution::

   The bucket interface is intended for debugging.
   It is not concurrency safe.
   
   The mapping of keys to buckets is implementation specific.

Buckets are numbered from 0 to ``unsafe_bucket_count()-1``. To iterate over a bucket use a 
``local_iterator`` or 
``const_local_iterator``.

The following table provides additional information on the
members of this template class.

= ========================================================================================
\ Member, Description
==========================================================================================
\ ``size_type unsafe_bucket_count() const``
  \
  **Returns**: Number of buckets.
------------------------------------------------------------------------------------------
\ ``size_type unsafe_max_bucket_count() const``
  \
  **Returns**: Upper bound on possible
  number of buckets.
------------------------------------------------------------------------------------------
\ ``size_type unsafe_bucket_size(size_type n)``
  \
  **Returns**: Number of items in bucket
  
  ``n``.
------------------------------------------------------------------------------------------
\ ``size_type unsafe_bucket(const key_type& k) const``
  \
  **Returns**: Index of bucket where
  item with key 
  *k* would be placed.
------------------------------------------------------------------------------------------
\ ``local_iterator unsafe_begin(size_type n)``
  \
  **Returns**: 
  ``local_iterator`` pointing to first item in
  bucket 
  *n*.
------------------------------------------------------------------------------------------
\ ``const_local_iterator unsafe_begin(size_type n) const``
  \
  **Returns**: 
  ``const_local_iterator`` pointing to first item
  in bucket 
  ``n``.
------------------------------------------------------------------------------------------
\ ``local_iterator unsafe_end(size_type n)``
  \
  **Returns**: 
  ``local_iterator`` pointing to immediately after
  the last item in bucket 
  ``n``.
------------------------------------------------------------------------------------------
\ ``const_local_iterator unsafe_end(size_type n) const``
  \
  **Returns**: ``const_local_iterator`` pointing to immediately
  after the last item in bucket 
  ``n``.
------------------------------------------------------------------------------------------
\ ``const_local_iterator unsafe_cbegin(size_type n) const``
  \
  **Returns**: 
  ``const_local_iterator`` pointing to first item
  in bucket 
  ``n``.
------------------------------------------------------------------------------------------
\ ``const_local_iterator unsafe_cend(size_type n) const``
  \
  **Returns**: 
  ``const_local_iterator`` pointing to immediately
  past last item in bucket 
  ``n``.
------------------------------------------------------------------------------------------
= ========================================================================================
