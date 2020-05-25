==========
queue_node
==========
**[flow_graph.queue_node]**

A node that forwards messages in first-in first-out (FIFO) order by maintaining a buffer of messages.

.. code:: cpp

    // Defined in header <tbb/flow_graph.h>

    namespace tbb {
    namespace flow {

        template <typename T >
        class queue_node : public graph_node, public receiver<T>, public sender<T> {
        public:
            explicit queue_node( graph &g );
            queue_node( const queue_node &src );
            ~queue_node();

            bool try_put( const T &v );
            bool try_get( T &v );
        };

    } // namespace flow
    } // namespace tbb

Requirements:

* The type ``T`` shall meet the `CopyConstructible` requirements from [copyconstructible] and
  `CopyAssignable`  requirements from [copyassignable] ISO C++ Standard sections.

``queue_node`` forwards messages in first-in first-out (FIFO) order to a single successor in
its successor set.

``queue_node`` is a ``graph_node``, ``receiver`` and ``sender``.

``queue_node`` has a `buffering` and `single-push` :doc:`properties <forwarding_and_buffering>`.

Member functions
----------------

.. cpp:function:: explicit queue_node( graph &g )

    Constructs an empty ``queue_node`` that belongs to the  graph ``g``.

.. cpp:function:: queue_node( const queue_node &src )

    Constructs an empty  ``queue_node`` that belongs to the same graph ``g`` as ``src``.
    The list of predecessors, the list of successors and the messages in the buffer are not copied.

.. cpp:function:: bool try_put( const T &v )

    Add item to internal FIFO buffer. If ``v`` is the only item in the ``queue_node`` , a task is
    spawned to forward the item to a successor.

    **Returns**: ``true``.

.. cpp:function:: bool try_get( T &v )

    **Returns**: ``true`` if an item can be removed from the front of the ``queue_node`` and
    assigned to ``v``. Returns ``false`` if there is no item currently in the ``queue_node`` or
    if the node is reserved.

Example
-------

Usage scenario is similar to :doc:`buffer_node <buffer_node_cls>` except that messages are passed
in first-in first-out (FIFO) order.
