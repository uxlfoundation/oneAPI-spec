.. SPDX-FileCopyrightText: 2019-2022 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

Parallel API
------------

oneDPL provides the set of parallel algorithms as defined by the `C++ Standard`_,
including parallel algorithms added in the 6th edition known as C++20.
All those algorithms work with *C++ Standard aligned execution policies* and with *DPC++
execution policies*.

Additionally, oneDPL provides wrapper functions for `SYCL`_ buffers, special iterators, and
a set of non-standard parallel algorithms.

C++ Standard aligned execution policies
+++++++++++++++++++++++++++++++++++++++

oneDPL has the set of execution policies and related utilities that are semantically aligned
with the `C++ Standard`_, 6th edition (C++20):

.. code:: cpp

  // Defined in <oneapi/dpl/execution>

  namespace oneapi {
    namespace dpl {
      namespace execution {

        class sequenced_policy { /*unspecified*/ };
        class parallel_policy { /*unspecified*/ };
        class parallel_unsequenced_policy { /*unspecified*/ };
        class unsequenced_policy { /*unspecified*/ };

        inline constexpr sequenced_policy seq { /*unspecified*/ };
        inline constexpr parallel_policy par { /*unspecified*/ };
        inline constexpr parallel_unsequenced_policy par_unseq { /*unspecified*/ };
        inline constexpr unsequenced_policy unseq { /*unspecified*/ };

        template <class T>
        struct is_execution_policy;

        template <class T>
        inline constexpr bool is_execution_policy_v = oneapi::dpl::execution::is_execution_policy<T>::value;
      }
    }
  }

See "Execution policies" in the `C++ Standard`_ for more information.

DPC++ Execution Policy
++++++++++++++++++++++

A DPC++ execution policy class :code:`oneapi::dpl::execution::device_policy` specifies
where and how an algorithm runs.

.. code:: cpp

  // Defined in <oneapi/dpl/execution>

  namespace oneapi {
    namespace dpl {
      namespace execution {

        template <typename KernelName = /*unspecified*/>
        class device_policy;

        device_policy<> dpcpp_default;

        template <typename KernelName = /*unspecified*/>
        device_policy<KernelName>
        make_device_policy( sycl::queue );

        template <typename KernelName = /*unspecified*/>
        device_policy<KernelName>
        make_device_policy( sycl::device );

        template <typename NewKernelName, typename OldKernelName>
        device_policy<NewKernelName>
        make_device_policy( const device_policy<OldKernelName>& = dpcpp_default );
      }
    }
  }

``dpcpp_default`` is a predefined execution policy object to run algorithms on the default DPC++ device.

device_policy class
^^^^^^^^^^^^^^^^^^^

.. code:: cpp

  template <typename KernelName = /*unspecified*/>
  class device_policy
  {
  public:
      using kernel_name = KernelName;

      device_policy();
      template <typename OtherName>
      device_policy( const device_policy<OtherName>& );
      explicit device_policy( sycl::queue );
      explicit device_policy( sycl::device );

      sycl::queue queue() const;
      operator sycl::queue() const;
  };

An object of the ``device_policy`` type is associated with a ``sycl::queue`` that is used
to run algorithms on a DPC++ compliant device. When an algorithm runs with ``device_policy``
it is capable of processing SYCL buffers (passed via :code:`oneapi::dpl::begin/end`),
data in the host memory and data in Unified Shared Memory (USM), including USM device memory.
Data placed in the host memory and USM can only be passed to oneDPL algorithms
as pointers and random access iterators. The way to transfer data from the host memory
to a device and back is unspecified; per-element data movement to/from a temporary storage
is a possible valid implementation.

The ``KernelName`` template parameter, also aliased as ``kernel_name`` within the class template,
is to explicitly provide a name for DPC++ kernels executed by an algorithm the policy is passed to.

.. code:: cpp

  device_policy()

Construct a policy object associated with a queue created with the default device selector.
  
.. code:: cpp

  template <typename OtherName>
  device_policy( const device_policy<OtherName>& policy )

Construct a policy object associated with the same queue as ``policy``, by changing
the kernel name of the given policy to ``kernel_name`` defined for the new policy.

.. code:: cpp

  explicit device_policy( sycl::queue queue )

Construct a policy object associated with the given queue.

