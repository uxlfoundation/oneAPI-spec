======================================
cache_aligned_allocator Template Class
======================================


Summary
-------

Template class for allocating memory in a way that
avoids false sharing.

Syntax
------

.. code:: cpp

   template<typename T> class cache_aligned_allocator;


Header
------

.. code:: cpp

   #include "tbb/cache_aligned_allocator.h"


Description
-----------

A 
``cache_aligned_allocator`` allocates memory on cache line
boundaries, in order to avoid false sharing. False sharing is when logically
distinct items occupy the same cache line, which can hurt performance if
multiple threads attempt to access the different items simultaneously. Even
though the items are logically separate, the processor hardware may have to
transfer the cache line between the processors as if they were sharing a
location. The net result can be much more memory traffic than if the logically
distinct items were on different cache lines.

A 
``cache_aligned_allocator`` models the Allocator Concept.
It can be used to replace a 
``std::allocator``. Used judiciously, 
``cache_aligned_allocator`` can improve performance by
reducing false sharing. However, it is sometimes an inappropriate replacement,
because the benefit of allocating on a cache line comes at the price that 
``cache_aligned_allocator`` implicitly adds pad memory.
The padding is typically 128 bytes. Hence allocating many small objects with 
``cache_aligned_allocator`` may increase memory usage.

Members
-------

.. code:: cpp

           namespace tbb {
            
               template<typename T>
               class cache_aligned_allocator {
               public:
                   typedef T* pointer;
                   typedef const T* const_pointer;
                   typedef T& reference;
                   typedef const T& const_reference;
                   typedef T value_type;
                   typedef size_t size_type;
                   typedef ptrdiff_t difference_type;
                   template<typename U> struct rebind {
                       typedef cache_aligned_allocator<U> other;
                   };
            
               #if _WIN64
                   char* _Charalloc( size_type size );
               #endif /* _WIN64 */
            
                   cache_aligned_allocator() throw();
                   cache_aligned_allocator( const cache_aligned_allocator& ) throw();
                   template<typename U> 
                   cache_aligned_allocator( const cache_aligned_allocator<U>& ) throw();
                   ~cache_aligned_allocator();
            
                   pointer address(reference x) const;
                   const_pointer address(const_reference x) const;
            
                   pointer allocate( size_type n, const void* hint=0 );
                   void deallocate( pointer p, size_type );
                   size_type max_size() const throw();
            
                   void construct( pointer p, const T& value );
                   void destroy( pointer p );
               };
            
               template<>
               class cache_aligned_allocator<void> {
               public:
                   typedef void* pointer;
                   typedef const void* const_pointer;
                   typedef void value_type;
                   template<typename U> struct rebind {
                       typedef cache_aligned_allocator<U> other;
                   };
               };
            
               template<typename T, typename U>
               bool operator==( const cache_aligned_allocator<T>&, 
                                const cache_aligned_allocator<U>& );
            
               template<typename T, typename U>
               bool operator!=( const cache_aligned_allocator<T>&, 
                                const cache_aligned_allocator<U>& );
            
           } 

For sake of brevity, the following table describes
only those methods that differ significantly from the corresponding methods of 
``std::allocator``.

= ========================================================================================
\ Member, Description
==========================================================================================
\ ``pointer allocate( size_type n, const void* hint=0 )``
  \
  Allocates 
  *n* bytes of memory on a cache-line boundary. The
  allocation may include extra hidden padding.
  
  **Returns**: Pointer to the allocated memory.
------------------------------------------------------------------------------------------
\ ``void deallocate( pointer p, size_type n )``
  \
  **Requirements**: Pointer 
  ``p`` must be the result of method 
  ``allocate(n)``. The memory must not have been
  already deallocated.
  
  **Effects**: Deallocates memory pointed to by 
  ``p``. The deallocation also deallocates any
  extra hidden padding.
------------------------------------------------------------------------------------------
\ ``char* _Charalloc( size_type size )``
  \
    .. note::

     This method is provided only on 64-bit Windows* OS
     platforms. It is a non-ISO method that exists for backwards compatibility with
     versions of Window's containers that seem to require it. Please do not use it
     directly.
  
------------------------------------------------------------------------------------------
= ========================================================================================
