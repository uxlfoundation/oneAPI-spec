===============================
speculative_spin_rw_mutex Class
===============================


Summary
-------

Class that models ReaderWriterMutex Concept, and for processors which
support hardware transactional memory (such as Intel® Transactional
Synchronization Extensions (Intel® TSX)) may be implemented in a
way that allows non-contending changes to the protected data to proceed
in parallel.

Syntax
------

.. code:: cpp

   class speculative_spin_rw_mutex;


Header
------

.. code:: cpp

   #include "tbb/spin_rw_mutex.h"


Description
-----------

A ``speculative_spin_rw_mutex`` models the ReaderWriterMutex Concept.  It is not
fair and not recursive.  A ``speculative_spin_rw_mutex`` is like a
``spin_rw_mutex``, but it may provide better throughput than
non-speculative mutexes when the following conditions are met:

* Running on a processor that supports hardware transactional memory, *and*
* multiple threads can concurrently execute the critical section(s) protected by
  the mutex, mostly without conflicting.

Otherwise it performs like a ``spin_rw_mutex``, possibly with
worse throughput.

Please see the Speculative locking section for more details.

For processors that support Intel TSX, ``speculative_spin_rw_mutex``
is implemented in a way such that

* speculative readers and writers do not block each other;
* a non-speculative reader blocks writers but allows speculative readers;
* a non-speculative writer blocks all readers and writers.


.. caution::

   The ``speculative_spin_rw_mutex`` is padded to ensure each instance appears on
   a separate cache line not shared with any other data.  Because of that the size of the
   mutex is three times the cache line size.


References
----------

`*Intel® 64 and IA-32 Architectures Optimization Reference Manual*, Order Number 248966-027, June 2013 <http://www.intel.com/content/dam/www/public/us/en/documents/manuals/64-ia-32-architectures-optimization-manual.pdf>`_
, Chapter 12.

Members
-------

See ReaderWriterMutex Concept.

See also:

* :doc:`ReaderWriterMutex Concept <readerwritermutex_concept>`
* :doc:`Speculative locking (Transactional Lock Elision) <hardware_transactional_locking>`
* :doc:`spin_rw_mutex <spin_rw_mutex_cls>`
