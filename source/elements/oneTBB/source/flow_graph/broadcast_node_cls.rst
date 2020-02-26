=============================
broadcast_node Template Class
=============================


Summary
-------

A node that broadcasts incoming messages to all of its successors.

Syntax
------

.. code:: cpp

   template < typename T > class broadcast_node;


Header
------

.. code:: cpp

   #include "tbb/flow_graph.h"


Description
-----------

A 
``broadcast_node`` is a 
``graph_node``, 
``receiver<T>`` and 
``sender<T>`` that broadcasts incoming messages of
type 
``T`` to all of its successors. There is no buffering in
the node, so all messages are forwarded immediately to all successors.

Rejection of messages by successors is handled using the protocol described in
the Message Passing Protocol.

``T`` must be copy-constructible and assignable.

Members
-------

.. code:: cpp

   namespace tbb {
   namespace flow {
    
   template< typename T >
   class broadcast_node :
     public graph_node, public receiver<T>, public sender<T> {
   public:
       explicit broadcast_node( graph &g );
       broadcast_node( const broadcast_node &src );
    
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
\ ``explicit broadcast_node( graph &g )``
  \
  Constructs an object of type 
  ``broadcast_node`` that belongs to the 
  ``graph g``.
------------------------------------------------------------------------------------------
\ ``broadcast_node( const broadcast_node &src )``
  \
  Constructs an object of type 
  ``broadcast_node`` that belongs to the same 
  ``graph g`` as 
  ``src``. The list of predecessors, the list of
  successors and the messages in the buffer are NOT copied.
------------------------------------------------------------------------------------------
\ ``bool try_put( const input_type &v )``
  \
  Adds 
  ``v`` to all successors.
  
  **Returns**: always returns 
  ``true``, even if it was unable to
  successfully forward the message to any of its successors.
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
  If the internal buffer is valid, assigns the value to 
  ``v``.
  
  **Returns**: 
  ``true`` if 
  ``v`` is assigned to. 
  ``false`` if 
  ``v`` is not assigned to.
------------------------------------------------------------------------------------------
\ ``bool try_reserve( output_type &v )``
  \
  **Returns**: 
  ``false``
------------------------------------------------------------------------------------------
\ ``bool try_release( )``
  \
  **Returns**: 
  ``false``
------------------------------------------------------------------------------------------
\ ``bool try_consume( )``
  \
  **Returns**: 
  ``false``
------------------------------------------------------------------------------------------
= ========================================================================================


See also:

* :doc:`Message Passing Protocol <message_passing_protocol>`
* :doc:`Sender and Buffer Policy <sender_and_buffer_policy>`
