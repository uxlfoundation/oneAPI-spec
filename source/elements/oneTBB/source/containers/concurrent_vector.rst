=================
concurrent_vector
=================


Summary
-------

Template class for a vector that can be concurrently grown and accessed.

Syntax
------

.. code:: cpp

   template<typename T, class Alloc=cache_aligned_allocator<T> >
   class concurrent_vector;


Header
------

.. code:: cpp

   #include "tbb/concurrent_vector.h"


Description
-----------

A
``concurrent_vector`` is a container with the following features:

* Random access by index. The index of the first element is zero.
* Multiple threads can grow the container and append new elements concurrently.
* Growing the container does not invalidate existing iterators or indices.

A ``concurrent_vector`` meets all requirements for a Container and a Reversible
Container as specified in the ISO C++ standard. It does not meet the Sequence requirements
due to absence of methods ``insert()`` and ``erase()``.

Members
-------

.. code:: cpp

   namespace tbb {
       template<typename T, typename Alloc=cache_aligned_allocator<T> >
       class concurrent_vector {
       public:
           typedef size_t size_type;
           typedef allocator-A-rebound-for-T allocator_type;
           typedef T value_type;
           typedef ptrdiff_t difference_type;
           typedef T& reference;
           typedef const T& const_reference;
           typedef T* pointer;
           typedef const T* const_pointer;
           typedef implementation-defined iterator;
           typedef implementation-defined const_iterator;
           typedef implementation-defined reverse_iterator;
           typedef implementation-defined const_reverse_iterator;
   
           // Parallel ranges
           typedef implementation-defined range_type;
           typedef implementation-defined const_range_type;
           range_type range( size_t grainsize );
           const_range_type range( size_t grainsize ) const;
   
           // Constructors
           explicit concurrent_vector( const allocator_type& a = allocator_type() );
           concurrent_vector( const concurrent_vector& x );
           concurrent_vector( const concurrent_vector& x, const allocator_type& a );
           template<typename M>
           concurrent_vector( const concurrent_vector<T, M>& x,
                              const allocator_type& a = allocator_type() );
           explicit concurrent_vector( size_type n, const T& t = T(),
                                       const allocator_type& a = allocator_type() );
           template<typename InputIterator>
           concurrent_vector( InputIterator first, InputIterator last,
                              const allocator_type& a = allocator_type());
           // Supported since C++11
           concurrent_vector( concurrent_vector&& x);
           concurrent_vector( concurrent_vector&& x, const allocator_type& a);
           concurrent_vector( std::initializer_list<T> il,
                              const allocator_type& a = allocator_type() );
   
           // Assignment
           concurrent_vector& operator=( const concurrent_vector& x );
           template<class M>
           concurrent_vector& operator=( const concurrent_vector<T, M>& x );
           void assign( size_type n, const T& t );
           template<class InputIterator >
           void assign( InputIterator first, InputIterator last );
           // Supported since C++11
           concurrent_vector& operator=( concurrent_vector&& x );
           concurrent_vector& operator=( std::initializer_list<T> il );
           void assign( std::initializer_list<T> il );
   
           // Concurrent growth operations
           iterator grow_by( size_type delta );
           iterator grow_by( size_type delta, const T& t );
           template<typename ForwardIterator>
           iterator grow_by( ForwardIterator first, ForwardIterator last );
           // Supported since C++11
           iterator grow_by( std::initializer_list<T>& il )
           iterator grow_to_at_least( size_type n );
           iterator grow_to_at_least( size_type n, const T& t );
           iterator push_back( const T& item );
           // Supported since C++11
           iterator push_back( T&& item );
           template<typename... Args>
           iterator emplace_back( Args&&... args);
   
           // Items access
           reference operator[]( size_type index );
           const_reference operator[]( size_type index ) const;
           reference at( size_type index );
           const_reference at( size_type index ) const;
           reference front();
           const_reference front() const;
           reference back();
           const_reference back() const;
   
           // Storage
           bool empty() const;
           size_type capacity() const;
           size_type max_size() const;
           size_type size() const;
           allocator_type get_allocator() const;
   
           // Non-concurrent operations on whole container
           void reserve( size_type n );
           void compact();
           void swap( concurrent_vector& vector );
           void clear();
           ~concurrent_vector();
   
           // Iterators
           iterator begin();
           iterator end();
           const_iterator begin() const;
           const_iterator end() const;
           reverse_iterator rbegin();
           reverse_iterator rend();
           const_reverse_iterator rbegin() const;
           const_reverse_iterator rend() const;
           const_iterator cbegin() const;
           const_iterator cend() const;
           const_reverse_iterator crbegin() const;
           const_reverse_iterator crend() const;
       };
   
       // Global functions
       template<typename T, class A1, class A2>
       bool operator==( const concurrent_vector<T, A1>& a,
                        const concurrent_vector<T, A2>& b );
   
       template<typename T, class A1, class A2>
       bool operator!=( const concurrent_vector<T, A1>& a,
                        const concurrent_vector<T, A2>& b );
   
       template<typename T, class A1, class A2>
       bool operator<( const concurrent_vector<T, A1>& a,
                          const concurrent_vector<T, A2>& b );
   
       template<typename T, class A1, class A2>
       bool operator>( const concurrent_vector<T, A1>& a,
                          const concurrent_vector<T, A2>& b );
   
       template<typename T, class A1, class A2>
       bool operator<=( const concurrent_vector<T, A1>& a,
                           const concurrent_vector<T, A2>& b );
   
       template<typename T, class A1, class A2>
       bool operator>=( const concurrent_vector<T, A1>& a,
                           const concurrent_vector<T, A2>& b );
   
       template<typename T, class A>
       void swap( concurrent_vector<T, A>& a, concurrent_vector<T, A>& b);
   }

