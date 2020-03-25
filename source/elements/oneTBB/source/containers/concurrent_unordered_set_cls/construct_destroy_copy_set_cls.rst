========================
Construct, Destroy, Copy
========================

The following tables provides information on the members of the
``concurrent_unordered_set`` and ``concurrent_unordered_multiset``
template classes.

concurrent_unordered_set
------------------------

= ========================================================================================
\ Member, Description
==========================================================================================
\ Constructors
  \
  ``explicit concurrent_unordered_set(size_type n = <implementation-defined>,
  const hasher& hf = hasher(),const key_equal& eql = key_equal(),
  const allocator_type& a = allocator_type())``

  ``concurrent_unordered_set(size_type n, const allocator_type& a)``

  ``concurrent_unordered_set(size_type n, const hasher& hf, const allocator_type& a)``

  Constructs a table with ``n`` buckets using hasher ``hf``,
  key equality ``eql`` and allocator ``a``.
  In the absence of arguments, their default values are used.
------------------------------------------------------------------------------------------
\ Constructors from a sequence
  \
  ``template <typename InputIterator> concurrent_unordered_set (InputIterator first,
  InputIterator last, size_type n = <implementation-defined>, const hasher& hf = hasher(), const key_equal& eql = key_equal(), const allocator_type& a = allocator_type())``
  
  ``template <typename InputIterator> concurrent_unordered_set (InputIterator first,
  InputIterator last, size_type n, const allocator_type& a)``
  
  ``template <typename InputIterator> concurrent_unordered_set (InputIterator first,
  InputIterator last, size_type n, const hasher& hf, const allocator_type& a)``

  Constructs a table with ``n`` buckets initialized with
  ``value_type(*i)`` where ``i`` is in the
  half open interval ``[first,last)`` using hasher ``hf``,
  key equality ``eql`` and allocator ``a``.
  In the absence of arguments, their default values are used.
------------------------------------------------------------------------------------------
\ ``concurrent_unordered_set(const unordered_set& m)``
  \
  Constructs a copy of set ``m``.
------------------------------------------------------------------------------------------
\ ``explicit concurrent_unordered_set(const allocator_type& a)``
  \
  Constructs an empty set using allocator *a*.
------------------------------------------------------------------------------------------
\ ``concurrent_unordered_set(const unordered_set&, const allocator_type& a)``
  \
  Constructs a copy of set *m* using allocator ``a``.
------------------------------------------------------------------------------------------
\ Constructors from an ``initializer_list``
  \
  ``concurrent_unordered_set(std::initializer_list<value_type> il, size_type n = <implementation-defined>,
  const hasher& hf = hasher(), const key_equal& eql = key_equal(), const allocator_type& a = allocator_type())``
  
  ``concurrent_unordered_set(std::initializer_list<value_type> il, size_type n, const allocator_type& a)``
  
  ``concurrent_unordered_set(std::initializer_list<value_type> il, size_type n, const hasher& hf, const allocator_type& a)``

  Supported since C++11. Equivalent to
  ``concurrent_unordered_set(il.begin(), il.end(), n, hf, eql, a)`` ,
  ``concurrent_unordered_set(il.begin(), il.end(), n, a)``  and
  ``concurrent_unordered_set(il.begin(), il.end(), n, hf, a)``
------------------------------------------------------------------------------------------
\ ``concurrent_unordered_set(concurrent_unordered_set&& m)``
  \
  Supported since C++11. Constructs a new table by moving content from *m*. *m*
  is left in an unspecified state, but can be safely destroyed.
------------------------------------------------------------------------------------------
\ ``concurrent_unordered_set(concurrent_unordered_set&& m, const allocator_type& a)``
  \
  Supported since C++11. Constructs a new table by moving content from *m* using
  specified allocator. *m* is left in an unspecified state, but can be safely
  destroyed.
------------------------------------------------------------------------------------------
\ ``~concurrent_unordered_set()``
  \
  Destroys the set.
------------------------------------------------------------------------------------------
\ ``concurrent_unordered_set& operator=(const concurrent_unordered_set& m);``
  \
  Assigns contents of ``m`` to ``*this``.
  
  **Returns**: a reference to ``*this``.
------------------------------------------------------------------------------------------
\ ``concurrent_unordered_set& operator=(concurrent_unordered_set&& m);``
  \
  Supported since C++11. Moves data from ``m`` to
  ``*this``. *m* is left in an unspecified state, but can
  be safely destroyed.
  
  **Returns**: a reference to ``*this``.
------------------------------------------------------------------------------------------
\ ``concurrent_unordered_set& operator=(std::initializer_list<value_type> il);``
  \
  Supported since C++11. Assigns contents of ``il`` to ``*this``.
  
  **Returns**: a reference to ``*this``.
------------------------------------------------------------------------------------------
\ ``allocator_type get_allocator() const;``
  \
  Returns a copy of the allocator associated with ``*this``.
