==========
async_node
==========
**[flow_graph.async_node]**

A node that enables communication between a flow graph and an external activity managed by
the user or another runtime.

.. code:: cpp

    // Defined in header <tbb/flow_graph.h>

    namespace tbb {
    namespace flow {

        template < typename Input, typename Output, typename Policy = /*implemetation-defined*/ >
        class async_node : public graph_node, public receiver<Input>, public sender<Output> {
        public:
            template<typename Body>
            async_node( graph &g, size_t concurrency, Body body, Policy /*unspecified*/ = Policy(),
                        node_priority_t priority = no_priority );
            template<typename Body>
            async_node( graph &g, size_t concurrency, Body body, node_priority_t priority = no_priority );

            async_node( const async_node& src );
            ~async_node();

            using gateway_type = /*implementation-defined*/;
            gateway_type& gateway();

            bool try_put( const input_type& v );
            bool try_get( output_type& v );
        };

    } // namespace flow
    } // namespace tbb

Requirements:

* The ``Input`` and ``Output`` types must meet the `CopyConstructible` requirements from
  [copyconstructible] and `CopyAssignable` requirements from [copyassignable] ISO C++ Standard sections.
* The type ``Policy`` can be specified as :doc:`lightweight, queueing and rejecting policies<functional_node_policies>` or defaulted.
* The type ``Body`` must meet the :doc:`AsyncNodeBody requirements <../named_requirements/flow_graph/async_node_body>`.

``async_node`` executes a user-provided body on incoming messages. The body submits input
messages to an external activity for processing outside of the task scheduler.
This node also provides the ``gateway_type`` interface that allows the external activity to
communicate with the flow graph.

``async_node`` is a ``graph_node``, ``receiver<Input>``, and a ``sender<Output>``.

``async_node`` has a `discarding` and `broadcast-push` :doc:`properties <forwarding_and_buffering>`.

``async_node`` has a user-settable concurrency limit, which can be set to one of :doc:`predefined values <predefined_concurrency_limits>`.
The user can also provide a value of type ``std::size_t`` to limit concurrency to a value between 1 and
:doc:`tbb::flow::unlimited <predefined_concurrency_limits>`.

The body object passed to a ``async_node`` is copied. Updates to member variables do not affect the original object used to construct the node. 
If the state held within a body object must be inspected from outside of the node, 
the :doc:`copy_body <copy_body_func>` function can be used to obtain an updated copy.

Member functions
----------------

``gateway_type`` meets the :doc:`GatewayType requirements <../named_requirements/flow_graph/gateway_type>`.

Member functions
----------------

.. code:: cpp

    template<typename Body>
    async_node( graph &g, size_t concurrency, Body body,
                   node_priority_t priority = no_priority );

Constructs an ``async_node`` that invokes a copy of ``body``. The ``concurrency`` value limits the number of simultaneous 
``body`` invocations for the node.

This function specifies :doc:`node priority<node_priorities>`.

----------------------------------------------------------------

.. code:: cpp

    template<typename Body>
    async_node( graph &g, size_t concurrency, Body body, Policy /*unspecified*/ = Policy(),
                   node_priority_t priority = no_priority );

Constructs a ``async_node`` that invokes a copy of ``body``. Most ``concurrency`` calls
to ``body`` can be made concurrently.

This function specifies a :doc:`policy<functional_node_policies>` and :doc:`node priority<node_priorities>`.

----------------------------------------------------------------

.. code:: cpp

    async_node( const async_node &src )

Constructs an ``async_node`` that has the same initial state that ``src`` had when it was
constructed. The ``async_node`` that is constructed has a reference to the same ``graph``
object as ``src``, has a copy of the initial body used by ``src``, and has the same
concurrency threshold as ``src``. The predecessors and successors of ``src`` are not copied.

The new body object is copy-constructed from a copy of the original body provided to ``src`` at
its construction. Changes made to member variables in ``src``'s body after the
construction of ``src`` do not affect the body of the new ``async_node.``

----------------------------------------------------------------

.. code:: cpp

    gateway_type& gateway()

Returns reference to the ``gateway_type`` interface.

----------------------------------------------------------------

.. code:: cpp

    bool try_put( const input_type& v )

Spawns a task that executes the ``body(v)``.

**Returns**: always returns ``true``, it is responsibility of ``body`` to be able to pass
``v`` to an external activity. If a message is not properly processed by the ``body`` it will be
lost.

----------------------------------------------------------------

.. code:: cpp

    bool try_get( output_type& v )

**Returns**: false

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

        tbb::flow::input_node<input_type> s( g, [](input_type& v)->bool { /* produce data for async work */ } );
        tbb::flow::async_node<output_type> f( g, unlimited, [](const output_type& v) { /* consume data from async work */ } );

        tbb::flow::make_edge( s, async_consumer );
        tbb::flow::make_edge( async_consumer, f );

        s.activiate();
        g.wait_for_all();
    }
