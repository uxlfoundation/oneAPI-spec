.. SPDX-FileCopyrightText: 2019-2020 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

================
Deduction guides
================

Where possible, constructors of ``tbb::concurrent_priority_queue`` support class template argument
deduction (since C++17). Copy and move constructors (including constructors with explicit
``allocator_type`` argument) provides implicitly generated deduction guides. In addition, the following explicit
deduction guides are provided:

.. code:: cpp

    template <typename InputIterator,
              typename Compare = std::less<iterator_value_t<InputIterator>>,
              typename Allocator = tbb::cache_aligned_allocator<iterator_value_t<InputIterator>>>
    concurrent_priority_queue( InputIterator, InputIterator,
                               Compare = Compare(),
                               Allocator = Allocator() )
    -> concurrent_priority_queue<iterator_value_t<InputIterator>,
                                 Compare,
                                 Allocator>;

    template <typename InputIterator,
              typename Allocator>
    concurrent_priority_queue( InputIterator, InputIterator,
                               Allocator )
    -> concurrent_priority_queue<iterator_value_t<InputIterator>,
                                 std::less<iterator_value_t<InputIterator>>,
                                 Allocator>;

    template <typename T,
              typename Compare = std::less<T>,
              typename Allocator = tbb::cache_aligned_allocator<T>>
    concurrent_priority_queue( std::initializer_list<T>,
                               Compare = Compare(),
                               Allocator = Allocator() )
    -> concurrent_priority_queue<T,
                                 Compare,
                                 Allocator>;

    template <typename T,
              typename Allocator>
    concurrent_priority_queue( std::initializer_list<T>,
                               Allocator )
    -> concurrent_priority_queue<T,
                                 std::less<T>,
                                 Allocator>;

Where the type alias ``iterator_value_t`` is defined as follows:

.. code:: cpp

    template <typename InputIterator>
    using iterator_value_t = typename std::iterator_traits<InputIterator>::value_type;

These deduction guides only participates in overload resolution if all of the following are ``true``:

* The type ``InputIterator`` meets the requirements of  ``InputIterator`` from the [input.iterators] ISO C++ Standard section.
* The type ``Allocator`` meets the requirements of ``Allocator`` from the [allocator.requirements] ISO C++ Standard section.
* The type ``Compare`` does not meet the requirements of ``Allocator``.

**Example**

.. code:: cpp

    #include <tbb/concurrent_priority_queue.h>
    #include <vector>
    #include <functional>

    int main() {
        std::vector<int> vec;

        // Deduces cpq1 as tbb::concurrent_priority_queue<int>
        tbb::concurrent_priority_queue cpq1(vec.begin(), vec.end());

        // Deduces cpq2 as tbb::concurrent_priority_queue<int, std::greater>
        tbb::concurrent_priority_queue cpq2(vec.begin(), vec.end(), std::greater{});
    }
