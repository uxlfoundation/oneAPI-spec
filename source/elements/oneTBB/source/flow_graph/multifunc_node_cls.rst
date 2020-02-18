=================================
multifunction_node Template Class
=================================


Summary
-------

A template class that is a receiver<InputType> and has a tuple of sender<T>
outputs. This node may have concurrency limits as set by the user. When the concurrency
limit allows, it executes the user-provided body on incoming messages. The body may create
one or more output messages and broadcast them to successors.

Syntax
------

.. code:: cpp

   template < typename Input, typename Output,
              typename Policy = queueing, typename Allocator=cache_aligned_allocator<Input> >
   class multifunction_node;


Header
------

.. code:: cpp

   #include "tbb/flow_graph.h"


Description
-----------

This type is used for nodes that receive messages at a single input port and may generate
one or more messages that are broadcast to successors.

A ``multifunction_node`` maintains an internal
constant threshold T and an internal counter C. At construction, C=0 and T is set the value
passed in to the constructor. The behavior of a call to 
``try_put`` is determined by the value of T and C as shown in the table
below.

.. table:: Behavior of a call to a multifunction_node's try_put

   ========================= ================== ==============================
   Value of threshold T      Value of counter C bool try_put( input_type v )
   ========================= ================== ==============================
   ``T == graph::unlimited`` NA                 A task is spawned that executes body(v). Returns 
                                                ``true``.
   ------------------------- ------------------ ------------------------------
   ``T != flow::unlimited``  C < T              Increments C. A task is spawned that executes body(v) and then decrements
                                                C. Returns ``true``.
   ------------------------- ------------------ ------------------------------
   ``T != flow::unlimited``  C >= T             Returns ``false``.
   ========================= ================== ==============================

A ``multifunction_node`` has a user-settable
concurrency limit. It can have ``flow::unlimited concurrency``, which allows an unlimited number of copies of the node to execute
concurrently. It can have ``flow::serial concurrency``, which allows only a single copy of the node to execute
concurrently. The user can also provide a value of type size_t to limit concurrency to a
value between 1 and unlimited.

The Body concept for ``multifunction_node`` is
shown in the table below.

= ========================================================================================
\ multifunction_node Body Concept: Pseudo-Signature, Semantics
==========================================================================================
\ ``B::B( const B& )``
  \
  Copy constructor.
------------------------------------------------------------------------------------------
\ ``B::~B()``
  \
  Destructor.
------------------------------------------------------------------------------------------
\ ``void operator=( const B& )``
  \
  Assignment
------------------------------------------------------------------------------------------
\ ``void B::operator()(const input_type &v, output_ports_type &p)``
  \
  Perform operation on ``v``. May call
  ``try_put`` on zero or more of the
  output ports. May call ``try_put``
  on any output port multiple times.
------------------------------------------------------------------------------------------
= ========================================================================================

.. caution::

   The body object passed to a ``multifunction_node`` is copied. Therefore
   updates to member variables will not affect the original object used to construct the
   node. If the state held within a body object must be inspected from outside of the node,
   the ``copy_body`` function can be used to obtain an updated copy.

.. note::

   The body object may throw or cancel its enclosing graph. See task_group_context and
   Exceptions sections for a description.


Example
-------

The example below shows a 
``multifunction_node`` that separates a stream of integers into odd and even, placing
each in the appropriate output queue.

The Body method will receive as parameters a read-only reference to the input value and a
reference to the tuple of output ports. The Body method may put items to one or more output
ports.

The output ports of the ``multifunction_node``
can be connected to other graph nodes using the 
``make_edge`` method or by using 
``register_successor``:

