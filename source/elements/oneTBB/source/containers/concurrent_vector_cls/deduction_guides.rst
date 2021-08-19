.. SPDX-FileCopyrightText: 2019-2020 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

================
Deduction guides
================

Where possible, constructors of ``concurrent_vector`` support
class template argument deduction (since C++17). Copy and move constructors (including constructors with explicit
``allocator_type`` argument) provides implicitly generated deduction guides. In addition, the following explicit
deduction guide is provided:

.. code:: cpp

    template <typename InputIterator,
              typename Allocator = tbb::cache_aligned_allocator<iterator_value_t<InputIterator>>>
    concurrent_vector( InputIterator, InputIterator,
                       Allocator = Allocator() )
    -> concurrent_vector<iterator_value_t<InputIterator>,
                         Allocator>;

Where type alias ``iterator_value_t`` defines as follows:

.. code:: cpp

    template <typename InputIterator>
    using iterator_value_t = typename std::iterator_traits<InputIterator>::value_type;

This deduction guide only participates in overload resolution if all of the following are ``true``:

* The type ``InputIterator`` meets the requirements of  ``InputIterator`` from the [input.iterators] ISO C++ Standard section.
* The type ``Allocator`` meets the requirements of ``Allocator`` from the [allocator.requirements] ISO C++ Standard section.

**Example**

.. code:: cpp

    #include <tbb/concurrent_vector.h>
    #include <array>
    #include <memory>

    int main() {
        std::array<int, 100> arr;

        // Deduces cv1 as tbb::concurrent_vector<int>
        tbb::concurrent_vector cv1(arr.begin(), arr.end());

        std::allocator<int> alloc;

        // Deduces cv2 as tbb::concurrent_vector<int, std::allocator<int>>
        tbb::concurrent_vector cv2(arr.begin(), arr.end(), alloc);
    }
