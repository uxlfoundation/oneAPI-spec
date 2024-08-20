.. SPDX-FileCopyrightText: 2019-2022 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

Parallel API
------------

oneDPL provides the set of parallel algorithms as defined by the `C++ Standard`_,
including parallel algorithms added in the 6th edition known as C++20.
All those algorithms work with *C++ Standard aligned execution policies* and with
*device execution policies*.

Additionally, oneDPL provides wrapper functions for `SYCL`_ buffers, special iterators, and
a set of non-standard parallel algorithms.

.. toctree::

   parallel_api/execution_policies.rst
   parallel_api/buffer_wrappers.rst

Iterators
+++++++++

The oneDPL iterators are defined in the ``<oneapi/dpl/iterator>`` header,
in ``namespace oneapi::dpl``.

.. code:: cpp

    template <typename Integral>
    class counting_iterator
    {
      public:
        using difference_type = /* a signed integer type of the same size as Integral */;
        using value_type = Integral;
        using reference = Integral;

        counting_iterator();
        explicit counting_iterator(Integral init);

        reference operator*() const;
        reference operator[](difference_type i) const;

        difference_type operator-(const counting_iterator& it) const;

        counting_iterator operator+(difference_type forward) const;
        counting_iterator operator-(difference_type backward) const;

        counting_iterator& operator+=(difference_type forward);
        counting_iterator& operator-=(difference_type backward);

        counting_iterator& operator++();
        counting_iterator& operator--();
        counting_iterator& operator++(int);
        counting_iterator& operator--(int);

        bool operator==(const counting_iterator& it) const;
        bool operator!=(const counting_iterator& it) const;
        bool operator<(const counting_iterator& it) const;
        bool operator>(const counting_iterator& it) const;
        bool operator<=(const counting_iterator& it) const;
        bool operator>=(const counting_iterator& it) const;
    };

``counting_iterator`` is a random access iterator-like type that represents an integer counter.
When dereferenced, ``counting_iterator`` provides an Integral rvalue equal to the value of the
counter; dereference operations cannot be used to modify the counter. The arithmetic and comparison
operators of ``counting_iterator`` behave as if applied to the values of Integral type
representing the counters of the iterator instances passed to the operators.

.. code:: cpp

    class discard_iterator
    {
      public:
        using difference_type = std::ptrdiff_t;
        using value_type = /* unspecified */;
        using reference = /* unspecified */;

        discard_iterator();
        explicit discard_iterator(difference_type init);

        reference operator*() const;
        reference operator[](difference_type) const;

        difference_type operator-(const discard_iterator& it) const;

        discard_iterator operator+(difference_type forward) const;
        discard_iterator operator-(difference_type backward) const;

        discard_iterator& operator+=(difference_type forward);
        discard_iterator& operator-=(difference_type backward);

        discard_iterator& operator++();
        discard_iterator& operator--();
        discard_iterator operator++(int);
        discard_iterator operator--(int);

        bool operator==(const discard_iterator& it) const;
        bool operator!=(const discard_iterator& it) const;
        bool operator<(const discard_iterator& it) const;
        bool operator>(const discard_iterator& it) const;
    };

``discard_iterator`` is a random access iterator-like type that, when dereferenced, provides an
lvalue that may be assigned an arbitrary value. The assignment has no effect on the
``discard_iterator`` instance; the write is discarded. The arithmetic and comparison operators
of ``discard_iterator`` behave as if applied to integer counter values maintained by the
iterator instances to determine their position relative to each other.

.. code:: cpp

    template <typename SourceIterator, typename IndexMap>
    class permutation_iterator
    {
      public:
        using difference_type =
            typename std::iterator_traits<SourceIterator>::difference_type;
        using value_type = typename std::iterator_traits<SourceIterator>::value_type;
        using pointer = typename std::iterator_traits<SourceIterator>::pointer;
        using reference = typename std::iterator_traits<SourceIterator>::reference;

        permutation_iterator(const SourceIterator& input1, const IndexMap& input2,
                             std::size_t index = 0);

        SourceIterator base() const;

        reference operator*() const;
        reference operator[](difference_type i) const;

        difference_type operator-(const permutation_iterator& it) const;

        permutation_iterator operator+(difference_type forward) const;
        permutation_iterator operator-(difference_type backward) const;

        permutation_iterator& operator+=(difference_type forward);
        permutation_iterator& operator-=(difference_type forward);

        permutation_iterator& operator++();
        permutation_iterator& operator--();
        permutation_iterator operator++(int);
        permutation_iterator operator--(int);

        bool operator==(const permutation_iterator& it) const;
        bool operator!=(const permutation_iterator& it) const;
        bool operator<(const permutation_iterator& it) const;
        bool operator>(const permutation_iterator& it) const;
        bool operator<=(const permutation_iterator& it) const;
        bool operator>=(const permutation_iterator& it) const;
    };

