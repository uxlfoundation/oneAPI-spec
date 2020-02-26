==================
task_group_context
==================


Summary
-------

A cancellable group of tasks.

Syntax
------

.. code:: cpp

   class task_group_context;


Header
------

.. code:: cpp

   #include "tbb/task.h"


Description
-----------

A 
``task_group_context`` represents a group of tasks that
can be cancelled, or have their priority level set, together. All tasks belong
to some group. A task can be a member of only one group at any moment.

A root task is associated with a group by passing 
``task_group_context`` object into ``task::allocate_root()`` call. A
child task automatically joins its parent task's group. A task can be moved
into other group using 
``task::change_group()`` method.

The 
``task_group_context`` objects form a forest of trees.
Each tree's root is a 
``task_group_context`` constructed as 
``isolated``.

A 
``task_group_context`` is cancelled explicitly by request,
or implicitly when an exception is thrown out of a task. Canceling a 
``task_group_context`` causes the entire subtree rooted at
it to be cancelled.

The priorities for all the tasks in a group can be
changed at any time either via the associated 
``task_group_context`` object, or via any task belonging
to the group. Priority changes propagate into the child task groups similarly
to cancellation. The effect of priorities on task execution is described in
Section Priorities.

Each user thread that creates a 
``task_scheduler_init`` implicitly has an 
``isolated task_group_context`` that acts as the root of
its initial tree. This context is associated with the dummy task returned by 
``task::self()`` when the user thread is not running any
task.

Members
-------

.. code:: cpp

   namespace tbb {
       class task_group_context {
       public:
           enum kind_t {
               isolated = implementation-defined,
               bound = implementation-defined
           };
   
           enum traits_type {
               exact_exception = implementation-defined,
               fp_settings     = implementation-defined,
               concurrent_wait = implementation-defined,
   #if TBB_USE_CAPTURED_EXCEPTION
               default_traits = 0
   #else
               default_traits = exact_exception
   #endif /* !TBB_USE_CAPTURED_EXCEPTION */
           };
           task_group_context( kind_t relation_with_parent = bound, 
                               uintptr_t traits = default_traits );
           ~task_group_context();
           void reset();
           bool cancel_group_execution();
           bool is_group_execution_cancelled() const;
           void capture_fp_settings();
           void set_priority( priority_t );
           priority_t priority() const;
           uintptr_t traits() const;
       }; 
   }

The following table provides additional information on the members
of this template class.

= ========================================================================================
\ Member, Description
==========================================================================================
\ ``task_group_context( kind_t relation_to_parent=bound, uintptr_t traits=default_traits )``
  \
  Constructs an empty 
  ``task_group_context``. If 
  *relation_to_parent* is bound, the 
  ``task_group_context`` will become a child of the
  innermost running task's group when it is first passed into the call to 
  ``task::allocate_root(task_group_context&)``.
  If this call is made directly from the user thread, the effect will be as if 
  ``relation_to_parent`` were isolated. If 
  ``relation_to_parent`` is 
  *isolated*, it has no parent 
  ``task_group_context``.
  
  The 
  *traits* argument should be the bitwise OR of 
  *traits_type* values. The flag 
  ``exact_exception`` controls how precisely
  exceptions are transferred between threads. See Section Exceptions for details.
  The flag 
  ``concurrent_wait`` controls the
  reference-counting behavior of methods 
  ``task::wait_for_all`` and 
  ``task::spawn_and_wait_for_all``.
  The flag ``fp_settings`` forces the context to capture floating-point settings
  from the current thread. See Section Floating-point Settings for more details.
------------------------------------------------------------------------------------------
\ ``~task_group_context()``
  \
  Destroys an empty task_group_context. It is
  a programmer error if there are still extant tasks in the group.
------------------------------------------------------------------------------------------
\ ``bool cancel_group_execution()``
  \
  Requests that tasks in group be cancelled.
  
  **Returns**: False if group is already
  cancelled; true otherwise. If concurrently called by multiple threads, exactly
  one call returns true and the rest return false.
------------------------------------------------------------------------------------------
\ ``bool is_group_execution_cancelled() const``
  \
  **Returns**: True if group has received cancellation.
------------------------------------------------------------------------------------------
\ ``void reset()``
  \
  Reinitializes this to uncancelled state.
  
  .. caution::

     This method is only safe to call once all tasks associated
     with the group's subordinate groups have completed. This method must not be
     invoked concurrently by multiple threads.
  
------------------------------------------------------------------------------------------
\ ``void set_priority( priority_t )``
  \
  Changes priority of the task group.
------------------------------------------------------------------------------------------
\ ``priority_t priority() const``
  \
  **Returns**: Priority of the task group.
------------------------------------------------------------------------------------------
\ ``void capture_fp_settings()``
  \
  Captures floating-point settings from the current thread. See Section Floating-point Settings for more details.
  
  .. caution::

     This method is only safe to call once all tasks associated
     with the group's subordinate groups have completed. This method must not be
     invoked concurrently by multiple threads.
  
------------------------------------------------------------------------------------------
\ ``uintptr_t traits() const``
  \
  **Returns**: Traits of the task group.
------------------------------------------------------------------------------------------
= ========================================================================================


See also:

* :doc:`Floating-point Settings <fpu_settings>`