.. note::

   The rebinding of
   ``allocator_type`` is similar to the Microsoft* and GNU* implementations of
   ``std::vector``.

Where possible, constructors of ``concurrent_vector`` support class template argument deduction for C++17. For example

.. code:: cpp

   std::vector<int> v = {0, 1, 2};
   tbb::concurrent_vector cv(v.begin(), v.end);

declares ``cv`` as ``tbb::concurrent_vector<int, tbb::cache_aligned_allocator<int>>``.

Exception Safety
----------------

Concurrent growing is fundamentally incompatible with ideal exception safety. Nonetheless,
``concurrent_vector`` offers a practical level of exception safety.

Element type T must meet the following requirements:

* Its destructor must not throw an exception.
* If its default constructor can throw an exception, its destructor must be non-virtual
  and work correctly on zero-filled memory.

Otherwise the program's behavior is undefined.

Growth and vector assignment append a sequence of elements to a vector. If an exception
occurs, the impact on the vector depends upon the cause of the exception:

* If the exception is thrown by the constructor of an element, then all subsequent
  elements in the appended sequence will be zero-filled.
* Otherwise, the exception was thrown by the vector's allocator. The vector becomes
  broken. Each element in the appended sequence will be in one of three states:
  
  * constructed
  * zero-filled
  * unallocated in memory
  

Once a vector becomes broken, care must be taken when accessing it:

* Accessing an unallocated element with the method ``at`` causes an exception
  ``std::range_error``. Accessing an unallocated element using any other
  method has undefined behavior.
* The values of ``capacity()`` and ``size()`` may be less than
  expected.
* Access to a broken vector via ``back()`` has undefined behavior.

However, the following guarantees hold for broken or unbroken vectors:

* Let ``k`` be an index of an unallocated element. Then
  ``size()<= capacity()<=k``.
* Growth operations never cause ``size()`` or ``capacity()`` to
  decrease.

If a concurrent growth operation successfully completes, the appended sequence remains valid
and accessible even if a subsequent growth operations fails.

Fragmentation
-------------

Unlike a ``std::vector``, a ``concurrent_vector`` never moves
existing elements when it grows. The container allocates a series of contiguous arrays. The
first reservation, growth, or assignment operation determines the size of the first array.
Using a small number of elements as initial size incurs fragmentation across cache lines
that may increase element access time. The method ``shrink_to_fit()`` merges
several smaller arrays into a single contiguous array, which may improve access time.

.. toctree::

   concurrent_vector/construction_copy_and_assignment.rst
   concurrent_vector/whole_vector_operations.rst
   concurrent_vector/concurrent_growth.rst
   concurrent_vector/access.rst
   concurrent_vector/parallel_iteration.rst
   concurrent_vector/capacity_vector.rst
   concurrent_vector/iterators_vector.rst
