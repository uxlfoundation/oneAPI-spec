=========================
async_node Template Class
=========================


Summary
-------

A template class that is a ``graph_node``,
``receiver<Input>`` and a ``sender<Output>``. It
executes a user-provided body on incoming messages. The body submits input messages to an
external activity for processing outside of the TBB thread pool. This node also
provides ``gateway_type`` interface that allows the external activity to
communicate with the flow graph.

Syntax
------

.. code:: cpp

   template < typename Input,
              typename Output,
              typename Policy = queueing_lightweight,
              typename Allocator=cache_aligned_allocator<Input> >
   class async_node;


Header
------

.. code:: cpp

   #include "tbb/flow_graph.h"


Description
-----------

An ``async_node`` allows a flow graph to communicate with an external activity
managed by the user or another runtime. This node receives messages of type
``Input`` and invokes the body to submit a message to the external activity. To
return a result back and push it to the output port of async_node, the
``gateway_type`` is provided.

An ``async_node`` has a user-settable concurrency limit.  It can have
``flow::unlimited`` concurrency, which allows an unlimited number of invocations of
the body to execute concurrently. It can have ``flow::serial`` concurrency,
which allows only a single call of body to execute concurrently. The user can also provide a
value of type ``size_t`` to limit concurrency to a value between 1 and
``unlimited``.

By default, ``async_node`` has ``lightweight`` semantics.
See description of ``lightweight`` policy for more details.

The Body concept for ``async_node`` is shown below.

= ========================================================================================
\ async_node Body Concept: Pseudo-Signature, Semantics
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
  Assignment.
------------------------------------------------------------------------------------------
\ ``void B::operator()( const input_type &v, gateway_type &gateway )``
  \
  The input value ``v`` is submitted by the flow graph to an external activity. The
  ``gateway`` interface allows the external activity to communicate
  with the enclosing flow graph.
------------------------------------------------------------------------------------------
= ========================================================================================

.. caution::

   The body object passed to an ``async_node`` is copied. Therefore updates to
   member variables will not affect the original object used to construct the node. If the
   state held within a body object must be inspected from outside of the node, the
   ``copy_body`` function can be used to obtain an updated copy.

.. note::

   The body object may throw an exception or cancel its enclosing graph. See
   ``task_group_context`` and Exceptions sections for a description.

The ``gateway_type`` interface is shown below.

= ========================================================================================
\ gateway_type Interface: Pseudo-Signature, Semantics
==========================================================================================
\ ``bool try_put( const output_type &v )``
  \
  Broadcasts ``v`` to all successors of an
  ``async_node``.
------------------------------------------------------------------------------------------
\ ``void reserve_wait()``
  \
  Notifies a flow graph that work has been submitted to an external activity.
------------------------------------------------------------------------------------------
\ ``void release_wait()``
  \
  Notifies a flow graph that work submitted to an external activity has completed.
------------------------------------------------------------------------------------------
= ========================================================================================

.. note::

   There is no requirement to call ``gateway_type::reserve_wait()``
   method for each input message submitted to an external activity. The only requirement is that
   each call to ``gateway_type::reserve_wait()`` must have a corresponding
   call to ``gateway_type::release_wait()``.
   
   ``graph::wait_for_all()`` will not exit while there are some reserve_wait()
   calls without matching ``release_wait()``’s.


Example
-------

The example below shows an ``async_node`` that submits some work to
``AsyncActivity`` for processing by a user thread.

.. code:: cpp

   #include "tbb/flow_graph.h"
   #include "tbb/concurrent_queue.h"
   #include <thread>
   
   using namespace tbb::flow;
   typedef int input_type;
   typedef int output_type;
   typedef tbb::flow::async_node<input_type, output_type> async_node_type;
   
   class AsyncActivity {
   public:
       typedef async_node_type::gateway_type gateway_type;
   
       struct work_type {
           input_type input;
           gateway_type* gateway;
       };
   
       AsyncActivity() : service_thread( [this]() {
           while( !end_of_work() ) {
               work_type w;
               while( my_work_queue.try_pop(w) ) {
                   output_type result = do_work( w.input );
                   //send the result back to the graph
                   w.gateway->try_put( result );
                   // signal that work is done
                   w.gateway->release_wait();
               }
           }
       } ) {}
   
       void submit( input_type i, gateway_type* gateway ) {
           work_type w = {i, gateway};
           gateway->reserve_wait();
           my_work_queue.push(w);
       }
   private:
       bool end_of_work() {
           // indicates that the thread should exit
       }
   
       output_type do_work( input_type& v ) {
           // performs the work on input converting it to output
       }
   
       tbb::concurrent_queue<work_type> my_work_queue;
       std::thread service_thread;
   };
   
   int main() {
       AsyncActivity async_activity;
       tbb::flow::graph g;
   
       async_node_type async_consumer( g, unlimited,
       // user functor to initiate async processing
       [&] ( input_type input, async_node_type::gateway_type& gateway ) {
       async_activity.submit( input, &gateway );
       } );
   
       tbb::flow::source_node<input_type> s( g, [](input_type& v)->bool { /* produce data for async work */ } );
       tbb::flow::async_node<output_type> f( g, unlimited, [](const output_type& v) { /* consume data from async work */ } );
   
       tbb::flow::make_edge( s, async_consumer );
       tbb::flow::make_edge( async_consumer, f );
   
       g.wait_for_all();
   }


