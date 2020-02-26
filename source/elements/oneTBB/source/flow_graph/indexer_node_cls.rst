===========================
indexer_node Template Class
===========================


Summary
-------

A node that broadcasts messages received at its
input ports to all of its successors. The messages are broadcast 
individually as they are received at each port. The output is a tagged message that contains a tag and a value; the tag identifies the input port on which the message was received.

Syntax
------

.. code:: cpp

   template<typename T0, typename T1...typename TN>
    class indexer_node;


Header
------

.. code:: cpp

    #include "tbb/flow_graph.h"


Description
-----------

An indexer_node is a 
``graph_node`` and 
``sender< indexer_node<T0..TN>::output_type >``. It contains a tuple of
input ports, each of which is a 
``receiver<Ti>`` for
each of the 
``T0 .. TN`` in the input. It supports multiple input receivers with distinct types
and broadcasts each received message to all of its successors. Unlike a 
``join_node``, each
message is broadcast individually to all successors of the 
``indexer_node`` as it arrives
at an input port. Before broadcasting, a message is tagged with the index of the port on which the message arrived.

The function template 
``input_port`` 
simplifies the syntax for getting a reference to a specific input port.

Rejection of messages by successors of the 
``indexer_node`` is handled
using the protocol described in the Message Passing Protocol. The input
ports never reject incoming messages.

Each type in the input list ``T0, T1 ... TN``  
should be copy-constructible and assignable.

Example
-------

.. code:: cpp

   #include<cstdio>
   #include "tbb/flow_graph.h"
   
   using namespace tbb::flow;
   
   int main() {
     graph g;
     function_node<int,int> f1( g, unlimited,
                                  [](const int &i) { return 2*i; } );
     function_node<float,float> f2( g, unlimited,
                                  [](const float &f) { return f/2; } );
   
     typedef indexer_node<int,float> my_indexer_type;
     my_indexer_type o(g);
   
     function_node< my_indexer_type::output_type >
       f3( g, unlimited,
           []( const my_indexer_type::output_type &v ) {
               if (v.tag() == 0) {
                 printf("Received an int %d\n", 
                        cast_to<int>(v));
               } else {
                 printf("Received a float %f\n", 
                        cast_to<float>(v));
              }
           }
       );
     make_edge( f1, input_port<0>(o) );
     make_edge( f2, input_port<1>(o) );
     make_edge( o, f3 );
   
     f1.try_put( 3 );
     f2.try_put( 3 );
     g.wait_for_all();
     return 0;
    }

In the example above, three 
``function_node`` objects
are created: 
``f1`` multiplies an int i
by 2, 
``f2`` divides a 
``float f`` by 2, and 
``f3`` prints the values
from 
``f1`` and 
``f2`` as they arrive. The

``indexer_node o`` wraps the
output of 
``f1`` and 
``f2`` and forwards each
result to 
``f3``. This example is
purely a syntactic demonstration since there is very little work in the nodes.

Members
-------

.. code:: cpp

   namespace tbb {
   namespace flow {
     template<typename T0, typename T1...typename TN>
     class indexer_node : public graph_node,
     public sender<implementation-dependent-output-type > {
     public:
       typedef tagged_msg< size_t tag, T result> output_type;
       typedef receiver<output_type> successor_type;
       implementation-dependent-tuple input_ports_type;
   
       indexer_node(graph &g);
       indexer_node(const indexer_node &src);
       input_ports_type &input_ports();
       bool register_successor( successor_type &r );
       bool remove_successor( successor_type &r );
       bool try_get( output_type &v );
       bool try_reserve( output_type & );
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
\ ``indexer_node(graph &g)``
  \
  Constructs an 
  ``indexer_node`` that
  belongs to the 
  ``graph g``.
------------------------------------------------------------------------------------------
\ ``indexer_node( const indexer_node &src )``
  \
  Constructs an 
  ``indexer_node``. The
  list of predecessors, messages in the input ports, and successors are NOT
  copied.
------------------------------------------------------------------------------------------
\ ``input_ports_type& input_ports()``
  \
  **Returns**: A 
  ``flow::tuple``
  of receivers. Each element inherits from 
  ``tbb::receiver<T>`` where T is the
  type of message expected at that input. Each tuple element can be used like any
  other 
  ``flow::receiver<T>``.
------------------------------------------------------------------------------------------
\ ``bool register_successor( successor_type & r )``
  \
  Adds 
  ``r`` to the set
  of successors.
  
  **Returns**: 
  ``true``.
------------------------------------------------------------------------------------------
\ ``bool remove_successor( successor_type & r )``
  \
  Removes 
  ``r`` from the
  set of successors.
  
  **Returns**: 
  ``true``.
------------------------------------------------------------------------------------------
\ ``bool try_get( output_type &v )``
  \
  An 
  ``indexer_node``
  contains no buffering and therefore does not support gets.
  
  **Returns**: 
  ``false``.
------------------------------------------------------------------------------------------
\ ``bool try_reserve( output_type & )``
  \
  An 
  ``indexer_node``
  contains no buffering and therefore cannot be reserved.
  
  **Returns**: 
  ``false``.
------------------------------------------------------------------------------------------
\ ``bool try_release( )``
  \
  An 
  ``indexer_node``
  contains no buffering and therefore cannot be reserved.
  
  **Returns**: 
  ``false``.
------------------------------------------------------------------------------------------
\ ``bool try_consume( )``
  \
  An 
  ``indexer_node``
  contains no buffering and therefore cannot be reserved.
  
  **Returns**: 
  ``false``.
------------------------------------------------------------------------------------------
= ========================================================================================

.. caution::

   On Microsoft Windows* operating systems, there is a known issue with 
   passing array types to indexer_node.


See also:

* :doc:`Message Passing Protocol <message_passing_protocol>`
* :doc:`Sender and Buffer Policy <sender_and_buffer_policy>`
* :doc:`input_port Template Class <input_port_func>`
* :doc:`tagged_msg Template Class <tagged_msg_cls>`