------------------------------------------------------------------------------------------
= ========================================================================================


concurrent_unordered_multiset
-----------------------------

= ========================================================================================
\ Member, Description
==========================================================================================
\ Constructors
  \
  ``explicit concurrent_unordered_multiset(size_type n = <implementation-defined>,
  const hasher& hf = hasher(), const key_equal& eql = key_equal(),
  const allocator_type& a = allocator_type())``
  
  ``concurrent_unordered_multiset(size_type n, const allocator_type& a)``
  
  ``concurrent_unordered_multiset(size_type n, const hasher& hf, const allocator_type& a)``

  Constructs a table with ``n`` buckets using hasher ``hf``,
  key equality ``eql`` and allocator ``a``.
  In the absence of arguments, their default values are used.
------------------------------------------------------------------------------------------
\ Constructors from a sequence
  \
  ``template <typename InputIterator> concurrent_unordered_multiset (InputIterator first,
  InputIterator last, size_type n = <implementation-defined>, const hasher& hf = hasher(), const key_equal& eql = key_equal(), const allocator_type& a = allocator_type())``
  
  ``template <typename InputIterator> concurrent_unordered_multiset (InputIterator first,
  InputIterator last, size_type n, const allocator_type& a)``
  
  ``template <typename InputIterator> concurrent_unordered_multiset (InputIterator first,
  InputIterator last, size_type n, const hasher& hf, const allocator_type& a)``

  Constructs a table with ``n`` buckets initialized with
  ``value_type(*i)`` where ``i`` is in the
  half open interval ``[first,last)`` using hasher ``hf``,
  key equality ``eql`` and allocator ``a``.
  In the absence of arguments, their default values are used.
------------------------------------------------------------------------------------------
\ ``concurrent_unordered_multiset(const unordered_multiset& m)``
  \
  Constructs a copy of set ``m``.
------------------------------------------------------------------------------------------
\ ``explicit concurrent_unordered_multiset(const allocator_type&a)``
  \
  Constructs an empty set using allocator*a*.
------------------------------------------------------------------------------------------
\ ``concurrent_unordered_multiset(const unordered_multiset&, const allocator_type& a)``
  \
  Constructs a copy of set *m* using allocator ``a``.
------------------------------------------------------------------------------------------
\ Constructors from an ``initializer_list``
  \
  ``concurrent_unordered_multiset(std::initializer_list<value_type> il, size_type n = <implementation-defined>,
  const hasher& hf = hasher(), const key_equal& eql = key_equal(), const allocator_type& a = allocator_type())``
  
  ``concurrent_unordered_multiset(std::initializer_list<value_type> il, size_type n, const allocator_type& a)``
  
  ``concurrent_unordered_multiset(std::initializer_list<value_type> il, size_type n, const hasher& hf, const allocator_type& a)``

  Supported since C++11. Equivalent to
  ``concurrent_unordered_multiset(il.begin(), il.end(), n, hf, eql, a)`` ,
  ``concurrent_unordered_multiset(il.begin(), il.end(), n, a)``  and
  ``concurrent_unordered_multiset(il.begin(), il.end(), n, hf, a)`` .
------------------------------------------------------------------------------------------
\ ``concurrent_unordered_multiset(concurrent_unordered_multiset&& m)``
  \
  Supported since C++11. Constructs a new table by moving content from *m*. *m*
  is left in an unspecified state, but can be safely destroyed.
------------------------------------------------------------------------------------------
\ ``concurrent_unordered_multiset(concurrent_unordered_multiset&& m, const allocator_type& a)``
  \
  Supported since C++11. Constructs a new table by moving content from *m* using
  specified allocator. *m* is left in an unspecified state, but can be safely
  destroyed.
------------------------------------------------------------------------------------------
\ ``~concurrent_unordered_multiset()``
  \
  Destroys the set.
------------------------------------------------------------------------------------------
\ ``concurrent_unordered_multiset& operator=( const concurrent_unordered_multiset& m);``
  \
  Assigns contents of ``m`` to ``*this``.
  
  **Returns**: a reference to ``*this``.
------------------------------------------------------------------------------------------
\ ``concurrent_unordered_multiset& operator=( concurrent_unordered_multiset&& m);``
  \
  Supported since C++11. Moves data from ``m`` to
  ``*this``. *m* is left in an unspecified state, but can
  be safely destroyed.
  
  **Returns**: a reference to ``*this``.
------------------------------------------------------------------------------------------
\ ``concurrent_unordered_multiset& operator=(std::initializer_list<value_type> il);``
  \
  Supported since C++11. Assigns contents of ``il`` to ``*this``.
  
  **Returns**: a reference to ``*this``.
------------------------------------------------------------------------------------------
\ ``allocator_type get_allocator() const;``
  \
  Returns a copy of the allocator associated with ``*this``.
------------------------------------------------------------------------------------------
= ========================================================================================
