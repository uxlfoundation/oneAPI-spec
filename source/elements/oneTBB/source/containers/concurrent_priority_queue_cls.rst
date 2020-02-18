========================================
concurrent_priority_queue Template Class
========================================


Summary
-------

Template class for priority queue with concurrent operations.

Syntax
------


.. code:: cpp

   template<typename T, typename Alloc = cache_aligned_allocator<T> >
   class concurrent_priority_queue;


Header
------


.. code:: cpp

   #include "tbb/concurrent_priority_queue.h"


Description
-----------

A ``concurrent_priority_queue`` is a container that permits multiple threads to
concurrently push and pop items. Items are popped in priority order as determined by a
template parameter. The capacity of the queue is unbounded, subject to memory limitations on
the target machine.

The interface is similar to STL ``std::priority_queue`` except where it must
differ to make concurrent modification safe.

.. table:: Differences Between STL queue and oneAPI Threading Building Blocks concurrent_priority_queue

   ================================= ==================================================== ==============================
   Feature                           STL std::priority_queue                              concurrent_priority_queue
   ================================= ==================================================== ==============================
   Choice of underlying container    Sequence template parameter                          No choice of underlying container; allocator choice is provided instead
   --------------------------------- ---------------------------------------------------- ------------------------------
   Access to highest priority item   ``const value_type& top() const``                    Not available. Unsafe for concurrent container
   --------------------------------- ---------------------------------------------------- ------------------------------
   Copy and pop item if present      ``bool b=!q.empty(); if(b) { x=q.top(); q.pop(); }`` ``bool b = q.try_pop(x);``
   --------------------------------- ---------------------------------------------------- ------------------------------
   Get number of items in queue      ``size_type size() const``                           Same, but may be inaccurate due to pending concurrent push or pop operations
   --------------------------------- ---------------------------------------------------- ------------------------------
   Check if there are items in queue ``bool empty() const``                               Same, but may be inaccurate due to pending concurrent push or pop operations
   ================================= ==================================================== ==============================


Members
-------

.. code:: cpp

   namespace tbb {
       template <typename T, typename Compare=std::less<T>,
                    typename A=cache_aligned_allocator<T> >
       class concurrent_priority_queue {
       public:
           typedef T value_type;
           typedef T& reference;
           typedef const T& const_reference;
           typedef size_t size_type;
           typedef ptrdiff_t difference_type;
           typedef A allocator_type;
   
           // Constructors
           concurrent_priority_queue(const allocator_type& a = allocator_type());
           concurrent_priority_queue(const Compare& c, allocator_type& a = allocator_type());
           concurrent_priority_queue(size_type init_capacity,
                                     const allocator_type& a = allocator_type());
           concurrent_priority_queue(size_type init_capacity, const Compare& c, 
                                     const allocator_type& a = allocator_type());
           template<typename InputIterator>
           concurrent_priority_queue(InputIterator begin, InputIterator end,
                                     const allocator_type& a = allocator_type());
           template<typename InputIterator>
           concurrent_priority_queue(InputIterator begin, InputIterator end,
                                     const Compare& c, const allocator_type& a = allocator_type());
           concurrent_priority_queue(const concurrent_priority_queue& src,
                                     const allocator_type& a = allocator_type());
           // Supported since C++11
           concurrent_priority_queue(concurrent_priority_queue&& src);
           concurrent_priority_queue(concurrent_priority_queue&& src,
                                     const allocator_type& a);
           concurrent_priority_queue(std::initializer_list<T> il,
                                     const allocator_type &a = allocator_type());
           concurrent_priority_queue(std::initializer_list<T> il,
                                     const Compare& c, const allocator_type &a = allocator_type());
   
           // Assignment
           concurrent_priority_queue& operator=(const concurrent_priority_queue& src);
           template<typename InputIterator>
           void assign(InputIterator begin, InputIterator end);
           // Supported since C++11
           concurrent_priority_queue& operator=(concurrent_priority_queue&& src);
           concurrent_priority_queue& operator=(std::initializer_list<T> il);
           void assign(std::initializer_list<T> il);
   
           void swap(concurrent_priority_queue& other);
   
           ~concurrent_priority_queue();
   
           allocator_type get_allocator() const;
   
           bool empty() const;
           size_type size() const;
   
           void push(const_reference elem);
           // Supported since C++11
           void push(T&& elem);
           template<typename... Args>
           void emplace(Args&&... args);
   
           bool try_pop(reference elem);
   
           void clear();
       };
   }

Where possible, constructors of ``concurrent_priority_queue`` support class template argument deduction for C++17. For example

.. code:: cpp

   std::vector<int> v = {0, 1, 2};
   tbb::concurrent_priority_queue pq(v.begin(), v.end);

declares ``pq`` as ``tbb::concurrent_priority_queue<int, tbb::cache_aligned_allocator<int>>``.

The following table provides additional information on the members of this template class.

= ========================================================================================
\ Member, Description
==========================================================================================
\ Constructors
  \
  ``concurrent_priority_queue(const allocator_type& a = allocator_type())``
  
  ``concurrent_priority_queue(const Compare& c, const allocator_type& a = allocator_type())``

  Constructs an empty queue.
------------------------------------------------------------------------------------------
\ Capacity constructors
  \
  ``concurrent_priority_queue(size_type init_capacity, const allocator_type& a = allocator_type())``
  
  ``concurrent_priority_queue(size_type init_capacity, const Compare& c, const allocator_type& a = allocator_type())``

  Constructs an empty queue with the specified initial capacity.
------------------------------------------------------------------------------------------
\ Constructors from a sequence
  \
  ``template <typename InputIterator> concurrent_priority_queue(InputIterator begin, InputIterator end, const allocator_type& a = allocator_type())``
  
  ``template <typename InputIterator> concurrent_priority_queue(InputIterator begin, InputIterator end, const Compare& c, const allocator_type& a = allocator_type())``

  Constructs a queue containing copies of elements in the iterator half-open
  interval ``[begin, end)``.
