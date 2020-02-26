====================
global_control Class
====================


Summary
-------

Use this class to control certain settings or behavior of the oneAPI Threading Building Blocks dynamic library.

Header
------

.. code:: cpp

   #include "tbb/global_control.h"
      


Syntax
------

.. code:: cpp

   class global_control;
      


Description
-----------

An object of class
``global_control``, or a "control variable", affects one
of several behavioral aspects, or parameters, of TBB. Class
``global_control`` is primarily intended for use at the
application level, to control the whole application behavior.

.. note::

   You should avoid using this class in libraries
   and plugins, as it could result in broad impact on composability and
   performance.

The current set of parameters that you can modify is defined by
``global_control::parameter`` enumeration. The parameter
and the value it should take are specified as arguments to the constructor of a
control variable. The impact of the
control variable ends when its lifetime is complete.

Control variables can be created in different threads, and may have
nested or overlapping scopes. However, at any point in time each controlled
parameter has a single active value that applies to the whole process. This
value is selected from all currently existing control variables by applying a
parameter-specific selection rule.

.. table:: Global control parameters

   =========================== ============== ==============================
   Parameter                   Selection rule Description
   =========================== ============== ==============================
   ``max_allowed_parallelism`` minimum        Limit total number of worker threads that
                                              can be active in the task scheduler to
                                              ``parameter value - 1``.
                                              
                                              .. note::

                                                 With ``max_allowed_parallelism`` set to
                                                 ``1``, ``global_control`` enforces serial execution
                                                 of all tasks by the application thread(s), i.e. the task scheduler does not
                                                 allow worker threads to run. There is one exception: if some work is submitted
                                                 for execution via ``task::enqueue`` or ``task_arena::enqueue``,
                                                 a single worker thread will still run ignoring the ``max_allowed_parallelism``
                                                 restriction.
                                              
   --------------------------- -------------- ------------------------------
   ``thread_stack_size``       maximum        Set stack size for threads created by the
                                              library, including working threads in the task scheduler and threads controlled
                                              by thread wrapper classes.
                                              
                                              .. note::

                                                 * For Windows 8 Store* applications stack size cannot be set.
                                                 * For Windows* OS, valid stack size values are limited to 4 GB.
                                                 
                                              
   =========================== ============== ==============================


Example
-------

.. code:: cpp

   #include "tbb/parallel_for.h"
   #include "tbb/task_scheduler_init.h"
   #include "tbb/global_control.h"
   
   using namespace tbb;
   
   void foo()
   {
       // The following code could use up to 16 threads.
       task_scheduler_init tsi(16);
       parallel_for( . . . );
   }
   
   void bar()
   {
       // The following code could use up to 8 threads.
       task_scheduler_init tsi(8);
       parallel_for( . . . );
   }
   
   int main()
   {
       {
           const size_t parallelism = task_scheduler_init::default_num_threads();
           // total parallelism that TBB can utilize is cut in half for the dynamic extension
           // of the given scope, including calls to foo() and bar()
           global_control c(global_control::max_allowed_parallelism, parallelism/2);
           foo();
           bar();
       } // restore previous parallelism limitation, if one existed
   }


Members
-------

.. code:: cpp

   namespace tbb {
       class global_control {
     public:
           enum parameter {
               max_allowed_parallelism,
               thread_stack_size
           };
   
           global_control(parameter p, size_t value);
          ~global_control();
           static size_t active_value(parameter param);
       };
   } // namespace tbb

The following table provides additional information on the members of the class.

= ========================================================================================
\ Member, Description
==========================================================================================
\ ``static size_t active_value(parameter param);``
  \
  Returns the currently active value of the
  setting defined by
  ``param``.
------------------------------------------------------------------------------------------
= ========================================================================================


See also:

* :doc:`task_arena Class <task_arena_cls>`
