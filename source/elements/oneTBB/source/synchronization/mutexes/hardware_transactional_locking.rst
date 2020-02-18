================================================
Speculative locking (Transactional Lock Elision)
================================================

On processors that support hardware transaction memory
(such as Intel® Transactional Synchronization Extensions (Intel® TSX))
speculative mutexes work by letting multiple threads acquire the same lock, as
long as there are no "conflicts" that may generate different results than
non-speculative locking.  The exact notion of a "conflict" depends on the hardware,
and typically means accessing the same cache line where one of the accesses
modifies the cache line.

On processors that do not support hardware transactional memory, speculative mutexes
behave like their non-speculating counterparts, but possibly with worse performance.

On Intel® processors, speculative mutexes use Intel TSX if available.
General guidance for speculative locking on such processors is:

* The protected critical sections should not conflict at cache-line granularity.
* The protected critical section should be short enough to not be affected by
  an interrupt or context switch.
* The protected critical section should not perform a system call.
* The protected critical section should not touch more data than fits in L1 cache.
* There may be a nesting limit for speculation.

Careful performance comparison with a non-speculative alternative is recommended.

For more guidance and examples about using Intel TSX effectively, see the
*Intel® 64 and IA-32 Architectures Optimization Reference Manual*, Chapter 12.

References
----------

`*Intel® 64 and IA-32 Architectures Optimization Reference Manual*, Order Number 248966-027, June 2013 <http://www.intel.com/content/dam/www/public/us/en/documents/manuals/64-ia-32-architectures-optimization-manual.pdf>`_
, Chapter 12.

See also:

* :doc:`Mutex Concept <mutex_concept>`
* :doc:`speculative_spin_mutex <speculative_spin_mutex_cls>`
* :doc:`speculative_spin_rw_mutex <speculative_spin_rw_mutex_cls>`
