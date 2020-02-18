===================
Specific Exceptions
===================


Summary
-------

Exceptions thrown by other library components.

Syntax
------

.. code:: cpp

   class bad_last_alloc;
   class invalid_multiple_scheduling;
   class user_abort;
   class missing_wait;


Header
------

.. code:: cpp

   #include "tbb/tbb_exception.h"


Description
-----------

The table below describes when the exceptions are thrown.

Classes for Specific Exceptions.

=========================== =====================================================
**Exception**               **Thrown when...**
=========================== =====================================================
bad_last_alloc              * A ``pop`` operation on a ``concurrent_queue`` or 
                              ``concurrent_bounded_queue`` corrersponds to a
                              push that threw an exception.
                            * An operation on a ``concurrent_vector``
                              cannot be performed because a prior
                              operation threw an exception.
--------------------------- -----------------------------------------------------
invalid_multiple_scheduling A ``task_group`` or ``structured_task_group``
                            attempts to run a ``task_handle`` twice.
--------------------------- -----------------------------------------------------
missing_wait                A ``task_group`` or ``structured_task_group``
                            is destroyed before method ``wait()`` is invoked.
--------------------------- -----------------------------------------------------
user_abort                  A ``push`` or ``pop`` operation on a 
                            ``concurrent_bounded_queue`` was aborted by the user.
=========================== =====================================================


Members
-------

.. code:: cpp

   namespace tbb {
           class bad_last_alloc: public std::bad_alloc {
           public:
               const char* what() const throw();
           };
   
           class invalid_multiple_scheduler: public std::exception {
              const char* what() const throw();
           };
   
           class missing_wait: public std::exception {
           public:
               const char* what() const throw();
           };

           class user_abort: public std::exception {
           public:
              const char* what() const throw();
           };
   		  
       }
