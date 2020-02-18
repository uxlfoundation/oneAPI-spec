========
Affinity
========

These methods enable optimizing for cache affinity. They enable you to
hint that a later task should run on the same thread as another task that was
executed earlier. To do this:

* In the earlier task, override 
  ``note_affinity(id)`` with a definition that
  records 
  ``id``.
* Before spawning the later task, run 
  ``set_affinity(id)`` using the 
  *id* recorded in step 1,

The 
*id* is a hint and may be ignored by the scheduler.

The following table provides additional information on the
members of this template class.

= ========================================================================================
\ Member, Description
==========================================================================================
\ ``affinity_id``
  \
  The type 
  ``task::affinity_id`` is an
  implementation-defined unsigned integral type. A value of 0 indicates no
  affinity. Other values represent affinity to a particular thread. Do not assume
  anything about non-zero values. The mapping of non-zero values to threads is
  internal to the oneAPI Threading Building Blocks library implementation.
------------------------------------------------------------------------------------------
\ ``virtual void note_affinity ( affinity_id id )``
  \
  The task scheduler invokes 
  ``note_affinity`` before invoking 
  ``execute()`` when:
  
  * The task has no affinity, but will
    execute on a thread different than the one that spawned it.
  
  * The task has affinity, but will
    execute on a thread different than the one specified by the affinity.
  
  You can override this method to record the id, so that it
  can be used as the argument to 
  ``set_affinity(id)`` for a later task.
  
  **Effects**: The default definition has no effect.
------------------------------------------------------------------------------------------
\ ``set_affinity ( affinity_id id )``
  \
  Sets affinity of this task to 
  *id*. The 
  *id* should be either 0 or obtained from 
  ``note_affinity``.
------------------------------------------------------------------------------------------
\ ``affinity_id affinity() const``
  \
  **Returns**: Affinity of this task as set by
  set_affinity.
------------------------------------------------------------------------------------------
= ========================================================================================
