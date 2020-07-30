===================
priority_queue_node
===================
**[flow_graph.priority_queue_node]**

A class template that forwards messages in a priority order by maintaining a buffer of messages.

.. code:: cpp

    // Defined in header <tbb/flow_graph.h>

    namespace tbb {
    namespace flow {

        template< typename T, typename Compare = std::less<T>>
        class priority_queue_node : public graph_node, public receiver<T>, public sender<T> {
        public:
            typedef size_t size_type;
            explicit priority_queue_node( graph &g );
            priority_queue_node( const priority_queue_node &src );
            ~priority_queue_node();

            bool try_put( const T &v );
            bool try_get( T &v );
        };

    } // namespace flow
    } // namespace tbb

Requirements:

* The type ``T`` must meet the `CopyConstructible` requirements from [copyconstructible] and
  `CopyAssignable` requirements from [copyassignable] ISO C++ Standard sections.
* The type ``Compare`` must meet the `Compare` type requirements from [alg.sorting] ISO C++
  Standard section. If ``Compare`` instance throws an exception, then behavior is undefined.

The next message to be forwarded has the largest priority as determined by the ``Compare`` template argument.

``priority_queue_node`` is a ``graph_node``, ``receiver<T>``, and ``sender<T>``.

``priority_queue_node`` has a `buffering` and `single-push` :doc:`properties <forwarding_and_buffering>`.

Member functions
----------------

.. cpp:function:: explicit priority_queue_node( graph &g )

    Constructs an empty ``priority_queue_node`` that belongs to the  graph ``g``.

.. cpp:function:: priority_queue_node( const priority_queue_node &src )

    Constructs an empty ``priority_queue_node`` that belongs to the same graph ``g`` as 
    ``src``. The list of predecessors, the list of successors, and the messages in the buffer are not
    copied.

.. cpp:function:: bool try_put( const T &v )

    Adds ``v`` to the ``priority_queue_node``. If priority of ``v`` is the largest of all of the
    currently buffered messages, a task is spawned to forward the item to a successor.

    **Returns**: ``true``

.. cpp:function:: bool try_put( T &v )

    **Returns**: ``true`` if a message is available in the node and the node is not currently reserved.
    Otherwise, returns ``false``. If the node returns ``true``, the message with the largest
    priority is copied to ``v``.

Example
-------

Usage scenario is similar to :doc:`sequencer_node <sequencer_node_cls>` except that the
``priority_queue_node`` provides local order, passing the message with highest priority of all
stored at the moment, while ``sequencer_node`` enforces global order and does not allow a
"smaller priority" message to pass through before all preceding messages.
