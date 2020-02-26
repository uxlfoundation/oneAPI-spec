=================
Size and Capacity
=================

The following table provides additional information on the
members of the 
``concurrent_unordered_map`` and 
``concurrent_unordered_multimap`` template classes.

= ========================================================================================
\ Member, Description
==========================================================================================
\ ``bool empty() const``
  \
  **Returns**: 
  ``size()!=0.``
------------------------------------------------------------------------------------------
\ ``size_type size() const``
  \
  **Returns**: Number of items in 
  ``*this``.
  
  .. caution::

     Though the current implementation takes
     time 
     ``O(1)``, possible future implementations
     might take time 
     ``O(P)``, where 
     ``P`` is the number of hardware threads.
  
------------------------------------------------------------------------------------------
\ ``size_type max_size() const``
  \
  **Returns**: Upper bound on number of
  items that 
  ``*this`` can hold.
  
  .. caution::

     The upper bound may be much higher than
     what the container can actually hold.
  
------------------------------------------------------------------------------------------
= ========================================================================================
