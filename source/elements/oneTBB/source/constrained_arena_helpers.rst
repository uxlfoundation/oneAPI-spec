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

.. cpp:function:: std::vector<oneapi::tbb::task_arena> create_numa_task_arenas(oneapi::tbb::task_arena::constraints other_constraints = {}, unsigned reserved_slots = 0)

    Returns a ``std::vector`` of ``task_arena`` objects, each bound to a separate NUMA node.
    The number of created ``task_arena`` is equal to the number of NUMA nodes available on the system.
    It optionally takes additional ``other_constraints`` argument to be applied to each created
    ``task_arena``, ignoring ``numa_id`` value. The second optional ``reserved_slots`` argument
    allows to reserve a number of slots in each created ``task_arena`` for application threads.

    .. note::
        If error occurs during system topology parsing, returns ``std::vector`` containing single
        ``task_arena`` object equivalent to ``task_arena(other_constraints, reserved_slots)``.
