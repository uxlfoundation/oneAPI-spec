=====================
Concurrent Operations
=====================






The following table provides additional information on the
members of this template class.

= ========================================================================================
\ Member, Description
==========================================================================================
\ ``reference local()``
  \
  If there is no current element
  corresponding to the current thread, then this method constructs a new element.
  A new element is copy-constructed if an exemplar was provided to the
  constructor for 
  ``*this``, otherwise a new element is default
  constructed. See Caution below.
  
  **Returns**: A reference to the
  element of 
  ``*this`` that corresponds to the current
  thread.
------------------------------------------------------------------------------------------
\ ``reference local( bool& exists )``
  \
  Similar to 
  ``local()``, except that 
  ``exists`` is set to true if an element
  was already present for the current thread; false otherwise. See Caution below.
  
  **Returns**: Reference to thread-local
  element.
------------------------------------------------------------------------------------------
\ ``size_type size() const``
  \
  **Returns**: The number of elements in
  
  ``*this``. The value is equal to the number of
  distinct threads that have called local() after 
  ``*this`` was constructed or most recently
  cleared. See Caution below.
------------------------------------------------------------------------------------------
\ ``bool empty() const``
  \
  **Returns**: 
  ``size()==0``
------------------------------------------------------------------------------------------
= ========================================================================================


.. caution::

   The OS-specific value returned by 
   ``tbb::this_tbb_thread::get_id()`` is used to identify
   threads, and is not guaranteed to be unique except for the life of the thread.
   A newly created thread may get an OS-specific ID equal to that of an already
   destroyed thread. The number of elements of the 
   ``enumerable_thread_specific`` may therefore be less than
   the number of actual distinct threads that have called 
   ``local()``, and the element returned by the first
   reference by a thread to the 
   ``enumerable_thread_specific`` may not be
   newly-constructed.
