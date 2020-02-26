==================
Parallel Iteration
==================

Types 
``const_range_type`` and 
``range_type`` model the Container Range concept. The
types differ only in that the bounds for a 
``const_range_type`` are of type 
``const_iterator``, whereas the bounds for a 
``range_type`` are of type 
``iterator``.

The following table provides additional information on the
members of this template class.

= ========================================================================================
\ Member, Description
==========================================================================================
\ ``range_type range( size_t grainsize=1 )``
  \
  **Returns**: Range over entire 
  ``concurrent_vector`` that permits read-write
  access.
------------------------------------------------------------------------------------------
\ ``const_range_type range( size_t grainsize=1 ) const``
  \
  **Returns**: Range over entire 
  ``concurrent_vector`` that permits read-only
  access.
------------------------------------------------------------------------------------------
= ========================================================================================


See also:

* :doc:`Container Range Concept <../container_range_concept>`
