======================
queuing_rw_mutex Class
======================


Summary
-------

Class that models ReaderWriterMutex Concept that is fair and scalable.

Syntax
------

.. code:: cpp

   class queuing_rw_mutex;


Header
------

.. code:: cpp

   #include "tbb/queuing_rw_mutex.h"


Description
-----------

A ``queuing_rw_mutex`` models the ReaderWriterMutex Concept. A ``queuing_rw_mutex`` is scalable, in the sense that if a thread has to wait to acquire the mutex, it spins on its own local cache line. A ``queuing_rw_mutex`` is fair. Threads acquire a lock on a ``queuing_rw_mutex`` in the order that they request it. A queuing_rw_mutex is not recursive.

Members
-------

See ReaderWriterMutex concept.

See also:

* :doc:`ReaderWriterMutex Concept <readerwritermutex_concept>`
