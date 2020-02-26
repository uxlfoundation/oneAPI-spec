========================
Message Passing Protocol
========================

In an oneAPI Threading Building Blocks flow graph, edges dynamically switch between a push and
pull protocol for passing messages. An TBB flow graph G = ( V, S, L ),
where V is the set of nodes, S is the set of edges that are currently using a
push protocol, and L is the set of edges that are currently using a pull
protocol. For each edge (Vi, Vj), Vi is the predecessor / sender and Vj is the
successor / receiver. When in the push set S, messages over an edge are
initiated by the sender, which tries to 
*put* to the receiver. When in the pull set, messages are initiated
by the receiver, which tries to 
*get* from the sender.

If a message attempt across an edge fails, the edge is moved to the
other set. For example, if a put across the edge (Vi, Vj) fails, the edge is
removed from the push set S and placed in the pull set L. This dynamic
push/pull protocol is the key to performance in a non-preemptive tasking
library such as TBB, where simply repeating failed sends or receives is
not an efficient option. The following graphic summarizes this dynamic
protocol.

.. figure:: ../Resources/flow-graph.jpg
   :width: 442
   :height: 196
   :align: center

   The dynamic push / pull protocol.

.. caution::

   Certain graph nodes will discard messages if no successor accepts a push.  Attaching
   these nodes to a successor that may reject a push may result in the loss of messages.
   For example, if a ``function_node````f1`` is
   attached to a rejecting serial ``function_node````f2``, and
   if ``f2`` is active, a message pushed by ``f1`` to 
   ``f2`` will be rejected, and because ``f1`` does not buffer,
   it will be discarded.
   
   Nodes that will not drop messages are those that accept try_get().  See the list of
   nodes in the section Forward, Buffering and Reception Policy.


See also:

* :doc:`Forwarding, Buffering and Reception Policy <sender_and_buffer_policy>`
