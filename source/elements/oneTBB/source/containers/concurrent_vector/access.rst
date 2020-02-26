======
Access
======

.. caution::

   The methods described in this section may be
   concurrently invoked on the same vector as methods for concurrent growth.
   However, the returned reference may be to an element that is being concurrently
   constructed.

The following table provides additional information on the
members of this template class.

= ========================================================================================
\ Member, Description
==========================================================================================
\ ``reference operator[]( size_type index )``
  \
  **Returns**: Reference to element with
  the specified index.
------------------------------------------------------------------------------------------
\ ``const_refrence operator[]( size_type index ) const``
  \
  **Returns**: Const reference to
  element with the specified index.
------------------------------------------------------------------------------------------
\ ``reference at( size_type index )``
  \
  **Returns**: Reference to element at
  specified index.
  
  **Throws** : 
  ``std::out_of_range`` if 
  ``index >= size()``.
------------------------------------------------------------------------------------------
\ ``const_reference at( size_type index ) const``
  \
  **Returns**: Const reference to
  element at specified index.
  
  **Throws**: 
  ``std::out_of_range`` if 
  ``index >= size()`` or 
  ``index`` is for broken portion of vector.
------------------------------------------------------------------------------------------
\ ``reference front()``
  \
  **Returns**: 
  ``(*this)[0]``
------------------------------------------------------------------------------------------
\ ``const_reference front() const``
  \
  **Returns**: 
  ``(*this)[0]``
------------------------------------------------------------------------------------------
\ ``reference back()``
  \
  **Returns**: 
  ``(*this)[size()-1]``
------------------------------------------------------------------------------------------
\ ``const_reference back() const``
  \
  **Returns**: 
  ``(*this)[size()-1]``
------------------------------------------------------------------------------------------
= ========================================================================================