``permutation_iterator`` is a random access iterator-like type whose dereferenced value set is
defined by the source iterator provided, and whose iteration order over the dereferenced value set
is defined by either another iterator or a functor that maps the ``permutation_iterator`` index
to the index of the source iterator. The arithmetic and comparison operators of
``permutation_iterator`` behave as if applied to integer counter values maintained by the
iterator instances to determine their position in the index map.

``permutation_iterator::operator*`` uses the counter value of the instance on which
it is invoked to index into the index map. The corresponding value in the map is then used
to index into the value set defined by the source iterator. The resulting lvalue is returned
as the result of the operator.

``permutation_iterator::operator[]`` uses the parameter ``i``
to index into the index map. The corresponding value in the map is then used
to index into the value set defined by the source iterator. The resulting lvalue is returned
as the result of the operator.

.. code:: cpp

    template <typename SourceIterator, typename IndexMap>
    permutation_iterator<SourceIterator, IndexMap>
    make_permutation_iterator(SourceIterator source, IndexMap map);

``make_permutation_iterator`` constructs and returns an instance of ``permutation_iterator``
using the source iterator and index map provided.

.. code:: cpp

    template <typename Iterator, typename UnaryFunc>
    class transform_iterator
    {
      public:
        using difference_type = typename std::iterator_traits<Iterator>::difference_type;
        using reference = typename std::invoke_result<UnaryFunc,
                              typename std::iterator_traits<Iterator>::reference>::type;
        using value_type = typename std::remove_reference<reference>::type;
        using pointer = typename std::iterator_traits<Iterator>::pointer;

        Iterator base() const;

        transform_iterator(Iterator it, UnaryFunc unary_func);
        transform_iterator(const transform_iterator& input);
        transform_iterator& operator=(const transform_iterator& input);

        reference operator*() const;
        reference operator[](difference_type i) const;

        difference_type operator-(const transform_iterator& it) const

        transform_iterator operator+(difference_type forward) const;
        transform_iterator operator-(difference_type backward) const;

        transform_iterator& operator+=(difference_type forward);
        transform_iterator& operator-=(difference_type backward);

        transform_iterator& operator++();
        transform_iterator& operator--();
        transform_iterator operator++(int);
        transform_iterator operator--(int);

        bool operator==(const transform_iterator& it) const;
        bool operator!=(const transform_iterator& it) const;
        bool operator<(const transform_iterator& it) const;
        bool operator>(const transform_iterator& it) const;
        bool operator<=(const transform_iterator& it) const;
        bool operator>=(const transform_iterator& it) const;
    };

``transform_iterator`` is a random access iterator-like type whose dereferenced value set is
defined by the unary function and source iterator provided. When dereferenced,
``transform_iterator`` provides the result of the unary function applied to the corresponding
element of the source iterator; dereference operations cannot be used to modify the elements of
the source iterator unless the unary function result includes a reference to the element. The
arithmetic and comparison operators of ``transform_iterator`` behave as if applied to the
source iterator itself.

.. code:: cpp

    template <typename UnaryFunc, typename Iterator>
    transform_iterator<UnaryFunc, Iterator>
    make_transform_iterator(Iterator, UnaryFunc);

``make_transform_iterator`` constructs and returns an instance of ``transform_iterator``
using the source iterator and unary function object provided.

.. code:: cpp

    template <typename... Iterators>
    class zip_iterator
    {
      public:
        using difference_type = typename std::make_signed<std::size_t>::type;
        using value_type =
            std::tuple<typename std::iterator_traits<Iterators>::value_type...>;
        using reference = /* unspecified tuple of reference types */;
        using pointer =
            std::tuple<typename std::iterator_traits<Iterators>::pointer...>;

        std::tuple<Iterators...> base() const;

        zip_iterator();
        explicit zip_iterator(Iterators... args);
        zip_iterator(const zip_iterator& input);
        zip_iterator& operator=(const zip_iterator& input);

        reference operator*() const;
        reference operator[](difference_type i) const;

        difference_type operator-(const zip_iterator& it) const;
        zip_iterator operator-(difference_type backward) const;
        zip_iterator operator+(difference_type forward) const;

        zip_iterator& operator+=(difference_type forward);
        zip_iterator& operator-=(difference_type backward);

        zip_iterator& operator++();
        zip_iterator& operator--();
        zip_iterator operator++(int);
        zip_iterator operator--(int);

        bool operator==(const zip_iterator& it) const;
        bool operator!=(const zip_iterator& it) const;
        bool operator<(const zip_iterator& it) const;
        bool operator>(const zip_iterator& it) const;
        bool operator<=(const zip_iterator& it) const;
        bool operator>=(const zip_iterator& it) const;
    };

