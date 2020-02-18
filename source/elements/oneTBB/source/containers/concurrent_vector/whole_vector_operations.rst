=======================
Whole Vector Operations
=======================

.. caution::

   Concurrent invocation of these operations on the
   same instance is not safe.

The following table provides additional information on the
members of this template class.

= ========================================================================================
\ Member, Description
==========================================================================================
\ ``void reserve( size_type n )``
  \
  Reserves space for at least 
  ``n`` elements.
  
  **Throws** ``std::length_error`` if 
  ``n>max_size()``. It can also throw an
  exception if the allocator throws an exception.
  
  **Safety**: If an exception is thrown,
  the instance remains in a valid state.
------------------------------------------------------------------------------------------
\ ``void shrink_to_fit()``
  \
  Compacts the internal representation to
  reduce fragmentation.
------------------------------------------------------------------------------------------
\ ``void swap( concurrent_vector& x )``
  \
  Swap contents of two vectors. Takes O(1)
  time.
------------------------------------------------------------------------------------------
\ ``void clear()``
  \
  Erases all elements. Afterwards, 
  ``size()==0``. Does not free internal arrays.
  
  .. tip::

     To free internal arrays, call 
     ``shrink_to_fit()`` after 
     ``clear()``.
  
------------------------------------------------------------------------------------------
\ ``~concurrent_vector()``
  \
  Erases all elements and destroys the
  vector.
------------------------------------------------------------------------------------------
= ========================================================================================
