===================
spin_rw_mutex Class
===================


Summary
-------

Class that models ReaderWriterMutex Concept that is unfair and not scalable.

Syntax
------

.. code:: cpp

   class spin_rw_mutex;


Header
------

.. code:: cpp

   #include "tbb/spin_rw_mutex.h"


Description
-----------

A ``spin_rw_mutex`` models the ReaderWriterMutex Concept. A ``spin_rw_mutex`` is not scalable, fair, or recursive. It is ideal when the lock is lightly contended and is held for only a few machine instructions. If a thread has to wait to acquire a ``spin_rw_mutex``, it busy waits, which can degrade system performance if the wait is long. However, if the wait is typically short, a ``spin_rw_mutex`` significantly improves performance compared to other mutexes..

Members
-------

See ReaderWriterMutex concept.

See also:

* :doc:`ReaderWriterMutex Concept <readerwritermutex_concept>`
