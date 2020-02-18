=============================
composite_node Template Class
=============================


Summary
-------

A node that encapsulates a collection of other nodes as a first class graph node. The use of 
``composite_node`` requires C++11 support. On Microsoft Windows*, at least Visual
Studio 2013 is required.

Syntax
------

.. code:: cpp

   template<typename InputTuple, typename OutputTuple>
   class composite_node;
         


Header
------

.. code:: cpp

   #include "tbb/flow_graph.h"
         


Description
-----------

The ``composite_node`` can package any number of other nodes. It
maintains input and output port references to nodes in the package that border the 
``composite_node``. This allows for the references to be used to make edges to other nodes
outside of the ``composite_node``. The 
``InputTuple`` is a tuple of input types. The 
``composite_node`` has an input port for each type in 
``InputTuple``. Likewise, the ``OutputTuple`` is a tuple of
output types. The ``composite_node`` has an output port for each
type in ``OutputTuple``.

The composite_node is a multi-port node with three specializations.

* **A multi-port node with multi-input ports and multi-output ports:** This specialization has a tuple of
  input ports, each of which is a ``receiver`` of a type in
  ``InputTuple``. Each input port is a reference to a port of a
  node that the ``composite_node`` encapsulates. Similarly, this specialization also has a tuple
  of output ports, each of which is a ``sender`` of a type in
  ``OutputTuple``. Each output port is a reference to a port of a
  node that the ``composite_node`` encapsulates.
* **A multi-port node with only input ports and no output ports:** This specialization only has a tuple of
  input ports.
* **A multi-port node with only output ports and no input_ports:** This specialization only has a tuple of
  output ports.


The function template ``input_port`` can be used to get a reference
to a specific input port and the function template ``output_port``
can be used to get a reference to a specific output port.

Construction of a ``composite_node`` is done in two stages:

* Defining the ``composite_node`` with specification of ``InputTuple`` and 
  ``OutputTuple``.
* Making aliases from the encapsulated nodes that border the 
  ``composite_node`` to the input and output ports of the 
  ``composite_node``. This step is mandatory as without it the 
  ``composite_node``'s input and output ports would not have been bound to any actual nodes. Making the
  aliases is achieved by calling the method 
  ``set_external_ports``.


The composite_node is not copy-constructible.

Example
-------

.. code:: cpp

   #include "tbb/flow_graph.h"
   #include <iostream>
   #include <tuple>
   using namespace tbb::flow;
   
   class adder : public composite_node<  tuple<int, int>,  tuple<int> > {
       join_node< tuple<int,int>, queueing > j;
       function_node< tuple<int,int>, int > f;
       typedef composite_node< tuple<int,int>, tuple<int> > base_type;
   
       struct f_body {
           int operator()(const tuple<int,int> &t) {
               int n = (get<1>(t)+1)/2;
               int sum = get<0>(t) + get<1>(t);
               std::cout << "Sum of the first " << n <<" positive odd numbers is  " << n <<" squared: "  << sum << std::endl;
               return  sum;
           }
       };
   
   public:
       adder(graph &g) : base_type(g), j(g), f(g, unlimited, f_body()) {
           make_edge(j, f);
           base_type::input_ports_type input_tuple(input_port<0>(j), input_port<1>(j));
           base_type::output_ports_type output_tuple(f);
           base_type::set_external_ports(input_tuple, output_tuple);
       }
   };
   
   int main() {
       graph g;
       split_node< tuple<int, int, int, int> > s(g);
       adder a0(g);
       adder a1(g);
       adder a2(g);
   
       make_edge(output_port<0>(s), input_port<0>(a0));
       make_edge(output_port<1>(s), input_port<1>(a0));
   
       make_edge(output_port<0>(a0),input_port<0>(a1));
       make_edge(output_port<2>(s), input_port<1>(a1));
   
       make_edge(output_port<0>(a1), input_port<0>(a2));
       make_edge(output_port<3>(s), input_port<1>(a2));
   
       s.try_put(std::make_tuple(1,3,5,7));
   
       g.wait_for_all();
   
       return 0;
   }
         

This example shows the use of ``composite_node`` to encapsulate two
flow graph nodes (a ``join_node`` and a 
``function_node``). In the example the concept that the sum of the first 
``n`` positive odd numbers is the same as 
``n`` squared is demonstrated.

A class ``adder`` is defined. This class has a 
``join_node j`` with two input ports and a 
``function_node f``. ``j`` receives a number at each of its
input ports and sends a tuple of these numbers to ``f`` which adds
the numbers. To encapsulate these two nodes, the ``adder`` inherits
from a ``composite_node`` type with two input ports and one output
port to match the two input ports of ``j`` and the one output port
of ``f``.

