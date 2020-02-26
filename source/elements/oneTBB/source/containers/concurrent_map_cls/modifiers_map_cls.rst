=========
Modifiers
=========

The following table provides information on the members of the
``concurrent_map`` and ``concurrent_multimap`` template classes.

= ========================================================================================
\ Member, Description
==========================================================================================
\ ``std::pair<iterator, bool> insert(const value_type& x)``
  \
  Constructs a copy of ``x`` and attempts to insert it into the table. If the attempt
  fails because an item with the same key already exists, this copy is destroyed.
  
  **Returns**: ``std::pair(iterator, success)``. The value of ``iterator``
  points to an item in the map with the matching key. The value of ``success`` is ``true``
  if the item was inserted, ``false`` otherwise.
------------------------------------------------------------------------------------------
\ ``template<typename P> std::pair<iterator, bool> insert(P&& x)``
  \
  Constructs an instance of ``value_type`` from ``x`` and attempts to insert it into the table.
  If the attempt fails because an item with the same key already exists, this item is destroyed.
  
  Only participate in overload resolution if
  ``std::is_constructible<value_type, P&&>::value == true``.
  
  **Returns**: ``std::pair(iterator, success)``. The value of ``iterator``
  points to an item in the map with the matching key. The value of ``success`` is ``true``
  if the item was inserted, ``false`` otherwise.
------------------------------------------------------------------------------------------
\ ``std::pair<iterator, bool> insert(value_type&& x)``
  \
  Moves ``x`` into the new instance of ``value_type`` and attempts to insert it into the table.
  If the attempt fails because an item with the same key already exists, this item is destroyed.
  
  ``x`` is left in a valid, but unspecified state.
  
  **Returns**: ``std::pair(iterator, success)``. The value of ``iterator``
  points to an item in the map with the matching key. The value of ``success`` is ``true`` if
  the item was inserted, ``false`` otherwise.
------------------------------------------------------------------------------------------
\ ``iterator insert(const_iterator hint, const value_type& x)``
  \
  The same as ``insert(const value_type& x)``.
  
  **Returns**: ``insert(x).first``.
------------------------------------------------------------------------------------------
\ ``template<typename P>   iterator insert(const_iterator hint, P&& x)``
  \
  The same as ``insert(P&& x)``.
  
  Only participate in overload resolution if
  ``std::is_constructible<value_type, P&&>::value == true``.
  
  **Returns**: ``insert(x).first``.
------------------------------------------------------------------------------------------
\ ``iterator insert(const_iterator hint, value_type&& x)``
  \
  The same as ``insert(value_type&& x)``.
  
  **Returns**: ``insert(x).first``.
------------------------------------------------------------------------------------------
\ ``template<typename InputIterator> void insert(InputIterator first, InputIterator last)``
  \
  Inserts elements from half-open interval ``[first, last)`` into the table.
------------------------------------------------------------------------------------------
\ ``void insert(std::initializer_list<value_type> il)``
  \
  The same as ``insert(il.begin(), il.end())``.
------------------------------------------------------------------------------------------
\ ``std::pair<iterator, bool> insert(node_type&& nh)``.
  \
  Attempts to insert the node owned by ``nh`` into the table.
  If the attempt fails because an item with the same key already exists,
  ownership of the node remains at ``nh``.
  Otherwise ``nh`` is left in an empty state.
  
  **Returns**: ``std::pair(iterator, success)``. The value of ``iterator``
  points to an item in the map with the matching key. The value of ``success`` is ``true``
  if the item was inserted, ``false`` otherwise.
------------------------------------------------------------------------------------------
\ ``iterator insert(const_iterator hint, node_type&& nh)``
  \
  The same as ``insert(node_type&& nh)``.
  
  **Returns**: ``insert(nh).first``.
------------------------------------------------------------------------------------------
\ ``template<typename... Args> std::pair<iterator, bool> emplace(Args&&... args)``
  \
  Constructs an instance of ``value_type`` from ``args`` and attempts to insert it
  into the table. If the attempt fails because an item with the same key already exists,
  this instance is destroyed.
  
  **Returns**: ``std::pair(iterator, success)``. The value of ``iterator``
  points to an item in the map with the matching key. The value of ``success`` is ``true``
  if the item was inserted, ``false`` otherwise.
