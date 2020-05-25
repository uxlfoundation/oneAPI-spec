======
Lookup
======

All methods in this section can be executed concurrently with each other,
concurrently-safe modifiers and while traversing the container.

count
-----

    .. code:: cpp

        size_type count( const key_type& key );

    **Returns**: the number of elements equal to ``key``.

-----------------------------------------------------------------------------

    .. code:: cpp

        template <typename K>
        size_type count( const K& key );

    **Returns**: the number of elements which compares equivalent with ``key``.

    This overload only participates in overload resolution if qualified-id
    ``hasher::transparent_key_equal`` is valid and denotes a type.

find
----

    .. code:: cpp

        iterator find( const key_type& key );

        const_iterator find( const key_type& key ) const;

    **Returns**: an iterator to the element equal to ``key`` or ``end()``
    if no such element exists.

-----------------------------------------------------------------------------

    .. code:: cpp

        template <typename K>
        iterator find( const K& key );

        template <typename K>
        const_iterator find( const K& key ) const;

    **Returns**: an iterator to the element which compares equivalent
    with ``key`` or ``end()`` if no such element exists.

    These overloads only participates in overload resolution if qualified-id
    ``hasher::transparent_key_equal`` is valid and denotes a type.

contains
--------

    .. code:: cpp

        bool contains( const key_type& key ) const;

    **Returns**: ``true`` if an element equal to ``key`` exists
    in the container, ``false`` otherwise.

-----------------------------------------------------------------------------

    .. code:: cpp

        template <typename K>
        bool contains( const K& key ) const;

    **Returns**: ``true`` if an element which compares equivalent
    with ``key`` exists in the container, ``false`` otherwise.

    This overload only participates in overload resolution if qualified-id
    ``hasher::transparent_key_equal`` is valid and denotes a type.

equal_range
-----------

    .. code:: cpp

        std::pair<iterator, iterator> equal_range( const key_type& key );

        std::pair<const_iterator, const_iterator> equal_range( const key_type& key ) const;

    **Returns**: if an element equal to ``key`` exists - a pair of iterators
    ``{f, l}``, where ``f`` is an iterator to this element, ``l`` is ``std::next(f)``.
    Otherwise - ``{end(), end()}``.

-----------------------------------------------------------------------------

    .. code:: cpp

        template <typename K>
        std::pair<iterator, iterator> equal_range( const K& key )

        template <typename K>
        std::pair<const_iterator, const_iterator> equal_range( const K& key )

    **Returns**: if an element which compares equivalent with ``key`` exists -
    a pair of iterators ``{f, l}``, where ``f`` is an iterator to this element,
    ``l`` is ``std::next(f)``. Otherwise - ``{end(), end()}``.

    These overloads only participates in overload resolution if qualified-id
    ``hasher::transparent_key_equal`` is valid and denotes a type.
