==============
zero_allocator
==============


Summary
-------

Template class for allocator that returns zeroed memory.

Syntax
------

.. code:: cpp

   template <typename T, 
             template<typename U> class Alloc = tbb_allocator> 
   class zero_allocator: public Alloc<T>;


Header
------

.. code:: cpp

   #include "tbb/tbb_allocator.h"


Description
-----------

A ``zero_allocator`` allocates zeroed memory. A
``zero_allocator<T,A>`` can be instantiated for any
class *A* that models the Allocator concept. The default for *A* is
``tbb_allocator``. A ``zero_allocator`` forwards
allocation requests to *A* and zeros the allocation before returning it.

Members
-------

.. code:: cpp

   namespace tbb {
       template <typename T, template<typename U> class Alloc = tbb_allocator>
       class zero_allocator : public Alloc<T> {
       public:
           typedef Alloc<T> base_allocator_type;
           typedef typename base_allocator_type::value_type  value_type;
           typedef typename base_allocator_type::pointer  pointer;
           typedef typename base_allocator_type::const_pointer  const_pointer;
           typedef typename base_allocator_type::reference  reference;
           typedef typename base_allocator_type::const_reference  const_reference;
           typedef typename base_allocator_type::size_type  size_type;
           typedef typename base_allocator_type::difference_type  difference_type;
           template<typename U> struct rebind {
               typedef zero_allocator<U, Alloc> other;
           };
   
           zero_allocator() throw() { }
           zero_allocator(const zero_allocator &a) throw();
           template<typename U>
           zero_allocator(const zero_allocator<U> &a) throw(); 
   
           pointer allocate(const size_type n, const void* hint=0);
       };
   } 
    