.. code:: cpp

  explicit device_policy( sycl::device device )

Construct a policy object associated with a queue created for the given device.

.. code:: cpp

  sycl::queue queue() const

Return the queue the policy is associated with.

.. code:: cpp

  operator sycl::queue() const

Allow implicit conversion of the policy to a ``sycl::queue`` object.

make_device_policy function
^^^^^^^^^^^^^^^^^^^^^^^^^^^

The ``make_device_policy`` function templates simplify ``device_policy`` creation.

.. code:: cpp

  template <typename KernelName = /*unspecified*/>
  device_policy<KernelName>
  make_device_policy( sycl::queue queue )

Return a policy object associated with ``queue``, with a kernel name possibly provided
as the template argument, otherwise unspecified.

.. code:: cpp

  template <typename KernelName = /*unspecified*/>
  device_policy<KernelName>
  make_device_policy( sycl::device device )

Return a policy object to run algorithms on ``device``, with a kernel name possibly provided
as the template argument, otherwise unspecified.
  
.. code:: cpp

  template <typename NewKernelName, typename OldKernelName>
  device_policy<NewKernelName>
  make_device_policy( const device_policy<OldKernelName>& policy = dpcpp_default )

Return a policy object constructed from ``policy``, with a new kernel name provided as the template
argument. If no policy object is provided, the new policy is constructed from ``dpcpp_default``.

Buffer wrappers
+++++++++++++++

.. code:: cpp

  // Defined in <oneapi/dpl/iterator>

  namespace oneapi {
    namespace dpl {

      template < typename T, typename AllocatorT, typename TagT >
      /*unspecified*/ begin( sycl::buffer<T, /*dim=*/1, AllocatorT> buf,
                             TagT tag = sycl::read_write );

      template < typename T, typename AllocatorT, typename TagT >
      /*unspecified*/ begin( sycl::buffer<T, /*dim=*/1, AllocatorT> buf,
                             TagT tag, sycl::property::no_init );

      template < typename T, typename AllocatorT >
      /*unspecified*/ begin( sycl::buffer<T, /*dim=*/1, AllocatorT> buf,
                             sycl::property::no_init );


      template < typename T, typename AllocatorT, typename TagT >
      /*unspecified*/ end( sycl::buffer<T, /*dim=*/1, AllocatorT> buf,
                           TagT tag = sycl::read_write );

      template < typename T, typename AllocatorT, typename TagT >
      /*unspecified*/ end( sycl::buffer<T, /*dim=*/1, AllocatorT> buf,
                           TagT tag, sycl::property::no_init );

      template < typename T, typename AllocatorT >
      /*unspecified*/ end( sycl::buffer<T, /*dim=*/1, AllocatorT> buf,
                           sycl::property::no_init );

    }
  }

``oneapi::dpl::begin`` and ``oneapi::dpl::end`` are helper functions
for passing DPC++ buffers to oneDPL algorithms.
These functions accept a buffer and return an object
of an unspecified type that satisfies the following requirements:

- it is ``CopyConstructible``, ``CopyAssignable``, and comparable
  with operators ``==`` and ``!=``;
- the following expressions are valid: ``a + n``, ``a - n``,
  ``a - b``, where ``a`` and ``b`` are objects of the type,
  and ``n`` is an integer value;
- it provides the ``get_buffer()`` method that returns the buffer
  passed to the ``begin`` or ``end`` function.

When invoking an algorithm, the buffer passed to ``begin`` should be the same
as the buffer passed to ``end``. Otherwise, the behavior is undefined.

SYCL deduction tags (the ``TagT`` parameters) and ``sycl::property::no_init`` 
allow to specify an access mode to be used by algorithms for accessing the buffer.
The mode serves as a hint, and can be overridden depending on semantics of the algorithm.
When invoking an algorithm, the same access mode arguments should be used
for ``begin`` and ``end``. Otherwise, the behavior is undefined.

.. code:: cpp
      
      using namespace oneapi;
      auto buf_begin = dpl::begin(buf, sycl::write_only);
      auto buf_end_1 = dpl::end(buf, sycl::write_only);
      auto buf_end_2 = dpl::end(buf, sycl::write_only, sycl::no_init);
      dpl::fill(dpl::execution::dpcpp_default, buf_begin, buf_end_1, 42); // allowed
      dpl::fill(dpl::execution::dpcpp_default, buf_begin, buf_end_2, 42); // not allowed

