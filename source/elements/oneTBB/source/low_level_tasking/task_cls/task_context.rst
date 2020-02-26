============
task Context
============

The methods detailed in the following table expose
relationships between 
*task* objects, and between 
*task* objects and the underlying physical threads.

= ========================================================================================
\ Member, Description
==========================================================================================
\ ``static task& self()``
  \
  **Returns**: Reference to innermost 
  *task* that the calling thread is running. A task is
  considered running if its methods 
  ``execute(), note_affinity()``, or destructor
  are running. If the calling thread is a user-created thread that is not running
  any task, 
  ``self()`` returns a reference to an implicit
  dummy task associated with the thread.
------------------------------------------------------------------------------------------
\ ``task* parent() const``
  \
  **Returns**: Value of the attribute 
  *successor*. The result is an undefined value if the
  task was allocated by 
  ``allocate_root`` and is currently running under
  control of 
  ``spawn_root_and_wait``.
------------------------------------------------------------------------------------------
\ ``void set_parent(task* p)``
  \
  **Requirements**: Both tasks must be
  in the same task group except for p == NULL. For example, for 
  ``task t, t.group() == p->group()``
  
  **Effects**: Sets parent task pointer
  to specified value 
  ``p``.
------------------------------------------------------------------------------------------
\ ``bool is_stolen_task() const``
  \
  **Returns**: 
  *true* if task is running on a thread different than the
  thread that spawned it.
  
  .. note::

     Tasks enqueued with 
     ``task::enqueue()`` are never reported as
     stolen.
  
------------------------------------------------------------------------------------------
\ ``task_group_context* group()``
  \
  **Returns**: Descriptor of the task
  group, which this task belongs to.
------------------------------------------------------------------------------------------
\ ``void change_group( task_group_context& ctx )``
  \
  Moves the task from its current task
  group into the one specified by the 
  ``ctx`` argument.
------------------------------------------------------------------------------------------
= ========================================================================================
