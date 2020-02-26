=========================
Memory Resource Interface
=========================

Starting from C++17, the standard library provides ``std::pmr::polymorphic_allocator`` class
that allocates memory from a supplied memory resource. Class ``std::pmr::memory_resource``
is an abstract interface for user-side implementation of different allocation strategies.

To provide a custom memory resource, inherit ``std::pmr::memory_resource``
class and override its pure virtual functions.
For details, see [mem.res.class] "Class memory_resource" C++17 standard section.

= ========================================================================================
\ std::pmr::memory_resource class members: Member, Description
==========================================================================================
\ ``void* allocate(std::size_t bytes, std::size_t alignment)``
  \
  Allocates storage of at least ``size`` bytes aligned on the specified alignment.
------------------------------------------------------------------------------------------
\ ``void deallocate(void* p, std::size_t bytes, std::size_t alignment)``
  \
  Deallocates the storage pointed to by ``p``.
------------------------------------------------------------------------------------------
\ ``bool is_equal(const memory_resource& other) const noexcept``
  \
  Checks if the current instance is equal to ``other``.
------------------------------------------------------------------------------------------
\ virtual methods
  \
  ``virtual void* do_allocate(size_t bytes, std::size_t alignment) = 0``
  
  ``virtual void do_deallocate(void* p, std::size_t bytes, std::size_t alignment) = 0``
  
  ``virtual bool do_is_equal(const std::pmr::memory_resource& other) const noexcept = 0``

  Pure virtual member functions that need to be overridden by custom memory resource implementations.
------------------------------------------------------------------------------------------
= ========================================================================================

TBB provides a set of ``std::pmr::memory_resource`` implementations:

* ``tbb::cache_aligned_resource`` class which ensures allocation on cache line boundaries.
* ``tbb::scalable_memory_resource()`` function that provides the memory resource
  managed by the TBB scalable memory allocator.

.. toctree::

   scalable_memory_resource_func.rst
   cache_aligned_resource_cls.rst
