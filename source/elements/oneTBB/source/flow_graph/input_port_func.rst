============================
input_port Template Function
============================


Summary
-------

A template function that given a 
``join_node``, ``indexer_node`` or a  
``composite_node`` returns a reference to a specific input
port.

Syntax
------

.. code:: cpp

   template<size_t N, typename NT>
   typename flow::tuple_element<N, typename NT::input_ports_type>::type&
   input_port(NT &n);


Header
------

.. code:: cpp

   #include "tbb/flow_graph.h"


See also:

* :doc:`join_node Template Class <join_node_cls>`
* :doc:`indexer_node Template Class <indexer_node_cls>`
* :doc:`composite_node Template Class <composite_node_cls>`