------------------------------------------------------------------------------------------
\ Constructors from an ``initializer_list``
  \
  ``concurrent_priority_queue(std::initializer_list<T> il, const allocator_type &a = allocator_type())``
  
  ``concurrent_priority_queue(std::initializer_list<T> il, const Compare& c, const allocator_type &a = allocator_type())``

  Supported since C++11. Equivalent to
  ``concurrent_priority_queue(il.begin(), il.end(), [c,] a)`` .
------------------------------------------------------------------------------------------
\ ``concurrent_priority_queue(const concurrent_priority_queue& src, const allocator_type& a = allocator_type())``
  \
  Constructs a copy of ``src``. This operation is not thread-safe and
  may result in an error or an invalid copy of ``src`` if another
  thread is concurrently modifying ``src.``
------------------------------------------------------------------------------------------
\ ``concurrent_priority_queue(concurrent_priority_queue&& src)``
  \
  Supported since C++11. Constructs a new queue by moving content from
  ``src``. ``src`` is left in an unspecified state, but
  can be safely destroyed. This operation is unsafe if there are pending concurrent
  operations on the ``src`` queue.
------------------------------------------------------------------------------------------
\ ``concurrent_priority_queue(concurrent_priority_queue&& src, const allocator_type& a)``
  \
  Supported since C++11. Constructs a new queue by moving content from ``src``
  using the allocator ``a``. ``src`` is left in an
  unspecified state, but can be safely destroyed. This operation is unsafe if there
  are pending concurrent operations on the ``src`` queue.
------------------------------------------------------------------------------------------
\ ``concurrent_priority_queue& operator=(const concurrent_priority_queue& src)``
  \
  Assigns contents of ``src`` to ``*this``. This operation
  is not thread-safe and may result in an error or an invalid copy of
  ``src`` if another thread is concurrently modifying
  ``src``.
  
  **Returns**: a reference to ``*this``.
------------------------------------------------------------------------------------------
\ ``concurrent_priority_queue& operator=(concurrent_priority_queue&& src);``
  \
  Supported since C++11. Moves data from ``src`` to
  ``*this``. ``src`` is left in an unspecified
  state, but can be safely destroyed. This operation is unsafe if there are pending
  concurrent operations on the ``src`` queue.
  
  **Returns**: a reference to ``*this``.
------------------------------------------------------------------------------------------
\ ``concurrent_priority_queue& operator=(std::initializer_list<T> il)``
  \
  Supported since C++11. Assigns contents of the initializer list ``il`` to
  ``*this``.
  
  **Returns**: a reference to ``*this``.
------------------------------------------------------------------------------------------
\ ``template <typename InputIterator> void assign(InputIterator begin, InputIterator end, const allocator_type&)``
  \
  Assigns contents of the iterator half-open interval ``[begin, end)``
  to ``*this``.
------------------------------------------------------------------------------------------
\ ``void assign(std::initializer_list<T> il)``
  \
  Supported since C++11. Equivalent to
  ``assign(il.begin(), il.end())`` .
------------------------------------------------------------------------------------------
\ ``~concurrent_priority_queue()``
  \
  Destroys all items in the queue, and the container itself, so that it can no
  longer be used.
------------------------------------------------------------------------------------------
\ ``bool empty() const``
  \
  **Returns**: ``true`` if queue has no items;
  ``false`` otherwise. May be inaccurate when concurrent
  ``push`` or ``try_pop`` operations are pending. This
  operation reads shared data and may trigger a race condition in race detection
  tools when used concurrently.
------------------------------------------------------------------------------------------
\ ``size_type size() const``
  \
  **Returns**: Number of items in the queue. May be inaccurate when concurrent
  ``push`` or ``try_pop`` operations are pending. This
  operation reads shared data and may trigger a race condition in race detection
  tools when used concurrently.
------------------------------------------------------------------------------------------
\ ``void push(const_reference elem)``
  \
  Pushes a copy of ``elem`` into the queue. This operation is
  thread-safe with other ``push``, ``try_pop`` and
  ``emplace`` operations.
------------------------------------------------------------------------------------------
\ ``void push(T&& elem)``
  \
  Supported since C++11. Pushes a given element into the queue using move constructor. This
  operation is thread-safe with other ``push``,
  ``try_pop`` and ``emplace`` operations.
------------------------------------------------------------------------------------------
\ ``template<typename... Args> void emplace(Args&&... args);``
  \
  Supported since C++11. Pushes a new element into the queue. The element is constructed
  with given arguments. This operation is thread-safe with other
  ``push``, ``try_pop`` and ``emplace``
  operations.
------------------------------------------------------------------------------------------
\ ``bool try_pop(reference elem)``
  \
  If the queue is not empty, copies the highest priority item from the queue and
  assigns it to ``elem``, and destroys the popped item in the queue;
  otherwise, does nothing. This operation is thread-safe with other
  ``push``, ``try_pop`` and ``emplace``
  operations.
  
  **Returns**: ``true`` if an item was popped;
  ``false`` otherwise.
------------------------------------------------------------------------------------------
\ ``void clear()``
  \
  Clears the queue; results in ``size()==0``. This operation is not
  thread-safe.
------------------------------------------------------------------------------------------
\ ``void swap(concurrent_priority_queue& other)``
  \
  Swaps the queue contents with those of other. This operation is not thread-safe.
------------------------------------------------------------------------------------------
\ ``allocator_type get_allocator() const``
  \
  **Returns**: A copy of allocator used to construct the queue.
------------------------------------------------------------------------------------------
= ========================================================================================
