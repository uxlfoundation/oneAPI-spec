==========================================
Specifying Priorities for Functional Nodes
==========================================


Summary
-------

The feature allows setting relative priorities at construction of flow graph functional
nodes, guiding threads that execute the graph to prefer nodes with higher priority.

Syntax
------

.. code:: cpp

   namespace tbb { namespace flow {
   
   typedef unsigned int node_priority_t;
   
   const node_priority_t no_priority = node_priority_t(0);
   
   template< typename Output, typename Policy = void >
   class continue_node : public graph_node, public continue_receiver, public sender<Output> {
   public:
       template<typename Body>
       continue_node( graph &g, Body body, node_priority_t = no_priority );
       // ...
   };
   
   template < typename Input, typename Output = continue_msg,
              typename Policy = queueing,
              typename A = cache_aligned_allocator<Input> >
   class function_node : public graph_node, public receiver<Input>, public sender<Output> {
   public:
       template<typename Body>
       function_node( graph &g, size_t concurrency, Body body, node_priority_t = no_priority );
       // ...
   };
   
   template < typename Input, typename Output,
              typename Policy = queueing, typename Allocator=cache_aligned_allocator<Input> >
   class multifunction_node : public graph_node, public receiver<Input> {
   public:
       template < typename Body >
       multifunction_node( graph &g, size_t concurrency, Body body, node_priority_t = no_priority );
       // ...
   };
   
   template < typename Input, typename Output,
              typename Policy = queueing_lightweight,
              typename Allocator = cache_aligned_allocator<Input> >
   class async_node : public graph_node, public receiver<Input>, public sender<Output> {
   public:
       template <typename Body>
       async_node( graph& g, size_t concurrency, Body body, node_priority_t = no_priority );
       // ...
   };
   
   }}


Header
------

.. code:: cpp

   #define TBB_PREVIEW_FLOW_GRAPH_FEATURES 1
   #include "tbb/flow_graph.h"

.. note::

   The feature requires linkage with TBB preview binaries.


Description
-----------

With this extension the ``function_node``, the
``multifunction_node``, the ``async_node`` and the
``continue_node`` accept additional contstructor parameter of
``node_priority_t`` type, which sets the node priority in the graph: the larger
the specified value for the parameter, the higher the priority. The special constant value
``no_priority``, also the default value of the parameter, switches priority off
for a particular node.

For a particular graph, tasks to execute the nodes whose priority is specified have
precedence over tasks for the nodes with lower or no priority value set. When looking for a
task to execute, a thread will choose the one with the highest priority from those in the
graph which are available to be executed.

If a node with priority has nested parallel construct the thread that waits this parallel
contruct to complete might take tasks with no priority, but may not take another priority
task. If such behavior is undesirable, we recommend to either use isolation or specify a
priority for each node.

Execution of tasks spawned on behalf of the nodes with priority value set takes precedence
over execution of tasks whose priority is set through pre-existing priority specification
mechanism in the library.

.. caution::

   The feature does not provide strong ordering guarantees. In particular, nodes whose policy
   include ``lightweight`` can be executed without scheduling a task. Therefore,
   priority of the task spawned on behalf of the node with priority value specified may be
   ignored.


Example
-------

The following basic example demostrates prioritization of one path in the graph over the
other, which may help to improve overall performance of the graph.

.. figure:: ../Resources/critical_path_in_graph.png
   :width: 463
   :height: 336
   :align: center

   Data flow graph with critical path.

Consider executing the graph from the picture above using two threads. Let the nodes
``f1`` and ``f3`` take equal time to
execute, while the node ``f2`` takes longer. That makes the nodes
``bs``, ``f2`` and
``fe`` constitute the critical path in this graph. Due to the
non-deterministic behavior in selection of the tasks, TBB might execute nodes
``f1`` and ``f3`` in parallel first, which
would make the whole graph execution time last longer than the case when one of the threads
chooses the node ``f2`` just after the broadcast node. By setting a
higher priority on node ``f2``, threads are guided to take the
critical path task earlier, thus reducing overall execution time.

.. include:: examples/node_priorities.cpp
   :code: cpp


Output:

.. code:: cpp

   Elapsed approximately 17 units of time

If no value or the special constant ``no_priority`` is passed as an argument
then the output would be:

.. code:: cpp

   Elapsed approximately 22 units of time


See also:

* :doc:`Lightweight policy <lightweight_policy>`
