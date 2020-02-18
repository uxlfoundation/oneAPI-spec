============================
speculative_spin_mutex Class
============================


Summary
-------

Class that models Mutex Concept using a spin lock, and for processors which
support hardware transactional memory (such as Intel® Transactional
Synchronization Extensions (Intel® TSX)) may be implemented in a
way that allows non-contending changes to the protected data to proceed
in parallel.

Syntax
------

.. code:: cpp

   class speculative_spin_mutex;


Header
------

.. code:: cpp

   #include "tbb/spin_mutex.h"


Description
-----------

A ``speculative_spin_mutex`` models the Mutex Concept.  It is not
fair and not recursive.  A ``speculative_spin_mutex`` is like a
``spin_mutex``, but it may provide better throughput than
non-speculative mutexes when the following conditions are met:

* Running on a processor that supports hardware transactional memory, *and*
* multiple threads can concurrently execute the critical section(s) protected by
  the mutex, mostly without conflicting.

Otherwise it performs like a ``spin_mutex``, possibly with
worse throughput.

Please see the Speculative locking section for more details.

.. caution::

   The ``speculative_spin_mutex`` is padded to ensure each instance appears on
   a separate cache line not shared with any other data.  Because of that the size of the
   mutex is twice the cache line size.


References
----------

`*Intel® 64 and IA-32 Architectures Optimization Reference Manual*, Order Number 248966-027, June 2013 <http://www.intel.com/content/dam/www/public/us/en/documents/manuals/64-ia-32-architectures-optimization-manual.pdf>`_
, Chapter 12.

Members
-------

See Mutex Concept.

See also:

* :doc:`Mutex Concept <mutex_concept>`
* :doc:`Speculative locking (Transactional Lock Elision) <hardware_transactional_locking>`
* :doc:`spin_mutex <spin_mutex_cls>`
