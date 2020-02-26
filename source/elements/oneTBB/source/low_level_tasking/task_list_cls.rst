===============
task_list Class
===============


Summary
-------

List of 
*task* objects.

Syntax
------

.. code:: cpp

   class task_list;


Header
------

.. code:: cpp

   #include "tbb/task.h"


Description
-----------

A 
``task_list`` is a list of references to *task objects*. The purpose of 
``task_list`` is to allow a 
*task* to create a list of tasks and spawn them all at once via
the method 
``task::spawn(task_list&)``, as described in Section
static void spawn ( task_list& list ).

A 
*task* can belong to at most one 
``task_list`` at a time, and on that 
``task_list`` at most once. A 
*task* that has been spawned, but not started running, must not
belong to a 
``task_list``. A 
``task_list`` cannot be copy-constructed or assigned.

Members
-------

.. code:: cpp

   namespace tbb {
                  class task_list {
                   public:
                       task_list();
                       ~task_list();
                       bool empty() const;
                       void push_back( task& task );
                       task& pop_front();
                       void clear();
                   };
               } 

The following table provides additional information on the
members of this template class.

= ========================================================================================
\ Member, Description
==========================================================================================
\ ``task_list()``
  \
  Constructs an empty list.
------------------------------------------------------------------------------------------
\ ``~task_list()``
  \
  Destroys the list. Does not destroy the task objects.
------------------------------------------------------------------------------------------
\ ``bool empty() const``
  \
  **Returns**: True if list is empty; false otherwise.
------------------------------------------------------------------------------------------
\ ``push_back( task& task )``
  \
  Inserts a reference to 
  *task* at back of the list.
------------------------------------------------------------------------------------------
\ ``task& task pop_front()``
  \
  Removes a 
  *task* reference from front of list.
  
  **Returns**: The reference that was removed.
------------------------------------------------------------------------------------------
\ ``void clear()``
  \
  Removes all 
  *task* references from the list. Does not destroy the
  task objects.
------------------------------------------------------------------------------------------
= ========================================================================================


See also:

* :doc:`Synchronization, static void spawn ( task_list& list ) <task_cls/synchronization_task>`
