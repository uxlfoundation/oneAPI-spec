=============================
output_port Template Function
=============================


Summary
-------

A template function that given a ``split_node``, ``multifunction_node`` or ``composite_node`` returns a reference to a specific output port.

Syntax
------

.. code:: cpp

   template<size_t N, typename NT>
   typename flow::tuple_element<N, typename NT::output_ports_type>::type&
   output_port(NT &n);
           


Header
------

.. code:: cpp

   #include "tbb/flow_graph.h"


See also:

* :doc:`split_node Template Class <split_node_cls>`
* :doc:`multifunction_node Template Class <multifunc_node_cls>`
* :doc:`composite_node Template Class <composite_node_cls>`
