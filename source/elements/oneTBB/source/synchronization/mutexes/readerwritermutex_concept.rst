=========================
ReaderWriterMutex Concept
=========================

The ReaderWriterMutex concept extends the Mutex
Concept to include the notion of reader-writer locks. It introduces a boolean
parameter
``write`` that specifies whether a writer lock
(``write`` =true) or reader lock (``write`` =false)
is being requested. Multiple reader locks can be held simultaneously on a
ReaderWriterMutex if it does not have a writer lock on it. A writer lock on a
ReaderWriterMutex excludes all other threads from holding a lock on the mutex
at the same time.

The following table shows the requirements for a
ReaderWriterMutex
``RW``. They form a superset of the Mutex Concept.

= ========================================================================================
\ ReaderWriterMutex Concept: Pseudo-Signature, Semantics
==========================================================================================
\ ``RW()``
  \
  Construct unlocked mutex.
------------------------------------------------------------------------------------------
\ ``~RW()``
  \
  Destroy unlocked mutex. The effect of destroying
  a locked mutex is undefined.
------------------------------------------------------------------------------------------
\ ``typename RW::scoped_lock``
  \
  Corresponding scoped-lock type.
------------------------------------------------------------------------------------------
\ ``RW::scoped_lock()``
  \
  Construct lock without acquiring any mutex.
------------------------------------------------------------------------------------------
\ ``RW::scoped_lock(RW&, bool write=true)``
  \
  Construct lock and acquire lock on a given mutex.
  The lock is a writer lock if ``write`` is true; a reader lock otherwise.
------------------------------------------------------------------------------------------
\ ``RW::~scoped_lock()``
  \
  Release lock (if acquired).
------------------------------------------------------------------------------------------
\ ``RW::scoped_lock::acquire(RW&,bool write=true)``
  \
  Acquire lock on a given mutex.
  The lock is a writer lock if ``write`` is true; a reader lock otherwise.
------------------------------------------------------------------------------------------
\ ``bool RW::scoped_lock::try_acquire(RW&, bool write=true)``
  \
  Try to acquire lock on a given mutex. The lock is a writer lock
  if ``write`` is true; a reader lock otherwise. Return
  ``true`` if lock acquired, ``false`` otherwise.
------------------------------------------------------------------------------------------
\ ``RW::scoped_lock::release()``
  \
  Release lock. The effect is undefined if no lock is held.
------------------------------------------------------------------------------------------
\ ``bool RW::scoped_lock::upgrade_to_writer()``
  \
  Change reader lock to writer lock. Return ``false``
  if lock was released and reacquired. ``true`` otherwise, including if the lock
  was already a writer lock.
------------------------------------------------------------------------------------------
\ ``bool RW::scoped_lock::downgrade_to_reader()``
  \
  Change writer lock to reader lock. Return ``false``
  if lock was released and reacquired. ``true`` otherwise, including if the lock
  was already a reader lock.
------------------------------------------------------------------------------------------
\ ``static const bool RW::is_rw_mutex = true``
  \
  True.
------------------------------------------------------------------------------------------
\ ``static const bool RW::is_recursive_mutex``
  \
  True if mutex is recursive; false otherwise.
------------------------------------------------------------------------------------------
\ ``static const bool RW::is_fair_mutex``
  \
  True if mutex is fair; false otherwise.
------------------------------------------------------------------------------------------
= ========================================================================================

Classes ``spin_rw_mutex``, ``speculative_spin_rw_mutex``
and ``queuing_rw_mutex`` model the ReaderWriterMutex concept.

.. note::

   For all currently provided reader-writer mutexes,
   
   * ``is_recursive_mutex`` is ``false``;
   * ``scoped_lock::downgrade_to_reader`` always returns ``true``.
   
   
   However, other implementations of the ReaderWriterMutex concept are not required to do the same.
