============
Cancellation
============

A 
*task* is a quantum of work that is cancelled or executes to
completion. A cancelled task skips its method 
``execute()`` if that method has not yet started.
Otherwise cancellation has no direct effect on the task. A task can poll 
``task::is_cancelled()`` to see if cancellation was
requested after it started running.

The following table provides additional information on the
members of this template class.

= ========================================================================================
\ Member, Description
==========================================================================================
\ ``bool cancel_group_execution()``
  \
  Requests cancellation of all tasks in its group and its
  subordinate groups.
  
  **Returns**: False if the task's group already received a
  cancellation request; true otherwise.
------------------------------------------------------------------------------------------
\ ``bool is_cancelled() const``
  \
  **Returns**: True if task's group has received a
  cancellation request; false otherwise.
------------------------------------------------------------------------------------------
= ========================================================================================


See also:

* :doc:`task_group_context <../../task_scheduler/task_group_context>`
