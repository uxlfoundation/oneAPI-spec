========================
Construct, Destroy, Copy
========================

The following tables provide information on the members of the
``concurrent_unordered_map`` and ``concurrent_unordered_multimap``
template classes.

concurrent_unordered_map
------------------------

= ========================================================================================
\ Member, Description
==========================================================================================
\ Constructors
  \
  ``explicit concurrent_unordered_map(size_type n = <implementation-defined>,
  const hasher& hf = hasher(), const key_equal& eql = key_equal(),
  const allocator_type& a = allocator_type())``

  ``concurrent_unordered_map(size_type n, const allocator_type& a)``

  ``concurrent_unordered_map(size_type n, const hasher& hf, const allocator_type& a)``

  Constructs a table with ``n`` buckets using hasher ``hf``,
  key equality ``eql`` and allocator ``a``.
  In the absence of arguments, their default values are used.
------------------------------------------------------------------------------------------
\ Constructors from a sequence
  \
  ``template <typename InputIterator> concurrent_unordered_map (InputIterator first,
  InputIterator last, size_type n = <implementation-defined>, const hasher& hf = hasher(), const key_equal& eql = key_equal(), const allocator_type& a = allocator_type())``
  
  ``template <typename InputIterator> concurrent_unordered_map (InputIterator first,
  InputIterator last, size_type n, const allocator_type& a)``
  
  ``template <typename InputIterator> concurrent_unordered_map (InputIterator first,
  InputIterator last, size_type n, const hasher& hf. const allocator_type& a)``

  Constructs a table with ``n`` buckets initialized with
  ``value_type(*i)`` where ``i`` is in the
  half open interval ``[first,last)`` using hasher ``hf``,
  key equality ``eql`` and allocator ``a``.
  In the absence of arguments, their default values are used.
------------------------------------------------------------------------------------------
\ ``concurrent_unordered_map(const concurrent_unordered_map& m)``
  \
  Constructs a copy of the map ``m``.
------------------------------------------------------------------------------------------
\ ``explicit concurrent_unordered_map(const allocator_type& a)``
  \
  Constructs an empty map using allocator ``a``.
------------------------------------------------------------------------------------------
\ ``concurrent_unordered_map(const concurrent_unordered_map& m, const allocator_type& a)``
  \
  Constructs a copy of the map ``m`` using allocator
  ``a``.
------------------------------------------------------------------------------------------
\ Constructors from an ``initializer_list``
  \
  ``concurrent_unordered_map(std::initializer_list<value_type> il, size_type n = <implementation-defined>,
  const hasher& hf = hasher(), const key_equal& eql = key_equal(), const allocator_type& a = allocator_type())``
  
  ``concurrent_unordered_map(std::initializer_list<value_type> il, size_type n, const allocator& a)``
  
  ``concurrent_unordered_map(std::initializer_list<value_type> il, size_type n, const hasher& hf, const allocator_type& a)``

  Supported since C++11. Equivalent to
  ``concurrent_unordered_map(il.begin(), il.end(), n, hf, eql, a)`` ,
  ``concurrent_unordered_map(il.begin(), il.end(), n, a)``  and
  ``concurrent_unordered_map(il.begin(), il.end(), n, hf, a)``  respectively.
------------------------------------------------------------------------------------------
\ ``concurrent_unordered_map(concurrent_unordered_map&& m)``
  \
  Supported since C++11. Constructs a new table by moving content from *m*. *m*
  is left in an unspecified state, but can be safely destroyed.
------------------------------------------------------------------------------------------
\ ``concurrent_unordered_map(concurrent_unordered_map&& m, const allocator_type& a)``
  \
  Supported since C++11. Constructs a new table by moving content from *m* using
  specifed allocator. *m* is left in an unspecified state, but can be safely
  destroyed.
------------------------------------------------------------------------------------------
\ ``~concurrent_unordered_map()``
  \
  Destroys the map.
------------------------------------------------------------------------------------------
\ ``concurrent_unordered_map& operator=(const concurrent_unordered_map& m);``
  \
  Assigns contents of ``m`` to ``*this``.
  
  **Returns**: a reference to ``*this``.
------------------------------------------------------------------------------------------
\ ``concurrent_unordered_map& operator=(concurrent_unordered_map&& m);``
  \
  Supported since C++11. Moves data from ``m`` to
  ``*this``. *m* is left in an unspecified state, but can
  be safely destroyed.
  
  **Returns**: a reference to ``*this``.
------------------------------------------------------------------------------------------
\ ``concurrent_unordered_map& operator=(std::initializer_list<value_type> il);``
  \
  Supported since C++11. Assigns contents of ``il`` to ``*this``.
  
  **Returns**: a reference to ``*this``.
------------------------------------------------------------------------------------------
\ ``allocator_type get_allocator() const;``
  \
  Returns a copy of the allocator associated with ``*this``.
------------------------------------------------------------------------------------------
= ========================================================================================


