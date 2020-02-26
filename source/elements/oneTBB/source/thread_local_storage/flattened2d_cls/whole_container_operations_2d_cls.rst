==========================
Whole Container Operations
==========================

**Safety**

These operations must not be invoked concurrently
on the same 
``flattened2d``.

The following table provides additional information on the
members of this template class.

= ========================================================================================
\ Member, Description
==========================================================================================
\ ``explicit flattened2d( const Container& c )``
  \
  Constructs a 
  ``flattened2d`` representing the sequence of
  elements in the inner containers contained by outer container c.
------------------------------------------------------------------------------------------
\ ``flattened2d( const Container& c, typename Container::const_iterator first, typename Container::const_iterator last )``
  \
  Constructs a 
  ``flattened2d`` representing the sequence of
  elements in the inner containers in the half-open interval 
  ``[first, last)`` of Container c.
------------------------------------------------------------------------------------------
= ========================================================================================