------------------------------------------------------------------------------------------
\ ``template<typename... Args> iterator emplace_hint(const_iterator hint, Args&& args)``
  \
  The same as ``emplace(args...)``.
  
  **Returns**: ``emplace(args...).first``.
------------------------------------------------------------------------------------------
\ ``merge``
  \
  ``template<typename SrcCompare> void merge(concurrent_map<key_type, mapped_type, SrcCompare, allocator_type>& source)``

  ``template<typename SrcCompare> void merge(concurrent_map<key_type, mapped_type, SrcCompare, allocator_type>&& source)``

  ``template<typename SrcCompare> void merge(concurrent_multimap<key_type, mapped_type, SrcCompare, allocator_type>& source)``

  ``template<typename SrcCompare> void merge(concurrent_multimap<key_typem mapped_type, SrcCompare, allocator_type>&& source)``

  Transfers those items from ``source`` which keys do not exists in ``*this``.
  
  .. caution::

     The ``merge`` operation is concurrency-safe for the target table
     (i.e. the instance for which the method is called), but not for the source table.
     The behaviour is underfined if ``source`` is concurrently
     modified or merged into more than one target table.
  
------------------------------------------------------------------------------------------
\ ``iterator unsafe_erase(const_iterator position)``
  \
  Removes the item pointed by ``position`` from the table.
  
  **Returns**: iterator pointing on the item that was immediately after the erased item,
  or ``end()`` if erased item was the last item in the table.
------------------------------------------------------------------------------------------
\ ``iterator unsafe_erase(iterator position)``
  \
  Removes the item pointed by ``position`` from the table.
  
  **Returns**: iterator pointing on the item that was immediately after the erased item,
  or ``end()`` if erased item was the last item in the table.
------------------------------------------------------------------------------------------
\ ``iterator unsafe_erase(const_iterator first, const_iterator last)``
  \
  Removes all the elements in half-open interval ``[first, last)``.
  
  **Returns**: iterator, following the last removed element.
------------------------------------------------------------------------------------------
\ ``size_type unsafe_erase(const key_type& k)``
  \
  Removes all items with the key, equivalent to ``k``.
  
  **Returns**: the number of the removed items.
------------------------------------------------------------------------------------------
\ ``template<typename K> size_type unsafe_erase(const K& k)``
  \
  Removes all items with the key, that compares ``equivalent``
  to the value ``k``.
  
  Only participates in overload resolution if ``key_compare::is_transparent``
  is valid and denotes a type and the type ``K`` is not convertible to
  neither ``iterator`` and ``const_iterator``.
  
  **Returns**: the number of the removed items.
------------------------------------------------------------------------------------------
\ ``node_type unsafe_extract(const_iterator position)``
  \
  Transfers ownership of the node with the item pointed by ``position`` from the table
  to a node handle.
  
  **Returns**: the node handle that owns the extracted node.
------------------------------------------------------------------------------------------
\ ``node_type unsafe_extract(const key_type& k)``
  \
  If an item with the key equal to ``k`` exists in the table,
  transfers ownership of the corresponding node to the node handle.
  
  **Returns**: the node handle that owns the extracted node, or an empty node handle
  if a matching item was not found.
------------------------------------------------------------------------------------------
\ ``void clear()``
  \
  Removes all items from the table.
------------------------------------------------------------------------------------------
= ========================================================================================

The following table provides additional information on the
``concurrent_map`` template class.

= ========================================================================================
\ Member, Description
==========================================================================================
\ ``void swap(concurrent_map& other)``
  \
  Swaps contents of ``*this`` and ``other``.
------------------------------------------------------------------------------------------
= ========================================================================================

The following table provides additional information on the
``concurrent_multimap`` template class.

= ========================================================================================
\ Member, Description
==========================================================================================
\ ``void swap(concurrent_multimap& other)``
  \
  Swaps contents of ``*this`` and ``other``.
------------------------------------------------------------------------------------------
= ========================================================================================


See also:

* :doc:`Node handles <../node_handles_cls>`
