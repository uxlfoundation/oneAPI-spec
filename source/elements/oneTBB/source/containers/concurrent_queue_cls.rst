===============================
concurrent_queue Template Class
===============================


Summary
-------

Template class for a queue with concurrent operations.

Syntax
------


.. code:: cpp

   template<typename T, typename Alloc=cache_aligned_allocator<T> >
   class concurrent_queue;


Header
------


.. code:: cpp

   #include "tbb/concurrent_queue.h"


Description
-----------

A ``concurrent_queue`` is a first-in first-out data structure that permits
multiple threads to concurrently push and pop items. Its capacity is unbounded, subject to
memory limitations on the target machine.

The interface is similar to STL ``std::queue`` except where it must differ to
make concurrent modification safe.



.. table:: Differences Between STL queue and oneAPI Threading Building Blocks concurrent_queue

   =============================================== ================================================== ==============================
   **Feature**                                     **STL std::queue**                                 **concurrent_queue**
   =============================================== ================================================== ==============================
   Access to front and back                        Methods ``front`` and ``back``                     Not present. They would be unsafe while concurrent operations are in progress.
   ----------------------------------------------- -------------------------------------------------- ------------------------------
   Requires type ``T`` to be default-constructible No                                                 Yes
   ----------------------------------------------- -------------------------------------------------- ------------------------------
   ``unsafe_size()``                               Returns number of items in queue                   Returns number of items in queue. May
                                                                                                      return incorrect value if any
                                                                                                      ``push`` or
                                                                                                      ``try_pop`` operations are concurrently in flight.
   ----------------------------------------------- -------------------------------------------------- ------------------------------
   Copy and pop item unless queue q is empty.      bool b=!q.empty(); if(b) { x=q.front(); q.pop(); } bool b = *q*.try_pop(x)
   =============================================== ================================================== ==============================


Members
-------

.. code:: cpp

   namespace tbb {
       template<typename T, typename A = cache_aligned_allocator<T> >
       class concurrent_queue {
       public:
           // types
           typedef T value_type;
           typedef T& reference;
           typedef const T& const_reference;
           typedef std::size_t size_type;
           typedef std::ptrdiff_t difference_type;
           typedef A allocator_type;
   
           explicit concurrent_queue( const allocator_type& a = allocator_type() );
           concurrent_queue( const concurrent_queue& src, const allocator_type& a = allocator_type() );
           template<typename InputIterator>
           concurrent_queue( InputIterator first, InputIterator last, const allocator_type& a = allocator_type() );
           // Supported since C++11
           concurrent_queue( concurrent_queue&& src );
           concurrent_queue( concurrent_queue&& src, const allocator_type& a );
   
           ~concurrent_queue();
   
           void push( const T& source );
           bool try_pop( T& destination );
           // Supported since C++11
           void push( T&& source );
           template<typename... Args>
           void emplace(Args&&... args);
   
           void clear();
   
           size_type unsafe_size() const;
           bool empty() const;
           allocator_type get_allocator() const;
   
           typedef implementation-defined iterator;
           typedef implementation-defined const_iterator;
   
           // iterators (these are slow and intended only for debugging)
           iterator unsafe_begin();
           iterator unsafe_end();
           const_iterator unsafe_begin() const;
           const_iterator unsafe_end() const;
       };
   }
         

Where possible, constructors of ``concurrent_queue`` support class template argument deduction for C++17. For example

.. code:: cpp

   std::vector<int> v = {0, 1, 2};
   tbb::concurrent_queue cq(v.begin(), v.end);

declares ``cq`` as ``tbb::concurrent_queue<int, tbb::cache_aligned_allocator<int>>``.

The following table provides additional information on the members of this template class.

= ========================================================================================
\ Member, Description
==========================================================================================
\ ``concurrent_queue( const allocator_type& a = allocator_type() )``
  \
  Constructs empty queue.
------------------------------------------------------------------------------------------
\ ``concurrent_queue( const concurrent_queue& src, const allocator_type& a = allocator_type() )``
  \
  Constructs a copy of *src*.
------------------------------------------------------------------------------------------
\ ``template<typename InputIterator> concurrent_queue( InputIterator first, InputIterator last, const allocator_type& a = allocator_type() )``
  \
  Constructs a queue containing copies of elements in the iterator half-open
  interval [*first,last*).
------------------------------------------------------------------------------------------
\ ``concurrent_queue( concurrent_queue&& src )``
  \
  Supported since C++11. Constructs new queue by moving content from *src*.
  *src* is left in an unspecified state, but can be safely destroyed.
