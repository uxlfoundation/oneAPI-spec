===================
Abstract Interfaces
===================

In order to be used as a graph node type, a class needs to inherit certain abstract types and implement the
corresponding interfaces. ``graph_node`` is the base class for any other node type; its interfaces
always have to be implemented. If a node sends messages to other nodes, it has to implement the ``sender``
interface, while with ``receiver`` interface the node may accept messages. For nodes that have multiple
inputs and/or outputs, each input port is a ``receiver`` and each output port is a ``sender``.

.. toctree::

   graph_node_cls.rst
