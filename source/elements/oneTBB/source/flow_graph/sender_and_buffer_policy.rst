=========================================
Fowarding, Buffering and Reception Policy
=========================================

In an oneAPI Threading Building Blocks flow::graph, nodes which
forward messages to successors have one of two possible forwarding policies, which are a
property of the node:

* **broadcast-push** - the message will be pushed to as many successors as will accept
  the message. If no successor accepts the message, the fate of the message depends on the
  output buffering policy of the node.
* **single-push** - if the message is accepted by a successor, no further push of that
  message will occur. This policy is unique to ``buffer_node``,
  ``queue_node``, ``priority_queue_node`` and
  ``sequencer_node``. If no successor accepts the message, it will be
  retained for a possible future push or pull.


There are two policies for handling a message which cannot be pushed to any successor:

* **buffering** - if no successor accepts a message, it is stored so subsequent node
  processing can use it. Nodes that buffer outputs have "yes" in the column "try_get()?"
  below.
* **discarding** - if no successor accepts a message, it is discarded and has no
  further effect on graph execution. Nodes that discard outputs have "no" in the column
  "try_get()?" below.


There are two policies for handling the reception of a message by a node:

* **accept** - the node will deal with as many messages as are pushed to it.
* **switch** - the message is not accepted, and the the state of the edge will change
  from push to pull mode.


.. note::

   Some successor nodes will accept or switch depending on whether the parallelism in the node
   is sufficient to accept, or based on the policy of the node. For example, an edge to a
   ``function_node`` with a <rejecting> policy but with unlimited
   parallelism will never switch from push to pull mode, because any message pushed to the node
   will result in a task being created to run the body of the node. If the node has limited
   parallelism and that limit is reached, then the node will switch an incoming edge from push
   to pull when the predecessor attempts to push a message.

.. note::

   Nodes that may attempt to pull from a predecessor have the Reception Policy "switch" in the
   table below.  If message loss is not desired, these nodes should have a predecessor that has
   "yes" in the column "try_get()?".

.. caution::

   The reserving ``join_node`` always reserves messages on its inputs.  The inputs
   to the reserving ``join_node`` should all support reservation ("yes" in the
   column "try_reserve()?" below.)

The following table lists the policies of each node:

.. table:: Input buffering, output buffering, reserving and forwarding policy

   ================================= ================ ========== ============== ==============================
   Node                              Reception Policy try_get()? try_reserve()? Forwarding
   ================================= ================ ========== ============== ==============================
   **Functional Nodes**
   --------------------------------- ---------------- ---------- -------------- ------------------------------
   ``source_node``                   --               yes        yes            broadcast-push
   --------------------------------- ---------------- ---------- -------------- ------------------------------
   ``function_node<rejecting>``      accept/switch    no         no             broadcast-push
   --------------------------------- ---------------- ---------- -------------- ------------------------------
   ``function_node<queueing>``       accept           no         no             broadcast-push
   --------------------------------- ---------------- ---------- -------------- ------------------------------
   ``continue_node``                 accept           no         no             broadcast-push
   --------------------------------- ---------------- ---------- -------------- ------------------------------
   ``multifunction_node<rejecting>`` accept/switch    no         no             broadcast-push
   --------------------------------- ---------------- ---------- -------------- ------------------------------
   ``multifunction_node<queueing>``  accept           no         no             broadcast-push
   --------------------------------- ---------------- ---------- -------------- ------------------------------
   **Buffering Nodes**
   --------------------------------- ---------------- ---------- -------------- ------------------------------
   ``buffer_node``                   accept           yes        yes            single-push
   --------------------------------- ---------------- ---------- -------------- ------------------------------
   ``priority_queue_node``           accept           yes        yes            single-push
   --------------------------------- ---------------- ---------- -------------- ------------------------------
   ``queue_node``                    accept           yes        yes            single-push
   --------------------------------- ---------------- ---------- -------------- ------------------------------
   ``sequencer_node``                accept           yes        yes            single-push
   --------------------------------- ---------------- ---------- -------------- ------------------------------
   ``overwrite_node``                accept           yes        yes            broadcast-push
   --------------------------------- ---------------- ---------- -------------- ------------------------------
   ``write_once_node``               accept once      yes        yes            broadcast-push
   --------------------------------- ---------------- ---------- -------------- ------------------------------
   **Split/Join Nodes**
   --------------------------------- ---------------- ---------- -------------- ------------------------------
   ``join_node<queueing>``           accept           yes        no             broadcast-push
   --------------------------------- ---------------- ---------- -------------- ------------------------------
   ``join_node<reserving>``          switch           yes        no             broadcast-push
   --------------------------------- ---------------- ---------- -------------- ------------------------------
   ``join_node<tag_matching>``       accept           yes        no             broadcast-push
   --------------------------------- ---------------- ---------- -------------- ------------------------------
   ``split_node``                    accept           no         no             broadcast-push
   --------------------------------- ---------------- ---------- -------------- ------------------------------
   ``indexer_node``                  accept           no         no             broadcast-push
   --------------------------------- ---------------- ---------- -------------- ------------------------------
   **Other Nodes**
   --------------------------------- ---------------- ---------- -------------- ------------------------------
   ``broadcast_node``                accept           no         no             broadcast-push
   --------------------------------- ---------------- ---------- -------------- ------------------------------
   ``limiter_node``                  accept/switch    no         no             broadcast-push
   ================================= ================ ========== ============== ==============================


See also:

* :doc:`Message Passing Protocol <message_passing_protocol>`
