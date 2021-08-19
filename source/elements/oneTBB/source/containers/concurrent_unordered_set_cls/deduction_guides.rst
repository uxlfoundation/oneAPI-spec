.. SPDX-FileCopyrightText: 2019-2020 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

================
Deduction guides
================

Where possible, constructors of ``concurrent_unordered_set`` support
class template argument deduction (since C++17). Copy and move constructors (including constructors with explicit
``allocator_type`` argument) provides implicitly generated deduction guides. In addition, the following explicit
deduction guides are provided:

.. code:: cpp

    template <typename InputIterator,
              typename Hash = std::hash<iterator_value_t<InputIterator>>,
              typename KeyEqual = std::equal_to<iterator_value_t<InputIterator>>,
              typename Allocator = tbb::tbb_allocator<iterator_value_t<InputIterator>>>
    concurrent_unordered_set( InputIterator, InputIterator,
                              set_size_type = {},
                              Hash = Hash(),
                              KeyEqual = KeyEqual(),
                              Allocator = Allocator() )
    -> concurrent_unordered_set<iterator_value_t<InputIterator>,
                                Hash,
                                KeyEqual,
                                Allocator>;

    template <typename InputIterator,
              typename Allocator>
    concurrent_unordered_set( InputIterator, InputIterator,
                              set_size_type,
                              Allocator )
    -> concurrent_unordered_set<iterator_value_t<InputIterator>,
                                std::hash<iterator_value_t<InputIterator>>,
                                std::equal_to<iterator_value_t<InputIterator>>,
                                Allocator>;

    template <typename T,
              typename Hash = std::hash<T>,
              typename KeyEqual = std::equal_to<T>,
              typename Allocator = tbb::tbb_allocator<T>>
    concurrent_unordered_set( std::initializer_list<T>,
                              set_size_type = {},
                              Hash = Hash(),
                              KeyEqual = KeyEqual(),
                              Allocator = Allocator() )
    -> concurrent_unordered_set<T,
                                Hash,
                                KeyEqual,
                                Allocator>;

    template <typename T,
              typename Allocator>
    concurrent_unordered_set( std::initializer_list<T>,
                              set_size_type,
                              Allocator )
    -> concurrent_unordered_set<T,
                                std::hash<T>,
                                std::equal_to<T>,
                                Allocator>;

    template <typename T,
              typename Allocator>
    concurrent_unordered_set( std::initializer_list<T>,
                              Allocator )
    -> concurrent_unordered_set<T,
                                std::hash<T>,
                                std::equal_to<T>,
                                Allocator>;

    template <typename T,
              typename Hash,
              typename Allocator>
    concurrent_unordered_set( std::initializer_list<T>,
                              set_size_type,
                              Hash,
                              Allocator )
    -> concurrent_unordered_set<T,
                                Hash,
                                std::equal_to<T>,
                                Allocator>;

Where the type ``set_size_type`` refers to the ``size_type`` member type of the deduced ``concurrent_unordered_set``
and the type alias ``iterator_value_t`` is defined as follows:

.. code:: cpp

    template <typename InputIterator>
    using iterator_value_t = typename std::iterator_traits<InputIterator>::value_type;

These deduction guides only participates in overload resolution if all of the following are ``true``:

* The type ``InputIterator`` meets the requirements of  ``InputIterator`` from the [input.iterators] ISO C++ Standard section.
* The type ``Allocator`` meets the requirements of ``Allocator`` from the [allocator.requirements] ISO C++ Standard section.
* The type ``Hash`` does not meet the requirements of ``Allocator``.
* The type ``KeyEqual`` does not meet the requirements of ``Allocator``.

**Example**

.. code:: cpp

    #include <tbb/concurrent_unordered_set.h>
    #include <vector>
    #include <functional>

    struct CustomHasher {...};

    int main() {
        std::vector<int> v;

        // Deduces s1 as concurrent_unordered_set<int>
        tbb::concurrent_unordered_set s1(v.begin(), v.end());

        // Deduces s2 as concurrent_unordered_set<int, CustomHasher>;
        tbb::concurrent_unordered_set s2(v.begin(), v.end(), CustomHasher{});
    }
