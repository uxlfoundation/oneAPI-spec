======================================
Non-member lexicographical comparisons
======================================

.. code:: cpp

    template <typename Key, typename T, typename Compare, typename Allocator>
    bool operator<( const concurrent_multimap<Key, T, Compare, Allocator>& lhs,
                    const concurrent_multimap<Key, T, Compare, Allocator>& rhs )

**Returns**: ``true`` if ``lhs`` is lexicographicaly `less` than ``rhs``.

-----------------------------------------------------

.. code:: cpp

    template <typename Key, typename T, typename Compare, typename Allocator>
    bool operator<=( const concurrent_multimap<Key, T, Compare, Allocator>& lhs,
                     const concurrent_multimap<Key, T, Compare, Allocator>& rhs )

**Returns**: ``true`` if ``lhs`` is lexicographicaly `less or equal` than ``rhs``.

-----------------------------------------------------

.. code:: cpp

    template <typename Key, typename T, typename Compare, typename Allocator>
    bool operator>( const concurrent_multimap<Key, T, Compare, Allocator>& lhs,
                    const concurrent_multimap<Key, T, Compare, Allocator>& rhs )

**Returns**: ``true`` if ``lhs`` is lexicographicaly `greater` than ``rhs``.

-----------------------------------------------------

.. code:: cpp

    template <typename Key, typename T, typename Compare, typename Allocator>
    bool operator>=( const concurrent_multimap<Key, T, Compare, Allocator>& lhs,
                     const concurrent_multimap<Key, T, Compare, Allocator>& rhs )

**Returns**: ``true`` if ``lhs`` is lexicographicaly `greater or equal` than ``rhs``.
