======================
Whole Table Operations
======================

These operations affect an entire table. Do not concurrently invoke them on the same table.

.. note::

   Since C++11, copy construction and assignment, move assignment and swapping respects
   ``std::allocator_traits`` for operations with allocators.

The following table provides additional information on the members of this template class.

= ========================================================================================
\ Member, Description
==========================================================================================
\ Constructors
  \
  ``explicit concurrent_hash_map( const allocator_type& a = allocator_type() )``
  
  ``explicit concurrent_hash_map( const HashCompare& compare, const allocator_type& a = allocator_type() )``

  Constructs an empty table.
------------------------------------------------------------------------------------------
\ Preallocating constructors
  \
  ``concurrent_hash_map( size_type n, const allocator_type& a = allocator_type() )``
  
  ``concurrent_hash_map ( size_type n, const HashCompare& compare, const allocator_type& a = allocator_type() )``

  Constructs an empty table with preallocated buckets for at least
  ``n`` items.
  
  .. note::

     In general, thread contention for buckets is inversely related to the number of
     buckets. If memory consumption is not an issue and *P* threads will be
     accessing the ``concurrent_hash_map``, set
     ``n>=4P``.
  
------------------------------------------------------------------------------------------
\ ``concurrent_hash_map( const concurrent_hash_map& table )``
  \
  Constructs a new table by copying content from ``table``.
------------------------------------------------------------------------------------------
\ ``concurrent_hash_map( const concurrent_hash_map& table, const allocator_type& a )``
  \
  Constructs a new table by copying content from ``table`` using specified allocator.
------------------------------------------------------------------------------------------
\ Constructors from a sequence
  \
  ``template<typename InputIterator> concurrent_hash_map( InputIterator first, InputIterator last, const allocator_type& a = allocator_type() )``
  
  ``template<typename InputIterator> concurrent_hash_map( InputIterator first, InputIterator last, const HashCompare& compare, const allocator_type& a = allocator_type() )``

  Constructs a table containing copies of elements in the iterator half-open
  interval [*first,last*).
------------------------------------------------------------------------------------------
\ Constructors from an ``initializer_list``
  \
  ``concurrent_hash_map( std::initializer_list<value_type> il, const allocator_type &a = allocator_type() )``
  
  ``concurrent_hash_map( std::initializer_list<value_type> il, const HashCompare& compare, const allocator_type& a = allocator_type() )``

  Supported since C++11. Equivalent to
  ``concurrent_hash_map( il.begin(), il.end(), a )``  and
  ``concurrent_hash_map( il.begin(), il.end(), compare, a )``  respectively.
------------------------------------------------------------------------------------------
\ ``concurrent_hash_map(concurrent_hash_map&& source)``
  \
  Supported since C++11. Constructs a new table by moving content from the *source*
  table. *source* is left in an unspecified state, but can be safely destroyed.
------------------------------------------------------------------------------------------
\ ``concurrent_hash_map(concurrent_hash_map&& source, const allocator_type& a)``
  \
  Supported since C++11. Constructs a new table by moving content from the *source*
  table using specified allocator. *source* is left in an unspecified state,
  but can be safely destroyed.
------------------------------------------------------------------------------------------
\ ``~concurrent_hash_map()``
  \
  Invokes ``clear()``. This method is not safe to execute concurrently
  with other methods on the same ``concurrent_hash_map``.
------------------------------------------------------------------------------------------
\ ``concurrent_hash_map& operator=( concurrent_hash_map& source )``
  \
  If source and destination (``this``) table are distinct, clears the
  destination table and copies all key-value pairs from the source table to the
  destination table. Otherwise, does nothing.
  
  **Returns**: a reference to ``*this``.
------------------------------------------------------------------------------------------
\ ``concurrent_hash_map& operator=(concurrent_hash_map&& source);``
  \
  Supported since C++11. Moves data from the *source* table to
  ``*this``. *source* is left in an unspecified state, but
  can be safely destroyed.
  
  **Returns**: a reference to ``*this``.
------------------------------------------------------------------------------------------
\ ``concurrent_hash_map& operator=( std::initializer_list<value_type> il )``
  \
  Supported since C++11. Assigns ``*this`` to contain data from
  ``il``.
  
  **Returns**: a reference to ``*this``.
------------------------------------------------------------------------------------------
\ ``void swap( concurrent_hash_map& table )``
  \
  Swaps contents and allocators of ``this`` and ``table``.
------------------------------------------------------------------------------------------
\ ``void rehash( size_type n = 0 )``
  \
  Internally, the table is partitioned into buckets. The ``rehash`` method
  reorganizes these internal buckets in a way that may improve performance of future
  lookups. Raises number of internal buckets to ``n`` if
  ``n>0`` and ``n`` exceeds the current
  number of buckets.
  
  .. caution::

     The current implementation never reduces the number of buckets. A future
     implementation might reduce the number of buckets if ``n``
     is less than the current number of buckets.
  
  .. note::

     The ratio of items to buckets affects time and space usage by a table. A high
     ratio saves space at the expense of time. A low ratio does the opposite. The
     default ratio is 0.5 to 1 items per bucket on average.
  
------------------------------------------------------------------------------------------
\ ``void clear()``
  \
  Erases all key-value pairs from the table. Does not hash or compare any keys.
  
  If ``TBB_USE_PERFORMANCE_WARNINGS`` is nonzero, issues a performance
  warning if the randomness of the hashing is poor enough to significantly impact
  performance.
------------------------------------------------------------------------------------------
\ ``allocator_type get_allocator() const``
  \
  **Returns**: a copy of allocator used to construct table.
------------------------------------------------------------------------------------------
= ========================================================================================
