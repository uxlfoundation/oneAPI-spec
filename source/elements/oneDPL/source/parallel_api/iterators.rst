.. SPDX-FileCopyrightText: 2019-2022 Intel Corporation
.. SPDX-FileCopyrightText: Contributors to the oneAPI Specification project.
..
.. SPDX-License-Identifier: CC-BY-4.0

.. _iterators:

Iterators
---------

Requirements For Iterator Use With Device Policies
++++++++++++++++++++++++++++++++++++++++++++++++++
Iterators are not assumed to refer to content that is accessible on the device by default. Without direct knowledge
that content is accessible on the device, oneDPL algorithms must copy the content to the device before being used inside
a `SYCL`_ kernel, and then back from the device afterward. We define the term "indirectly device accessible" to mean 
representing content that is accessible on the device within a SYCL kernel. "Indirectly device accessible iterators"
are iterators that can inherently be dereferenced on the device within a SYCL kernel.

Examples of "indirectly device accessible" iterators include SYCL USM shared or device memory, or iterator types like
``counting_iterator`` or ``discard_iterator`` that do not require any data to be copied to the device to be used in a
SYCL kernel. An example of an iterator type that is not "indirectly device accessible" is a ``std::vector`` iterator
with a host allocator, which requires the data to be copied to the device in some way before usage in a SYCL kernel
within algorithms used with a ``device_policy``.

:doc:`*buffer position objects* <buffer_wrappers>` returned by ``oneapi::dpl::begin`` and ``oneapi::dpl::end`` are not
iterators, but they are "indirectly device accessible" because they represent data that is accessible on the device.
When using oneDPL algorithms with a ``device_policy``, "indirectly device accessible" types avoid unnecessary data
movement when provided as input or output arguments.

"Indirectly device accessible iterators" must also be SYCL device-copyable to be used as input or output for oneDPL
algorithms using a ``device_policy``.

oneDPL Iterators
++++++++++++++++

The oneDPL iterators are defined in the ``<oneapi/dpl/iterator>`` header,
in ``namespace oneapi::dpl``.

Let us define a named requirement, ``AdaptingIteratorSource``, to describe valid random access iterator-like
types that can be used as source for oneDPL iterators as described below.
The type ``Iter`` satisfies the ``AdaptingIteratorSource`` named requirement if it is any of the following:

* A random access iterator
* The unspecified iterator-like type returned by ``oneapi::dpl::begin`` or ``oneapi::dpl::end``
* A ``permutation_iterator``
* A ``transform_iterator``
* A ``counting_iterator``
* A ``discard_iterator``
* A ``zip_iterator``

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

``counting_iterator`` is SYCL device-copyable, and is an "indirectly device accessible iterator".

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

``discard_iterator`` is SYCL device-copyable, and is an "indirectly device accessible iterator".

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
iterator instances to determine their position in the index map. ``SourceIterator`` must satisfy
``AdaptingIteratorSource``.

The type ``IndexMap`` must be one of the following:

* A random access iterator
* The unspecified iterator-like type returned by ``oneapi::dpl::begin`` or ``oneapi::dpl::end``
* A ``permutation_iterator``
* A ``transform_iterator``
* A ``counting_iterator``
* A functor with a signature equivalent to ``T operator()(const T&) const`` where ``T`` is a
  ``std::iterator_traits<SourceIterator>::difference_type``


``permutation_iterator::operator*`` uses the counter value of the instance on which
it is invoked to index into the index map. The corresponding value in the map is then used
to index into the value set defined by the source iterator. The resulting lvalue is returned
as the result of the operator.

``permutation_iterator::operator[]`` uses the parameter ``i``
to index into the index map. The corresponding value in the map is then used
to index into the value set defined by the source iterator. The resulting lvalue is returned
as the result of the operator.

``permutation_iterator`` is SYCL device-copyable if both the ``SourceIterator`` and the ``IndexMap``
are SYCL device-copyable. ``permutation_iterator`` is "indirectly device accessible" if both the
``SourceIterator`` and the ``IndexMap`` are "indirectly device accessible".

When using ``permutation_iterator`` in combination with an algorithm with a ``device_policy``, ``SourceIterator`` must
be "indirectly device accessible".

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
source iterator itself. The template type ``Iterator`` must satisfy
``AdaptingIteratorSource``.

``transform_iterator`` is SYCL device-copyable if the source iterator is SYCL device-copyable, and
is "indirectly device accessible iterator" if the source iterator is an "indirectly device accessible iterators".

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
operation were applied to each of these iterators. The types ``T`` within the template pack 
``Iterators...`` must satisfy ``AdaptingIteratorSource``.

``zip_iterator`` is SYCL device-copyable if all the source iterators are SYCL device-copyable, and is an "indirectly
device accessible iterator" if all the source iterators are "indirectly device accessible iterators".

.. code:: cpp

    template <typename... Iterators>
    zip_iterator<Iterators...>
    make_zip_iterator(Iterators...);

