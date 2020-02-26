=======================
task_scheduler_observer
=======================


Summary
-------

Class that represents thread's interest in task scheduling services.

Syntax
------

.. code:: cpp

   class task_scheduler_observer;


Header
------

.. code:: cpp

   #include "tbb/task_scheduler_observer.h"


Description
-----------

A ``task_scheduler_observer`` permits clients to observe when a thread starts
and stops processing tasks, either globally or in a certain task scheduler arena. You typically
derive your own observer class from ``task_scheduler_observer``, and override
virtual methods ``on_scheduler_entry`` or ``on_scheduler_exit``.
Observation can be enabled and disabled for an observer instance; it is disabled on creation.
Remember to call ``observe()`` to enable observation.

.. caution::

   ``task_scheduler_observer`` is not suitable for floating-point settings management. Using it
   for this purpose will cause undefined behavior. See Section Floating-point Settings for more details.

.. caution::

   Exceptions thrown and not caught in the overridden methods of ``task_scheduler_observer``
   result in undefined behavior.


Members
-------

.. code:: cpp

   namespace tbb {
       class task_scheduler_observer {
       public:
           explicit task_scheduler_observer( bool local = false );
           explicit task_scheduler_observer( task_arena & a );
           virtual ~task_scheduler_observer();
           void observe( bool state=true );
           bool is_observing() const;
           virtual void on_scheduler_entry( bool is_worker ) {}
           virtual void on_scheduler_exit( bool is_worker } {}
       };
   }


Example
-------

The following example sketches the code of an observer that pins
TBB worker threads to hardware threads.

.. code:: cpp

   class pinning_observer: public tbb::task_scheduler_observer {
   public:
       affinity_mask_t m_mask; // HW affinity mask to be used for threads in an arena
       pinning_observer( tbb::task_arena &a, affinity_mask_t mask )
         : tbb::task_scheduler_observer(a), m_mask(mask) {
           observe(true); // activate the observer
       }
       /*override*/ void on_scheduler_entry( bool worker ) {
           set_thread_affinity(tbb::this_task_arena::current_thread_index(), m_mask);
       }
       /*override*/ void on_scheduler_exit( bool worker ) { }
   };


See also:

* :doc:`Floating-point Settings <fpu_settings>`

.. toctree::

   task_scheduler_observer/task_scheduler_observer_member.rst
