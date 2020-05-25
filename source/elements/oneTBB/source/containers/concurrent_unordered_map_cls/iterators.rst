=========
Iterators
=========

The types ``concurrent_unordered_map::iterator`` and ``concurrent_unordered_map::const_iterator``
meets the requirements of ``ForwardIterator`` from [forward.iterators] ISO C++ Standard section.

begin and cbegin
----------------

    .. code:: cpp

        iterator begin();

        const_iterator begin() const;

        const_iterator cbegin() const;

    **Returns**: an iterator to the first element in the container.

end and cend
------------

    .. code:: cpp

        iterator end();

        const_iterator end() const;

        const_iterator cend() const;

    **Returns**: an iterator to the element which follows the last element in the container.
