===============
Non-member swap
===============

.. code:: cpp

    template <typename T, typename Compare, typename Allocator>
    void swap( concurrent_priority_queue<T, Compare, Allocator>& lhs,
               concurrent_priority_queue<T, Compare, Allocator>& rhs );

Equivalent to ``lhs.swap(rhs)``.
