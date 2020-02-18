===============
Synchronization
===============

Spawning a task 
*t* either causes the calling thread to invoke 
*t*.``execute()``, or causes ``t`` to be put into the ready pool. Any thread participating in task
scheduling may then acquire the task and invoke 
*t*.``execute()``. Section Scheduling Algorithm
describes the structure of the ready pool.

The calls that spawn come in two forms:

* Spawn a single 
  ``task``.
* Spawn multiple 
  ``task`` objects specified by a 
  ``task_list`` and clear 
  ``task_list``.

Some calls distinguish between spawning root tasks
and non-root tasks. A root task is one that was created using method 
``allocate_root``.

.. note::

   A 
   ``task`` should not spawn any predecessor task until it
   has called method 
   ``set_ref_count`` to indicate both the number of
   predecessors and whether it intends to use one of the "wait_for_all" methods.

The following table provides additional information on the
members of this template class.

= ========================================================================================
\ Member, Description
==========================================================================================
\ ``void set_ref_count( int count )``
  \
  **Requirements**: *count>=0*. If the
  intent is to subsequently spawn 
  *n* predecessors and wait, then 
  *count* should be 
  *n+1*. Otherwise count should be 
  *n*.
  
  **Effects**: Sets the 
  *refcount* attribute to 
  ``count``.
------------------------------------------------------------------------------------------
\ ``int add_ref_count( int count )``
  \
  Atomically adds ``count`` to 
  *refcount* attribute.
  
  **Returns**: New value of *refcount*
  attribute.
------------------------------------------------------------------------------------------
\ ``void increment_ref_count();``
  \
  Atomically increments 
  *refcount* attribute.
------------------------------------------------------------------------------------------
\ ``int decrement_ref_count();``
  \
  Atomically decrements 
  *refcount* attribute.
  
  **Returns**: New value of *refcount*
  attribute.
  
  .. note::

     Explicit use of 
     ``add_ref_count``, ``increment_ref_count``, and 
     ``decrement_ref_count`` are typically necessary
     only when a task has more than one immediate successor task. Section "General
     Acyclic Graphs of Tasks" of the Tutorial explains more.
  
------------------------------------------------------------------------------------------
\ ``void wait_for_all()``
  \
  **Requirements**: 
  ``refcount=n+1``, where 
  *n* is the number of predecessors that are still
  running.
  
  **Effects**: Executes tasks in ready
  pool until 
  *refcount* is 1. Afterwards, leaves 
  *refcount=1* if the task's 
  ``task_group_context`` specifies 
  ``concurrent_wait``, otherwise sets *refcount* to
  0. The figure below summarizes the state transitions.
  
  Also, 
  ``wait_for_all()``automatically resets the
  cancellation state of the 
  ``task_group_context`` implicitly associated
  with the task , when all of the following conditions hold:
  
  * The task was allocated without
    specifying a context.
  * The calling thread is a user-created
    thread, not an oneAPI Threading Building Blocks worker thread.
  * It is the outermost call to 
    ``wait_for_all()`` by the thread.
  
  .. tip::

     Under such conditions there is no way to know afterwards
     if the 
     ``task_group_context`` was cancelled. Use an
     explicit 
     ``task_group_context`` if you need to know.
  
  .. figure:: ../../Resources/0600000D.png

     Effect of wait_for_all

  k=0 by default
  
  k=1 if corresponding 
  ``task_group_context`` specifies 
  ``concurrent_wait``
------------------------------------------------------------------------------------------
\ ``static void spawn( task& t )``
  \
  Puts task 
  *t* into the ready pool and immediately returns.
  
  If the 
  *successor* of 
  ``t`` is not null, then 
  ``set_ref_count`` must be called on that 
  *successor* before spawning any child tasks, because
  once the child tasks commence, their completion will cause 
  *successor*.*refcount* to be decremented
  asynchronously. The debug version of the library often detects when a required
  call to 
  ``set_ref_count`` is not made, or is made too
  late.
