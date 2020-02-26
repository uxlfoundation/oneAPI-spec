============================
cache_aligned_resource Class
============================


Summary
-------

Memory resource class that avoids false sharing.

Syntax
------

.. code:: cpp

   class cache_aligned_resource;


Header
------

.. code:: cpp

   #include "tbb/cache_aligned_allocator.h"


Description
-----------

A ``cache_aligned_resource`` acts as a wrapper to another memory resource to ensure that all allocations
are aligned on cache line boundaries to avoid false sharing. See the ``cache_aligned_allocator``
Template Class section for more information about false sharing avoidance.

Members
-------

.. code:: cpp

   namespace tbb {
       class cache_aligned_resource {
       public:
           cache_aligned_resource();
           explicit cache_aligned_resource( std::pmr::memory_resource* );
   
           std::pmr::memory_resource* upstream_resource() const;
   
       private:
           void* do_allocate(size_t n, size_t alignment) override;
           void do_deallocate(void* p, size_t n, size_t alignment) override;
           bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override;
       };
   }

= ========================================================================================
\ Member, Description
==========================================================================================
\ ``cache_aligned_resource();``
  \
  Constructs a ``cache_aligned_resource`` over ``std::pmr::get_default_resource()``.
------------------------------------------------------------------------------------------
\ ``explicit cache_aligned_resource(std::pmr::memory_resource*);``
  \
  Constructs a ``cache_aligned_resource`` over the specified memory resource.
------------------------------------------------------------------------------------------
\ ``std::pmr::memory_resource* upstream_resource() const;``
  \
  Returns the underlying memory resource.
------------------------------------------------------------------------------------------
\ ``void* do_allocate(size_t n, size_t alignment) override;``
  \
  Allocates ``n`` bytes of memory on a cache-line boundary, with alignment not less than requested.
  The allocation may include extra memory for padding.
  
  **Returns**: Pointer to the allocated memory.
------------------------------------------------------------------------------------------
\ ``void do_deallocate(void* p, size_t n, size_t alignment) override;``
  \
  Deallocates memory pointed to by p and any extra padding.
  
  **Note**: Pointer ``p`` must be obtained with ``do_allocate(n, alignment)``.
  The memory must not be deallocated beforehand.
------------------------------------------------------------------------------------------
\ ``bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override;``
  \
  Compares upstream memory resources of ``*this`` and ``other``.
  If ``other`` is not a ``cache_aligned_resource``, returns false.
------------------------------------------------------------------------------------------
= ========================================================================================


See also:

* :doc:`cache_aligned_allocator Template Class <cache_aligned_allocator_cls>`
