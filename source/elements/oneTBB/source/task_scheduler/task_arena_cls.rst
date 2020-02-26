==============================================
task_arena Class and this_task_arena Namespace
==============================================


Summary
-------

A class that represents an explicit, user-managed task scheduler arena, and a namespace
for functions applicable to the current arena.

Syntax
------

.. code:: cpp

   class task_arena;


Header
------

.. code:: cpp

   #include "tbb/task_arena.h"


Description
-----------

A ``task_arena`` class represents a place where threads may share and execute tasks.

The number of threads that may simultaneously execute tasks in a task_arena is limited
by its concurrency level. The concurrency level affects only that arena, and is not affected
by previous ``task_scheduler_init`` specifications.

.. note::

   The total number of threads that the scheduler may use is limited by whichever is largest:
   the default number of threads for the machine or the value specified for the first task
   scheduler initialization. Therefore the number of threads assigned to a task_arena will
   never exceed that maximum value, regardless of its concurrency level. Moreover, a task_arena
   might not get the specified number of threads even if it is lower than the allowed maximum.


Each user thread that explicitly or implicitly initializes the task scheduler creates and
uses an implicit internal task arena object. The tasks spawned or enqueued into one arena
cannot be executed in another arena.

A ``task_arena`` instance also holds a reference to such internal
representation, but does not fully control its lifetime. The internal representation cannot
be destroyed while it contains tasks or other threads reference it.

.. note::

   The ``task_arena`` constructors do not create an internal arena object.
   It may already exist in case of the "attaching" constructor, otherwise it is created
   by explicit call to ``task_arena::initialize`` or lazily on first use.


.. note::

   oneAPI Threading Building Blocks does not allocate an implicit
   arena object for the current thread when dealing with an explicit arena object represented
   by ``task_arena``. But, a subsequent scheduler initialization in the same
   thread will use default settings, regardless of the number of threads specified for
   ``task_scheduler_init``. This provides backward compatibility with previous
   TBB releases where a call to any method related to the task scheduler initialized
   the scheduler for the current thread, including creation of an implicit arena object.


The namespace ``this_task_arena`` contains global functions for interaction
with the arena (either explicit ``task_arena`` or implicit arena object)
currently used by the calling thread.

Members
-------

.. code:: cpp

   namespace tbb {
       class task_arena {
       public:
           static const int automatic = implementation-defined;
           static const int not_initialized = implementation-defined;
           struct attach {};
   
           task_arena(int max_concurrency = automatic, unsigned reserved_for_masters = 1);
           task_arena(const task_arena &s);
           explicit task_arena(task_arena::attach);
           ~task_arena();
   
           void initialize();
           void initialize(int max_concurrency, unsigned reserved_for_masters = 1);
           void initialize(task_arena::attach);
           void terminate();
   
           bool is_active() const;
           int max_concurrency() const;
   
           // Supported until C++11
           template<typename F> void execute(F& f);
           template<typename F> void execute(const F& f);
           template<typename F> void enqueue(const F& f);
           template<typename F> void enqueue(const F& f, priority_t p);
   
           // Supported since C++11
           template<typename F> auto execute(F& f) -> decltype(f());
           template<typename F> auto execute(const F& f) -> decltype(f());
           template<typename F> void enqueue(F&& f);
           template<typename F> void enqueue(F&& f, priority_t p);
   
           static int current_thread_index(); // deprecated
       };
       namespace this_task_arena {
           int current_thread_index();
           int max_concurrency();
   
           // Supported until C++11
           template<typename F> void isolate(F& f);
           template<typename F> void isolate(const F& f);
   
           // Supported since C++11
           template<typename F> auto isolate(F& f) -> decltype(f());
           template<typename F> auto isolate(const F& f) -> decltype(f());
       }
   }


Examples
--------

The following example runs two ``parallel_for`` loops concurrently; one that is
scalable and one that is not. The non-scalable loop is limited to at most 2 threads so that
the majority of the threads can be saved for the more scalable loop. It uses
``task_group`` to wait for a specific subset of tasks.

.. code:: cpp

   tbb::task_scheduler_init def_init; // Use the default number of threads.
   tbb::task_arena limited(2);        // No more than 2 threads in this arena.
   tbb::task_group tg;
   
   limited.execute([&]{ // Use at most 2 threads for this job.
       tg.run([]{ // run in task group
           tbb::parallel_for(1, N, unscalable_work());
       });
   });
   
   // Run another job concurrently with the loop above.
   // It can use up to the default number of threads.
   tbb::parallel_for(1, M, scalable_work());
   
   // Wait for completion of the task group in the limited arena.
   limited.execute([&]{ tg.wait(); });