------------------------------------------------------------------------------------------
\ ``static void spawn ( task_list& list )``
  \
  Equivalent to executing spawn on each
  task in 
  *list* and clearing 
  *list*, but may be more efficient. If 
  *list* is empty, there is no effect.
  
  .. note::

     Spawning a long linear list of tasks
     can introduce a bottleneck, because tasks are stolen individually. Instead,
     consider using a recursive pattern or a parallel loop template to create many
     pieces of independent work.
  
------------------------------------------------------------------------------------------
\ ``void spawn_and_wait_for_all( task& t )``
  \
  **Requirements**: Any other
  predecessors of 
  ``this`` must already be spawned. The 
  ``task``*t* must have a non-null attribute 
  *successor*. There must be a chain of 
  *successor* links from 
  *t* to the calling 
  ``task``. Typically, this chain contains a
  single link. That is, 
  *t* is typically an immediate predecessor of 
  ``this``.
  
  **Effects**: Similar to 
  ``{spawn(t); wait_for_all();}``, but
  often more efficient. Furthermore, it guarantees that 
  *task* is executed by the current thread. This
  constraint can sometimes simplify synchronization. The figure below illustrates
  the state transitions. It is similar to the figure above, with task 
  *t* being the 
  *n*\ :sup:`th` task.
  
  .. figure:: ../../Resources/0600000E.png

     Effect of spawn_and_wait_for_all

  k=0 by default
  
  k=1 if corresponding 
  ``task_group_context`` specifies 
  ``concurrent_wait``
------------------------------------------------------------------------------------------
\ ``void spawn_and_wait_for_all( task_list& list )``
  \
  Similar to 
  ``{spawn(list); wait_for_all();}``, but
  often more efficient.
------------------------------------------------------------------------------------------
\ ``static void spawn_root_and_wait( task& root )``
  \
  **Requirements**: The memory for task 
  *root* was allocated by 
  ``task::allocate_root()``.
  
  **Effects**: Sets 
  *parent* attribute of 
  *root* to an undefined value and execute root as
  described in Section Processing of execute(). Destroys 
  *root* afterwards unless 
  *root* was recycled.
------------------------------------------------------------------------------------------
\ ``static void spawn_root_and_wait( task_list& root_list )``
  \
  **Requirements**: Each 
  ``task`` object 
  *t* in 
  *root_list* must meet the requirements in static void
  spawn_root_and_wait( task& root ).
  
  **Effects**: For each 
  ``task`` object 
  *t* in root_list, performs 
  ``spawn_root_and_wait(t)``, possibly in
  parallel. Section static void spawn_root_and_wait( task& root ) describes
  the actions of 
  ``spawn_root_and_wait(t)``.
------------------------------------------------------------------------------------------
\ ``static void enqueue ( task& )``
  \
  The task is scheduled for eventual
  execution by a worker thread even if no thread ever explicitly waits for the
  task to complete. If the total number of worker threads is zero, a special
  additional worker thread is created to execute enqueued tasks.
  
  Enqueued tasks are processed in roughly,
  but not precisely, first-come first-serve order.
  
  .. caution::

     Using enqueued tasks for recursive
     parallelism can cause high memory usage, because the recursion will expand in a
     breadth-first manner. Use ordinary spawning for recursive parallelism.
  
  .. caution::

     Explicitly waiting on an enqueued task
     should be avoided, because other enqueued tasks from unrelated parts of the
     program might have to be processed first. The recommended pattern for using an
     enqueued task is to have it asynchronously signal its completion, for example,
     by posting a message back to the thread that enqueued it. See the oneAPI
     Threading Building Blocks
     *Design Patterns* manual for such an example.
  
------------------------------------------------------------------------------------------
\ ``static void enqueue ( task& t, task_arena& arena, priority_t p = priority_normal )``
  \
  Similar to ``enqueue( task& )`` but enqueues the task into given arena with possibly specified task priority.
  See the description of ``task_arena::enqueue(...)`` set of methods for more details.
------------------------------------------------------------------------------------------
= ========================================================================================


See also:

* :doc:`Scheduling Algorithm <../scheduling_algorithm>`
* :doc:`task_group_context <../../task_scheduler/task_group_context>`
* :doc:`task Derivation, Processing of execute() <task_derivation>`
* :doc:`task_arena Class and this_task_arena Namespace <../../task_scheduler/task_arena_cls>`
