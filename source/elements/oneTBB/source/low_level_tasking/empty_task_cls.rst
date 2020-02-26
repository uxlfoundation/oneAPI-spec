================
empty_task Class
================


Summary
-------

Subclass of *task* that represents doing nothing.

Syntax
------

.. code:: cpp

   class empty_task;


Header
------

.. code:: cpp

   #include "tbb/task.h"


Description
-----------

An ``empty_task`` is a task that does nothing. It is useful as a continuation of a parent task when the continuation should do nothing except wait for its predecessors to complete.

Members
-------

.. code:: cpp

    namespace tbb {
           class empty_task: public task {
               /*override*/ task* execute() {return NULL;}
           };  
    } 