concurrent_unordered_multimap
-----------------------------

= ========================================================================================
\ Member, Description
==========================================================================================
\ Constructors
  \
  ``explicit concurrent_unordered_multimap(size_type n = <implementation-defined>,
  const hasher& hf = hasher(), const key_equal& eql = key_equal(),
  const allocator_type& a = allocator_type())``
  
  ``concurrent_unordered_multimap(size_type n, const allocator_type& a)``
  
  ``concurrent_unordered_multimap(size_type n, const hasher& hf, const allocator_type& a)``

  Constructs a table with ``n`` buckets using hasher ``hf``,
  key equality ``eql`` and allocator ``a``.
  In the absence of arguments, their default values are used.
------------------------------------------------------------------------------------------
\ Constructors from a sequence
  \
  ``template <typename InputIterator> concurrent_unordered_multimap(InputIterator first,
  InputIterator last, size_type n = <implementation-defined>, const hasher& hf = hasher(),
  const key_equal& eql = key_equal(), const allocator_type& a = allocator_type())``
  
  ``template <typename InputIterator> concurrent_unordered_multimap(InputIterator first,
  InputIterator last, size_type n, const allocator_type& a)``
  
  ``template <typename InputIterator> concurrent_unordered_multimap(InputIterator first,
  InputIterator last, size_type n, const hasher& hf, const allocator_type& hf)``

  Constructs a table with ``n`` buckets initialized with
  ``value_type(*i)`` where ``i`` is in the
  half open interval ``[first,last)`` using hasher ``hf``,
  key equality ``eql`` and allocator ``a``.
  In the absence of arguments, their default values are used.
------------------------------------------------------------------------------------------
\ ``concurrent_unordered_multimap(const concurrent_unordered_multimap& m)``
  \
  Constructs a copy of the multimap ``m``.
------------------------------------------------------------------------------------------
\ ``explicit concurrent_unordered_multimap(const allocator_type& a)``
  \
  Constructs empty multimap using allocator ``a``.
------------------------------------------------------------------------------------------
\ ``concurrent_unordered_multimap(const concurrent_unordered_multimap&, const allocator_type& a)``
  \
  Constructs a copy of the multimap ``m`` using allocator
  ``a``.
------------------------------------------------------------------------------------------
\ Constructors from an ``initializer_list``
  \
  ``concurrent_unordered_multimap(std::initializer_list<value_type> il, size_type n = <implementation-defined>,
  const hasher& hf = hasher(), const key_equal& eql = key_equal(), const allocator_type& a = allocator_type())``
  
  ``concurrent_unordered_multimap(std::initializer_list<value_type> il, size_type n, const allocator_type& a)``
  
  ``concurrent_unordered_multimap(std::initializer_list<value_type> il, size_type n, const hasher& hf, const allocator_type& a)``

  Supported since C++11. Equivalent to
  ``concurrent_unordered_multimap(il.begin(), il.end(), n, hf, eql, a)`` ,
  ``concurrent_unordered_multimap(il.begin(), il.end(), n, a)``  and
  ``concurrent_unordered_multimap(il.begin(), il.end(), n, hf, a)``  respectively.
------------------------------------------------------------------------------------------
\ ``concurrent_unordered_multimap(concurrent_unordered_multimap&& m)``
  \
  Supported since C++11. Constructs a new table by moving content from *m*. *m*
  is left in an unspecified state, but can be safely destroyed.
------------------------------------------------------------------------------------------
\ ``concurrent_unordered_multimap(concurrent_unordered_multimap&& m, const allocator_type& a)``
  \
  Supported since C++11. Constructs a new table by moving content from *m* using
  specifed allocator. *m* is left in an unspecified state, but can be safely
  destroyed.
------------------------------------------------------------------------------------------
\ ``~concurrent_unordered_multimap()``
  \
  Destroys the multimap.
------------------------------------------------------------------------------------------
\ ``concurrent_unordered_multimap& operator=(const concurrent_unordered_multimap& m);``
  \
  Assigns contents of ``m`` to ``*this``.
  
  **Returns**: a reference to ``*this``.
------------------------------------------------------------------------------------------
\ ``concurrent_unordered_multimap& operator=(concurrent_unordered_multimap&& m);``
  \
  Supported since C++11. Moves data from ``m`` to
  ``*this``. *m* is left in an unspecified state, but can
  be safely destroyed.
  
  **Returns**: a reference to ``*this``.
------------------------------------------------------------------------------------------
\ ``concurrent_unordered_multimap& operator=( std::initializer_list<value_type> il);``
  \
  Supported since C++11. Assigns contents of ``il`` to ``*this``.
  
  **Returns**: a reference to ``*this``.
------------------------------------------------------------------------------------------
\ ``allocator_type get_allocator() const;``
  \
  Returns a copy of the allocator associated with ``*this``.
------------------------------------------------------------------------------------------
= ========================================================================================
