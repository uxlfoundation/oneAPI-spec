.. SPDX-FileCopyrightText: 2019-2020 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

==================================
Concurrently safe member functions
==================================

All member functions in this section can be performed concurrently with each other.

Pushing elements
----------------

    .. code:: cpp

        void push( const value_type& value );

    Pushes a copy of ``value`` into the container.

    **Requirements**: the type ``T`` must meet the ``CopyInsertable`` requirements from the
    [container.requirements] ISO C++ Standard section.

-----------------------------

    .. code:: cpp

        void push( value_type&& value );

    Pushes ``value`` into the container using move semantics.

    **Requirements**: the type ``T`` must meet the ``MoveInsertable`` requirements from the
    [container.requirements] ISO C++ Standard section.

    ``value`` is left in a valid, but unspecified state.

-----------------------------

    .. code:: cpp

        template <typename... Args>
        void emplace( Args&&... args );

    Pushes a new element constructed from ``args`` into the container.

    **Requirements**: the type ``T`` must meet the ``EmplaceConstructible`` requirements from the
    [container.requirements] ISO C++ Standard section.

Popping elements
----------------

    .. code:: cpp

        bool try_pop( value_type& value );

    If the container is empty, does nothing.

    Otherwise, copies the last element from the container and assigns it to ``value``.
    The popped element is destroyed.

    **Requirements**: the type ``T`` must meet the ``MoveAssignable`` requirements from the [moveassignable]
    ISO C++ Standard section.

    **Returns**: ``true`` if the element was popped; ``false``, otherwise.

get_allocator
-------------

    .. code:: cpp

        allocator_type get_allocator() const;

    **Returns**: a copy of the allocator, associated with ``*this``.