The following table provides additional information on the members of the class ``task_arena``.

= ========================================================================================
\ Member, Description
==========================================================================================
\ ``task_arena(int max_concurrency = automatic, unsigned reserved_for_masters = 1)``
  \
  Creates a ``task_arena`` with a certain concurrency limit
  (``max_concurrency``). Some portion of the limit can be
  reserved for application threads with ``reserved_for_masters``.
  The amount for reservation cannot exceed the limit.
  
  .. caution::

     If ``max_concurrency`` and ``reserved_for_masters`` are
     explicitly set to be equal and greater than 1, TBB worker threads will never
     join the arena. As a result, the execution guarantee for enqueued tasks is not valid
     in such arena. Do not use ``task_arena::enqueue()`` and
     ``task::enqueue()`` with an arena set to have no worker threads.
  
------------------------------------------------------------------------------------------
\ ``static const int automatic``
  \
  When passed as ``max_concurrency`` to the above constructor, arena
  concurrency will be automatically set based on the hardware configuration.
------------------------------------------------------------------------------------------
\ ``static const int not_initialized``
  \
  When returned by a method or function, indicates that there is no active arena
  or that the arena object has not yet been initialized.
------------------------------------------------------------------------------------------
\ ``task_arena(const task_arena&)``
  \
  Copies settings from another ``task_arena`` instance.
------------------------------------------------------------------------------------------
\ ``explicit task_arena(task_arena::attach)``
  \
  Creates an instance of ``task_arena`` that is connected
  to the internal arena currently used by the calling thread. If no such arena
  exists yet, creates a ``task_arena`` with default parameters.
  
  .. note::

     Unlike other constructors, this one automatically initializes
     the new ``task_arena`` when connecting to an already existing arena.
  
------------------------------------------------------------------------------------------
\ ``~task_arena()``
  \
  Removes the reference to the internal arena representation, and destroys the
  ``task_arena`` instance. Not thread safe w.r.t. concurrent
  invocations of other methods.
------------------------------------------------------------------------------------------
\ ``initialize``
  \
  ``void initialize()``
  
  ``void initialize(int max_concurrency, unsigned reserved_for_masters = 1)``
  
  ``void initialize(task_arena::attach)``

  Performs actual initialization of internal arena representation. If arguments are
  specified, they override previous arena parameters. If an instance of class
  ``task_arena::attach`` is specified as the argument, and there exists
  an internal arena currently used by the calling thread, the method ignores arena
  parameters and connects ``task_arena`` to that internal arena.
  The method has no effect when called for an already initialized arena.
  
  .. note::

     After the call to ``initialize``, the arena parameters
     are fixed and cannot be changed.
  
------------------------------------------------------------------------------------------
\ ``void terminate()``
  \
  Removes the reference to the internal arena representation without destroying the
  task_arena object, which can then be re-used. Not thread safe w.r.t. concurrent
  invocations of other methods.
------------------------------------------------------------------------------------------
\ ``bool is_active() const``
  \
  Returns ``true`` if the arena has been initialized,
  ``false`` otherwise.
------------------------------------------------------------------------------------------
\ ``int max_concurrency() const``
  \
  Returns the concurrency level of the arena.
  Does not require the arena to be initialized and does not perform initialization.
------------------------------------------------------------------------------------------
\ ``enqueue``
  \
  *Until C++11:* ``template<F> void enqueue(const F& f)``
  
  *Since C++11:* ``template<F> void enqueue(F&& f)``

  Enqueues a task into the arena to process the specified functor (which is copied or moved
  into the task), and immediately returns.
  
  .. note::

     The method does not require the calling thread to join the arena; i.e. any number
     of threads outside of the arena can submit work to it without blocking.
  
  .. caution::

     There is no guarantee that tasks enqueued into an arena execute concurrently with
     respect to any other tasks there.
  
  .. caution::

     An exception thrown and not caught in the functor results in undefined behavior.
  
------------------------------------------------------------------------------------------
\ ``enqueue`` with priority
  \
  *Until C++11:* ``template<F> void enqueue(const F& f, priority_t)``
  
  *Since C++11:* ``template<F> void enqueue(F&& f, priority_t)``

  Enqueues a task with specified task priority. Is similar to
  ``enqueue(f)`` in all other ways.
