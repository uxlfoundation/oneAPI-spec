=========
Iterators
=========

The types ``concurrent_vector::iterator`` and ``concurrent_vector::const_iterator``
meets the requirements of ``RandomAccessIterator`` from [random.access.iterators]
ISO C++ Standard section.

begin and cbegin
----------------

    .. code:: cpp

        iterator begin();

        const_iterator begin() const;

        const_iterator cbegin() const;

    **Returns**: an iterator to the first element in the vector.

end and cend
------------

    .. code:: cpp

        iterator end();

        const_iterator end() const;

        const_iterator cend() const;

    **Returns**: an iterator to the element which follows the last element in the vector.

rbegin and crbegin
------------------

    .. code:: cpp

        reverse_iterator rbegin();

        const_reverse_iterator rbegin() const;

        const_reverse_iterator crbegin() const;

    **Returns**: a reverse iterator to the first element of the reversed vector.

rend and crend
--------------

    .. code:: cpp

        reverse_iterator rend();

        const_reverse_iterator rend() const;

        const_reverse_iterator crend() const;

    **Returns**: a reverse iterator which follows the last element of the reversed vector.
