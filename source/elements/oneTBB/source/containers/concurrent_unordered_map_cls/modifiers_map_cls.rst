=========
Modifiers
=========

The following table provides additional information on the members of the
``concurrent_unordered_map`` and
``concurrent_unordered_multimap`` template classes.

= ========================================================================================
\ Member, Description
==========================================================================================
\ ``std::pair<iterator, bool>insert(const value_type& x)``
  \
  Constructs a copy of ``x`` and attempts to insert it into the map.
  If the attempt fails because an item with the same key already exists, this copy is destroyed.
  
  **Returns**: ``std::pair(iterator,success)``. The
  ``iterator`` points to the inserted item or an existing item with the same key.
  The value of ``success`` is true if the item was inserted; false
  otherwise.
  
  .. note::

     This and other methods always succeed for ``concurrent_unordered_multimap``,
     and the value of ``success`` is always true.
  
------------------------------------------------------------------------------------------
\ ``iterator insert(const_iterator hint, const value_type& x)``
  \
  Same as ``insert(x)``, except for the returned value.
  
  .. note::

     In this and other methods, the ``hint`` argument exists for
     similarity with ``std::unordered_map``/``std::unordered_multimap``,
     and is ignored by the current implementation.
  
  **Returns**: Iterator pointing to the inserted item or an existing item with the same key.
------------------------------------------------------------------------------------------
\ ``std::pair<iterator, bool> insert(value_type&& x)``
  \
  Supported since C++11. Moves ``x`` into new instance of ``value_type`` and attempts
  to insert it into the map. If the attempt fails because an item with the same key
  already exists, this instance is destroyed.
  
  **Returns**: the same as ``insert(const value_type& x)``.
------------------------------------------------------------------------------------------
\ ``iterator insert(const_iterator hint, value_type&& x)``
  \
  Same as ``insert(x)``, except for the returned value.
  
  **Returns**: the same as ``insert(const_iterator hint, const value_type& x)``.
------------------------------------------------------------------------------------------
\ ``template<class InputIterator> void insert(InputIterator first, InputIterator last)``
  \
  Does ``insert(*i)`` where``i`` is in the
  half-open interval ``[first,last)``.
------------------------------------------------------------------------------------------
\ ``void insert(std::initializer_list<value_type> il)``
  \
  Supported since C++11. Inserts each element from the initializer list into the map.
------------------------------------------------------------------------------------------
\ ``std::pair<iterator, bool> insert(node_type&& nh)``
  \
  Supported since C++11. Attempts to insert the item owned by ``nh``
  into the map. If the attempt fails because an item with the same key already exists,
  ownership of the item remains at ``nh``.
  
  **Returns**: ``std::pair(iterator,success)``. The
  ``iterator`` points to the inserted item or an existing item with the same key.
  The value of ``success`` is true if the item was inserted; false otherwise.
------------------------------------------------------------------------------------------
\ ``iterator insert(const_iterator hint, node_type&& nh)``
  \
  Same as ``insert(nh)``, except for the returned value.
  
  **Returns**: Iterator pointing to the inserted item or an existing item with the same key.
------------------------------------------------------------------------------------------
\ ``template<typename... Args> std::pair<iterator, bool> emplace(Args&&... args);``
  \
  Supported since C++11. Constructs new instance of ``value_type``
  from ``args`` and attempts to insert it into the
  map. If the attempt fails because an item with the same key already exists, this instance is destroyed.
  
  **Returns**: the same as ``insert(const value_type& x)`` version.
------------------------------------------------------------------------------------------
\ ``template<typename... Args> iterator emplace_hint(const_iterator hint, Args&&... args);``
  \
  Same as ``emplace(args)``.
  
  **Returns**: Iterator pointing to inserted item, or item already in the map
  with the same key.
------------------------------------------------------------------------------------------
\ ``merge``
  \
  ``template<typename SrcHash, typename SrcEquality> void merge
  (concurrent_unordered_multimap<Key, T, SrcHash, SrcEquality, Allocator>& source);``
  
  ``template<typename SrcHash, typename SrcEquality> void merge
  (concurrent_unordered_multimap<Key, T, SrcHash, SrcEquality, Allocator>&& source);``
  
  ``template<typename SrcHash, typename SrcEquality> void merge
  (concurrent_unordered_map<Key, T, SrcHash, SrcEquality, Allocator>& source);``
  
  ``template<typename SrcHash, typename SrcEquality> void merge
  (concurrent_unordered_map<Key, T, SrcHash, SrcEquality, Allocator>&& source);``

  Supported since C++11. Transfers those items from ``source``
  which keys do not exist in ``*this``.
  
  .. caution::

     The ``merge`` method is concurrency-safe for the target container
     (i.e. the instance for which the method is called), but not for the source container.
     The behavior is undefined if ``source`` is concurrently
     modified or merged into more than one target container.
  
------------------------------------------------------------------------------------------
\ ``iterator unsafe_erase(const_iterator position)``
  \
  Removes the item pointed to by ``position`` from the map.
  
  **Returns**: Iterator pointing to item that was immediately after the erased
  item, or ``end()`` if erased item was the last item in the map.
------------------------------------------------------------------------------------------
\ ``size_type unsafe_erase(const key_type& k)``
  \
  Removes item with key, equivalent to ``k`` if such an item exists.
  
  **Returns**: 1 if an item was removed; 0 otherwise.
------------------------------------------------------------------------------------------
\ ``iterator unsafe_erase(const_iterator first, const_iterator last)``
  \
  Removes ``*i`` where ``i`` is in the half-open interval
  ``[first,last)``.
  
  **Returns**: ``last``
------------------------------------------------------------------------------------------
\ ``node_type unsafe_extract(const_iterator position)``
  \
  Transfers ownership of the item pointed to by ``position`` from the map
  to a node handle.
  
  **Returns**: the node handle that owns the extracted item.
------------------------------------------------------------------------------------------
\ ``node_type unsafe_extract(const key_type& k)``
  \
  If an item with the key equal to ``k`` exists in the map,
  the method transfers ownership of the item to a node handle.
  
  **Returns**: the node handle that owns the extracted item,
  or an empty node handle if a matching item was not found.
------------------------------------------------------------------------------------------
\ ``void clear()``
  \
  Removes all items from the map.
------------------------------------------------------------------------------------------
= ========================================================================================

The following table provides additional information on the
``concurrent_unordered_map`` template class.

= ========================================================================================
\ Member, Description
==========================================================================================
\ ``void swap(concurrent_unordered_map& m)``
  \
  Swaps contents of ``*this`` and ``m``.
------------------------------------------------------------------------------------------
= ========================================================================================

The following table provides additional information on the
``concurrent_unordered_multimap`` template class.

= ========================================================================================
\ Member, Description
==========================================================================================
\ ``void swap(concurrent_unordered_multimap& m)``
  \
  Swaps contents of ``*this`` and ``m``.
------------------------------------------------------------------------------------------
= ========================================================================================


See also:

* :doc:`Node handles <../node_handles_cls>`
