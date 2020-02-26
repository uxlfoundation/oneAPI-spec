=======
Mutexes
=======

Mutexes provide MUTual EXclusion of threads from sections of code.

In general, strive for designs that minimize the use of explicit locking, because it can lead to serial bottlenecks. If explicitly locking is necessary, try to spread it out so that multiple threads usually do not contend to lock the same mutex.

.. toctree::

   mutexes/mutex_concept.rst
   mutexes/hardware_transactional_locking.rst
   mutexes/spin_mutex_cls.rst
   mutexes/speculative_spin_mutex_cls.rst
   mutexes/queuing_mutex_cls.rst
   mutexes/readerwritermutex_concept.rst
   mutexes/spin_rw_mutex_cls.rst
   mutexes/speculative_spin_rw_mutex_cls.rst
   mutexes/queuing_rw_mutex_cls.rst
   mutexes/null_mutex_cls.rst
   mutexes/null_rw_mutex_cls.rst
