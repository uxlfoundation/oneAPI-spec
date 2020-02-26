===========
graph Class
===========


Summary
-------

Class that serves as a handle to a flow graph of nodes and edges.

Syntax
------

.. code:: cpp

   class graph;


Header
------

.. code:: cpp

   #include "tbb/flow_graph.h"


Description
-----------

A 
``graph`` object contains a root task that is the parent
of all tasks created on behalf of the flow graph and its nodes. It provides
methods that can be used to access the root task, to wait for the children of
the root task to complete, to explicitly increment or decrement the root task's
reference count, and to run a task as a child of the root task.

.. caution::

   Destruction of flow graph nodes before calling 
   ``wait_for_all`` on their associated 
   ``graph`` object has undefined behavior and can lead
   to program failure.

.. caution::

   The flow graph now uses spawned tasks instead of enqueued tasks.  In some limited
   cases, when no worker threads are available, progress will not be made on 
   graph-related tasks until a call is made to ``wait_for_all``.  
   To avoid the need for explicit calls to ``wait_for_all``, the
   task enqueuing implementation of the flow graph can still be used.  However, 
   the task enqueuing implementation of the flow graph has been deprecated and 
   its use is discouraged.

.. caution::

   If a 
   ``graph`` is cancelled or if an exception is thrown
   during its execution, the graph objects may be in an inconsistent state after
   the 
   ``wait_for_all()``. If the user wishes to execute the 
   ``graph`` again, the 
   ``reset()`` method must be called to reset the graph edges to their
   initial state.


Members
-------

.. code:: cpp

   namespace tbb {
   namespace flow {
   
   // optional flags to reset() method
   enum reset_flags {
       rf_reset_protocol,
       rf_reset_bodies,  // delete the current node body, reset to a copy of the initial node body.
       rf_clear_edges     // delete all the edges so the user can recreate the graph
   };
   
   class graph {
   public:
   
       graph();
       graph(task_group_context& context);
       ~graph();
    
       void increment_wait_count();
       void decrement_wait_count();
    
       template< typename Receiver, typename Body >
       void run( Receiver &r, Body body );
       template< typename Body >
       void run( Body body );
       void wait_for_all();
       task *root_task();
    
       bool is_cancelled();
       bool exception_thrown();
       void reset(reset_flags f = rf_reset_protocol);
   };
    
   }
   }

The following table provides additional information on the
members of this class.

= ========================================================================================
\ Member, Description
==========================================================================================
\ ``graph([task_group_context& group] )``
  \
  Constructs a graph with no nodes. If 
  ``group`` is specified the graph tasks are
  executed in this group. By default the graph is executed in a bound context of
  its own. Instantiates a root task of class 
  ``empty_task`` to serve as a parent for all of
  the tasks generated during runs of the graph. Sets 
  ``ref_count`` of the root task to 1.
------------------------------------------------------------------------------------------
\ ``~graph()``
  \
  Calls 
  ``wait_for_all`` on the graph, then destroys
  the root task.
------------------------------------------------------------------------------------------
\ ``void increment_wait_count()``
  \
  Used to register that an external entity may still interact
  with the graph.
  
  Increments the 
  ``ref_count`` of the root task.
------------------------------------------------------------------------------------------
\ ``void decrement_wait_count()``
  \
  Used to unregister an external entity that may have
  interacted with the graph.
  
  Decrements the 
  ``ref_count`` of the root task.
------------------------------------------------------------------------------------------
\ ``template< typename Receiver, typename Body > void run( Receiver &r, Body body )``
  \
  Use this method to spawn a task that runs a body and puts
  its output to a specific receiver. The task is created as a child of the
  graph's root task and therefore 
  ``wait_for_all`` will not return until this
  task completes.
  
  Enqueues a task that invokes 
  ``r.try_````put(````body() )``. It does not wait for the task to
  complete. The spawned task is a child of the root task.
------------------------------------------------------------------------------------------
\ ``template< typename Body > void run( Body body )``
  \
  This method spawns a task that runs as a child of the
  graph's root task. Calls to 
  ``wait_for_all`` will not return until this
  spawned task completes.
  
  Enqueues a task that invokes 
  ``body(````)``. It does not
  wait for the task to complete.
------------------------------------------------------------------------------------------
\ ``void wait_for_all()``
  \
  Blocks until all tasks associated with the root task have
  completed and the number of 
  ``decrement_wait_count`` calls equals the
  number of 
  ``increment_wait_count`` calls. Because it
  calls 
  ``wait_for_all`` on the root graph task, the
  calling thread may participate in work-stealing while it is blocked.
------------------------------------------------------------------------------------------
\ ``task *root_task()``
  \
  **Returns**: a pointer to the root task of the flow
  graph.
------------------------------------------------------------------------------------------
\ ``bool is_cancelled()``
  \
  **Returns**: 
  ``true`` if the graph was cancelled during the
  last call to 
  ``wait_for_all``(), 
  ``false`` otherwise.
  
  See 
  ``task_group_context`` for a description of
  cancellation.
------------------------------------------------------------------------------------------
\ ``bool exception_thrown()``
  \
  **Returns**: 
  ``true`` if during the last call to 
  ``wait_for_all``() an exception was thrown, 
  ``false`` otherwise.
  
  See Section "Exceptions" for information on exception
  handling.
------------------------------------------------------------------------------------------
\ ``void reset(reset_flags f = rf_reset_protocol)``
  \
  Flags to ``reset()`` can be combined with
  bitwise-``or``.
  
  See 
  ``task_group_context`` for a description of
  cancellation. See Section "Exceptions" for information on exception handling.
------------------------------------------------------------------------------------------
= ========================================================================================

Optional flags for reset()

= ========================================================================================
\ Flag, Description
==========================================================================================
\ ``rf_reset_protocol``
  \
  All edges are switched to push state, all buffers
  are emptied, internal state of nodes reinitialized.  
  All calls to ``reset()`` perform
  these actions.
------------------------------------------------------------------------------------------
\ ``rf_reset_bodies``
  \
  When nodes with bodies are created, the body specified in the constructor
  is copied and preserved.  When
  ``rf_reset_bodies``
  is specified, the current body of the node is deleted and replaced
  with a copy of the body saved during construction.
  
  .. caution::

     If the body contains state which has an external component (such
     as a file descriptor) then the node may not behave the same on
     re-execution of the graph after body replacement.  In this case
     the node should be re-created.
  
------------------------------------------------------------------------------------------
\ ``rf_clear_edges``
  \
  All edges are removed from the graph.
------------------------------------------------------------------------------------------
= ========================================================================================


See also:

* :doc:`task_group_context <../task_scheduler/task_group_context>`
* :doc:`Exceptions <../exceptions>`