``make_zip_iterator`` constructs and returns an instance of ``zip_iterator``
using the set of source iterators provided.

Other Supported Iterators
+++++++++++++++++++++++++
``std::reverse_iterator<IteratorT>`` is an ``AdaptingIteratorSource`` if ``IteratorT`` is an ``AdaptingIteratorSource``.
``std::reverse_iterator<IteratorT>`` is an "indirectly device accessible iterator" if ``IteratorT`` is an "indirectly
device accessible iterator". The SYCL device-copyable requirement of ``std::reverse_iterator<IteratorT>`` for use in
algorithms with a ``device_policy`` relies upon the trivial copyability of ``IteratorT`` and the specific implementation
of ``std::reverse_iterator``. oneDPL does not specialize ``sycl::is_device_copyable`` for ``std::reverse_iterator``.

Pointers are assumed to be USM shared or device memory pointers and are "indirectly device accessible iterators".
Pointers are trivially copyable and therefore SYCL device-copyable.

.. _iterators-device-accessible:

Customization For User Defined Iterators
++++++++++++++++++++++++++++++++++++++++

oneDPL provides a mechanism to indicate whether custom iterators are "indirectly device accessible iterators" by
defining an Argument-Dependent Lookup (ADL) based customization point, ``is_onedpl_indirectly_device_accessible``.
oneDPL also defines a public trait, ``is_indirectly_device_accessible[_v]`` to indicate whether an iterator is an
"indirectly device accessible iterators".

oneDPL queries this information at compile time to determine how to handle input and output types when they are passed
to oneDPL algorithms with a ``device_policy`` to avoid unnecessary data movement.

ADL Customization Point: ``is_onedpl_indirectly_device_accessible``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

A free function ``is_onedpl_indirectly_device_accessible(T)`` may be defined, which accepts an argument of type ``T``
and returns a type with the base characteristic of ``std::true_type`` if ``T`` represents "indirectly device accessible"
content, or otherwise returns a type with the base characteristic of ``std::false_type``. The function must be
discoverable by ADL.

The function ``is_onedpl_indirectly_device_accessible`` may be used by oneDPL to determine if the type represents
"indirectly device accessible" content by interrogating its return type at compile-time only. Overloads may be provided
as forward declarations only, without a body defined. ADL is used to determine which function overload to use according
to the rules in the `C++ Standard`_. Therefore, derived iterator types without an overload for their exact type will
match their most specific base iterator type if such an overload exists.

Public Trait: ``oneapi::dpl::is_indirectly_device_accessible[_v]``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The following class template and variable template are defined in ``<oneapi/dpl/iterator>`` inside the namespace
``oneapi::dpl``:

.. code:: cpp

    template <typename T>
    struct is_indirectly_device_accessible{ /* see below */ };

    template <typename T>
    inline constexpr bool is_indirectly_device_accessible_v = is_indirectly_device_accessible<T>::value;

``template <typename T> oneapi::dpl::is_indirectly_device_accessible`` is a type which has the base characteristic
of ``std::true_type`` if ``T`` represents "indirectly device accessible" content, otherwise it has the base
characteristic of ``std::false_type``.

Example
^^^^^^^

The following example shows how to define a customization for `is_indirectly_device_accessible` trait for a simple
user defined iterator.  It also shows a more complicated example where the customization is defined as a hidden friend
of the iterator class.

.. code:: cpp

    namespace usr
    {
        struct accessible_it
        {
            /* unspecified user definition of a iterator which represents "indirectly device accessible" content*/
        };

        std::true_type
        is_onedpl_indirectly_device_accessible(accessible_it);

        struct inaccessible_it
        {
            /* unspecified user definition of iterator which doesn't represent "indirectly device accessible" content */
        };

        // This could be omitted. It would rely upon the default implementation with the same result
        std::false_type
        is_onedpl_indirectly_device_accessible(inaccessible_it);
    }

    static_assert(oneapi::dpl::is_indirectly_device_accessible<usr::accessible_it> == true);
    static_assert(oneapi::dpl::is_indirectly_device_accessible<usr::inaccessible_it> == false);

    // Example with base iterators and ADL overload as a hidden friend
    template <typename It1, typename It2>
    struct it_pair
    {
        It1 first;
        It2 second;
        friend auto is_onedpl_indirectly_device_accessible(it_pair) ->
            std::conjunction<oneapi::dpl::is_indirectly_device_accessible<It1>,
                             oneapi::dpl::is_indirectly_device_accessible<It2>>;
    };

    static_assert(oneapi::dpl::is_indirectly_device_accessible<it_pair<usr::accessible_it, usr::accessible_it>> == true);
    static_assert(oneapi::dpl::is_indirectly_device_accessible<it_pair<usr::accessible_it, usr::inaccessible_it>> == false);

.. _`C++ Standard`: https://isocpp.org/std/the-standard
.. _`SYCL`: https://registry.khronos.org/SYCL/specs/sycl-2020/html/sycl-2020.html
