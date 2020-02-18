========================
Construct, Destroy, Copy
========================

The following table provides information on the members of the
``concurrent_set`` and ``concurrent_multiset``
template classes.

= ========================================================================================
\ Member, Description
==========================================================================================
\ ``concurrent_[multi]set()``
  \
  Constructs an empty set.
------------------------------------------------------------------------------------------
\ Constructors
  \
  ``explicit concurrent_[multi]set(const key_compare& c, const allocator_type& alloc = allocator_type())``
  
  ``explicit concurrent_[multi]set(const allocator_type& alloc)``

  Constructs an empty set using compare ``c`` and allocator ``alloc``.
  If the absence of arguments, their default values are used.
------------------------------------------------------------------------------------------
\ Constructors from a sequence
  \
  ``template <typename InputIterator> concurrent_[multi]set(InputIterator first,
  InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())``

  ``template <typename InputIterator> concurrent_[multi]set(InputIterator first,
  InputIterator last, const allocator_type& alloc)``

  Constructs a set, containing copies of the elements in the half-open interval
  ``[first, last)`` using compare ``comp`` and allocator ``alloc``. If the absence of
  arguments, their default values are used.
------------------------------------------------------------------------------------------
\ ``concurrent_[multi]set(const concurrent_[multi]set& other)``
  \
  Constructs a copy of the set ``other``.
------------------------------------------------------------------------------------------
\ ``concurrent_[multi]set(const concurrent_[multi]set& other, const allocator_type& alloc)``
  \
  Constructs a copy of the set ``other`` using allocator ``alloc``.
------------------------------------------------------------------------------------------
\ ``concurrent_[multi]set(concurrent_[multi]set&& other)``
  \
  Constructs a set by moving elements from ``other``.
  
  ``other`` is left in a valid, but unspecified state.
------------------------------------------------------------------------------------------
\ ``concurrent_[multi]set(concurrent_[multi]set&& other, const allocator_type& alloc)``
  \
  Constructs a set by moving elements from ``other`` using allocator ``alloc``
  
  ``other`` is left in a valid, but unspecified state.
------------------------------------------------------------------------------------------
\ Constructors from an ``initializer_list``
  \
  ``concurrent_[multi]set(std::initializer_list<value_type> il, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())``
  
  ``concurrent_[multi]set(std::initializer_list<value_type> il, const allocator_type& alloc)``

  Equivalent to ``concurrent_[multi]set(il.begin(), il.end(), comp, alloc)`` and
  ``concurrent_[multi]set(il.begin(), il.end(), alloc)`` respectively.
------------------------------------------------------------------------------------------
\ ``~concurrent_[multi]set()``
  \
  Destroys the set.
------------------------------------------------------------------------------------------
\ ``concurrent_[multi]set& operator=(const concurrent_[milti]set& other)``
  \
  If ``*this`` and ``other`` are distinct, clears the ``*this``
  and copies elements from ``other`` to ``*this``. Otherwise, does nothing.
  
  **Returns**: a reference to ``*this``.
------------------------------------------------------------------------------------------
\ ``concurrent_[multi]set& operator=(concurrent_[multi]set&& other)``
  \
  If ``*this`` and ``other`` are distinct, clears the ``*this``
  and moves elements from ``other`` to ``*this``.
  
  ``other`` is left in a valid, but unspecified state. Otherwise, do nothing.
  
  **Returns**: a reference to ``*this``.
------------------------------------------------------------------------------------------
\ ``concurrent_[multi]set& operator=(std::initializer_list<value_type> il)``
  \
  Assigns contents of ``il`` to ``*this``.
  
  **Returns**: a reference to ``*this``.
------------------------------------------------------------------------------------------
= ========================================================================================
