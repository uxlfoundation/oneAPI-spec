========
Overview
========

In addition to loop parallelism, the oneAPI Threading Building Blocks 
library also supports graph parallelism. It's possible to create graphs that are highly scalable,
but it is also possible to create graphs that are completely sequential.

There are 3 types of components used to implement a graph:

* A ``graph`` object
* Nodes
* Edges

Nodes invoke user-provided function objects or manage messages flow to/from
other nodes. There are pre-defined nodes that buffer, filter,
broadcast or order items as they flow through the graph.

Edges are the connections between the nodes, managed by calls to the 
``make_edge`` and ``remove_edge`` functions.

The ``graph`` object is the owner of the tasks created on
behalf of the flow graph. Users can wait on the
``graph`` if they need to wait for the completion of all
of the tasks related to the flow graph execution. One can also register
external interactions with the
``graph`` and run tasks under the ownership of the flow
graph.

.. note::

   The tasks related to the flow graph are executed in the ``task_group_context``
   of that flow graph.  If no context is specified when a flow graph is created, a
   new context is created and bound to the enclosing context.
   
   The context a body of a flow graph node is executed in is that node's graph.
   If a cancellation or exception occurs in that node, the context of its
   graph is cancelled, and if necessary the exception thrown is passed to
   the enclosing context for further processing.

.. toctree::

   dependency_flow_graph_example.rst
   message_flow_graph_example.rst
   body_objects.rst
   message_passing_protocol.rst
   sender_and_buffer_policy.rst
   lightweight_policy.rst
   node_priorities.rst
