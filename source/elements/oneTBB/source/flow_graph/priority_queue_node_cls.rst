==================================
priority_queue_node Template Class
==================================


Summary
-------

An unbounded buffer of messages of type 
``T``. Messages are forwarded in priority order.

Syntax
------

.. code:: cpp

   template< typename T,
             typename Compare = std::less<T>,
             typename A = cache_aligned_allocator<T> >
   class priority_queue_node;


Header
------

.. code:: cpp

   #include "tbb/flow_graph.h"


Description
-----------

A 
``priority_queue_node`` is a 
``graph_node``, 
``receiver<T>`` and 
``sender<T>`` that forwards messages in priority
order to a single successor in its successor set. Successors are tried in the
order that they were registered with the node. If a successor rejects the
message, it is removed from the successor list as described by the policy in
the Message Passing Protocol, and the next successor in the set is tried. This
continues until a successor accepts the message, or all successors have been
attempted. Items that are successfully transferred to a successor are removed
from the buffer.

The next message to be forwarded has the largest priority as
determined by 
``Compare``.

A 
``priority_queue_node`` is reservable and supports a
single reservation at a time. While the 
``priority_queue_node`` is reserved, no other items will
be forwarded to successors and all 
``try_get`` calls will return 
``false``. While reserved, 
``try_put`` will still return 
``true`` and add items to the 
``priority_queue_node``.

An allocator of type 
``A`` is used to allocate internal memory for the 
``priority_queue_node.``

``T`` must be copy-constructible and assignable.

Rejection of messages by successors is handled using the protocol described in
the Message Passing Protocol.

.. caution::

   The ``Compare`` function object must not throw an exception.


Example
-------

Usage scenario is similar to
:doc:`sequencer_node <sequencer_node_cls>`
except that the ``priority_queue_node`` provides local order, passing the message
with highest priority of all stored at the moment, while ``sequencer_node`` enforces
global order and does not allow a "smaller priority" message to pass through before all its preceding messages.

Members
-------

.. code:: cpp

   namespace tbb {
   namespace flow {
    
   template< typename T, typename Compare = std::less<T>,
             typename A = cache_aligned_allocator<T>>
   class priority_queue_node : public queue_node<T> {
   public:
       typedef size_t size_type;
       explicit priority_queue_node( graph &g );
       priority_queue_node( const priority_queue_node &src );
       ~priority_queue_node();
    
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

The following table provides additional information on the
members of this template class.

= ========================================================================================
\ Member, Description
==========================================================================================
\ ``explicit priority_queue_node( graph &g )``
  \
  Constructs an empty 
  ``priority_queue_node`` that belongs to the 
  ``graph g``.
------------------------------------------------------------------------------------------
\ ``priority_queue_node( const priority_queue_node &src )``
  \
  Constructs an empty 
  ``priority_queue_node`` that belongs to the
  same 
  ``graph g`` as 
  ``src``. The list of predecessors, the list of
  successors and the messages in the buffer are NOT copied.
------------------------------------------------------------------------------------------
\ ``bool try_put( const input_type &v )``
  \
  Adds 
  ``v`` to the 
  ``priority_queue_node``. If 
  ``v``'s priority is the largest of all of the
  currently buffered messages, a task is spawned to forward the item to a
  successor.
  
  **Returns**: 
  ``true``
------------------------------------------------------------------------------------------
\ ``bool register_predecessor( predecessor_type &p )``
  \
  Never rejects puts and therefore does not need to maintain a
  list of predecessors.
  
  **Returns**: 
  ``false``
------------------------------------------------------------------------------------------
\ ``bool remove_predecessor( predecessor_type &p )``
  \
  Never rejects puts and therefore does not need to maintain a
  list of predecessors.
  
  **Returns**: 
  ``false``
------------------------------------------------------------------------------------------
\ ``bool register_successor( successor_type &r )``
  \
  Adds 
  ``r`` to the set of successors.
  
  **Returns**: 
  ``true``
------------------------------------------------------------------------------------------
\ ``bool remove_successor( successor_type &r )``
  \
  Removes 
  ``r`` from the set of successors.
  
  **Returns**: 
  ``true``
------------------------------------------------------------------------------------------
\ ``bool try_get( output_type &v )``
  \
  **Returns**: 
  ``true`` if a message is available in the node
  and the node is not currently reserved. Otherwise returns 
  ``false``. If the node returns 
  ``true``, the message with the largest
  priority will have been copied to 
  ``v``.
------------------------------------------------------------------------------------------
\ ``bool try_reserve( output_type &v )``
  \
  If the call returns 
  ``true``, the node is reserved and will
  forward no more messages until the reservation has been released or consumed.
  
  **Returns**: 
  ``true`` if a message is available in the node
  and the node is not currently reserved. Otherwise returns 
  ``false``. If the node returns 
  ``true``, the message with the largest
  priority will have been copied to 
  ``v``.
------------------------------------------------------------------------------------------
\ ``bool try_release( )``
  \
  Releases the reservation on the node. The item that was
  returned in the last successful call to 
  ``try_reserve`` remains in the 
  ``priority_queue_node``.
  
  **Returns**: 
  ``true`` if the buffer is currently reserved
  and 
  ``false`` otherwise.
------------------------------------------------------------------------------------------
\ ``bool try_consume( )``
  \
  Releases the reservation on the node. The item that was
  returned in the last successful call to 
  ``try_reserve`` is popped from the front of
  the queue.
  
  **Returns**: 
  ``true`` if the buffer is currently reserved
  and 
  ``false`` otherwise.
------------------------------------------------------------------------------------------
= ========================================================================================


See also:

* :doc:`Message Passing Protocol <message_passing_protocol>`
* :doc:`Sender and Buffer Policy <sender_and_buffer_policy>`
