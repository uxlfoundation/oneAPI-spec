=========================
split_node Template Class
=========================


Summary
-------

A template class that is a 
``receiver<TupleType>`` and has a
tuple of 
``sender< tuple_element< i, TupleType >::type >`` output ports; where i is the index in the
tuple. A 
``split_node`` sends each
element of the incoming tuple to the output port that matches the element's
index in the incoming tuple. This node has unlimited concurrency.

Syntax
------

.. code:: cpp

   template < typename TupleType >
    class split_node;


Header
------

.. code:: cpp

   #include "tbb/flow_graph.h"


Description
-----------

This node receives a tuple at its single input port
and generates a message from each element of the tuple, passing each to the
corresponding output port.

A 
``split_node`` has
unlimited concurrency, no buffering, and behaves as a 
``broadcast_node`` with
multiple output ports.

Example
-------

The example below shows a 
``split_node`` that
separates a stream of tuples of integers, placing each element of the tuple in
the appropriate output queue.

The output ports of the 
``split_node`` can be
connected to other graph nodes using the 
``make_edge`` method or by
using 
``register_successor``:

.. code:: cpp

   #include "tbb/flow_graph.h"
   using namespace tbb::flow;
   
   int main() {
     graph g;
   
     queue_node<int> first_queue(g);
     queue_node<int> second_queue(g);
     split_node< tbb::flow::tuple<int,int> > my_split_node(g);
     output_port<0>(my_split_node).register_successor(first_queue);
     make_edge(output_port<1>(my_split_node), second_queue);
   
     for(int i = 0; i < 1000; ++i) {
       tuple<int, int> my_tuple(2*i, 2*i+1);
       my_split_node.try_put(my_tuple);
     }
     g.wait_for_all();
    }


Members
-------

.. code:: cpp

   namespace tbb {
     template < typename TupleType >
       class split_node : public graph_node, public receiver<TupleType>
     {
     public:
   
       explicit split_node( graph &g );
       split_node( const split_node &other);
       ~split_node();
   
       // receiver< TupleType >
       typedef TupleType input_type;
       typedef sender<input_type> predecessor_type;
       bool try_put( const input_type &v );
       bool register_predecessor( predecessor_type &p );
       bool remove_predecessor( predecessor_type &p );
   
       typedef implementation-dependent output_ports_type;
       output_ports_type& output_ports();
     };
   }

The following table provides additional information on the
members of this template class.

= ========================================================================================
\ Member, Description
==========================================================================================
\ ``explicit split_node( graph &g )``
  \
  Constructs a 
  ``split_node`` registered with graph 
  ``g``.
------------------------------------------------------------------------------------------
\ ``split_node( const split_node &other)``
  \
  Constructs a 
  ``split_node`` that has the same initial state
  that 
  ``other`` had when it was constructed. The 
  ``split_node`` that is constructed will have a
  reference to the same 
  ``graph`` object as 
  ``other``. The predecessors and successors of 
  ``other`` will not be copied.
------------------------------------------------------------------------------------------
\ ``~split_node()``
  \
  Destructor
------------------------------------------------------------------------------------------
\ ``bool try_put( const input_type &v )``
  \
  Broadcasts each element of the incoming tuple to the nodes
  connected to the 
  ``split_node``'s output ports. The element at
  index 
  ``i`` of 
  ``v`` will be broadcast through the 
  ``i``\ :sup:`th` output port.
  
  **Returns**: 
  ``true``
------------------------------------------------------------------------------------------
\ ``bool register_predecessor( predecessor_type &p )``
  \
  Adds 
  ``p`` to the set of predecessors.
  
  **Returns**: 
  ``true``
------------------------------------------------------------------------------------------
\ ``bool remove_predecessor( predecessor_type &p )``
  \
  Removes 
  ``p`` from the set of predecessors.
  
  **Returns**: 
  ``true``
------------------------------------------------------------------------------------------
\ ``output_ports_type& output_ports();``
  \
  **Returns**: a tuple of output ports.
------------------------------------------------------------------------------------------
= ========================================================================================


See also:

* :doc:`Message Passing Protocol <message_passing_protocol>`
* :doc:`Sender and Buffer Policy <sender_and_buffer_policy>`
