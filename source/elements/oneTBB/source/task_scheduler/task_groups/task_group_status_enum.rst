======================
task_group_status Enum
======================

A ``task_group_status`` represents the status of a ``task_group``.

Members
-------

.. code:: cpp

   namespace tbb {
                       enum task_group_status {
                           not_complete, // Not cancelled and not all tasks in group have completed. 
                           complete,     // Not cancelled and all tasks in group have completed
                           canceled      // Task group received cancellation request
        };
    }
