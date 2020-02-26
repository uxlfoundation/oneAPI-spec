=================
Utility Functions
=================

The following table provides additional information on the members
of this template class.

= ========================================================================================
\ Member, Description
==========================================================================================
\ ``template <typename Container>  flattened2d<Container> flatten2d(const Container &c, const typename Container::const_iterator b, const typename Container::const_iterator e)``
  \
  **Returns**: Constructs and returns a 
  ``flattened2d`` that provides iterators that
  traverse the elements in the containers within the half-open range 
  ``[b, e)`` of Container c.
------------------------------------------------------------------------------------------
\ ``template <typename Container> flattened2d( const Container &c )``
  \
  **Returns**: Constructs and returns a 
  ``flattened2d`` that provides iterators that
  traverse the elements in all of the containers within Container c.
------------------------------------------------------------------------------------------
= ========================================================================================
