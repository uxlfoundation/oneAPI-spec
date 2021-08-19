.. SPDX-FileCopyrightText: 2019-2020 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

================
Deduction guides
================

Where possible, constructors of ``tbb::concurrent_queue`` support class template argument
deduction (since C++17). Copy and move constructors (including constructors with explicit
``allocator_type`` argument) provides implicitly generated deduction guides. In addition, the following explicit
deduction guides are provided:

.. code:: cpp

    template <typename InputIterator,
              typename Allocator = tbb::cache_aligned_allocator<iterator_value_t<InputIterator>>
    concurrent_queue( InputIterator, InputIterator,
                      Allocator = Allocator() )
    -> concurrent_queue<iterator_value_t<InputIterator>,
                        Allocator>;

Where the type alias ``iterator_value_t`` is defined as follows:

.. code:: cpp

    template <typename InputIterator>
    using iterator_value_t = typename std::iterator_traits<InputIterator>::value_type;

These deduction guides only participates in overload resolution if all of the following are ``true``:

* The type ``InputIterator`` meets the requirements of  ``InputIterator`` from the [input.iterators] ISO C++ Standard section.
* The type ``Allocator`` meets the requirements of ``Allocator`` from the [allocator.requirements] ISO C++ Standard section.

**Example**

.. code:: cpp

    #include <tbb/concurrent_queue.h>
    #include <vector>
    #include <memory>

    int main() {
        std::vector<int> vec;

        // Deduces cq1 as tbb::concurrent_queue<int>
        tbb::concurrent_queue cq1(vec.begin(), vec.end());

        // Deduces cq2 as tbb::concurrent_queue<int, std::allocator<int>>
        tbb::concurrent_queue cq2(vec.begin(), vec.end(), std::allocator<int>{})
    }
