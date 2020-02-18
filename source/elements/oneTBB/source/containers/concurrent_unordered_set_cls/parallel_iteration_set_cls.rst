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
\ ``const_range_type range() const``
  \
  **Returns**: 
  ``const_range_type`` object representing all
  keys in the table.
------------------------------------------------------------------------------------------
\ ``range_type range()``
  \
  **Returns**: 
  ``range_type`` object representing all keys in
  the table.
------------------------------------------------------------------------------------------
= ========================================================================================


See also:

* :doc:`Container Range <../container_range_concept>`
