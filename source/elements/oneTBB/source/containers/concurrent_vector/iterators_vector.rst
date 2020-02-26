=========
Iterators
=========

Template class 
``concurrent_vector<T>`` supports random access
iterators as defined in Chapter 24 of the  ISO C++ Standard. Unlike a 
``std::vector``, the iterators are not raw pointers. A 
``concurrent_vector<T>`` meets the reversible
container requirements in Chapter 23 of the ISO C++ Standard.

The following table provides additional information on the
members of this template class.

= ========================================================================================
\ Member, Description
==========================================================================================
\ ``iterator begin()``
  \
  **Returns**: 
  ``iterator`` pointing to beginning of the
  vector.
------------------------------------------------------------------------------------------
\ ``const_iterator begin() const``
  \
  **Returns**: 
  ``const_iterator`` pointing to beginning of the
  vector.
------------------------------------------------------------------------------------------
\ ``iterator end()``
  \
  **Returns**: 
  ``iterator`` pointing to end of the vector.
------------------------------------------------------------------------------------------
\ ``const_iterator end() const``
  \
  **Returns**: 
  ``const_iterator`` pointing to end of the
  vector.
------------------------------------------------------------------------------------------
\ ``reverse_iterator rbegin()``
  \
  **Returns**: 
  ``reverse iterator`` pointing to beginning of reversed vector.
------------------------------------------------------------------------------------------
\ ``const_reverse_iterator rbegin() const``
  \
  **Returns**: 
  ``const_reverse_iterator`` pointing to beginning
  of reversed vector.
------------------------------------------------------------------------------------------
\ ``iterator rend()``
  \
  **Returns**: 
  ``const_reverse_iterator`` pointing to end of
  reversed vector.
------------------------------------------------------------------------------------------
\ ``const_reverse_iterator rend()``
  \
  **Returns**: 
  ``const_reverse_iterator`` pointing to end of
  reversed vector.
------------------------------------------------------------------------------------------
= ========================================================================================