Iterators
+++++++++

The oneDPL iterators are defined in the :code:`<oneapi/dpl/iterator>` header,
in :code:`namespace oneapi::dpl`.

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

:code:`counting_iterator` is a random access iterator-like type that represents an integer counter.
When dereferenced, :code:`counting_iterator` provides an Integral rvalue equal to the value of the
counter; dereference operations cannot be used to modify the counter. The arithmetic and comparison
operators of :code:`counting_iterator` behave as if applied to the values of Integral type
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

:code:`discard_iterator` is a random access iterator-like type that, when dereferenced, provides an
lvalue that may be assigned an arbitrary value. The assignment has no effect on the
:code:`discard_iterator` instance; the write is discarded. The arithmetic and comparison operators
of :code:`discard_iterator` behave as if applied to integer counter values maintained by the
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

:code:`permutation_iterator` is a random access iterator-like type whose dereferenced value set is
defined by the source iterator provided, and whose iteration order over the dereferenced value set
is defined by either another iterator or a functor that maps the :code:`permutation_iterator` index
to the index of the source iterator. The arithmetic and comparison operators of
:code:`permutation_iterator` behave as if applied to integer counter values maintained by the
iterator instances to determine their position in the index map.

:code:`permutation_iterator::operator*` uses the counter value of the instance on which
it is invoked to index into the index map. The corresponding value in the map is then used
to index into the value set defined by the source iterator. The resulting lvalue is returned
as the result of the operator.

:code:`permutation_iterator::operator[]` uses the parameter :code:`i` 
to index into the index map. The corresponding value in the map is then used
to index into the value set defined by the source iterator. The resulting lvalue is returned
as the result of the operator.

.. code:: cpp

    template <typename SourceIterator, typename IndexMap>
    permutation_iterator<SourceIterator, IndexMap>
    make_permutation_iterator(SourceIterator source, IndexMap map);

:code:`make_permutation_iterator` constructs and returns an instance of :code:`permutation_iterator`
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

:code:`transform_iterator` is a random access iterator-like type whose dereferenced value set is
defined by the unary function and source iterator provided. When dereferenced,
:code:`transform_iterator` provides the result of the unary function applied to the corresponding
element of the source iterator; dereference operations cannot be used to modify the elements of
the source iterator unless the unary function result includes a reference to the element. The
arithmetic and comparison operators of :code:`transform_iterator` behave as if applied to the
source iterator itself.

.. code:: cpp

    template <typename UnaryFunc, typename Iterator>
    transform_iterator<UnaryFunc, Iterator>
    make_transform_iterator(Iterator, UnaryFunc);

:code:`make_transform_iterator` constructs and returns an instance of :code:`transform_iterator`
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

:code:`zip_iterator` is an iterator-like type defined over one or more iterators. When dereferenced,
the value returned from :code:`zip_iterator` is a tuple of the values returned by dereferencing the
source iterators over which the :code:`zip_iterator` is defined.  The arithmetic operators of
:code:`zip_iterator` update the source iterators of a :code:`zip_iterator` instance as though the
operation were applied to each of these iterators.

.. code:: cpp

    template <typename... Iterators>
    zip_iterator<Iterators...>
    make_zip_iterator(Iterators...);

:code:`make_zip_iterator` constructs and returns an instance of :code:`zip_iterator`
using the set of source iterators provided.

Parallel Algorithms
+++++++++++++++++++

The parallel algorithms are defined in the :code:`<oneapi/dpl/algorithm>` header,
in :code:`namespace oneapi::dpl`.

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

:code:`oneapi::dpl::exclusive_scan_by_segment` performs partial prefix scans by applying the
:code:`binary_op` operation to a sequence of values. Each partial scan applies to a contiguous
subsequence determined by the keys associated with the values being equal according to the
:code:`binary_pred` predicate, and the first element of each scan is the initial value provided.
The return value is an iterator targeting the end of the result sequence.

The initial value used if one is not provided is an instance of the :code:`value_type` of the
:code:`InputValueIt` iterator type initialized to 0. If no binary predicate is provided for the
comparison of keys an instance of :code:`std::equal_to` with the :code:`value_type` of the
:code:`InputKeyIt` iterator type is used.  Finally, an instance of :code:`std::plus` with the
:code:`value_type` of the :code:`InputValueIt` iterator type is used if no binary operator is
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

