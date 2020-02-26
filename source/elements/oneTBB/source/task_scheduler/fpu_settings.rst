=======================
Floating-point Settings
=======================

For applications that need to control CPU-specific settings for floating-point computations,
there are two ways to propagate desired settings to tasks executed by oneAPI Threading Building Blocks task scheduler:

* When a task_arena or the task scheduler for a given application thread are initialized,
  they capture the current floating-point settings of the thread;
* The class task_group_context has a method to capture the current floating-point
  settings.


By default, worker threads use the floating-point settings captured during initialization of
an application thread's implicit arena or explicit task_arena. These settings are applied to
all parallel computations within the task_arena or started by the application thread, until
that thread terminates its task scheduler instance. If the thread later re-initializes the
task scheduler, new settings are captured.

For finer control over floating point behavior, a thread may capture the current settings in
a task group context. It can be done at context creation if a special flag is passed to the 
constructor:


.. code:: cpp

   task_group_context ctx( task_group_context::isolated,
                           task_group_context::default_traits | task_group_context::fp_settings );
           


or by a call to the method ``capture_fp_settings``:


.. code:: cpp

   task_group_context ctx;
   ctx.capture_fp_settings();
           


The task group context can then be passed to most TBB parallel algorithms (including
``flow::graph``) to ensure that all tasks related to this algorithm use the
specified floating-point settings. It is possible to execute parallel algorithms with
different floating-point settings captured to separate contexts, even at the same time.

Floating-point settings captured to a task group context prevail over the settings captured
during task scheduler initialization. Thus if a context is passed to a parallel algorithm
then floating-point settings captured to the context are used. Otherwise, if floating-point
settings are not captured to the context, or a context is not explicitly specified, then the
settings captured during task scheduler initialization are used.

In a nested call to a parallel algorithm not using a task group context with explicitly
captured floating-point settings, the settings from the outer level are used. If neither of
the outer level contexts captured floating-point settings then the settings captured during
task scheduler initialization are used.

It is guaranteed that:

* Floating-point settings captured to a task group context or at the moment of task
  scheduler initialization are applied to all tasks executed by the task scheduler.
* An invocation of an TBB parallel algorithm does not visibly modify the
  floating-point settings of the calling thread, even if the algorithm is executed with
  different settings.


.. caution::

   The above guarantees only apply in the following conditions:
   
   * The user code inside a task either does not change floating-point settings, or reverts
     any modifications and restores previous settings before the end of the task.
   * TBB task scheduler observers are not used to set or modify floating point
     settings.
   
   Otherwise, the stated guarantees are not valid and the behavior related to floating-point
   settings is undefined.


See also:

* :doc:`task_group_context Class <task_group_context>`
* :doc:`task_arena Class <task_arena_cls>`