------------------------------------------------------------------------------------------
\ ``execute``
  \
  *Until C++11:*
  
  ``template<F> void execute(F&)``
  
  ``template<F> void execute(const F&)``
  
  *Since C++11:*
  
  ``template<F> auto execute(F&) -> decltype(f())``
  
  ``template<F> auto execute(const F&) -> decltype(f())``

  Executes the specified functor in the arena. Since C++11 the function returns
  the value returned by the functor.
  
  The calling thread joins the arena if possible, and executes the functor.
  Upon return it restores the previous task scheduler state
  and floating-point settings.
  
  If joining the arena is not possible, the call wraps the functor into a task,
  enqueues it into the arena, waits using an OS kernel synchronization object
  for another opportunity to join, and finishes after the task completion.
  
  .. caution::

     Joining an arena (B) for the second time indirectly (like
     ``B.execute([]{ A.execute([]{ B.execute(f); }); });``)
     reduces effective concurrency of this arena and thus may lead to deadlock.
  
  .. note::

     Any number of threads outside of the arena can submit work to the arena and be
     blocked. However, only the maximal number of threads specified for the arena can
     participate in executing the work.
  
  .. note::

     ``execute`` may decrement the arena demand for worker threads,
     causing a worker to leave, and thereby freeing a slot for the calling thread.
  
  .. note::

     An exception thrown in the functor will be captured and re-thrown from
     ``execute``. If exact exception propagation is unavailable or
     disabled, the exception will be wrapped into
     ``tbb::captured_exception`` even for the same thread.
  
------------------------------------------------------------------------------------------
\ ``static int current_thread_index()``
  \
  **Deprecated**.
  Is equivalent to ``this_task_arena::current_thread_index()``
  (see below) except that it returns -1 if the calling thread has not yet
  initialized the task scheduler.
------------------------------------------------------------------------------------------
= ========================================================================================

The next table provides information on the members of the namespace ``this_task_arena``.

= ========================================================================================
\ Member, Description
==========================================================================================
\ ``int current_thread_index()``
  \
  Returns the thread index in a task arena currently used by the calling
  thread, or ``task_arena::not_initialized`` if the thread has not yet
  initialized the task scheduler.
  
  A thread index is an integer number between 0 and the arena concurrency level.
  Thread indexes are assigned to both application (master) threads and worker threads
  on joining an arena and are kept until exiting the arena. Indexes of threads that
  share an arena are unique - i.e. no two threads within the arena may have the same
  index at the same time - but not necessarily consecutive.
  
  .. note::

     Since a thread may exit the arena at any time if it does not execute a task, the
     index of a thread may change between any two tasks, even those belonging to the
     same task group or algorithm.
  
  .. note::

     Threads that use different arenas may have the same current index value.
  
  .. note::

     Joining a nested arena in ``execute()`` may change current index
     value while preserving the index in the outer arena which will be restored on
     return.
  
  .. note::

     This method can be used, for example, by ``task_scheduler_observer``
     to pin threads entering an arena to specific hardware.
  
------------------------------------------------------------------------------------------
\ ``int max_concurrency()``
  \
  Returns the concurrency level of the task arena currently used by the calling
  thread. If the thread has not yet initialized the task scheduler, returns
  the concurrency level determined automatically for the hardware configuration.
------------------------------------------------------------------------------------------
\ ``isolate``
  \
  *Until C++11:*
  
  ``template<F> void isolate(F&)``
  
  ``template<F> void isolate(const F&)``
  
  *Since C++11:*
  
  ``template<F> auto isolate(F&) -> decltype(f())``
  
  ``template<F> auto isolate(const F&) -> decltype(f())``

  Runs the specified functor in isolation by restricting the calling thread to
  process only tasks scheduled in the scope of the functor (also called the
  isolation region). Since C++11 the function returns the value returned by
  the functor.
  
  .. caution::

     The object returned by the functor cannot be a reference.
     ``std::reference_wrapper`` can be used instead.
  
  .. caution::

     Asynchronous parallel constructs such as a flow graph or a
     ``task_group`` should be used with care within an isolated region.
     For ``graph::wait_for_all`` or ``task_group::wait``
     executed in isolation, tasks scheduled by calling ``try_put`` for a
     flow graph node or by ``task_group::run`` are only accessible if
     scheduled in the same isolation region or in a task previously spawned in that
     region. Otherwise, performance issues and even deadlocks are possible.
  
------------------------------------------------------------------------------------------
= ========================================================================================


See also:

* :doc:`Task Groups <task_groups>`
* :doc:`task_scheduler_observer Class <task_scheduler_observer>`
* :doc:`Exceptions <../exceptions>`
* :doc:`Floating-point Settings <fpu_settings>`
