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

The following table provides additional information on the
members of this template class.

= ========================================================================================
\ Member, Description
==========================================================================================
\ ``const_range_type range( size_t grainsize=1 ) const``
  \
  **Returns**: A 
  ``const_range_type`` representing all elements
  in 
  ``*this``. The parameter 
  ``grainsize`` is in units of elements.
------------------------------------------------------------------------------------------
\ ``range_type range( size_t grainsize=1 )``
  \
  **Returns**: A 
  ``range_type`` representing all elements in 
  ``*this``. The parameter 
  ``grainsize`` is in units of elements.
------------------------------------------------------------------------------------------
= ========================================================================================
