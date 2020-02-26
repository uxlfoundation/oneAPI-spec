=================
buffer_node Class
=================


Summary
-------

An unbounded buffer of messages of type ``T``. Messages are forwarded in
arbitrary order.

Syntax
------

.. code:: cpp

   template< typename T, typename A = cache_aligned_allocator<T> >
   class buffer_node;


Header
------

.. code:: cpp

   #include "tbb/flow_graph.h"


Description
-----------

A ``buffer_node`` is a ``graph_node``,
``receiver<T>`` and ``sender<T>`` that forwards
messages in arbitrary order to a single successor in its successor set. Successors are tried
in the order that they were registered with the node. If a successor rejects the message, it
is removed from the successor list according to the policy in the Message Passing Protocol,
and the next successor in the set is tried. This continues until a successor accepts the
message, or all successors have been attempted. Items that are successfully transferred to a
successor are removed from the buffer.

A ``buffer_node`` is reservable and supports a single reservation at a
time. While an item is reserved, other items may still be forwarded to successors and
``try_get`` calls will return other non-reserved items if available. While an
item is reserved, ``try_put`` will still return ``true`` and
add items to the buffer.

An allocator of type ``A`` is used to allocate internal memory for the
``buffer_node.``

``T`` must be copy-constructible and assignable.

Rejection of messages by successors is handled using the protocol described in the Message
Passing Protocol.

Example
-------

The example below shows a possible ``buffer_node`` usage scenario. A
``buffer_node`` is used as a load balancer that stores rejected messages,
preventing their loss and allowing another graph node to process them.

.. include:: ./examples/buffer_node_cls.cpp
   :code: cpp



Members
-------

.. code:: cpp

   namespace tbb {
   namespace flow {
   
   template< typename T, typename A = cache_aligned_allocator<T> >
   class buffer_node :
     public graph_node, public receiver<T>, public sender<T> {
   public:
       explicit buffer_node( graph &g );
       buffer_node( const buffer_node &src );
   
       // receiver<T>
       typedef T input_type;
       typedef sender<input_type> predecessor_type;
       bool try_put( const input_type &v );
       bool register_predecessor( predecessor_type &p );
       bool remove_predecessor( predecessor_type &p );
   
       // sender<T>
       typedef T output_type;
       typedef receiver<output_type> successor_type;
       bool register_successor( successor_type &r );
       bool remove_successor( successor_type &r );
       bool try_get( output_type &v );
       bool try_reserve( output_type &v );
       bool try_release( );
       bool try_consume( );
   };
   
   }
   }

The following table provides additional information on the members of this class.

= ========================================================================================
\ Member, Description
==========================================================================================
\ ``explicit buffer_node( graph &g )``
  \
  Constructs an empty ``buffer_node`` that belongs to the
  ``graph g``.
------------------------------------------------------------------------------------------
\ ``buffer_node( const buffer_node &src )``
  \
  Constructs an empty ``buffer_node``. The buffered value and list of
  successors is NOT copied from ``src``.
------------------------------------------------------------------------------------------
\ ``bool try_put( const input_type &v )``
  \
  Adds ``v`` to the buffer. If ``v`` is the only item
  in the buffer, a task is also spawned to forward the item to a successor.
  
  **Returns**: ``true``
------------------------------------------------------------------------------------------
\ ``bool register_predecessor( predecessor_type &p )``
  \
  Never rejects puts and therefore does not need to maintain a list of predecessors.
  
  **Returns**: ``false``
------------------------------------------------------------------------------------------
\ ``bool remove_predecessor( predecessor_type &p )``
  \
  Never rejects puts and therefore does not need to maintain a list of predecessors.
  
  **Returns**: ``false``
------------------------------------------------------------------------------------------
\ ``bool register_successor( successor_type &r )``
  \
  Adds ``r`` to the set of successors.
  
  **Returns**: ``true``
------------------------------------------------------------------------------------------
\ ``bool remove_successor( successor_type &r )``
  \
  Removes ``r`` from the set of successors.
  
  **Returns**: ``true``
------------------------------------------------------------------------------------------
\ ``bool try_get( output_type &v )``
  \
  **Returns**: ``true`` if an item can be removed from the buffer
  and assigned to ``v``. Returns ``false`` if there is
  no non-reserved item currently in the buffer.
------------------------------------------------------------------------------------------
\ ``bool try_reserve( output_type &v )``
  \
  Assigns a newly reserved item to ``v`` if there is no reservation
  currently held and there is at least one item available in the buffer. If a new
  reservation is made, the buffer is marked as reserved.
  
  **Returns**: ``true`` if ``v`` has been assigned
  a newly reserved item. Returns ``false`` otherwise.
------------------------------------------------------------------------------------------
\ ``bool try_release( )``
  \
  Releases the reservation on the buffer. The item that was returned in the last
  successful call to ``try_reserve`` remains in the buffer.
  
  **Returns**: ``true`` if the buffer is currently reserved and
  ``false`` otherwise.
------------------------------------------------------------------------------------------
\ ``bool try_consume( )``
  \
  Releases the reservation on the buffer. The item that was returned in the last
  successful call to ``try_reserve`` is removed from the buffer.
  
  **Returns**: ``true`` if the buffer is currently reserved and
  ``false`` otherwise.
------------------------------------------------------------------------------------------
= ========================================================================================


See also:

* :doc:`Message Passing Protocol <message_passing_protocol>`
* :doc:`Sender and Buffer Policy <sender_and_buffer_policy>`
