=====================
Concurrent Operations
=====================
Concurrent Operations
The operations ``count``, ``find``, ``insert``, and
``erase`` are the only operations that may be concurrently invoked on the same
``concurrent_hash_map``. These operations search the table for a key-value pair
that matches a given key. The ``find`` and ``insert`` methods each
have two variants. One takes a ``const_accessor`` argument and provides
read-only access to the desired key-value pair. The other takes an accessor argument and
provides write access. Additionally, ``insert`` has a variant without any
accessor.

.. caution::

   The concurrent operations (``count``, ``find``,
   ``insert``, and ``erase``) invalidate any iterators pointing
   into the affected instance even with a ``const`` qualifier. It is unsafe to
   use these operations concurrently with any other operation. An exception to this rule is
   that ``count`` and ``find`` do not invalidate iterators if no
   insertions or erasures have occurred after the most recent call to method
   ``rehash``.

.. tip::

   In serial code, use the ``equal_range`` method instead of the
   ``find`` method for lookup, since ``equal_range`` is faster and
   does not invalidate iterators.

.. tip::

   If the ``nonconst`` variant succeeds in finding the key, the consequent write
   access blocks any other thread from accessing the key until the accessor object is
   destroyed. Where possible, use the const variant to improve concurrency.

Each map operation in this section returns true if the operation succeeds, false otherwise.

.. caution::

   Though there can be at most one occurrence of a given key in the map, there may be other
   key-value pairs in flight with the same key. These arise from the semantics of the
   ``insert`` and ``erase`` methods. The ``insert``
   methods can create and destroy a temporary key-value pair that is not inserted into a map.
   The erase methods remove a key-value pair from the map before destroying it, thus
   permitting another thread to construct a similar key before the old one is destroyed.

.. tip::

   To guarantee that only one instance of a resource exists simultaneously for a given key,
   use the following technique:
   
   * To construct the resource: Obtain an ``accessor`` to the key in the map
     before constructing the resource.
   * To destroy the resource: Obtain an ``accessor`` to the key, destroy the
     resource, and then erase the key using the accessor.
   

Below is a sketch of how this can be done.

.. code:: cpp

   extern tbb::concurrent_hash_map<Key,Resource,HashCompare> Map;
   
   void ConstructResource( Key key ) {
       accessor acc;
       if( Map.insert(acc,key) ) {
           // Current thread inserted key and has exclusive access.
           ...construct the resource here...
       }
       // Implicit destruction of acc releases lock
   }
   
   void DestroyResource( Key key ) {
       accessor acc;
       if( Map.find(acc,key) ) {
           // Current thread found key and has exclusive access.
           ...destroy the resource here...
           // Erase key using accessor.
           Map.erase(acc);
       }
   }

The following table provides additional information on the members of this template class.

= ========================================================================================
\ Member, Description
==========================================================================================
\ ``size_type count( const Key& key ) const``
  \
  .. caution::

     This method may invalidate previously obtained iterators. In serial code, you
     can use ``equal_range`` that does not have such problems.
  
  **Returns**: 1 if map contains key; 0 otherwise.
------------------------------------------------------------------------------------------
\ ``bool find( const_accessor& result, const Key& key ) const``
  \
  Searches table for pair with given key. If key is found, sets result to provide
  read-only access to the matching pair.
  
  .. caution::

     This method may invalidate previously obtained iterators. In serial code, you
     can use ``equal_range`` that does not have such problems.
  
  **Returns**: True if key was found; false if key was not found.
------------------------------------------------------------------------------------------
\ ``bool find( accessor& result, const Key& key )``
  \
  Searches table for pair with given key. If key is found, sets result to provide
  write access to the matching pair
  
  .. caution::

     This method may invalidate previously obtained iterators. In serial code, you
     can use ``equal_range`` that does not have such problems.
  
  **Returns**: True if key was found; false if key was not found.
------------------------------------------------------------------------------------------
\ ``bool insert( const_accessor& result, const Key& key )``
  \
  Searches table for pair with given key. If not present, inserts new
  ``pair(key,T())`` into the table. Sets ``result``
  to provide read-only access to the matching pair.
  
  **Returns**: True if new pair was inserted; false if key was already in the
  map.
