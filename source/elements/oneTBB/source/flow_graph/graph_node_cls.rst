================
graph_node Class
================


Summary
-------

A base class for all graph nodes.

Syntax
------

.. code:: cpp

   class graph_node;


Header
------

.. code:: cpp

   #include "tbb/flow_graph.h"


Description
-----------

The class ``graph_node`` is a base class for all flow graph nodes.  The virtual destructor allows flow graph nodes to be destroyed through pointers to ``graph_node``.  For example, a ``vector< graph_node * >`` could be used to hold the addresses of flow graph nodes that will later need to be destroyed.

Members
-------

.. code:: cpp

   namespace tbb {
   namespace flow {
    
   class graph_node {
   public:
       explicit graph_node( graph &g );
       virtual ~graph_node() {}
   };
    
   }
   }
