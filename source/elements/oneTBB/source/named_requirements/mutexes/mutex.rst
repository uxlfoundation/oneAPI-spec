=====
Mutex
=====
**[req.mutex]**

The mutexes and locks here have relatively spartan interfaces that are designed for high performance.
The interfaces enforce the *scoped locking pattern*, which is widely used in C++ libraries because:

* Does not require the programmer to remember to release the lock
* Releases the lock if an exception is thrown out of the mutual exclusion region protected by the lock

There are two parts to the pattern: a *mutex* object, for which construction of a *lock* object acquires a lock on the mutex
and destruction of the *lock* object releases the lock. Here's an example:

.. code:: cpp

   {
       // Construction of myLock acquires lock on myMutex
       M::scoped_lock myLock( myMutex );
       // ... actions to be performed while holding the lock ...
       // Destruction of myLock releases lock on myMutex
   }

If the actions throw an exception, the lock is automatically released as the block is exited.

.. code:: cpp

    class M {
        // Implementation specifics
        // ...

        // Represents acquisition of a mutex
        class scoped_lock {
        public:
            constexpr scoped_lock() noexcept;
            scoped_lock(M& m);
            ~scoped_lock();

            scoped_lock(const scoped_lock&) = delete;
            scoped_lock& operator=(const scoped_lock&) = delete;

            void acquire(M& m);
            bool try_acquire(M& m);
            void release();
        };
    };

A type `M` satisfies the `Mutex` if it meets the following requirements:

.. cpp:type:: M::scoped_lock

    Corresponding scoped lock type.

.. cpp:function:: M::scoped_lock()

    Construct ``scoped_lock`` without acquiring mutex.

.. cpp:function:: M::scoped_lock(M&)

    Construct ``scoped_lock`` and acquire the lock on a provided mutex.

.. cpp:function:: M::~scoped_lock()

    Releases a lock (if acquired).

.. cpp:function:: void M::scoped_lock::acquire(M&)

    Acquire a lock on a provided mutex.

.. cpp:function:: bool M::scoped_lock::try_acquire(M&)

    Attempts to acquire a lock on a provided mutex. Returns true if the lock is acquired, false otherwise.

.. cpp:function:: void M::scoped_lock::release()

    Releases an acquired lock.

Also, the ``Mutex`` type requires a set of traits to be defined:

.. cpp:member:: static constexpr bool M::is_rw_mutex

    True if mutex is reader-writer mutex; false otherwise.

.. cpp:member:: static constexpr bool M::is_recursive_mutex

    True if mutex is recursive mutex; false otherwise.

.. cpp:member:: static constexpr bool M::is_fair_mutex

    True if mutex is fair; false otherwise.

A mutex type and an ``M::scoped_lock`` type are neither copyable nor movable.

The following table summarizes the library classes that model the ``Mutex`` requirement and provided qurantees.

.. table:: Provided gurantees for Mutexes that model the Mutex requirement

   ============================= ============ =============
   .                             **Fair**     **Reentrant**
   ============================= ============ =============
   ``spin_mutex``                No           No
   ----------------------------- ------------ -------------
   ``speculative_spin_mutex``    No           No
   ----------------------------- ------------ -------------
   ``queuing_mutex``             Yes          No
   ----------------------------- ------------ -------------
   ``null_mutex``                Yes          Yes
   ============================= ============ =============

.. note::

    Implementation is alowed to have an opposite gurantees (positive) in case of negative statements from the table above.

See the oneAPI Threading Building Blocks Developer Guide for a discussion of the mutex properties and the rationale for null mutexes.

See also:

* :doc:`spin_mutex <../../mutual_exclusion/spin_mutex_cls>`
* :doc:`speculative_spin_mutex <../../mutual_exclusion/speculative_spin_mutex_cls>`
* :doc:`queuing_mutex <../../mutual_exclusion/queuing_mutex_cls>`
* :doc:`null_mutex <../../mutual_exclusion/null_mutex_cls>`

