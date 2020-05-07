==============
Element access
==============

at
--

    .. code:: cpp

        value_type& at( const key_type& key );

        const value_type& at( const key_type& key ) const;

    **Returns**: a reference to ``item.second`` where ``item`` is the element with the key equal to ``key``.

    **Throws**: ``std::out_of_range`` exception if the element with the key equal to ``key`` is not presented in the container.

operator[]
----------

    .. code:: cpp

        value_type& operator[]( const key_type& key );

    If the element with the key equal to ``key`` is not presented in the container,
    inserts a new element, constructed in-place from
    ``std::piecewise_construct, std::forward_as_tuple(key), std::tuple<>()``.

    **Requirements**: the type ``value_type`` shall meet the ``EmplaceConstructible`` requirements
    from [container.requirements] ISO C++ section.

    **Returns**: a reference to ``item.second`` where ``item`` is the element with the key equal to ``key``.

---------------------------------------------------------------------------------------------

    .. code:: cpp

        value_type& operator[]( key_type&& key );

    If the element with the key equal to ``key`` is not presented in the container,
    inserts a new element, constructed in-place from
    ``std::piecewise_construct, std::forward_as_tuple(std::move(key)), std::tuple<>()``.

    **Requirements**: the type ``value_type`` shall meet the ``EmplaceConstructible`` requirements
    from [container.requirements] ISO C++ section.

    **Returns**: a reference to ``item.second`` where ``item`` is the element with the key equal to ``key``.
