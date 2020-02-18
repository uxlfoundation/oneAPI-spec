================
spin_mutex Class
================


Summary
-------

Class that models Mutex Concept using a spin lock.

Syntax
------

.. code:: cpp

   class spin_mutex;


Header
------

.. code:: cpp

   #include "tbb/spin_mutex.h"


Description
-----------

A ``spin_mutex`` models the Mutex Concept. A ``spin_mutex`` is not scalable, fair, or recursive. It is ideal when the lock is lightly contended and is held for only a few machine instructions. If a thread has to wait to acquire a ``spin_mutex``, it busy waits, which can degrade system performance if the wait is long. However, if the wait is typically short, a ``spin_mutex`` significantly improve performance compared to other mutexes.

Members
-------

See Mutex Concept.

See also:

* :doc:`Mutex Concept <mutex_concept>`
