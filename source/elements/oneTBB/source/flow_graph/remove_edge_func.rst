===========
remove_edge
===========
**[flow_graph.remove_edge]**

A function template for building edges between nodes.

.. code:: cpp

    // Defined in header <tbb/flow_graph.h>

    namespace tbb {
    namespace flow {

        template<typename Message>
        inline void remove_edge( sender<Message> &p, receiver<Message> &s );

        template< typename MultiOutputNode, typename MultiInputNode >
        inline void remove_edge( MultiOutputNode& output, MultiInputNode& input );

        template<typename MultiOutputNode, typename Message>
        inline void remove_edge( MultiOutputNode& output, receiver<Message> input );

        template<typename Message, typename MultiInputNode>
        inline void remove_edge( sender<Message> output, MultiInputNode& input );

    } // namespace flow
    } // namespace tbb

Requirements:

* The `MultiOutputNode` type shall have a valid ``MultiOutputNode::output_ports_type`` qualified-id
  that denotes a type.
* The `MultiInputNode` type shall have a valid ``MultiInputNode::input_ports_type`` qualified-id
  that denotes a type.

The common form of ``remove_edge(sender, receiver)`` creates an edge between provided ``sender``
and ``receiver`` instances.

Overloads that accepts a `MultiOutputNode` type instance removes an edge from port ``0`` of a
multi-output predecessor.

Overloads that accepts a `MultiInputNode` type instance removes an edge to port ``0`` of a multi-input
successor.
