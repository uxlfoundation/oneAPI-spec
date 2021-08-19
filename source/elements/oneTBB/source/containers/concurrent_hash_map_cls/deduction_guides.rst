.. SPDX-FileCopyrightText: 2019-2020 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

================
Deduction guides
================

Where possible, constructors of ``concurrent_hash_map`` support
class template argument deduction (since C++17). Copy and move constructors (including constructors with explicit
``allocator_type`` argument) provides implicitly generated deduction guides. In addition, the following explicit
deduction guides are provided:

.. code:: cpp

    template <typename InputIterator,
              typename HashCompare = tbb_hash_compare<iterator_key_t<InputIterator>>,
              typename Alloc = tbb_allocator<iterator_alloc_value_t<InputIterator>>>
    concurrent_hash_map( InputIterator, InputIterator,
                         HashCompare = HashCompare(),
                         Alloc = Alloc() )
    -> concurrent_hash_map<iterator_key_t<InputIterator>,
                           iterator_mapped_t<InputIterator>,
                           HashCompare,
                           Alloc>;

    template <typename InputIterator,
              typename Alloc>
    concurrent_hash_map( InputIterator, InputIterator, Alloc )
    -> concurrent_hash_map<iterator_key_t<InputIterator>,
                           iterator_mapped_t<InputIterator>,
                           tbb_hash_compare<iterator_key_t<InputIterator>>,
                           Alloc>;

    template <typename Key, typename T,
              typename HashCompare = tbb_hash_compare<std::remove_const_t<Key>>,
              typename Alloc = tbb_allocator<std::pair<const Key, T>>>
    concurrent_hash_map( std::initializer_list<std::pair<Key, T>>,
                         HashCompare = HashCompare(),
                         Alloc = Alloc() )
    -> concurrent_hash_map<std::remove_const_t<Key>,
                           T,
                           HashCompare,
                           Alloc>;

    template <typename Key, typename T,
              typename Alloc>
    concurrent_hash_map( std::initializer_list<std::pair<Key, T>>,
                         Alloc )
    -> concurrent_hash_map<std::remove_const_t<Key>,
                           T,
                           tbb_hash_compare<std::remove_const_t<Key>>,
                           Alloc>;

Where the type aliases ``iterator_key_t``, ``iterator_mapped_t``, and ``iterator_alloc_value_t``
are defined as follows:

.. code:: cpp

    template <typename InputIterator>
    using iterator_key_t = std::remove_const_t<typename std::iterator_traits<InputIterator>::value_type::first_type>;

    template <typename InputIterator>
    using iterator_mapped_t = typename std::iterator_traits<InputIterator>::value_type::second_type;

    template <typename InputIterator>
    using iterator_alloc_value_t = std::pair<std::add_const_t<iterator_key_t<InputIterator>,
                                             iterator_mapped_t<InputIterator>>>;

These deduction guides only participates in overload resolution if all of the following are ``true``:

* The type ``InputIterator`` meets the requirements of  ``InputIterator`` from the [input.iterators] ISO C++ Standard section.
* The type ``Alloc`` meets the requirements of ``Allocator`` from the [allocator.requirements] ISO C++ Standard section.
* The type ``HashCompare`` does not meet the requirements of ``Allocator``.

**Example**

.. code:: cpp

    #include <tbb/concurrent_hash_map.h>
    #include <vector>

    int main() {
        std::vector<std::pair<const int, float>> v;

        // Deduces chmap1 as tbb::concurrent_hash_map<int, float>
        tbb::concurrent_hash_map chmap1(v.begin(), v.end());

        std::allocator<std::pair<const int, float>> alloc;
        // Deduces chmap2 as tbb::concurrent_hash_map<int, float,
        //                                            tbb_hash_compare<int>,
        //                                            std::allocator<std::pair<const int, float>>>
        tbb::concurrent_hash_map chmap2(v.begin(), v.end(), alloc);
    }
