===============
task Derivation
===============

Class ``task`` is an abstract base class. You **must** override method
``task::execute``. Method ``execute`` should perform
the necessary actions for running the task, and then return the next
``task`` to execute, or NULL if the scheduler should choose the
next task to execute. Typically, if non-NULL, the returned task is one of the
predecessor tasks of ``this``. Unless one of the recycle/reschedule
methods, described in Section Recycling Tasks, is called while method
``execute()`` is running, the ``this`` object will be
implicitly destroyed after method ``execute`` returns.

Override the virtual destructor if necessary to release resources allocated by the constructor.

Override ``note_affinity`` to improve cache reuse across tasks, as described in Section Affinity.

Processing of execute()
-----------------------

When the scheduler decides that a thread should begin executing a *task*, it performs the
following steps:

* Invokes ``execute()`` and waits for it to return.
* If the task has not been marked by a method ``recycle_*``:

  * Calls the task's destructor.
  * If the task's *parent* is not null, then atomically decrements
    *successor*->\ ``refcount``, and if becomes zero, puts the
    successor into the ready pool.
  * Frees the memory of the task for reuse.
  
* If the task has been marked for recycling:

  * If marked by ``recycle_to_reexecute`` (deprecated), puts the task back
    into the ready pool.
  * Otherwise it was marked by ``recycle_as_child`` or ``recycle_as_continuation``.
  


See also:

* :doc:`Recycling Tasks <recycling_tasks>`
* :doc:`Affinity <affinity>`
