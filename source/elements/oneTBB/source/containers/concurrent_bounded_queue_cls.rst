=======================================
concurrent_bounded_queue Template Class
=======================================


Summary
-------

Template class for bounded dual queue with
concurrent operations.

Syntax
------

.. code:: cpp

   template<typename T, class Alloc=cache_aligned_allocator<T> >
               class concurrent_bounded_queue;


Header
------

.. code:: cpp

   #include "tbb/concurrent_queue.h"


Description
-----------

A 
``concurrent_bounded_queue`` is similar to a 
``concurrent_queue`` , but with the following differences:

* Adds the ability to specify a capacity. The
  default capacity makes the queue practically unbounded.
* Changes the 
  ``push`` operation so that it waits until it can
  complete without exceeding the capacity.
* Adds a waiting 
  ``pop`` operation that waits until it can pop an item.
* Changes the 
  ``size_type`` to a 
  *signed* type.
* Changes the 
  ``size()`` operation to return the number of push
  operations minus the number of pop operations. For example, if there are 3 pop
  operations waiting on an empty queue, 
  ``size()`` returns -3.
* Adds an 
  ``abort`` operation that causes any waiting 
  ``push`` or 
  ``pop`` operation to abort and throw an exception.


Members
-------

To aid comparison, the parts that differ from 
``concurrent_queue`` are in bold and annotated.

.. code:: cpp

   namespace tbb {
              template<typename T, typename A=cache_aligned_allocator<T> >
              class concurrent_bounded_queue {
              public:
                  // types
                  typedef T value_type;
                  typedef A allocator_type;
                  typedef T& reference;
                  typedef const T& const_reference;
                  // size_type is signed type
                  typedef std::ptrdiff_t size_type;
                  typedef std::ptrdiff_t difference_type;
   
                  explicit concurrent_bounded_queue(const allocator_type& a = allocator_type());
                  concurrent_bounded_queue( const concurrent_bounded_queue& src, const allocator_type& a = allocator_type());
                  template<typename InputIterator>
                  concurrent_bounded_queue( InputIterator begin, InputIterator end, const allocator_type& a = allocator_type());
                  // Supported since C++11
                  concurrent_bounded_queue( concurrent_bounded_queue&& src );
                  concurrent_bounded_queue( concurrent_bounded_queue&& src, const allocator_type& a );
   
                  ~concurrent_bounded_queue();
   
                  // waits until it can push without exceeding capacity.
                  void push( const T& source );
                  // waits if *this is empty
                  void pop( T& destination );
                  // Supported since C++11
                  void push( T&& source );
                  // the same as push except that the item is constructed with given arguments.
                  template<typename... Arguments>
                  void emplace(Arguments&&... args);
   
                  // skips push if it would exceed capacity.
                  bool try_push( const T& source );
                  bool try_pop( T& destination );
                  // Supported since C++11
                  bool try_push( T&& source );
                  // the same as try_push except that the item is constructed with given arguments.
                  template<typename... Arguments>
                  bool try_emplace(Arguments&&... args);
   
                  void abort();
                  void clear();
   
                  // safe to call during concurrent modification, can return negative size.
                  size_type size() const;
                  bool empty() const;
                  size_type capacity() const;
                  void set_capacity( size_type capacity );
                  allocator_type get_allocator() const;
   
                  typedef implementation-defined iterator;
                  typedef implementation-defined const_iterator;
   
                  // iterators (these are slow an intended only for debugging)
                  iterator unsafe_begin();
                  iterator unsafe_end();
                  const_iterator unsafe_begin() const;
                  const_iterator unsafe_end() const;
           };
       }


Because 
``concurrent_bounded_queue`` is similar to 
``concurrent_queue``, the following table describes only
methods that differ.

= ========================================================================================
\ Member, Description
==========================================================================================
\ ``void push( const T& source )``
  \
  Waits until size()<capacity, and then pushes a copy of
  source onto back of the queue.
------------------------------------------------------------------------------------------
\ ``void push( T&& source)``
  \
  Supported since C++11. Waits until size()<capacity, and then moves source
  onto back of the queue.
------------------------------------------------------------------------------------------
\ ``template<typename... Arguments> void emplace(Arguments&&... args);``
  \
  Supported since C++11. Waits until size()<capacity, and then pushes
  a new element into the queue. The element is constructed with given
  arguments.
------------------------------------------------------------------------------------------
\ ``void pop( T& destination )``
  \
  Waits until a value becomes available and pops it from the
  queue. Assigns it to destination. Destroys the original value.
------------------------------------------------------------------------------------------
\ ``void abort()``
  \
  Wakes up any threads that are waiting on the queue via the 
  ``push`` and 
  ``pop`` operations and raises the 
  ``tbb::user_abort`` exception on those threads.
  This feature is unavailable if 
  ``TBB_USE_EXCEPTIONS`` is not set.
------------------------------------------------------------------------------------------
\ ``bool try_push( const T& source )``
  \
  If size()<capacity, pushes a copy of source onto back of
  the queue.
  
  **Returns**: True if a copy was pushed; false otherwise.
------------------------------------------------------------------------------------------
\ ``bool try_push( T&& source )``
  \
  Supported since C++11. If size()<capacity, moves source onto back of the queue.
  
  **Returns**: True if an item was moved; false otherwise.
------------------------------------------------------------------------------------------
\ ``template<typename... Arguments> bool try_emplace(Arguments&&... args);``
  \
  Supported since C++11. If size()<capacity, constructs an item
  with given arguments and moves it onto back of the queue.
  
  **Returns**: True if an item was moved; false otherwise.
------------------------------------------------------------------------------------------
\ ``bool try_pop( T& destination )``
  \
  If a value is available, pops it from the queue, assigns it
  to destination, and destroys the original value. Otherwise does nothing.
  
  **Returns**: True if a value was popped; false otherwise.
------------------------------------------------------------------------------------------
\ ``size_type size() const``
  \
  **Returns**: Number of pushes minus number of pops. The
  result is negative if there are pop operations waiting for corresponding
  pushes. The result can exceed capacity() if the queue is full and there are
  push operations waiting for corresponding pops.
------------------------------------------------------------------------------------------
\ ``bool empty() const``
  \
  **Returns**: 
  ``size()<=0``
------------------------------------------------------------------------------------------
\ ``size_type capacity() const``
  \
  **Returns**
  
  Maximum number of values that the queue can hold.
------------------------------------------------------------------------------------------
\ ``void set_capacity( size_type capacity )``
  \
  Sets the maximum number of values that the queue can hold.
------------------------------------------------------------------------------------------
= ========================================================================================


See also:

* :doc:`concurrent_queue <concurrent_queue_cls>`
