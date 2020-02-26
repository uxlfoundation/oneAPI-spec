===============
Resumable tasks
===============


Summary
-------

Functions to suspend task execution at a specific point and signal to resume it later.

Syntax
------

.. code:: cpp

   tbb::task::suspend_point;
   template < typename Func > void tbb::task::suspend( Func );
   void tbb::task::resume( tbb::task::suspend_point );


Header
------

.. code:: cpp

   #define TBB_PREVIEW_RESUMABLE_TASKS 1
   #include "tbb/task.h"

.. note::

   The feature requires linkage with TBB preview binaries.


Description
-----------

I/O operations in their various forms may block TBB threads, decreasing overall CPU utilization. The ``tbb::task::suspend`` function called within a running task suspends execution of the task and switches the thread to participate in other TBB parallel work. This function accepts a user callable object with the current execution context ``tbb::task::suspend_point`` as an argument. This object must model the requirements from the following table:

.. table:: Requirements for tbb::task::suspend functional object

   ===================================================== ==============================
   Pseudo-signarute                                      Semantics
   ===================================================== ==============================
   ``Func::Func( const Func& )``                         Copy constructor.
   ----------------------------------------------------- ------------------------------
   ``void Func::operator()( tbb::task::suspend_point )`` Body that accepts the current task execution point to resume later.
   ===================================================== ==============================

Pass the ``tbb::task::suspend_point`` context tag to the ``tbb::task::resume`` function to trigger a program execution at the suspended point. The ``tbb::task::resume`` function can be called at any point of an application, even on a separate thread. In this regard, this function acts as a signal for the TBB scheduler.

.. note::

   Note, that there are no guarantees, that the same thread that called ``tbb::task::suspend`` will continue execution after the suspended point. However, these guarantees are provided for the outermost blocking TBB calls (such as ``tbb::parallel_for`` and ``tbb::flow::graph::wait_for_all``) and ``tbb::task_arena::execute`` calls.


Example
-------

TBB Flow Graph has a
:doc:`tbb::flow::async_node <../flow_graph/async_node_cls>`
class to communicate with an external activity managed by the user or another runtime.
This example shows, how to achieve the same purpose (as illustrated in ``tbb::flow::async_node`` example)
but within a usual ``tbb::parallel_for`` region.
Note, that a callback support or a dedicated thread is still required, but this approach is slightly simpler
because explicit ``reserve/release_wait`` calls and flow graph instance are not needed.

.. include:: examples/resumable_tasks.cpp
   :code: cpp



See also:

* :doc:`task Class <../low_level_tasking/task_cls>`
* :doc:`async_node Template Class <../flow_graph/async_node_cls>`
