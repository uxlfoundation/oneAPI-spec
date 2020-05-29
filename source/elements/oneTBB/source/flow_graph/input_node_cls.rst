==========
input_node
==========
**[flow_graph.input_node]**

A node that generates messages by invoking the user-provided functor and broadcasts the
result to all of its successors.

.. code:: cpp

    // Defined in header <tbb/flow_graph.h>

    namespace tbb {
    namespace flow {

        template < typename Output >
        class input_node : public graph_node, public sender<Output> {
        public:
            template< typename Body >
            input_node( graph &g, Body body );
            input_node( const input_node &src );
            ~input_node();

            void activate();
            bool try_get( Output &v );
        };

    } // namespace flow
    } // namespace tbb

Requirements:

* The ``Output`` type shall meet the `CopyConstructible` requirements from [copyconstructible] and
  `CopyAssignable`  requirements from [copyassignable] ISO C++ Standard sections.
* The type ``Body`` shall meet the :doc:`InputNodeBody requirements <../named_requirements/flow_graph/input_node_body>`.

This node can have no predecessors. It executes a user-provided ``body`` function object to
generate messages that are broadcast to all successors. It is a serial node and will never call
its ``body`` concurrently. It is able to buffer a single item.  If no successor accepts an
item that it has generated, the message is buffered and will be provided to successors
before a new item is generated.

``input_node`` is a ``graph_node`` and ``sender<Output>``.

``input_node`` has a `buffering` and `broadcast-push` :doc:`properties <forwarding_and_buffering>`.

An ``input_node`` will continue to invoke ``body`` and broadcast messages until the ``body``
toggles ``fc.stop()`` or it has no valid successors. A message may be generated and then rejected
by all successors. In that case, the message is buffered and will be the next message sent once a
successor is added to the node or ``try_get`` is called. Calls to ``try_get`` will return a
buffer message if available or will invoke ``body`` to attempt to generate a new message.
A call to ``body`` is made only when the internal buffer is empty.

The body object passed to a ``input_node`` is copied. Therefore updates to member variables will
not affect the original object used to construct the node. If the state held within a body object
must be inspected from outside of the node, the :doc:`copy_body function <copy_body_func>` can be
used to obtain an updated copy.

Member functions
----------------

.. cpp:function:: template< typename Body > input_node( graph &g, Body body )

    Constructs an ``input_node`` that will invoke ``body``. By default
    the node is created in an inactive state, that is, messages will
    not be generated until a call to ``activate`` is made.

.. cpp:function:: input_node( const input_node &src )

    Constructs an ``input_node`` that has the same initial state that
    ``src`` had when it was constructed. The ``input_node`` that is
    constructed will have a reference to the same ``graph`` object as
    ``src``, will have a copy of the initial body used by ``src,`` and
    have the same initial active state as ``src``. The predecessors and
    successors of ``src`` will not be copied.

    The new body object is copy-constructed from a copy of the original
    body provided to ``src`` at its construction. Therefore changes
    made to member variables in ``src``'s body after the construction
    of ``src`` will not affect the body of the new ``input_node.``

.. cpp:function:: void activate()

    Sets the ``input_node`` to the active state, allowing it to begin
    generating messages.

.. cpp:function:: bool try_get( Output &v )

    Will copy the buffered message into ``v`` if available or will
    invoke ``body`` to attempt to generate a new message that will be
    copied into ``v``. 

    **Returns:** ``true`` if a message is copied to v.  ``false`` otherwise.

Deduction Guides
----------------

.. code:: cpp

    template <typename Body>
    input_node(graph&, Body) -> input_node<std::decay_t<input_t<Body>>>;

Where:

* ``input_t`` is an alias to ``Body`` input argument type.