Members
-------

.. code:: cpp

   namespace tbb {
       namespace flow {
   
           template < typename Input, typename Output,
                      typename Policy = queueing_lightweight,
                      typename Allocator = cache_aligned_allocator<Input> >
           class async_node : public graph_node, public receiver<Input>, public sender<Output> {
           public:
               template <typename Body>
               async_node( graph& g, size_t concurrency, Body body );
               async_node( const async_node& src );
   
               typedef implementation-defined gateway_type;
               gateway_type& gateway();
   
               // receiver<Input>
               typedef Input input_type;
               typedef sender<input_type> predecessor_type;
               bool try_put( const input_type& v );
               bool register_predecessor( predecessor_type& p );
               bool remove_predecessor( predecessor_type& p );
   
               // sender<Output>
               typedef Output output_type;
               typedef receiver<output_type> successor_type;
               bool register_successor( successor_type& r );
               bool remove_successor( successor_type& r );
               bool try_get( output_type& v );
               bool try_reserve( output_type& v );
               bool try_release();
               bool try_consume();
           };
   
       }
   }

The following table provides additional information on the members of this template class.

= ========================================================================================
\ Member, Description
==========================================================================================
\ ``template<typename Body> async_node(graph& g, size_t concurrency, Body body)``
  \
  Constructs an ``async_node`` that will invoke a copy of
  ``body``. At most ``concurrency`` calls to body may be
  made concurrently.
------------------------------------------------------------------------------------------
\ ``async_node( const async_node& src )``
  \
  Constructs an ``async_node`` that has the same initial state that
  ``src`` had when it was constructed. The ``async_node``
  that is constructed will have a reference to the same graph object as
  ``src``, will have a copy of the initial body used by
  ``src``, and have the same concurrency threshold as ``src``.
  The predecessors and successors of ``src`` will not be copied.
  
  .. caution::

     The new body object is copy-constructed from a copy of the original body
     provided to ``src`` at its construction. Therefore changes made
     to member variables in ``src``'s body after the construction of
     ``src`` will not affect the body of the new
     ``async_node``.
  
------------------------------------------------------------------------------------------
\ ``gateway_type& gateway()``
  \
  Returns reference to ``gateway_type`` interface.
------------------------------------------------------------------------------------------
\ ``bool try_put( const input_type& v )``
  \
  A task is spawned that executes the ``body(v)``.
  
  **Returns**: always returns ``true``, it is responsibility of
  ``body`` to be able to pass ``v`` to an external activity.
  If a message is not properly processed by the ``body`` it will be
  lost.
------------------------------------------------------------------------------------------
\ ``bool try_get( output_type& v )``
  \
  An ``async_node`` does not contain buffering of its output. Therefore
  it always rejects ``try_get`` calls.
  
  **Returns**: false
------------------------------------------------------------------------------------------
\ ``bool try_reserve( output_type& v )``
  \
  An ``async_node`` does not contain buffering of its output. Therefore
  it cannot be reserved.
  
  **Returns**: false
------------------------------------------------------------------------------------------
\ ``bool try_release()``
  \
  An ``async_node`` does not contain buffering of its output. Therefore
  it cannot be reserved.
  
  **Returns**: false
------------------------------------------------------------------------------------------
\ ``bool try_consume()``
  \
  An ``async_node`` does not contain buffering of its output. Therefore
  it cannot be reserved.
  
  **Returns**: false
------------------------------------------------------------------------------------------
= ========================================================================================


See also:

* :doc:`Lightweight policy <lightweight_policy>`
