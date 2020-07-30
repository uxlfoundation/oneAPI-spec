======================================
Non-member lexicographical comparisons
======================================

.. code:: cpp

    template <typename T, typename Allocator>
    bool operator<( const concurrent_vector<T, Allocator>& lhs,
                    const concurrent_vector<T, Allocator>& rhs );

**Returns**: ``true`` if ``lhs`` is lexicographicaly `less` than ``rhs``; ``false``, otherwise.

.. code:: cpp

    template <typename T, typename Allocator>
    bool operator<=( const concurrent_vector<T, Allocator>& lhs,
                     const concurrent_vector<T, Allocator>& rhs );

**Returns**: ``true`` if ``lhs`` is lexicographicaly `less or equal` than ``rhs``; ``false``, otherwise.

.. code:: cpp

    template <typename T, typename Allocator>
    bool operator>( const concurrent_vector<T, Allocator>& lhs,
                    const concurrent_vector<T, Allocator>& rhs );

**Returns**: ``true`` if ``lhs`` is lexicographicaly `greater` than ``rhs``; ``false``, otherwise.

.. code:: cpp

    template <typename T, typename Allocator>
    bool operator>=( const concurrent_vector<T, Allocator>& lhs,
                     const concurrent_vector<T, Allocator>& rhs );

**Returns**: ``true`` if ``lhs`` is lexicographicaly `greater or equal` than ``rhs``; ``false``, otherwise.
