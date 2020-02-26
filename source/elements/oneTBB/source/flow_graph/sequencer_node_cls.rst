=============================
sequencer_node Template Class
=============================


Summary
-------

An unbounded buffer of messages of type
``T``. Messages are forwarded in sequence order.

Syntax
------

.. code:: cpp

   template< typename T, typename A = cache_aligned_allocator<T> >
   class sequencer_node;


Header
------

.. code:: cpp

   #include "tbb/flow_graph.h"


Description
-----------

A
``sequencer_node`` is a
``graph_node``,
``receiver<T>`` and
``sender<T>`` that forwards messages in sequence
order to a single successor in its successor set. Successors are tried in the
order that they were registered with the node. If a successor rejects the
message, it is removed from the successor list as described by the policy in
the Message Passing Protocol, and the next successor in the set is tried. This
continues until a successor accepts the message, or all successors have been
attempted. Items that are successfully transferred to a successor are removed
from the buffer.

Each item that passes through a
``sequencer_node`` is ordered by its sequencer order
number. These sequence order numbers range from 0 to N, where N is the largest
integer representable by the
``size_t`` type. An item's sequencer order number is
determined by passing the item to a user-provided function object that models
the Sequencer Concept shown below.

.. note::

   The ``sequencer_node`` will reject duplicate sequencer numbers.

= ========================================================================================
\ sequencer_node<T> Sequencer Concept: Pseudo-Signature, Semantics
==========================================================================================
\ ``S::S( const S& )``
  \
  Copy constructor.
------------------------------------------------------------------------------------------
\ ``S::~S()``
  \
  Destructor.
------------------------------------------------------------------------------------------
\ ``void operator=( const S& )``
  \
  Assignment. The return type
  ``void`` in the pseudo-signature denotes that
  ``operator=`` is not required to return a value.
  The actual
  ``operator=`` can return a value, which will be
  ignored.
------------------------------------------------------------------------------------------
\ ``size_t S::operator()( const T &v )``>
  \
  Returns the sequence number for the provided message
  ``v``.
------------------------------------------------------------------------------------------
= ========================================================================================

A
``sequencer_node`` is reservable and supports a single
reservation at a time. While a
``sequencer_node`` is reserved, no other items will be
forwarded to successors and all
``try_get`` calls will return
``false``. While reserved,
``try_put`` will still return
``true`` and add items to the
``sequencer_node``.

An allocator of type
``A`` is used to allocate internal memory for the
``sequencer_node.``

``T`` must be copy-constructible and assignable.

Rejection of messages by successors is handled using the protocol described in
the Message Passing Protocol.

Example
-------

The example demonstrates ordering capabilities of the ``sequencer_node``.
While being processed in parallel, the data are passed to the successor node
in the exact same order they were read.

.. include:: ./examples/sequencer_node_cls.cpp
   :code: cpp



Members
-------

.. code:: cpp

   namespace tbb {
   namespace flow {
   
   template< typename T, typename A = cache_aligned_allocator<T> >
   class sequencer_node :
     public queue_node<T> {
   public:
       template< typename Sequencer >
       sequencer_node( graph &g, const Sequencer &s );
       sequencer_node( const sequencer_node &src );
   
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
\ ``template<typename Sequencer> sequencer_node( graph& g, const Sequencer &s )``
  \
  Constructs an empty
  ``sequencer_node`` that belongs to the
  ``graph g`` and uses
  ``s`` to compute sequence numbers for items.
  
  .. caution::

     The ``Sequencer`` function object must not throw an exception.
  
------------------------------------------------------------------------------------------
\ ``sequencer_node( const sequencer_node &src )``
  \
  Constructs an empty
  ``sequencer_node`` that belongs to the same
  ``graph g`` as
  ``src`` and will use a copy of the
  ``Sequencer s`` used to construct
  ``src``. The list of predecessors, the list of
  successors and the messages in the buffer are NOT copied.
  
  .. caution::

     The new sequencer object is copy-constructed from a copy
     of the original sequencer object provided to
     ``src`` at its construction. Therefore
     changes made to member variables in
     ``src``'s object will not affect the
     sequencer of the new
     ``sequencer_node.``
  
------------------------------------------------------------------------------------------
\ ``bool try_put( const input_type &v )``
  \
  Adds
  ``v`` to the
  ``sequencer_node``. If
  ``v``'s sequence number is the next item in
  the sequence, a task is spawned to forward the item to a successor.
  
  **Returns**:
  ``true``
------------------------------------------------------------------------------------------
\ ``bool register_predecessor( predecessor_type &p )``
  \
  The ``sequencer_node`` may reject puts, but the
  arc to the ``sequencer_node`` will never be reversed,
  so it does not need to maintain a list of predecessors.
  
  **Returns**:
  ``false``
------------------------------------------------------------------------------------------
\ ``bool remove_predecessor( predecessor_type &p )``
  \
  The ``sequencer_node`` may reject puts, but the
  arc to the ``sequencer_node`` will never be reversed,
  so it does not need to maintain a list of predecessors.
  
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
  ``true`` if the next item in the sequence is
  available in the
  ``sequencer_node``. If so, it is removed from
  the node and assigned to
  ``v``. Returns
  ``false`` if the next item in sequencer order
  is not available or if the node is reserved.
------------------------------------------------------------------------------------------
\ ``bool try_reserve( output_type &v )``
  \
  If the call returns
  ``true``, the node is reserved and will
  forward no more messages until the reservation has been released or consumed.
  
  **Returns**:
  ``true`` if the next item in sequencer order
  is available in the
  ``sequencer_node``. If so, the item is
  assigned to
  ``v``, but is not removed from the
  ``sequencer_node``. Returns
  ``false`` if the next item in sequencer order
  is not available or if the node is reserved.
------------------------------------------------------------------------------------------
\ ``bool try_release( )``
  \
  Releases the reservation on the node. The item that was
  returned in the last successful call to
  ``try_reserve`` remains in the
  ``sequencer_node``.
  
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