A ``split_node s`` is created to serve as the source of the
positive odd numbers. The first four positive odd numbers 1, 3, 5 and 7 are used. Three 
``adders a0``, ``a1`` and ``a2`` are created. The first ``adder a0`` receives 1 and 3 from the ``split_node``. These are
added and the sum forwarded to ``a1``. The second 
``adder a1`` receives the sum of 1 and 3 on one input port and receives 5 on the
other input port from the ``split_node``. These are also added and
the sum forwarded to ``a2``. Likewise, the third 
``adder a2`` receives the sum of 1, 3 and 5 on one input port and receives 7 on the
other input port from the ``split_node``. Each
``adder`` reports the sum it computes which is the square of the count of numbers accumulated when
that ``adder`` is reached in the graph.
The output of running the example is as follows:

.. code:: cpp

   Sum of the first 2 positive odd numbers is  2^2: 4
   Sum of the first 3 positive odd numbers is  3^2: 9
   Sum of the first 4 positive odd numbers is  4^2: 16
         


Members
-------

.. code:: cpp

   namespace tbb {
   namespace flow {
   
       template< typename InputTuple, typename OutputTuple > class composite_node;
   
       //composite_node with both input ports and output ports
       template< typename... InputTypes, typename... OutputTypes>
       class composite_node <tbb::flow::tuple<InputTypes...>, tbb::flow::tuple<OutputTypes...> > : public graph_node {
       public:
           typedef tbb::flow::tuple< receiver<InputTypes>&... > input_ports_type;
           typedef tbb::flow::tuple< sender<OutputTypes>&... > output_ports_type;
   
           composite_node( graph &g );
           virtual ~composite_node();
   
           void set_external_ports(input_ports_type&& input_ports_tuple, output_ports_type&& output_ports_tuple);
           input_ports_type& input_ports();
           output_ports_type& output_ports();
       };
   
       //composite_node with only input ports
       template< typename... InputTypes>
       class composite_node <tbb::flow::tuple<InputTypes...>, tbb::flow::tuple<> > : public graph_node{
       public:
           typedef tbb::flow::tuple< receiver<InputTypes>&... > input_ports_type;
   
           composite_node( graph &g );
           virtual ~composite_node();
   
           void set_external_ports(input_ports_type&& input_ports_tuple);
           input_ports_type& input_ports();
       };
   
       //composite_nodes with only output_ports
       template<typename... OutputTypes>
       class composite_node <tbb::flow::tuple<>, tbb::flow::tuple<OutputTypes...> > : public graph_node{
       public:
           typedef tbb::flow::tuple< sender<OutputTypes>&... > output_ports_type;
   
           composite_node( graph &g );
           virtual ~composite_node();
   
           void set_external_ports(output_ports_type&& output_ports_tuple);
           output_ports_type& output_ports();
       };
   }
   }
         

The following table provides additional information on the members of this template class.

= ========================================================================================
\ Member, Description
==========================================================================================
\ ``composite_node( graph &g )``
  \
  Constructs a ``composite_node`` that belongs to the
  ``graph g``.
------------------------------------------------------------------------------------------
\ ``void set_external_ports(input_ports_type&& input_ports_tuple, output_ports_type&& output_ports_tuple);``
  \
  Creates input and output ports of the ``composite_node``
  as aliases to the ports referenced by ``input_ports_tuple`` and ``output_ports_tuple``
  respectively. That is, a port referenced at position 
  ``N`` in ``input_ports_tuple`` is mapped as the
  ``Nth`` input port of the 
  ``composite_node``, similarly for output ports.
------------------------------------------------------------------------------------------
\ ``input_ports_type& input_ports()``
  \
  **Returns**: A ``flow::tuple`` of 
  ``receivers``. Each element is a reference to the actual node or input
  port that was aliased to that position in 
  ``set_external_ports()``.
  
  .. caution::

     Calling input_ports() without a prior call to set_external_ports() results in undefined behavior.
  
------------------------------------------------------------------------------------------
\ ``output_ports_type& output_ports()``
  \
  **Returns**: A ``flow::tuple`` of 
  ``senders``. Each element is a reference to the actual node or output
  port that was aliased to that position in 
  ``set_external_ports()``.
  
  .. caution::

     Calling output_ports() without a prior call to set_external_ports() results in undefined behavior.
  
------------------------------------------------------------------------------------------
= ========================================================================================


See also:

* :doc:`input_port Template Class <input_port_func>`
* :doc:`output_port Template Class <output_port_func>`
