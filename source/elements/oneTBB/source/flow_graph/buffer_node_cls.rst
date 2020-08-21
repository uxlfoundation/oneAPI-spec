===========
buffer_node
===========
**[flow_graph.buffer_node]**

A node that is an unbounded buffer of messages. Messages are forwarded in an arbitrary order.

.. code:: cpp

    // Defined in header <tbb/flow_graph.h>

    namespace tbb {
    namespace flow {

        template< typename T>
        class buffer_node : public graph_node, public receiver<T>, public sender<T> {
        public:
            explicit buffer_node( graph &g );
            buffer_node( const buffer_node &src );
            ~buffer_node();

            bool try_put( const T &v );
            bool try_get( T &v );
        };

    } // namespace flow
    } // namespace tbb

Requirements:

* The type ``T`` must meet the `CopyConstructible` requirements from [copyconstructible] and
  `CopyAssignable` requirements from [copyassignable] ISO C++ Standard sections.

``buffer_node`` is a ``graph_node``, ``receiver<T>``, and ``sender<T>``.

``buffer_node`` has a `buffering` and `single-push` :doc:`properties <forwarding_and_buffering>`.

``buffer_node`` forwards messages in an arbitrary order to a single successor in its successor set.

Member functions
----------------

.. cpp:function:: explicit buffer_node( graph &g )

    Constructs an empty ``buffer_node`` that belongs to the graph ``g``.

.. cpp:function:: explicit buffer_node( const buffer_node &src )

    Constructs an empty ``buffer_node``. The buffered value and list of successors is not copied
    from ``src``.

.. cpp:function:: bool try_put( const T &v )

    Adds ``v`` to the buffer. If ``v`` is the only item in the buffer, a task is also spawned to
    forward the item to a successor.

    **Returns**: ``true``

.. cpp:function:: bool try_get( T &v )

    **Returns**: ``true`` if an item can be removed from the buffer and assigned to ``v``.
    Returns ``false`` if there is no non-reserved item currently in the buffer.