.. code:: cpp

   #include "tbb/flow_graph.h"
   using namespace tbb::flow;
   typedef multifunction_node<int, tbb::flow::tuple<int,int> > multi_node;
   
   struct MultiBody {
     void operator()(const int &i, multi_node::output_ports_type &op) {
       if(i % 2)
         std::get<1>(op).try_put(i); // put to odd queue
       else
         std::get<0>(op).try_put(i); // put to even queue
     }
   };
   
   int main() {
     graph g;
   
     queue_node<int> even_queue(g);
     queue_node<int> odd_queue(g);
   
     multi_node node1(g,unlimited,MultiBody());
   
     output_port<0>(node1).register_successor(even_queue);
     make_edge(output_port<1>(node1), odd_queue);
   
     for(int i = 0; i < 1000; ++i) {
       node1.try_put(i);
     }
     g.wait_for_all();
   }


Members
-------

.. code:: cpp

   namespace tbb {
     template < typename Input, typename Output,
                typename Policy = queueing, typename Allocator=cache_aligned_allocator<Input> >
     class multifunction_node : public graph_node, public receiver<Input> {
     public:
       template < typename Body >
       multifunction_node( graph &g, size_t concurrency, Body body );
       multifunction_node( const multifunction_node &other );
       ~multifunction_node();
   
       // receiver< Input >
       typedef Input input_type;
       typedef sender<input_type> predecessor_type;
       bool try_put( const input_type &v );
       bool register_predecessor( predecessor_type &p );
       bool remove_predecessor( predecessor_type &p );
   
       typedef implementation-dependent output_ports_type;
       output_ports_type& output_ports();
     };
   }

The following table provides additional information on the members of this template class.

= ========================================================================================
\ Member, Description
==========================================================================================
\ ``template < typename Body > multifunction_node( graph &g, size_t concurrency, Body body )``
  \
  Constructs a ``multifunction_node`` with ``body`` as
  its Body. At most ``concurrency`` calls to the body may be made
  concurrently.
------------------------------------------------------------------------------------------
\ ``multifunction_node( const multifunction_node &other )``
  \
  Constructs a ``multifunction_node`` that has the same initial state
  that ``other`` had when it was constructed. The
  ``multifunction_node`` that is constructed will have a reference to
  the same ``graph`` object as ``other``, will have a
  copy of the initial ``body`` used by ``other``, and
  have the same concurrency threshold as ``other``. The predecessors
  and successors of ``other`` will not be copied.
  
  .. caution::

     The new body object is copy-constructed from a copy of the original body
     provided to ``other`` at its construction. Therefore changes made
     to member variables in ``other``'s body after the construction of
     ``other`` will not affect the body of the new
     ``multifunction_node.``
  
------------------------------------------------------------------------------------------
\ ``~multifunction_node()``
  \
  Destructor
------------------------------------------------------------------------------------------
\ ``bool try_put( const input_type &v )``
  \
  See the table above describing the behavior of try_put for a
  ``multifunction_node`` for more information.
  
  **Returns**: ``true``
------------------------------------------------------------------------------------------
\ ``bool register_predecessor( predecessor_type &p )``
  \
  Adds ``p`` to the set of predecessors.
  
  **Returns**: ``true``
------------------------------------------------------------------------------------------
\ ``bool remove_predecessor( predecessor_type &p )``
  \
  Removes ``p`` from the set of predecessors.
  
  **Returns**: ``true``
------------------------------------------------------------------------------------------
\ ``output_ports_type& output_ports();``
  \
  **Returns**: a tuple of output ports.
------------------------------------------------------------------------------------------
= ========================================================================================


See also:

* :doc:`make_edge Template Function <make_edge_func>`
* :doc:`remove_edge Template Function <remove_edge_func>`
* :doc:`copy_body Template Function <copy_body_func>`
* :doc:`Message Passing Protocol <message_passing_protocol>`
* :doc:`Sender and Buffer Policy <sender_and_buffer_policy>`
* :doc:`task_group_context <../task_scheduler/task_group_context>`
* :doc:`Exceptions <../exceptions>`
* :doc:`Lightweight policy <lightweight_policy>`
