==============================
task_scheduler_observer Member
==============================

The following table provides additional information on the members
of this template class.

= ========================================================================================
\ Member, Description
==========================================================================================
\ ``explicit task_scheduler_observer( bool local = false )``
  \
  Constructs a ``task_scheduler_observer``
  object in the inactive state (observation is disabled).
  If ``local`` is ``false``,
  the entry or exit notifications are invoked for threads which start or stop
  participate in task scheduling (globally).
  If ``local`` is ``true``,
  the entry notifications are invoked for threads that join or have already joined
  the current arena, and the exit notifications are invoked for threads leaving the arena.
------------------------------------------------------------------------------------------
\ ``explicit task_scheduler_observer( task_arena & )``
  \
  Constructs a ``task_scheduler_observer``
  object in the inactive state (observation is disabled), which receives notifications
  from threads entering and exiting the specified ``task_arena``.
  
  .. note::

     Enabling the observation for such an observer forces
     initialization of the internal arena representation of the specified
     ``task_arena`` object.
  
------------------------------------------------------------------------------------------
\ ``~task_scheduler_observer()``
  \
  Disables observing and destroys the observer instance.
  Waits for extant invocations of ``on_scheduler_entry`` and
  ``on_scheduler_exit`` to complete.
------------------------------------------------------------------------------------------
\ ``void observe( bool state=true )``
  \
  Enables observing if ``state`` is true;
  disables observing if ``state`` is false.
------------------------------------------------------------------------------------------
\ ``bool is_observing() const``
  \
  **Returns**: True if observing is
  enabled; false otherwise.
------------------------------------------------------------------------------------------
\ ``virtual void on_scheduler_entry( bool is_worker )``
  \
  The task scheduler invokes this method for each thread that starts participating
  in TBB work or enters an arena after the observation is enabled.
  For threads that already execute tasks, the method is invoked
  before executing the first task stolen after enabling the observation.
  
  .. note::

     If a thread enables the observation and then
     spawns a task, it is guaranteed that the task, as well as all the tasks it creates,
     will be executed by threads which have invoked ``on_scheduler_entry``.
  
  The flag ``is_worker`` is true
  if the thread was created by TBB; false otherwise.
  
  **Effects**: The default behavior does nothing.
------------------------------------------------------------------------------------------
\ ``virtual void on_scheduler_exit( bool is_worker )``
  \
  The task scheduler invokes this method when
  a thread stops participating in task processing or leaves an arena.
  
  .. caution::

     Sometimes
     ``on_scheduler_exit`` is invoked for a thread but
     ``on_scheduler_entry`` is not. This situation can arise
     if a thread never steals a task after the observation is enabled.
  
  .. caution::

     A process does not wait for the worker threads to clean up,
     and can terminate before ``on_scheduler_exit`` is invoked.
  
  **Effects**: The default behavior does nothing.
------------------------------------------------------------------------------------------
= ========================================================================================
