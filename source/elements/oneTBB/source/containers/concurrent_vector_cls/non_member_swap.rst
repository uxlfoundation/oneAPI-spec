===============
Non-member swap
===============

.. code:: cpp

    template <typename T, typename Allocator>
    void swap( concurrent_vector<T, Allocator>& lhs,
               concurrent_vector<T, Allocator>& rhs );

Equivalent to ``lhs.swap(rhs)``.