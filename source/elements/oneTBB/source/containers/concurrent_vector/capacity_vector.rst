========
Capacity
========

The following table provides additional information on the members
of this template class.

= ========================================================================================
\ Member, Description
==========================================================================================
\ ``size_type size() const``
  \
  **Returns**: Number of elements in the
  vector. The result may include elements that are allocated but still under
  construction by concurrent calls to any of the growth methods.
------------------------------------------------------------------------------------------
\ ``bool empty() const``
  \
  **Returns**: 
  ``size()==0``
------------------------------------------------------------------------------------------
\ ``size_type capacity() const``
  \
  **Returns**: Maximum size to which
  vector can grow without having to allocate more memory.
  
  .. note::

     Unlike an 
     ``std::vector``, a 
     ``concurrent_vector`` does not move existing
     elements if it allocates more memory.
  
------------------------------------------------------------------------------------------
\ size_type max_size() const
  \
  **Returns**: The highest possible size
  of the vector could reach.
------------------------------------------------------------------------------------------
= ========================================================================================
