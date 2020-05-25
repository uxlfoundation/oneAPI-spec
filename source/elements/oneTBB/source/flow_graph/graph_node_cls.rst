==========
graph_node
==========
**[flow_graph.graph_node]**

A base class for all graph nodes.

.. code:: cpp

    namespace tbb {
    namespace flow {
    
        class graph_node {
        public:
            explicit graph_node( graph &g );
            virtual ~graph_node();
        };

    } // namespace flow
    } // namespace tbb

The class ``graph_node`` is a base class for all flow graph nodes.
The virtual destructor allows flow graph nodes to be destroyed through pointers to ``graph_node``.
For example, a ``vector< graph_node * >`` could be used to hold the addresses of flow graph nodes
that will later need to be destroyed.
