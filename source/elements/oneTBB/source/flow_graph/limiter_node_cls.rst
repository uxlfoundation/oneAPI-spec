===========================
limiter_node Template Class
===========================


Summary
-------

An node that counts and limits the number of messages that pass through it.

Syntax
------

.. code:: cpp

   template < typename T, typename DecrementType=continue_msg >
   class limiter_node;


Header
------

.. code:: cpp

   #include "tbb/flow_graph.h"


Description
-----------

A ``limiter_node`` is a ``graph_node``,
``receiver<T>`` and ``sender<T>`` that broadcasts
messages to all of its successors. It keeps a counter ``C`` of the number of
broadcasts it makes and does not accept new messages once its user-specified
``threshold`` is reached. The internal count of broadcasts ``C``
can be adjusted through use of its embedded ``decrement`` object, but its
values are truncated to be inside [0, ``threshold``] interval.

The behavior of a call to a ``limiter_node``'s ``try_put`` is
shown below.

.. table:: Behavior of a call to a limiter_node's try_put

   ================== ==============================================================
   Value of counter C bool try_put( const input_type &v )
   ================== ==============================================================
   ``C < threshold``  ``C`` is incremented and ``v`` is broadcast to all successors.
                      If no successor accepts the message, ``C`` is decremented.
                      Returns ``true`` if the message was successfully broadcast
                      to at least one successor and ``false`` otherwise.
   ------------------ --------------------------------------------------------------
   ``C == threshold`` Returns ``false``.
   ================== ==============================================================

The template parameter ``DecrementType`` specifies the type of the message that
can be sent to the member object ``decrement``. This template parameter can be
either integral type or ``continue_msg``. The latter is the default. If an
integral type is specified, positive values sent to ``decrement`` port
determine the value on which the internal counter ``C`` will be decreased,
while negative values determine the value on which the internal counter ``C``
will be increased.

The ``continue_msg`` sent to the member object ``decrement``
decreases the internal counter ``C`` by one.

When ``try_put`` call on the member object ``decrement`` results
in the new value of internal counter ``C`` to be less than the
``threshold``, the ``limiter_node`` will try to get a message from
one of its known predecessors and forward that message to all of its successors. If it
cannot obtain a message from a predecessor, it will decrement ``C``. Rejection
of messages by successors and failed gets from predecessors are handled using the protocol
described in the Message Passing Protocol.

``T`` must be copy-constructible and assignable.

Example
-------

The example from "Using limiter_node" section of TBB Developer Guide
shows usage specifics for this node type.

Members
-------

.. code:: cpp

   namespace tbb {
   namespace flow {
   
   template< typename T, typename DecrementType=continue_msg >
   class limiter_node : public graph_node, public receiver<T>,
                        public sender<T> {
   public:
       limiter_node( graph &g, size_t threshold );
       // deprecated constructor
       limiter_node( graph &g, size_t threshold,
                     int number_of_decrement_predecessors = 0 );
       limiter_node( const limiter_node &src );
   
       // receiver<DecrementType>
       implementation-dependent-type decrement;
   
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

The following table provides additional information on the members of this template class.

= ========================================================================================
\ Member, Description
==========================================================================================
\ ``limiter_node( graph &g, size_t threshold )``
  \
  Constructs a ``limiter_node`` that allows up to
  ``threshold`` items to pass through before rejecting
  ``try_put``'s.
------------------------------------------------------------------------------------------
\ ``limiter_node( graph &g, size_t threshold, int number_of_decrement_predecessors = 0 )``
  \
  Constructs a ``limiter_node`` that allows up to
  ``threshold`` items to pass through before rejecting
  ``try_put``'s. Optionally a
  ``number_of_decrement_predecessors`` value can be supplied. This value
  is passed on to the ``continue_receiver decrement``'s constructor.
  
  .. note::

     This constructor has been deprecated. Its use is discouraged. One can specify
     ``TBB_DEPRECATED_LIMITER_NODE_CONSTRUCTOR`` to be able to use this
     constructor again for a while.
  
------------------------------------------------------------------------------------------
\ ``limiter_node( const limiter_node &src )``
  \
  Constructs a ``limiter_node`` that has the same initial state that
  ``src`` had at its construction. The new ``limiter_node``
  will belong to the same ``graph g`` as ``src``, have the
  same ``threshold``, and have the same initial
  ``number_of_decrement_predecessors``. The list of predecessors, the
  list of successors, and the current count of broadcasts, C, are NOT copied from
  ``src``.
------------------------------------------------------------------------------------------
\ ``bool try_put( const input_type &v )``
  \
  If the broadcast count is below the threshold, ``v`` is broadcast to
  all successors. For each successor ``s``, if ``s.try_put( v ) == false && s.register_predecessor( *this ) == true``, then
  ``s`` is removed from the set of successors.  Otherwise,
  ``s`` will remain in the set of successors.
  
  **Returns**: ``true`` if ``v`` is broadcast.
  ``false`` if ``v`` is not broadcast because the threshold
  has been reached.
------------------------------------------------------------------------------------------
\ ``bool register_predecessor( predecessor_type &p )``
  \
  Adds a predecessor that can be pulled from once the broadcast count falls below the
  threshold.
  
  Adds ``p`` to the set of predecessors.
  
  **Returns**:``true``.
------------------------------------------------------------------------------------------
\ ``bool remove_predecessor( predecessor_type &p )``
  \
  Removes ``p`` from the set of predecessors.
  
  **Returns**:
  ``true``
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
  Does not contain buffering and therefore cannot be pulled from.
  
  **Returns**: ``false``.
------------------------------------------------------------------------------------------
\ ``bool try_reserve( output_type &v )``
  \
  Does not support reservations.
  
  **Returns**: ``false``.
------------------------------------------------------------------------------------------
\ ``bool try_release( )``
  \
  Does not support reservations.
  
  **Returns**: ``false``.
------------------------------------------------------------------------------------------
\ ``bool try_consume( )``
  \
  Does not support reservations.
  
  **Returns**: ``false``.
------------------------------------------------------------------------------------------
= ========================================================================================


See also:

* :doc:`Message Passing Protocol <message_passing_protocol>`
* :doc:`Sender and Buffer Policy <sender_and_buffer_policy>`
