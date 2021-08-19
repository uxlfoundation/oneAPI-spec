.. SPDX-FileCopyrightText: 2019-2020 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

================
Deduction guides
================

Where possible, constructors of ``concurrent_multiset`` support class template argument
deduction (since C++17). Copy and move constructors (including constructors with explicit
``allocator_type`` argument) provides implicitly generated deduction guides. In addition, the following explicit
deduction guides are provided:

.. code:: cpp

    template <typename InputIterator,
              typename Compare = std::less<iterator_value_t<InputIterator>>,
              typename Allocator = tbb::tbb_allocator<iterator_value_t<InputIterator>>>
    concurrent_multiset( InputIterator, InputIterator,
                         Compare = Compare(),
                         Allocator = Allocator() )
    -> concurrent_multiset<iterator_value_t<InputIterator>,
                           Compare,
                           Allocator>;

    template <typename InputIterator,
              typename Allocator>
    concurrent_multiset( InputIterator, InputIterator,
                         Allocator )
    -> concurrent_multiset<iterator_value_t<InputIterator>,
                           std::less<iterator_value_t<InputIterator>>,
                           Allocator>;

    template <typename Key,
              typename Compare = std::less<Key>,
              typename Allocator = tbb::tbb_allocator<Key>>
    concurrent_multiset( std::initializer_list<Key>,
                         Compare = Compare(),
                         Allocator = Allocator() )
    -> concurrent_multiset<Key,
                           Compare,
                           Allocator>;

    template <typename Key,
              typename Allocator>
    concurrent_multiset( std::initializer_list<Key>,
                         Allocator )
    -> concurrent_multiset<Key,
                           std::less<Key>,
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

    #include <tbb/concurrent_set.h>
    #include <vector>

    int main() {
        std::vector<int> v;

        // Deduces cs1 as concurrent_multiset<int>
        tbb::concurrent_multiset cs1(v.begin(), v.end());

        // Deduces cs2 as concurrent_multiset<int>
        tbb::concurrent_multiset cs2({1, 2, 3});
    }