:code:`oneapi::dpl::inclusive_scan_by_segment` performs partial prefix scans by applying the
:code:`binary_op` operation to a sequence of values. Each partial scan applies to a contiguous
subsequence determined by the keys associated with the values being equal according to the
:code:`binary_pred` predicate. The return value is an iterator targeting the end of the result
sequence.

If no binary predicate is provided for the comparison of keys an instance of :code:`std::equal_to`
with the :code:`value_type` of the :code:`InputKeyIt` iterator type is used.  An instance of
:code:`std::plus` with the :code:`value_type` of the :code:`InputValueIt` iterator type is used if
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

:code:`oneapi::dpl::reduce_by_segment` performs partial reductions on a sequence of values. Each
reduction is computed with the :code:`binary_op` operation for a contiguous subsequence of values
determined by the associated keys being equal according to the :code:`binary_pred` predicate.
For each subsequence the first of the equal keys is stored into :code:`keys_result` and the computed
reduction is stored into :code:`values_result`. The return value is a pair of
iterators holding the end of the resulting sequences.

If no binary predicate is provided for the comparison of keys an instance of :code:`std::equal_to`
with the :code:`value_type` of the :code:`InputKeyIt` iterator type is used. An instance of
:code:`std::plus` with the :code:`value_type` of the :code:`InputValueIt` iterator type is used to
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

:code:`oneapi::dpl::binary_search` performs a binary search over the data in :code:`[start, end)`
for each value in :code:`[value_first, value_last)`.  If the value exists in the data searched then
the corresponding element in :code:`[result, result + distance(value_first, value_last))` is set to
true, otherwise it is set to false.

If no comparator is provided, :code:`operator<` is used to determine when the search value is less
than an element in the range being searched.

The elements e of [start, end) must be partitioned with respect to the comparator used. For all
elements e in [start, end) and a given search value v in [value_first, value_last) comp(e, v) implies !comp(v, e).

.. code:: cpp

    template<typename Policy, typename InputIt1, typename InputIt2, typename OutputIt,
        typename Comparator =
            std::less<typename std::iterator_traits<InputIt>::value_type>>
    OutputIt
    lower_bound(Policy&& policy, InputIt1 start, InputIt1 end,
        InputIt2 value_first, InputIt2 value_last, OutputIterator result,
        Comparator comp =
            std::less<typename std::iterator_traits<InputIt1>::value_type>());

:code:`oneapi::dpl::lower_bound` performs a binary search over the data in :code:`[start, end)` for
each value in :code:`[value_first, value_last)` to find the lowest index at which the search value
could be inserted in :code:`[start, end)` without violating the ordering defined by the comparator
provided. That lowest index is then assigned to the corresponding element in
:code:`[result, result + distance(value_first, value_last))`.

If no comparator is provided, :code:`operator<` is used to determine when the search value is less
than an element in the range being searched.

The elements e of [start, end) must be partitioned with respect to the comparator used.

.. code:: cpp

    template<typename Policy, typename InputIt1, typename InputIt2, typename OutputIt,
        typename Comparator =
            std::less<typename std::iterator_traits<InputIt>::value_type>>
    OutputIt
    upper_bound(Policy&& policy, InputIt1 start, InputIt1 end,
        InputIt2 value_first, InputIt2 value_last, OutputIterator result,
        Comparator comp =
            std::less<typename std::iterator_traits<InputIt1>::value_type>());

:code:`oneapi::dpl::upper_bound` performs a binary search over the data in :code:`[start, end)`
for each value in :code:`[value_first, value_last)` to find the highest index at which the search
value could be inserted in :code:`[start, end)` without violating the ordering defined by the
comparator provided. That highest index is then assigned to the corresponding element in
:code:`[result, result + distance(value_first, value_last))`.

If no comparator is provided, :code:`operator<` is used to determine when the search value is less
than an element in the range being searched.

The elements e of [start, end) must be partitioned with respect to the comparator used.

.. _`C++ Standard`: https://isocpp.org/std/the-standard
.. _`SYCL`: https://registry.khronos.org/SYCL/specs/sycl-2020/html/sycl-2020.html
