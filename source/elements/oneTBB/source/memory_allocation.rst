=================
Memory Allocation
=================
**[memory_allocation]**

This section describes classes and functions related to memory allocation.

Allocators
----------

oneAPI Threading Building Blocks implements several classes that meet the allocator requirements
from the [allocator.requirements] ISO C++ Standard section.

.. toctree::
    :titlesonly:

    memory_allocation/tbb_allocator_cls.rst
    memory_allocation/scalable_allocator_cls.rst
    memory_allocation/cache_aligned_allocator_cls.rst

Memory Resources
----------------

Starting from C++17, the standard library provides a ``std::pmr::polymorphic_allocator`` class
that allocates memory from a supplied memory resource (see the [mem.poly.allocator.class] ISO/IEC 14882:2017 section).
Class ``std::pmr::memory_resource`` is an abstract interface for user-side implementation of different allocation strategies.
For details, see [mem.res.class] ISO/IEC 14882:2017 standard section.

oneAPI Threading Building Blocks provides a set of ``std::pmr::memory_resource`` implementations.

.. toctree::
    :titlesonly:

    memory_allocation/cache_aligned_resource_cls.rst
    memory_allocation/scalable_memory_resource_func.rst

Library Functions
-----------------

.. toctree::
    :titlesonly:

    memory_allocation/c_interface_to_scalable_allocator.rst

