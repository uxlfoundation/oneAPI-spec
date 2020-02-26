=================
Concurrent Growth
=================

The methods described in the following table may be invoked concurrently on the same
vector.

= ========================================================================================
\ Member, Description
==========================================================================================
\ ``grow_by``
  \
  ``iterator grow_by( size_type delta )``
  
  ``iterator grow_by( size_type delta, const_reference t )``

  Appends a sequence comprising *delta* new elements to the end of the vector.
  If the second parameter *t* is specified, the new elements are initialized by
  copying *t*; otherwise, the new elements are default-constructed.
  
  **Returns**: Iterator pointing to the beginning of the appended sequence.
------------------------------------------------------------------------------------------
\ ``template<typename ForwardIterator> iterator grow_by( ForwardIterator first, ForwardIterator last )``
  \
  Appends a sequence to the vector by copying each element in the sequence
  ``[first,last)``.
  
  **Returns**: Iterator pointing to the beginning of the appended sequence.
------------------------------------------------------------------------------------------
\ ``iterator grow_by( std::initializer_list<T> il )``
  \
  Supported since C++11. Appends a sequence to the vector by copying each element from the
  initializer list.
  
  **Returns**: Iterator pointing to the beginning of the appended sequence.
------------------------------------------------------------------------------------------
\ ``grow_to_at_least``
  \
  ``iterator grow_to_at_least( size_type n )``
  
  ``iterator grow_to_at_least( size_type n, const_reference t )``

  Appends minimal sequence of elements such that
  ``vector.size()>=n``. If the second parameter *t* is
  specified, the new elements are initialized by copying *t*; otherwise, the
  new elements are default-constructed. Blocks until all elements in range
  *[0..n)* are allocated (but not necessarily constructed if they are under
  construction by a different thread).
  
  .. tip::

     If a thread must know whether construction of an element has completed, consider
     the following technique. Instantiate the ``concurrent_vector``
     using a ``zero_allocator``. Define the constructor
     ``T()`` such that when it completes, it sets a field of
     ``T`` to non-zero. A thread can check whether an item in the
     ``concurrent_vector`` is constructed by checking whether the field 
     is non-zero.
  
  **Returns**: Iterator that points to the beginning of the appended sequence, or
  a pointer to ``(*this)[n]`` if no elements were appended.
------------------------------------------------------------------------------------------
\ ``iterator push_back( const_reference value )``
  \
  Appends copy of ``value`` to the end of the vector.
  
  **Returns**: Iterator that points to the copy.
------------------------------------------------------------------------------------------
\ ``iterator push_back( T&& value )``
  \
  Supported since C++11. Moves ``value`` to a new element appended at the end
  of the vector.
  
  **Returns**: Iterator that points to the new element.
------------------------------------------------------------------------------------------
\ ``template<typename... Args> iterator emplace_back( Args&&... args );``
  \
  Supported since C++11. Appends a new element to the end of the vector. The element is
  constructed with given arguments.
  
  **Returns**: Iterator that points to the new element.
------------------------------------------------------------------------------------------
= ========================================================================================
