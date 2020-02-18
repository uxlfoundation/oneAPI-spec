=================================
scalable_memory_resource Function
=================================


Summary
-------

Function that returns a memory resource for scalable memory allocation.

Syntax
------

.. code:: cpp

   std::pmr::memory_resource* scalable_memory_resource();


Header
------

.. code:: cpp

   #include "tbb/scalable_allocator.h"


Description
-----------

The ``scalable_memory_resource()`` function returns the pointer to the memory resource managed by
the TBB scalable memory allocator. In particular, its ``allocate`` method uses ``scalable_aligned_malloc()``,
and ``deallocate`` uses ``scalable_free()``. The memory resources returned by this function compare equal.

``std::pmr::polymorphic_allocator`` instantiated with
``tbb::scalable_memory_resource()`` behaves like ``tbb::scalable_allocator``.

See also:

* :doc:`scalable_allocator Template Class <scalable_allocator_cls>`
* :doc:`C Interface to Scalable Allocator <c_interface_to_scalable_allocator>`
