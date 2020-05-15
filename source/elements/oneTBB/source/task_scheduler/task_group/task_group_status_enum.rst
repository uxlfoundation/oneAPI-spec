=================
task_group_status
=================
**[scheduler.task_group_status]**

A ``task_group_status`` type represents the status of a ``task_group``.

.. code:: cpp

    namespace tbb {
        enum task_group_status {
            not_complete,
            complete,
            canceled
        };
    }

Member constants
----------------

.. c:macro:: not_complete

    Not cancelled and not all tasks in group have completed.

.. c:macro:: compete

    Not cancelled and all tasks in group have completed.

.. c:macro:: canceled

    Task group received cancellation request.

