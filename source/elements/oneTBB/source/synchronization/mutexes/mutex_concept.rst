=============
Mutex Concept
=============

The mutexes and locks here have relatively spartan interfaces that are
designed for high performance. The interfaces enforce the 
*scoped locking pattern*, which is widely used in C++ libraries
because:

* Does not require the programmer to remember to release the lock
* Releases the lock if  an exception is thrown out of the mutual
  exclusion region protected by the lock

There are two parts to the pattern: a 
*mutex* object, for which construction of a 
*lock* object acquires a lock on the mutex and destruction of the 
*lock* object releases the lock. Here's an example:

.. code:: cpp

   {
       // Construction of myLock acquires lock on myMutex 
       M::scoped_lock myLock( myMutex );
       // ... actions to be performed while holding the lock ...
       // Destruction of myLock releases lock on myMutex
   }

If the actions throw an exception, the lock is automatically released
as the block is exited.

The following table shows the requirements for the Mutex concept for a
mutex type M.

= ========================================================================================
\ Mutex Concept: Pseudo-Signature, Semantics
==========================================================================================
\ ``M()``
  \
  Construct unlocked mutex.
------------------------------------------------------------------------------------------
\ ``~M()``
  \
  Destroy unlocked mutex.
------------------------------------------------------------------------------------------
\ ``typename M::scoped_lock``
  \
  Corresponding scoped-lock type.
------------------------------------------------------------------------------------------
\ ``M::scoped_lock()``
  \
  Construct lock without acquiring mutex.
------------------------------------------------------------------------------------------
\ ``M::scoped_lock(M&)``
  \
  Construct lock and acquire lock on mutex.
------------------------------------------------------------------------------------------
\ ``M::~scoped_lock()``
  \
  Release lock (if acquired).
------------------------------------------------------------------------------------------
\ ``M::scoped_lock::acquire(M&)``
  \
  Acquire lock on mutex.
------------------------------------------------------------------------------------------
\ ``bool M::scoped_lock::try_acquire(M&)``
  \
  Try to acquire lock on mutex. Return true if lock acquired,
  false otherwise.
------------------------------------------------------------------------------------------
\ ``M::scoped_lock::release()``
  \
  Release lock.
------------------------------------------------------------------------------------------
\ ``static const bool M::is_rw_mutex``
  \
  True if mutex is reader-writer mutex; false otherwise.
------------------------------------------------------------------------------------------
\ ``static const bool M::is_recursive_mutex``
  \
  True if mutex is recursive mutex; false otherwise.
------------------------------------------------------------------------------------------
\ ``static const bool M::is_fair_mutex``
  \
  True if mutex is fair; false otherwise.
------------------------------------------------------------------------------------------
= ========================================================================================

A mutex type and an ``M::scoped_lock`` type are neither
copyable nor movable.

The following table summarizes the classes that model the Mutex
concept.

.. table:: Mutexes that Model the Mutex Concept

   ============================= ============ ============ ============= ============= ==============================
   .                             **Scalable** **Fair**     **Reentrant** **Long Wait** **Size**
   ============================= ============ ============ ============= ============= ==============================
   ``mutex``                     OS dependent OS dependent No            Blocks        >=3 words
   ----------------------------- ------------ ------------ ------------- ------------- ------------------------------
   ``recursive_mutex``           OS dependent OS dependent Yes           Blocks        >=3 words
   ----------------------------- ------------ ------------ ------------- ------------- ------------------------------
   ``spin_mutex``                No           No           No            Yields        1 byte
   ----------------------------- ------------ ------------ ------------- ------------- ------------------------------
   ``speculative_spin_mutex``    HW dependent No           No            Yields        2 cache lines
   ----------------------------- ------------ ------------ ------------- ------------- ------------------------------
   ``queuing_mutex``             Yes          Yes          No            Yields        1 word
   ----------------------------- ------------ ------------ ------------- ------------- ------------------------------
   ``spin_rw_mutex``             No           No           No            Yields        1 word
   ----------------------------- ------------ ------------ ------------- ------------- ------------------------------
   ``speculative_spin_rw_mutex`` HW dependent No           No            Yields        3 cache lines
   ----------------------------- ------------ ------------ ------------- ------------- ------------------------------
   ``queuing_rw_mutex``          Yes          Yes          No            Yields        1 word
   ----------------------------- ------------ ------------ ------------- ------------- ------------------------------
   ``null_mutex``                -            Yes          Yes           -             empty
   ----------------------------- ------------ ------------ ------------- ------------- ------------------------------
   ``null_rw_mutex``             -            Yes          Yes           -             empty
   ============================= ============ ============ ============= ============= ==============================

See the oneAPI Threading Building Blocks Developer Guide for a discussion of
the mutex properties and the rationale for null mutexes.

C++11 Compatibility
-------------------

Classes 
``mutex, recursive_mutex, spin_mutex,`` and 
``spin_rw_mutex`` support the C++11 interfaces
described in the following table.

= ========================================================================================
\ C++11 Methods Available for Some Mutexes: Pseudo-Signature, Semantics
==========================================================================================
\ ``void M::lock()``
  \
  Acquire lock.
------------------------------------------------------------------------------------------
\ ``bool M::try_lock()``
  \
  Try to acquire lock on mutex. Return true if lock acquired,
  false otherwise.
------------------------------------------------------------------------------------------
\ ``void M::unlock()``
  \
  Release lock.
------------------------------------------------------------------------------------------
\ ``class lock_guard<M>``
  \
  See Section C++11 Synchronization
------------------------------------------------------------------------------------------
\ ``class unique_lock<M>``
  \
  
------------------------------------------------------------------------------------------
= ========================================================================================

Classes mutex and recursive mutex also provide the C++11 idiom for
accessing their underlying OS handles, as described in the following table.

Native handle interface (M is mutex or recursive_mutex).

= ========================================================================================
\ Native handle interface: Pseudo-Signature, Semantics
==========================================================================================
\ ``M::native_handle_type``
  \
  Native handle type.
  
  For Windows* operating system, LPCRITICAL_SECTION is the
  Native handle type.
  
  For all other operating system, it is (pthread_mutex*).
------------------------------------------------------------------------------------------
\ ``native_handle_type M::native_handle()``
  \
  Get underlying native handle of mutex M.
------------------------------------------------------------------------------------------
= ========================================================================================

As an extension to C++11, class 
``spin_rw_mutex`` also has methods 
``read_lock()`` and 
``try_read_lock()`` for corresponding operations that
acquire reader locks.

