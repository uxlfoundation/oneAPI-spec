===============
Recycling Tasks
===============

It is often more efficient to recycle a task object
rather than reallocate one from scratch. Often the parent can become the
continuation, or one of the predecessors.

.. caution::

   **Overlap rule**: A recycled task 
   *t* must not be put in jeopardy of having 
   ``t.execute()`` rerun while the previous
   invocation of 
   ``t.execute()`` is still running. The debug
   version of the library detects some violations of this rule.

For example, 
``t.execute()`` should never spawn 
``t`` directly after recycling it. Instead, 
``t.execute()`` should return a pointer to 
``t``, so that 
``t`` is spawned after 
``t.execute()`` completes.

The following table provides additional information on the
members of this template class.

= ========================================================================================
\ Member, Description
==========================================================================================
\ ``void recycle_as_continuation()``
  \
  **Requirements**: Must be called while
  method 
  ``execute()`` is running.
  
  The 
  ``refcount`` for the recycled task should
  be set to 
  ``n``, where 
  ``n`` is the number of predecessors of
  the continuation task.
  
  .. caution::

     The caller must guarantee that the
     task's 
     ``refcount`` does not become zero until
     after method 
     ``execute()`` returns, otherwise the overlap
     rule is broken. If the guarantee is not possible, use method 
     ``recycle_as_safe_continuation()`` instead,
     and set the 
     ``refcount`` to 
     ``n+1``.
  
  The race can occur for a task 
  ``t`` when:
  
  ``t.execute()``
  recycles 
  ``t`` as a continuation.
  
  The continuation has predecessors that
  all complete before 
  ``t.execute()`` returns.
  
  Hence the recycled 
  ``t`` will be implicitly respawned with the original
  
  ``t.execute()`` still running, which
  breaks the overlap rule.
  
  Patterns that use 
  ``recycle_as_continuation()`` typically avoid
  the race by making 
  ``t.execute()`` return a pointer to one
  of the predecessors instead of explicitly spawning that predecessor. The
  scheduler implicitly spawns that predecessor after 
  ``t.execute()`` returns, thus
  guaranteeing that the recycled t does not rerun prematurely.
  
  **Effects**: Causes 
  ``this`` to not be destroyed when method 
  ``execute()`` returns.
------------------------------------------------------------------------------------------
\ ``void recycle_as_safe_continuation()``
  \
  **Requirements**: Must be called while
  method 
  ``execute()`` is running.
  
  The 
  ``refcount`` for the recycled task should
  be set to 
  ``n+1``, where 
  ``n`` is the number of predecessors of
  the continuation task. The additional 
  ``+1`` represents the task to be recycled.
  
  **Effects**: Causes 
  ``this`` to not be destroyed when method 
  ``execute()`` returns.
  
  This method avoids the race discussed for
  recycle_as_continuation because the additional +1 in the 
  ``refcount`` prevents the continuation
  from executing until the original invocation of 
  ``execute()`` completes.
------------------------------------------------------------------------------------------
\ ``void recycle_as_child_of( task& new_successor )``
  \
  **Requirements**: Must be called while
  method 
  ``execute()`` is running.
  
  **Effects**: Causes 
  ``this`` to become a predecessor of 
  ``new_successor``, and not be destroyed
  when method 
  ``execute()`` returns.
------------------------------------------------------------------------------------------
= ========================================================================================