``zip_iterator`` is an iterator-like type defined over one or more iterators. When dereferenced,
the value returned from ``zip_iterator`` is a tuple of the values returned by dereferencing the
source iterators over which the ``zip_iterator`` is defined. The arithmetic operators of
``zip_iterator`` update the source iterators of a ``zip_iterator`` instance as though the
operation were applied to each of these iterators.

.. code:: cpp

    template <typename... Iterators>
    zip_iterator<Iterators...>
    make_zip_iterator(Iterators...);

``make_zip_iterator`` constructs and returns an instance of ``zip_iterator``
using the set of source iterators provided.

Parallel Algorithms
+++++++++++++++++++

The parallel algorithms are defined in the ``<oneapi/dpl/algorithm>`` header,
in ``namespace oneapi::dpl``.

.. code:: cpp

    template<typename Policy, typename InputKeyIt, typename InputValueIt,
        typename OutputValueIt,
        typename T = typename std::iterator_traits<InputValueIt>::value_type,
        typename BinaryPred =
            std::equal_to<typename std::iterator_traits<InputKeyIt>::value_type>,
        typename BinaryOp =
            std::plus<typename std::iterator_traits<InputValueIt>::value_type>>
    OutputValueIt
    exclusive_scan_by_segment(Policy&& policy, InputKeyIt keys_first,
        InputKeyIt keys_last, InputValueIt values_first, OutputValueIt values_result,
        T initial_value = 0,
        BinaryPred binary_pred =
            std::equal_to<typename std::iterator_traits<InputKeyIt>::value_type>(),
        BinaryOp binary_op =
            std::plus<typename std::iterator_traits<InputValueIt>::value_type>());

``oneapi::dpl::exclusive_scan_by_segment`` performs partial prefix scans by applying the
``binary_op`` operation to a sequence of values. Each partial scan applies to a contiguous
subsequence determined by the keys associated with the values being equal according to the
``binary_pred`` predicate, and the first element of each scan is the initial value provided.
The return value is an iterator targeting the end of the result sequence.

The initial value used if one is not provided is an instance of the ``value_type`` of the
``InputValueIt`` iterator type initialized to 0. If no binary predicate is provided for the
comparison of keys an instance of ``std::equal_to`` with the ``value_type`` of the
``InputKeyIt`` iterator type is used. Finally, an instance of ``std::plus`` with the
``value_type`` of the ``InputValueIt`` iterator type is used if no binary operator is
provided to combine the elements of the value subsequences.

.. code:: cpp

    template<typename Policy, typename InputKeyIt, typename InputValueIt,
        typename OutputValueIt,
        typename BinaryPredcate =
            std::equal_to<typename std::iterator_traits<InputKeyIt>::value_type,
        typename BinaryOp =
            std::plus<typename std::iterator_traits<InputValueIt>::value_type>>
    OutputValueIt
    inclusive_scan_by_segment(Policy&& policy, InputKeyIt keys_first,
        InputKeyIt keys_last, InputValueIt values_first, OutputValueIt values_result
        BinaryPred binary_pred =
            std::equal_to<typename std::iterator_traits<InputKeyIt>::value_type>(),
        BinaryOp binary_op =
            std::plus<typename std::iterator_traits<InputValueIt>::value_type>());

``oneapi::dpl::inclusive_scan_by_segment`` performs partial prefix scans by applying the
``binary_op`` operation to a sequence of values. Each partial scan applies to a contiguous
subsequence determined by the keys associated with the values being equal according to the
``binary_pred`` predicate. The return value is an iterator targeting the end of the result
sequence.

If no binary predicate is provided for the comparison of keys an instance of ``std::equal_to``
with the ``value_type`` of the ``InputKeyIt`` iterator type is used. An instance of
``std::plus`` with the ``value_type`` of the ``InputValueIt`` iterator type is used if
no binary operator is provided to combine the elements of the value subsequences.

