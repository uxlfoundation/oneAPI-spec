================
task_group Class
================


Description
-----------

A ``task_group`` represents
concurrent execution of a group of tasks. Tasks may be
dynamically added to the group as it is executing.

Example with Lambda Expressions
-------------------------------

.. code:: cpp

   #include "tbb/task_group.h"
   
   int Fib(int n) {
       if( n<2 ) {
           return n;
       } else {
           int x, y;
           tbb::task_group g;
           g.run([&]{x=Fib(n-1);}); // spawn a task
           g.run([&]{y=Fib(n-2);}); // spawn another task
           g.wait();                // wait for both tasks to complete
           return x+y;
       }
   }

.. caution::

   Creating a large number of tasks
   for a single task_group is not scalable, because
   task creation becomes a serial bottleneck. If
   creating more than a small number of concurrent
   tasks, consider using
   ``parallel_for`` or
   ``parallel_invoke`` instead, or
   structure the spawning as a recursive tree.


Members
-------

.. code:: cpp

   namespace tbb {
       class task_group {
       public:
           task_group();
           ~task_group();
   
           // Supported until C++11
           template<typename Func>
           void run( const Func& f );
   
           // Supported since C++11
           template<typename Func>
           void run( Func&& f );
   
           template<typename Func>
           void run( task_handle<Func>& handle );
   
           template<typename Func>
           task_group_status run_and_wait( const Func& f );
   
           template<typename Func>
           task_group_status run_and_wait( task_handle<Func>& handle );
   
           task_group_status wait();
           bool is_canceling();
           void cancel();
       };
   }

The following table provides additional information on the members
of class ``task_group``.

= ========================================================================================
\ Member, Description
==========================================================================================
\ ``task_group()``
  \
  Constructs an empty ``task_group``.
------------------------------------------------------------------------------------------
\ ``~task_group()``
  \
  Destroys the ``task_group``.
  
  **Requires**: Method
  ``wait`` must be called before destroying a
  ``task_group``, otherwise the destructor throws an
  exception.
------------------------------------------------------------------------------------------
\ ``run``
  \
  *Until C++11*: ``template<typename Func> void run( const Func& f )``
  
  *Since C++11*: ``template<typename Func> void run( Func&& f )``

  Spawns a task to compute``f()``
  and returns immediately.
------------------------------------------------------------------------------------------
\ ``template<typename Func> void run ( task_handle<Func>& handle );``
  \
  Spawns a task to compute
  ``handle()`` and returns immediately.
------------------------------------------------------------------------------------------
\ ``template<typename Func> task_group_status run_and_wait( const Func& f )``
  \
  Equivalent to
  ``{run(f); return wait();}``, but guarantees
  that ``f()`` runs on the current thread.
  
  .. note::

     Template method
     ``run_and_wait`` is intended to be more
     efficient than separate calls to
     ``run`` and
     ``wait``.
  
------------------------------------------------------------------------------------------
\ ``template<typename Func> task_group_status run_and_wait( task_handle<Func>& handle );``
  \
  Equivalent to
  ``{run(handle); return wait();}``, but guarantees
  that ``handle()`` runs on the current thread.
  
  .. note::

     Template method
     ``run_and_wait`` is intended to be more
     efficient than separate calls to
     ``run`` and
     ``wait``.
  
------------------------------------------------------------------------------------------
\ ``task_group_status wait()``
  \
  Waits for all tasks in the group to complete
  or be cancelled.
  
  **Returns**: The status of ``task_group``:doc:`More information <task_group_status_enum>`
------------------------------------------------------------------------------------------
\ ``bool is_canceling()``
  \
  **Returns**: True if this task group is
  cancelling its tasks.
------------------------------------------------------------------------------------------
\ ``void cancel()``
  \
  Cancels all tasks in this
  ``task_group``.
------------------------------------------------------------------------------------------
= ========================================================================================
