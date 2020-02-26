============
Node Handles
============


Summary
-------

Concurrent associative containers in TBB (``concurrent_unordered_{map, multimap, set, multiset}``,
``concurrent_{map, multimap, set, multiset}``) store data in individually allocated, connected nodes.
It makes possible to transfer data between containers with compatible node types by changing the connections,
without copying or moving the actual data.

A node handle (supported since C++11) is a container-specific move-only nested type
(exposed as ``container::node_type``) that represents a node outside of any
container instance. It allows reading and modifying the data stored in the node, and
inserting the node into a compatible container instance. The following containers have
compatible node types and may exchange nodes:

* ``concurrent_unordered_{map,multimap}`` classes with the same
  ``key_type``, ``mapped_type`` and ``allocator_type``
* ``concurrent_unordered_{set,multiset}`` classes with the same
  ``value_type`` and ``allocator_type``
* Preview ``concurrent_{map,multimap}`` classes with the same
  ``key_type``, ``mapped_type`` and ``allocator_type``
* Preview ``concurrent_{set,multiset}`` classes with the same
  ``value_type`` and ``allocator_type``

Default-constructed node handles are empty, i.e. do not represent a valid node.
A non-empty node handle is typically created when a node is extracted out of a container,
e.g. with the ``unsafe_extract`` method. It stores the node along with a copy of the container’s
allocator. If the node is then moved into another handle or inserted into a container, the
moved-from handle becomes empty. Upon assignment or destruction, a non-empty node handle
destroys the stored data and deallocates the node.

Members
-------

.. code:: cpp

   class node-handle { // Exposition-only name; use container::node_type instead
   public:
       typedef container-specific key_type;    // Only for maps
       typedef container-specific mapped_type; // Only for maps
       typedef container-specific value_type;  // Only for sets
       typedef container-specific allocator_type;
   
       node-handle();
       node-handle(node-handle&& nh);
       ~node-handle();
   
       node-handle& operator=(node-handle&& nh);
   
       void swap(node-handle& nh);
   
       bool empty() const;
       explicit operator bool() const;
   
       key_type& key() const;       // Only for maps
       mapped_type& mapped() const; // Only for maps
       value_type& value() const;   // Only for sets
       allocator_type get_allocator() const;
   };

The following table provides additional information on the members of a node handle class:

= ========================================================================================
\ Member, Description
==========================================================================================
\ ``node-handle()``
  \
  Constructs an empty node handle.
------------------------------------------------------------------------------------------
\ ``node-handle(node-handle&& nh)``
  \
  Constructs a node handle that takes ownership of the node from
  ``nh``, leaving it in the empty state.
------------------------------------------------------------------------------------------
\ ``~node-handle()``
  \
  If ``*this`` is not empty, destroys and deallocates the owned node.
------------------------------------------------------------------------------------------
\ ``node-handle& operator=(node-handle&& nh)``
  \
  If ``*this`` is not empty, destroys and deallocates the owned node.
  In either case, takes ownership of the node from ``nh``, leaving it in the empty state.
  
  **Returns**:
  A reference to ``*this``.
------------------------------------------------------------------------------------------
\ ``void swap(node-handle& nh)``
  \
  Exchanges the nodes owned by ``*this`` and ``nh``.
------------------------------------------------------------------------------------------
\ ``bool empty()``
  \
  **Returns**:
  ``true`` if the node handle is empty, ``false`` otherwise.
------------------------------------------------------------------------------------------
\ ``explicit operator bool() const``
  \
  Equivalent to ``!nh.empty()``.
------------------------------------------------------------------------------------------
\ ``key_type& key() const``
  \
  Available only for map node handles.
  
  **Returns**:
  Reference to the key of the element stored in the owned node.
  The behavior is undefined if the node handle is empty.
------------------------------------------------------------------------------------------
\ ``mapped_type& mapped() const``
  \
  Available only for map node handles.
  
  **Returns**:
  Reference to the value of the element stored in the owned node.
  The behavior is undefined if the node handle is empty.
------------------------------------------------------------------------------------------
\ ``value_type& value() const``
  \
  Available only for set node handles.
  
  **Returns**:
  Reference to the element stored in the owned node.
  The behavior is undefined if the node handle is empty.
------------------------------------------------------------------------------------------
\ ``allocator_type get_allocator() const;``
  \
  **Returns**:
  Copy of the stored allocator instance.
  The behavior is undefined if the node handle is empty.
------------------------------------------------------------------------------------------
= ========================================================================================


Example
-------

The following simplified example shows how to transfer data between containers with the
help of a node handle:

.. include:: ./examples/node_handles.cpp
   :code: cpp

