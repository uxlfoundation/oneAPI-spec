========================
Construct, Destroy, Copy
========================

The following table provides information on the members of the
``concurrent_map`` and ``concurrent_multimap``
template classes.

= ========================================================================================
\ Member, Description
==========================================================================================
\ ``concurrent_[multi]map()``
  \
  Constructs an empty table.
------------------------------------------------------------------------------------------
\ Constructors
  \
  ``explicit concurrent_[multi]map(const key_compare& c, const allocator_type& alloc = allocator_type())``
  
  ``explicit concurrent_[multi]map(const allocator_type& alloc)``

  Constructs an empty table using compare ``c`` and allocator ``alloc``.
  If the absence of arguments, their default values are used.
------------------------------------------------------------------------------------------
\ Constructors from a sequence
  \
  ``template <typename InputIterator> concurrent_[multi]map(InputIterator first,
  InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())``

  ``template <typename InputIterator> concurrent_[multi]map(InputIterator first,
  InputIterator last, const allocator_type& alloc)``

  Constructs a table, containing copies of the elements in the half-open interval
  ``[first, last)`` using compare ``comp`` and allocator ``alloc``. If the absence
  of arguments, their default values are used.
------------------------------------------------------------------------------------------
\ ``concurrent_[multi]map(const concurrent_[multi]map& other)``
  \
  Constructs a copy of the table ``other``.
------------------------------------------------------------------------------------------
\ ``concurrent_[multi]map(const concurrent_[multi]map& other, const allocator_type& alloc)``
  \
  Constructs a copy of the table ``other`` using allocator ``alloc``.
------------------------------------------------------------------------------------------
\ ``concurrent_[multi]map(concurrent_[multi]map&& other)``
  \
  Constructs a table by moving elements from ``other``.
  
  ``other`` is left in a valid, but unspecified state.
------------------------------------------------------------------------------------------
\ ``concurrent_[multi]map(concurrent_[multi]map&& other, const allocator_type& alloc)``
  \
  Constructs a table by moving elements from ``other`` using allocator ``alloc``
  
  ``other`` is left in a valid, but unspecified state.
------------------------------------------------------------------------------------------
\ Constructors from an ``initializer_list``
  \
  ``concurrent_[multi]map(std::initializer_list<value_type> il, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())``
  
  ``concurrent_[multi]map(std::initializer_list<value_type> il, const allocator_type& alloc)``

  Equivalent to ``concurrent_[multi]map(il.begin(), il.end(), comp, alloc)`` and
  
  ``concurrent_[multi]map(il.begin(), il.end(), alloc)`` respectively.
------------------------------------------------------------------------------------------
\ ``~concurrent_[multi]map()``
  \
  Destroys the table.
------------------------------------------------------------------------------------------
\ ``concurrent_[multi]map& operator=(const concurrent_[milti]map& other)``
  \
  If ``*this`` and ``other`` are distinct, clears the ``*this``
  and copies elements from ``other`` to ``*this``. Otherwise, does nothing.
  
  **Returns**: a reference to ``*this``.
------------------------------------------------------------------------------------------
\ ``concurrent_[multi]map& operator=(concurrent_[multi]map&& other)``
  \
  If ``*this`` and ``other`` are distinct, clears the ``*this``
  and moves elements from ``other`` to ``*this``.
  
  ``other`` is left in a valid, but unspecified state. Otherwise, do nothing.
  
  **Returns**: a reference to ``*this``.
------------------------------------------------------------------------------------------
\ ``concurrent_[multi]map& operator=(std::initializer_list<value_type> il)``
  \
  Assigns contents of ``il`` to ``*this``.
  
  **Returns**: a reference to ``*this``.
------------------------------------------------------------------------------------------
= ========================================================================================
