===============
Non-member swap
===============

.. code:: cpp

    template <typename T, typename Hash,
              typename KeyEqual, typename Allocator>
    void swap( concurrent_unordered_multiset<T, Hash, KeyEqual, Allocator>& lhs,
               concurrent_unordered_multiset<T, Hash, KeyEqual, Allocator>& rhs ) noexcept(noexcept(lhs.swap(rhs)));

Equivalent to ``lhs.swap(rhs)``.
