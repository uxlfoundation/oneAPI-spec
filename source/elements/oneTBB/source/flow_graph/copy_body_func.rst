===========================
copy_body Template Function
===========================


Summary
-------

A template function that returns a copy of the body function object
from a 
``continue_node``,
``function_node``,
``multifunction_node``,
or 
``source_node``.

Syntax
------

.. code:: cpp

   template< typename Body, typename Node >
   Body copy_body( Node &n );


Header
------

.. code:: cpp

   #include "tbb/flow_graph.h"


See also:

* :doc:`continue_node Template Class <continue_node_cls>`
* :doc:`function_node Template Class <func_node_cls>`
* :doc:`multifunction_node Template Class <multifunc_node_cls>`
* :doc:`source_node Template Class <source_node_cls>`
