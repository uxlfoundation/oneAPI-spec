=================
Allocator Concept
=================

The Allocator concept for allocators in oneAPI Threading Building Blocks
is similar to the "Allocator requirements" in Table 32 of the ISO C++ Standard (2003), but with further
guarantees required by the Standard for use with ISO C++ containers. The table below summarizes
the Allocator concept. Here, A and B represent instances of an allocator class.

= ========================================================================================
\ Allocator Concept: Pseudo-Signature, Semantics
==========================================================================================
\ ``typedef T* A::pointer``
  \
  Pointer to *T*.
------------------------------------------------------------------------------------------
\ ``typedef const T* A::const_pointer``
  \
  Pointer to const *T*.
------------------------------------------------------------------------------------------
\ ``typedef T& A::reference``
  \
  Reference to *T*.
------------------------------------------------------------------------------------------
\ ``typedef const T& A::const_reference``
  \
  Reference to const *T*.
------------------------------------------------------------------------------------------
\ ``typedef T A::value_type``
  \
  Type of value to be allocated.
------------------------------------------------------------------------------------------
\ ``typedef size_t A::size_type``
  \
  Type for representing number of values.
------------------------------------------------------------------------------------------
\ ``typedef ptrdiff_t A::difference_type``
  \
  Type for representing pointer difference.
------------------------------------------------------------------------------------------
\ ``template<typename U> struct rebind { typedef A<U> A::other;};``
  \
  Rebind to a different type U
------------------------------------------------------------------------------------------
\ ``A() throw()``
  \
  Default constructor.
------------------------------------------------------------------------------------------
\ ``A( const A& ) throw()``
  \
  Copy constructor.
------------------------------------------------------------------------------------------
\ ``template<typename U> A( const A& )``
  \
  Rebinding constructor.
------------------------------------------------------------------------------------------
\ ``~A() throw()``
  \
  Destructor.
------------------------------------------------------------------------------------------
\ ``T* A::address( T& x ) const``
  \
  Take address.
------------------------------------------------------------------------------------------
\ ``const T* A::const_address( const T& x ) const``
  \
  Take const address.
------------------------------------------------------------------------------------------
\ ``T* A::allocate( size_type n, const void* hint=0 )``
  \
  Allocate space for ``n`` values.
------------------------------------------------------------------------------------------
\ ``void A::deallocate( T* p, size_t  n )``
  \
  Deallocate ``n`` values.
------------------------------------------------------------------------------------------
\ ``size_type A::max_size() const throw()``
  \
  Maximum plausible argument to method allocate.
------------------------------------------------------------------------------------------
\ ``void A::construct( T* p, const T& value )``
  \
  ``new(p) T(value)``
------------------------------------------------------------------------------------------
\ ``void A::destroy( T* p )``
  \
  ``p->T::~T()``
------------------------------------------------------------------------------------------
\ ``bool operator==( const A&, const B& )``
  \
  Return true.
------------------------------------------------------------------------------------------
\ ``bool operator!=( const A&, const B& )``
  \
  Return false.
------------------------------------------------------------------------------------------
= ========================================================================================

**Model Types**

Template classes: ``tbb_allocator``, ``scalable_allocator``, and ``cached_aligned_allocator``, and
``zero_allocator`` model the Allocator concept.

.. toctree::

   tbb_allocator_cls.rst
   scalable_allocator_cls.rst
   cache_aligned_allocator_cls.rst
   zero_allocator.rst
