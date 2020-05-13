===============
Non-member swap
===============

.. code:: cpp

    template <typename T, typename Compare, typename Allocator>
    void swap( concurrent_multiset<T, Compare, Allocator>& lhs,
               concurrent_multiset<T, Compare, Allocator>& rhs );

Equivalent to ``lhs.swap(rhs)``.