.. code:: cpp

    template<typename Policy, typename InputKeyIt, typename InputValueIt,
        typename OutputKeyIt, typename OutputValueIt,
        typename BinaryPredcate =
            std::equal_to<typename std::iterator_traits<InputKeyIt>::value_type,
        typename BinaryOp =
            std::plus<typename std::iterator_traits<InputValueIt>::value_type>>
    std::pair<OutputKeyIt,OutputValueIt>
    reduce_by_segment(Policy&& policy, InputKeyIt keys_first, InputKeyIt keys_last,
        InputValueIt values_first, OutputKeyIt keys_result,
        OutputValueIt values_result,
        BinaryPred binary_pred =
            std::equal_to<typename std::iterator_traits<InputKeyIt>::value_type>(),
        BinaryOp binary_op =
            std::plus<typename std::iterator_traits<InputValueIt>::value_type>());

``oneapi::dpl::reduce_by_segment`` performs partial reductions on a sequence of values. Each
reduction is computed with the ``binary_op`` operation for a contiguous subsequence of values
determined by the associated keys being equal according to the ``binary_pred`` predicate.
For each subsequence the first of the equal keys is stored into ``keys_result`` and the computed
reduction is stored into ``values_result``. The return value is a pair of
iterators holding the end of the resulting sequences.

If no binary predicate is provided for the comparison of keys an instance of ``std::equal_to``
with the ``value_type`` of the ``InputKeyIt`` iterator type is used. An instance of
``std::plus`` with the ``value_type`` of the ``InputValueIt`` iterator type is used to
combine the values in each subsequence identified if a binary operator is not provided.

.. code:: cpp

    template<typename Policy, typename InputIt1, typename InputIt2, typename OutputIt,
        typename Comparator =
            std::less<typename std::iterator_traits<InputIt>::value_type>>
    OutputIt
    binary_search(Policy&& policy, InputIt1 start, InputIt1 end,
        InputIt2 value_first, InputIt2 value_last, OutputIterator result,
        Comparator comp =
            std::less<typename std::iterator_traits<InputIt1>::value_type>());

``oneapi::dpl::binary_search`` performs a binary search over the data in ``[start, end)``
for each value in ``[value_first, value_last)``. If the value exists in the data searched then
the corresponding element in ``[result, result + distance(value_first, value_last))`` is set to
true, otherwise it is set to false.

If no comparator is provided, ``operator<`` is used to determine when the search value is less
than an element in the range being searched.

The elements of ``[start, end)`` must be partitioned with respect to the comparator used. For all
elements ``e`` in ``[start, end)`` and a given search value ``v`` in ``[value_first, value_last)``,
``comp(e, v)`` implies ``!comp(v, e)``.

.. code:: cpp

    template<typename Policy, typename InputIt1, typename InputIt2, typename OutputIt,
        typename Comparator =
            std::less<typename std::iterator_traits<InputIt>::value_type>>
    OutputIt
    lower_bound(Policy&& policy, InputIt1 start, InputIt1 end,
        InputIt2 value_first, InputIt2 value_last, OutputIterator result,
        Comparator comp =
            std::less<typename std::iterator_traits<InputIt1>::value_type>());

``oneapi::dpl::lower_bound`` performs a binary search over the data in ``[start, end)`` for
each value in ``[value_first, value_last)`` to find the lowest index at which the search value
could be inserted in ``[start, end)`` without violating the ordering defined by the comparator
provided. That lowest index is then assigned to the corresponding element in
``[result, result + distance(value_first, value_last))``.

If no comparator is provided, ``operator<`` is used to determine when the search value is less
than an element in the range being searched.

The elements of ``[start, end)`` must be partitioned with respect to the comparator used.

.. code:: cpp

    template<typename Policy, typename InputIt1, typename InputIt2, typename OutputIt,
        typename Comparator =
            std::less<typename std::iterator_traits<InputIt>::value_type>>
    OutputIt
    upper_bound(Policy&& policy, InputIt1 start, InputIt1 end,
        InputIt2 value_first, InputIt2 value_last, OutputIterator result,
        Comparator comp =
            std::less<typename std::iterator_traits<InputIt1>::value_type>());

``oneapi::dpl::upper_bound`` performs a binary search over the data in ``[start, end)``
for each value in ``[value_first, value_last)`` to find the highest index at which the search
value could be inserted in ``[start, end)`` without violating the ordering defined by the
comparator provided. That highest index is then assigned to the corresponding element in
``[result, result + distance(value_first, value_last))``.

If no comparator is provided, ``operator<`` is used to determine when the search value is less
than an element in the range being searched.

The elements of ``[start, end)`` must be partitioned with respect to the comparator used.

.. _`C++ Standard`: https://isocpp.org/std/the-standard
.. _`SYCL`: https://registry.khronos.org/SYCL/specs/sycl-2020/html/sycl-2020.html