------------------------------------------------------------------------------------------
\ ``bool insert( accessor& result, const Key& key )``
  \
  Searches table for pair with given key. If not present, inserts new
  ``pair(key,T())`` into the table. Sets ``result``
  to provide write access to the matching pair.
  
  **Returns**: True if new pair was inserted; false if key was already in the map.
------------------------------------------------------------------------------------------
\ ``bool insert( const_accessor& result, const value_type& value )``
  \
  Searches table for pair with given key. If not present, inserts new pair
  copy-constructed from *value* into the table. Sets *result* to provide
  read-only access to the matching pair.
  
  **Returns**: True if new pair was inserted; false if key was already in the
  map.
------------------------------------------------------------------------------------------
\ ``bool insert( accessor& result, const value_type& value )``
  \
  Searches table for pair with given key. If not present, inserts new pair
  copy-constructed from ``value`` into the table. Sets
  ``result`` to provide write access to the matching pair.
  
  **Returns**: True if new pair was inserted; false if key was already in the
  map.
------------------------------------------------------------------------------------------
\ ``bool insert( const value_type& value )``
  \
  Searches table for pair with given key. If not present, inserts new pair
  copy-constructed from ``value`` into the table.
  
  **Returns**: True if new pair was inserted; false if key was already in the
  map.
  
  .. tip::

     If you do not need to access the data after insertion, use the form of insert
     that does not take an accessor; it may work faster and use fewer locks.
  
------------------------------------------------------------------------------------------
\ ``template<typename InputIterator> void insert( InputIterator first, InputIterator last )``
  \
  For each pair ``p`` in the half-open interval
  [``first,last``), does ``insert(p)`` . The
  order of the insertions, or whether they are done concurrently, is unspecified.
  
  .. caution::

     The current implementation processes the insertions in order. Future
     implementations may do the insertions concurrently. If duplicate keys exist in
     [``first,last``), be careful to not depend on their
     insertion order.
  
------------------------------------------------------------------------------------------
\ ``void insert( std::initializer_list<value_type> il )``
  \
  Supported since C++11. Inserts a sequence to the map by inserting each element from the
  initializer list. The order of the insertions, or whether they are done
  concurrently, is unspecified.
  
  .. caution::

     The current implementation processes the insertions in order. Future
     implementations may do the insertions concurrently. If duplicate keys exist in
     the initializer list, be careful to not depend on their insertion order.
  
------------------------------------------------------------------------------------------
\ ``bool erase( const Key& key )``
  \
  Searches table for pair with given key. Removes the matching pair if it exists. If
  there is an accessor pointing to the pair, the pair is nonetheless removed from
  the table but its destruction is deferred until all accessors stop pointing to it.
  
  **Returns**: True if pair was removed by the call; false if key was not found
  in the map.
------------------------------------------------------------------------------------------
\ ``bool erase( const_accessor& item_accessor )``
  \
  **Requirements**: ``item_accessor.empty()==false``
  
  **Effects**
  
  Removes pair referenced by ``item_accessor``. If there is
  another ``const_accessor`` pointing to the ``pair``,
  the ``pair`` is nonetheless removed from the table but its
  destruction is deferred until all ``accessors`` stop pointing to
  it. Concurrent insertion of the same key creates a new ``pair`` in
  the table, which can temporarily co-exist with the one being destroyed.
  
  **Returns**: True if pair was removed by this thread; false if pair was removed
  by another thread.
------------------------------------------------------------------------------------------
\ ``bool erase( accessor& item_accessor )``
  \
  **Requirements**: ``item_accessor.empty()==false``
  
  **Effects** Removes pair referenced by``item_accessor``
  from the table and destroys it. Concurrent insertion of the same key creates a new
  ``pair`` in the table, which can temporarily co-exist with the one
  being destroyed.
  
  **Returns**: True if pair was removed by this thread; false if pair was removed
  by another thread.
------------------------------------------------------------------------------------------
= ========================================================================================
