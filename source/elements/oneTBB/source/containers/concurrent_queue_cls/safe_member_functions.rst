==================================
Concurrently safe member functions
==================================

All member functions in this section can be performed concurrently with each other.

Pushing elements
----------------

    .. code:: cpp

        void push( const value_type& value );

    Pushes a copy of ``value`` into the container.

    **Requirements**: the type ``T`` shall meet the ``CopyInsertable`` requirements from
    [container.requirements] ISO C++ Standard section.

-----------------------------

    .. code:: cpp

        void push( value_type&& value );

    Pushes ``value`` into the container using move semantics.

    **Requirements**: the type ``T`` shall meet the ``MoveInsertable`` requirements from
    [container.requirements] ISO C++ Standard section.

    ``value`` is left in a valid, but unspecified state.

-----------------------------

    .. code:: cpp

        template <typename... Args>
        void emplace( Args&&... args );

    Pushes a new element constructed from ``args`` into the container.

    **Requirements**: the type ``T`` shall meet the ``EmplaceConstructible`` requirements from
    [container.requirements] ISO C++ Standard section.

Popping elements
----------------

    .. code:: cpp

        bool try_pop( value_type& value );

    If the container is empty, does nothing.

    Otherwise, copies the last element from the container and assigns it to the ``value``.
    The popped element is destroyed.

    **Requirements**: the type ``T`` shall meet the ``MoveAssignable`` requirements from [moveassignable]
    ISO C++ Standard section.

    **Returns**: ``true`` if the element was popped, ``false`` otherwise.

get_allocator
-------------

    .. code:: cpp

        allocator_type get_allocator() const;

    **Returns**: a copy of the allocator, associated with ``*this``.
