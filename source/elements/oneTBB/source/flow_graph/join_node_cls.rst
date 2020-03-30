========================
join_node Template Class
========================


Summary
-------

A node that creates a tuple<T0,T1, ... > from a set of messages
received at its input ports and broadcasts the tuple to all of its successors.
The
``class````join_node`` supports three buffering policies at its
input ports:
``reserving``,
``queueing`` and
``key_matching``. By default,
``join_node`` input ports use the
``queueing`` policy.

Syntax
------

.. code:: cpp

   struct queueing;
   struct reserving;
   template<typename K, typename KHash=tbb_hash_compare<K> > struct key_matching;
   typedef key_matching<tag_value> tag_matching;
   
   template<typename OutputTuple, class JP = queueing>
   class join_node;


Header
------

.. code:: cpp

   #include "tbb/flow_graph.h"


Description
-----------

A join_node is a
``graph_node`` and a
``sender< flow::tuple< T0, T1, ... > >``. It
contains a tuple of input ports, each of which is a
``receiver<Ti>`` for each of the
``T0`` ..
``TN`` in
``OutputTuple``. It supports multiple input receivers
with distinct types and broadcasts a tuple of received messages to all of its
successors. All input ports of a
``join_node`` must use the same buffering policy. The
behavior of a
``join_node`` based on its buffering policy is shown in
the table below.

= ========================================================================================
\ Behavior of a join_node based on the buffering policy of its input ports.: Buffering Policy, Behavior
==========================================================================================
\ queueing
  \
  As each input port is put to, the incoming message is added to
  an unbounded first-in first-out queue in the port. When there is at least one
  message at each input port, the
  ``join_node`` broadcasts a tuple containing the
  head of each queue to all successors. If at least one successor accepts the
  tuple, the head of each input port's queue is removed; otherwise, the messages
  remain in their respective input port queues.
------------------------------------------------------------------------------------------
\ reserving
  \
  As each input port is put to, the
  ``join_node`` marks that an input may be
  available at that port and returns
  ``false``. When all ports have been marked as
  possibly available, the
  ``join_node`` will try to reserve a message at
  each port from their known predecessors. If it is unable to reserve a message
  at a port, it unmarks that port, and releases all previously acquired
  reservations. If it is able to reserve a message at all ports, it broadcasts a
  tuple containing these messages to all successors. If at least one successor
  accepts the tuple, the reservations are consumed; otherwise, they are released.
