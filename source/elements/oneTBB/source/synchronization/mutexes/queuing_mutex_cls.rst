===================
queuing_mutex Class
===================


Summary
-------

Class that models Mutex Concept that is fair and scalable.

Syntax
------

.. code:: cpp

   class queuing_mutex;


Header
------

.. code:: cpp

   #include "tbb/queuing_mutex.h"


Description
-----------

A ``queuing_mutex`` models the Mutex Concept. A
``queuing_mutex`` is scalable, in the sense that if a thread has to
wait to acquire the mutex, it spins on its own local cache line. A
``queuing_mutex`` is fair. Threads acquire a lock on a mutex in the
order that they request it. A ``queuing_mutex`` is not recursive.

The current implementation does busy-waiting, so using a ``queuing_mutex`` may degrade system performance if the wait is long.

Members
-------

See Mutex Concept.

See also:

* :doc:`Mutex Concept <mutex_concept>`
