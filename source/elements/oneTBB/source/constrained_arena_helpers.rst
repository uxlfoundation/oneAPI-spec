.. SPDX-FileCopyrightText: 2025 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

=========================
Constrained Arena Helpers
=========================
**[constrained_arena_helpers]**

Helper interfaces to create and manage multiple ``task_arena`` objects with constraints.

.. code:: cpp

    // Defined in header <oneapi/tbb/task_arena.h>

    namespace oneapi {
    namespace tbb {
        std::vector<oneapi::tbb::task_arena> create_numa_task_arenas(
            oneapi::tbb::task_arena::constraints other_constraints = {},
            unsigned reserved_slots = 0);
    } // namespace tbb
    } // namespace oneapi

Functions
---------

.. cpp:function:: std::vector<oneapi::tbb::task_arena> create_numa_task_arenas(oneapi::tbb::task_arena::constraints constraints = {}, unsigned reserved_slots = 0)

    Returns a ``std::vector`` of non-initialized ``task_arena`` objects, each bound to a separate NUMA node.
    The number of created ``task_arena`` is equal to the number of NUMA nodes available on the system.
    Additional ``constraints`` argument can be specified to further limit the threads joined
    the ``task_arena`` objects. The ``numa_id`` value in the ``constraints`` argument is
    ignored. The ``reserved_slots`` argument allows reserving specified number of slots in
    ``task_arena`` objects for application threads.

    .. note::

        If error occurs during system topology parsing, returns ``std::vector`` containing single
        ``task_arena`` object equivalent to ``task_arena(other_constraints, reserved_slots)``.