------------------------------------------------------------------------------------------
\ key_matching<typename K, class KHash=tbb_hash_compare<K> >
  \
  As each input port is put to, a user-provided function object
  is applied to the message to obtain its key. The message is then added to a
  hash table of the input port. When there is a message
  at each input port for a given key, the ``join_node``
  removes all matching messages from the input ports,
  constructs a tuple containing the matching messages
  and attempts to broadcast it to all successors.
  If no successor accepts the tuple, it is saved and will be
  forwarded on a subsequent try_get.
  
  If K is a reference type (such as int&) then the function
  objects provided to the constructor should have the type signature::

                                                const K' &(const Ti&)
                                              
  
  (where K == K'&) for each type Ti of the tuple.  If
  K is not a reference type, the type signature of the function objects
  provided to the constructor are
  
  .. code:: cpp

                                                K (const Ti&)
                                              
  
  for each type Ti of the tuple.
------------------------------------------------------------------------------------------
\ tag_matching
  \
  A specialization of key_matching that accepts keys of type tag_value.
  Otherwise the behavior is the same as key_matching.
------------------------------------------------------------------------------------------
= ========================================================================================

Rejection of messages by successors of the
``join_node`` and failed gets from predecessors of the
input ports are handled using the protocol described in the Message Passing Protocol.

The function template
``input_port`` simplifies the syntax for getting a
reference to a specific input port.

``OutputTuple`` must be a
``flow::tuple<T0,T1, ... >`` where each element is
copy-constructible and assignable.

Example
-------

.. code:: cpp

   #include<cstdio>
   #include "tbb/flow_graph.h"
   
   using namespace tbb::flow;
   
   int main() {
      graph g;
      function_node<int,int>
          f1( g, unlimited, [](const int &i) { return 2*i; } );
      function_node<float,float>
          f2( g, unlimited, [](const float &f) { return f/2; } );
   
      join_node< tbb::flow::tuple<int,float> > j(g);
   
      function_node< flow::tuple<int,float> >
          f3( g, unlimited,
              []( const flow::tuple<int,float> &t ) {
                  printf( "Result is %f\n",
                          std::get<0>(t) + std::get<1>(t));
              } );
   
      make_edge( f1, input_port<0>( j ) );
      make_edge( f2, input_port<1>( j ) );
      make_edge( j, f3 );
   
      f1.try_put( 3 );
      f2.try_put( 3 );
      g.wait_for_all( );
      return 0;
   }

In the example above, three
``function_node`` objects are created:
``f1`` multiplies an
``int i`` by 2,
``f2`` divides a
``float f`` by 2, and
``f3`` receives a
``flow::tuple<int,float> t``, adds its elements
together and prints the result. The
``join_node j`` combines the output of
``f1`` and
``f2``, and then forwards the resulting tuple to
``f3``. This example is purely a syntactic demonstration
since there is very little work in the nodes.

Members
-------

.. code:: cpp

   namespace tbb {
   namespace flow {
   
   struct reserving;
   struct queueing;
   template<typename K, class KHash=tbb_hash_compare<K> >
   struct key_matching;
   typedef key_matching<tag_value> tag_matching;
   
   template<typename OutputTuple, class JP = queueing>
   class join_node :
       public graph_node, public sender< OutputTuple > {
   
   public:
       typedef OutputTuple output_type;
       typedef receiver<output_type> successor_type;
       typedef implementation-dependent-tuple input_ports_type;
   
       explicit join_node( graph &g );
       join_node( const join_node &src );
       input_ports_type &input_ports( );
       bool register_successor( successor_type &r );
       bool remove_successor( successor_type &r );
       bool try_get( output_type &v );
       bool try_reserve( output_type &v );
       bool try_release( );
       bool try_consume( );
   
   };
   
   //
   // Specialization for key_matching
   //
   
   template<typename OutputTuple, typename K, class KHash=tbb_hash_compare<K> >
   class join_node<OutputTuple, key_matching<K,KHash> > :
       public graph_node, public sender< OutputTuple > {
   
   public:
   
       // Has the same methods as previous join_node,
       // but has constructors to specify the key_matching
       // function objects
   
       template<typename B0, typename B1>
       join_node( graph &g, B0 b0, B1 b1 );
   
       // Constructors are defined similarly for
       // 3 through 10 elements ...
   };
   
   }
   }

The following table provides additional information on the
members of this template class.

= ========================================================================================
\ Member, Description
==========================================================================================
\ ``explicit join_node( graph &g )``
  \
  Constructs a
  ``join_node`` that will spawn tasks using the
  root task in
  ``g``.
------------------------------------------------------------------------------------------
\ ``template < typename B0, typename B1, ... > join_node( graph &g, B0 b0, B1 b1, ... )``
  \
  A constructor only available in the
  ``key_matching`` specialization of
  ``join_node``.
  
  Creates a
  ``join_node`` that uses the function objects
  ``b0``,
  ``b1``, ... ,
  ``bN`` to determine that tags for the input
  ports 0 through N. It will spawn tasks using the root task in
  ``g``.
  
  .. caution::

     Function objects passed to the join_node constructor must not
     throw. They are called in parallel, and should be pure, take minimal
     time and be non-blocking.
  
------------------------------------------------------------------------------------------
\ ``join_node( const join_node &src )``
  \
  Creates a
  ``join_node`` that has the same initial state
  that
  ``src`` had at its construction. The list of
  predecessors, messages in the input ports, and successors are NOT copied.
------------------------------------------------------------------------------------------
\ ``input_ports_type &input_ports( )``
  \
  **Returns**: a
  ``flow::tuple`` of receivers. Each element
  inherits from
  ``tbb::receiver<T>`` where
  ``T`` is the type of message expected at that
  input. Each tuple element can be used like any other
  ``flow::receiver<T>``. The behavior of
  the ports based on the selected
  ``join_node`` policy is shown in the table
  above.
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
  Attempts to generate a tuple based on the buffering policy
  of the
  ``join_node``.
  
  **Returns**: If it can successfully generate a tuple, it
  copies it to
  ``v`` and returns
  ``true``. Otherwise it returns
  ``false``.
------------------------------------------------------------------------------------------
\ ``bool try_reserve( output_type &v )``
  \
  Does not support reservations.
  
  **Returns**:
  ``false``.
------------------------------------------------------------------------------------------
\ ``bool try_release( )``
  \
  Does not support reservations.
  
  **Returns**:
  ``false``.
------------------------------------------------------------------------------------------
\ ``bool try_consume( )``
  \
  Does not support reservations.
  
  **Returns**:
  ``false``.
------------------------------------------------------------------------------------------
\ ``template<size_t N, typename JNT> typename flow::tuple_element<N, typename JNT::input_ports_type>::type &input_port( JNT &jn )``
  \
  Calling
  ``input_port <N>( jn )`` is equivalent
  to calling
  ``std::get<N>( jn.input_ports() )``
  
  **Returns**: the N\ :sup:`th` input port for
  ``join_node jn``.
------------------------------------------------------------------------------------------
= ========================================================================================


See also:

* :doc:`input_port Template Function <input_port_func>`
* :doc:`Message Passing Protocol <message_passing_protocol>`
* :doc:`Sender and Buffer Policy <sender_and_buffer_policy>`
