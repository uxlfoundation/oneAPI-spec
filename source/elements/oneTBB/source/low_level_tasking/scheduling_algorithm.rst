====================
Scheduling Algorithm
====================

The scheduler employs a technique known as 
*work stealing*. Each thread keeps a "ready pool" of tasks that
are ready to run. The ready pool is structured as a deque (double-ended queue)
of task objects that were 
*spawned*. Additionally, there is a shared queue of 
``task`` objects that were 
*enqueued*. The distinction between spawning a task and enqueuing
a task affects when the scheduler runs the task.

After completing a task 
``t``, a thread chooses its next task according to
the first applicable rule below:

* The task returned by 
  ``t.execute()``
* The successor of 
  ``t`` if 
  ``t`` was its last completed predecessor.
* A task popped from the end of the thread’s own deque.
* A task with affinity for the thread.
* A task popped from approximately the beginning of the shared queue.
* A task popped from the beginning of another randomly chosen
  thread’s deque.

When a thread 
``spawns`` a task, it pushes it onto the end of its
own deque. Hence rule (3) above gets the task most recently spawned by the
thread, whereas rule (6) gets the least recently spawned task of another
thread.

When a thread 
*enqueues* a task, it pushes it onto the end of the shared queue.
Hence rule (5) gets one of the less recently enqueued tasks, and has no
preference for tasks that are enqueued. This is in contrast to spawned tasks,
where by rule (3) a thread prefers its own most recently spawned task.

Note the “approximately” in rule (5). For scalability reasons, the
shared queue does 
**not** guarantee precise first-in first-out behavior. If strict
first-in first-out behavior is desired, put the real work in a separate queue,
and create tasks that pull work from that queue. See "Non-Preemptive Priorities"
article in the TBB Developer Guide for more information.

It is important to understand the implications of spawning versus
enqueuing for nested parallelism.

* Spawned tasks emphasize locality. Enqueued tasks
  emphasize fairness.

* For nested parallelism, spawned tasks tend
  towards depth-first execution, whereas enqueued tasks cause breadth-first
  execution. Because the space demands of breadth-first execution can be
  exponentially higher than depth-first execution, enqueued tasks should be used
  with care.

* A spawned task might never be executed until a
  thread explicitly waits on the task to complete. An enqueued tasks will
  eventually run if all previously enqueued tasks complete. In the case where
  there would ordinarily be no other worker thread to execute an enqueued task,
  the scheduler creates an extra worker.

In general, use spawned tasks unless there is a clear reason to use an
enqueued task. Spawned tasks yield the best balance between locality of
reference, space efficiency, and parallelism. The algorithm for spawned tasks
is similar to the work-stealing algorithm used by Cilk (Blumofe 1995). The
notion of work-stealing dates back to the 1980s (Burton 1981). The thread
affinity support is more recent (Acar 2000).
