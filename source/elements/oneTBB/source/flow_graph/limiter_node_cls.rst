============
limiter_node
============
**[flow_graph.limiter_node]**

A node that counts and limits the number of messages that pass through it.

.. code:: cpp

    // Defined in header <tbb/flow_graph.h>

    namespace tbb {
    namespace flow {

        template< typename T, typename DecrementType=continue_msg >
        class limiter_node : public graph_node, public receiver<T>, public sender<T> {
        public:
            limiter_node( graph &g, size_t threshold );
            limiter_node( const limiter_node &src );

            receiver<DecrementType>& decrementer();

            bool try_put( const T &v );
            bool try_get( T &v );
        };

    } // namespace flow
    } // namespace tbb

Requirements:

* ``T`` type must meet the `DefaultConstructible` requirements from
  [defaultconstructible] ISO C++ Standard section.
* The ``DecrementType`` type must be an integral type or ``continue_msg``.

``limiter_node`` is a ``graph_node``, ``receiver<T>``, and ``sender<T>``

``limiter_node`` has a `discarding` and `broadcast-push` :doc:`properties <forwarding_and_buffering>`.

This node does not accept new messages once the user-specified ``threshold`` is
reached. The internal count of broadcasts is adjusted through use of
its embedded ``receiver`` object, and its values are truncated to be
inside the [0, ``threshold``] interval. The embedded ``receiver`` object can be
obtained by calling ``decrementer`` method.

The template parameter ``DecrementType`` specifies the type of the message that
can be sent to the embedded ``receiver`` object. This template parameter is defined to
``continue_msg`` by default. If an integral type is specified, positive values sent
to the embedded ``receiver`` port determine the value by which the internal counter of broadcasts
will be decreased, while negative values determine the value by which the internal
counter of broadcasts will be increased.

The ``continue_msg`` sent to the embedded ``receiver`` object
decreases the internal counter of broadcasts by one.

When ``try_put`` call on the embedded ``receiver`` object results in
the new value of internal counter of broadcasts to be less than the
``threshold``, the ``limiter_node`` tries to get a message from one
of its known predecessors and forward that message to all its
successors. If it cannot obtain a message from a predecessor, it decrements a counter of broadcasts.

Member functions
----------------

.. namespace:: tbb::flow::limiter_node
	       
.. cpp:function:: limiter_node( graph &g, size_t threshold )

    Constructs a ``limiter_node`` that allows up to ``threshold`` items
    to pass through before rejecting ``try_put``'s.

.. cpp:function:: limiter_node( const limiter_node &src )

    Constructs a ``limiter_node`` that has the same initial state that
    ``src`` had at its construction. The new ``limiter_node``
    belongs to the same graph ``g`` as ``src``, has the same
    ``threshold``. The list of predecessors, the list of successors,
    and the current count of broadcasts are not copied from ``src``.

.. cpp:function:: receiver<DecrementType>& decrementer()

    Obtains a reference to the embedded ``receiver`` object that is used for the
    internal counter adjustments.

.. cpp:function:: bool try_put( const T &v )

    If the broadcast count is below the threshold, ``v`` is broadcast
    to all successors.

    **Returns**: ``true`` if ``v`` is broadcast; ``false`` if ``v``
    is not broadcast because the threshold has been reached.

.. cpp:function:: bool try_get( T &v )

    **Returns**: ``false``.
