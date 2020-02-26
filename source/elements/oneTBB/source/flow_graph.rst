==========
Flow Graph
==========

There are some applications that best express dependencies as messages
passed between nodes in a flow graph. These messages may contain data or simply
act as signals that a predecessor has completed. The ``graph`` class and its
associated node classes can be used to express such applications. All
graph-related classes and functions are in the ``tbb::flow`` namespace.

.. toctree::

   flow_graph/overview.rst
   flow_graph/graph_cls.rst
   flow_graph/abstract_interfaces.rst
   flow_graph/special_message_types.rst
   flow_graph/functional_nodes.rst
   flow_graph/buffering_nodes.rst
   flow_graph/service_nodes.rst
   flow_graph/ports_and_edges.rst
