==========
null_mutex
==========
**[mutex.null_mutex]**

A ``null_mutex`` is a class that models the :doc:`Mutex requirement <../named_requirements/mutexes/mutex>` concept syntactically, but does nothing.
It is useful for instantiating a template that expects a Mutex, but no mutual exclusion is actually needed for that instance.

.. code:: cpp

    // Defined in header <tbb/null_mutex.h>

    namespace tbb {
        class null_mutex {
        public:
            constexpr null_mutex() noexcept;
            ~null_mutex();

            null_mutex(const null_mutex&) = delete;
            null_mutex& operator=(const null_mutex&) = delete;

            class scoped_lock;

            void lock();
            bool try_lock();
            void unlock();

            static constexpr bool is_rw_mutex = false;
            static constexpr bool is_recursive_mutex = true;
            static constexpr bool is_fair_mutex = true;
        };
    }

Member classes
--------------

.. cpp:class:: scoped_lock

    Corresponding ``scoped_lock`` class. See the :doc:`Mutex requirement <../named_requirements/mutexes/mutex>`.

Member functions
----------------

.. cpp:function:: null_mutex()

    Construct unlocked mutex.

.. cpp:function:: ~null_mutex()

    Destroy unlocked mutex.

.. cpp:function:: void lock()

    Acquire lock.

.. cpp:function:: bool try_lock()

    Try acquiring lock (non-blocking)

.. cpp:function:: void unlock()

    Release the lock.