------------------------------------------------------------------------------------------
\ ``concurrent_queue( concurrent_queue&& src, const allocator_type& a )``
  \
  Supported since C++11. Constructs new queue by moving content from *src* using
  specifed allocator. *src* is left in an unspecified state, but can be safely
  destroyed.
------------------------------------------------------------------------------------------
\ ``~concurrent_queue()``
  \
  Destroys all items in the queue.
------------------------------------------------------------------------------------------
\ ``void push( const T& source )``
  \
  Pushes a copy of ``source`` onto back of the queue.
------------------------------------------------------------------------------------------
\ ``void push(T&& elem)``
  \
  Supported since C++11. Pushes given element into the queue by utilizing element's
  move constructor (if available).
------------------------------------------------------------------------------------------
\ ``template<typename... Arguments> void emplace(Arguments&&... args);``
  \
  Supported since C++11. Pushes a new element into the queue. The element is constructed
  with given arguments.
------------------------------------------------------------------------------------------
\ ``bool try_pop ( T& destination )``
  \
  If value is available, pops it from the queue, assigns it to destination, and
  destroys the original value. Otherwise does nothing.
  
  **Returns**: ``true`` if value was popped; ``false``
  otherwise.
------------------------------------------------------------------------------------------
\ ``void clear()``
  \
  Clears the queue. Afterwards ``size() == 0``.
------------------------------------------------------------------------------------------
\ ``size_type unsafe_size() const``
  \
  **Returns:** Number of items in the queue. If there are concurrent
  modifications in flight, the value might not reflect the actual number of items in
  the queue.
------------------------------------------------------------------------------------------
\ ``bool empty() const``
  \
  **Returns**: ``true`` if queue has no items; false otherwise.
------------------------------------------------------------------------------------------
\ ``allocator_type get_allocator() const``
  \
  **Returns**: Copy of allocator used to construct the queue.
------------------------------------------------------------------------------------------
= ========================================================================================


Exception Safety
----------------

The class ``concurrent_queue`` provides the following exception safety
guarantees:

* for constructors, ``push`` and ``try_pop`` methods, if an
  exception is thrown during construction or copying of a data item:
  
  * the queue remains valid; simultaneous operations with the same queue, as well as
    all future operations, are not affected;
  * the data item which is supposed to be added by a constructor or
    ``push`` or removed by ``try_pop`` is lost;
  
* all other methods of ``concurrent_queue`` may not throw an exception.

These guarantees are only provided if the destructor of the type T does not throw an
exception; otherwise the behavior is undefined.

Iterators
---------

A ``concurrent_queue`` provides limited iterator support that is intended
solely to allow programmers to inspect a queue during debugging. It provides iterator and
const_iterator types. Both follow the usual STL conventions for forward iterators. The
iteration order is from least recently pushed to most recently pushed. Modifying a
``concurrent_queue`` invalidates any iterators that reference it.

.. caution::

   The iterators are relatively slow. They should be used only for debugging.


Example
-------

The following program builds a queue with the integers 0..9, and then dumps the queue to
standard output. Its overall effect is to print 0 1 2 3 4 5 6 7 8 9.

.. code:: cpp

   #include "tbb/concurrent_queue.h"
   #include <iostream>
   
   using namespace std;
   using namespace tbb;
   
   int main() {
       concurrent_queue<int> queue;
       for( int i=0; i<10; ++i )
           queue.push(i);
       typedef concurrent_queue<int>::iterator iter;
       for( iter i(queue.unsafe_begin()); i!=queue.unsafe_end(); ++i )
           cout << *i << " ";
       cout << endl;
       return 0;
   }

The following table provides additional information on the members of this template class.

= ========================================================================================
\ Member, Description
==========================================================================================
\ ``iterator unsafe_begin()``
  \
  **Returns**: ``iterator`` pointing to beginning of the queue.
------------------------------------------------------------------------------------------
\ ``iterator unsafe_end()``
  \
  **Returns**: ``iterator`` pointing to end of the queue.
------------------------------------------------------------------------------------------
\ ``const_iterator unsafe_begin() const``
  \
  **Returns**: ``const_iterator`` with pointing to beginning of the
  queue.
------------------------------------------------------------------------------------------
\ ``const_iterator unsafe_end() const``
  \
  **Returns**: ``const_iterator`` pointing to end of the queue.
------------------------------------------------------------------------------------------
= ========================================================================================
